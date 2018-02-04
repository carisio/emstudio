#ifndef TNT_IML_H
#define TNT_IML_H


namespace TNT { 
namespace Linear_Algebra { 

/**
	Diagonal preconditioner object is used in iterative methods to
	approximate the original matrix A in the equation by its diagonals.  It
	is one of the simplest preconditioners used in practice, and one of
	the eaisest to create.  (One needs only a list of the matrix diagonals.)

	<p>
	Example:

	<pre>
		double Vals1 = { .... };
		complex<double> Vals2 = { .... };
		double Vals3 = { ... };

		Matrix<double> A(N, N, Vals1);
		Sparse_Matrix< complex<double> > S(M, M, nz, I, J, Vals2);

		DiagonalPreconditioner<double>  D1 (A.diag());
		DiagonalPreconditioner<complex> D2(S.diag());
		DiagonalPreconditioner<double> D3(N, Vals3);

		x = D1(b);    (solve diag(A) * x = b )
  </pre>
	<p>
	This is a funciton object which is invoked using operator().  That is,
	its use appears like a function call, f(x), where x is a vector.
	Preconditioners are read-only objects --their contents cannot be modified. 
	If one of the diagonal elements of A is zero, then the results are undefined.
	(In some implementations, the reciprocals of the diagonals are kept to 
	avoid costly floating point divisions.  These may be created at time of
	object construction and result in floating point exceptions.

*/
template <class SCALAR>
class Diagonal_Preconditioner
{

	public:


	  /**
			Create a diagonal preconditioner from a C/C++ array of nonzero values.

			@param N the length of vector
			@param V the vector (C/C++ array) of values.
		*/
		Diagonal_Preconditioner(int N, const SCALAR *V) : one_over_diag_(N)
		{
			for (int i=0; i<N; i++)
				one_over_diag_[0] =  1.0/ V[0];
		}

		/**
			Create a diagonal preconditioner from a TNT Vector of nonzero values.
	
				@param V a vector of (nozero) diagonals.

		*/
		Diagonal_Preconditioner(const Vector<SCALAR> &V) : one_over_diag_(V.dim())
		{
			for (int i=0; i<V.dim(); i++)
				one_over_diag_[0] =  1.0/ V[0];
		}

		/**
			Apply diagonal preconditioner, i.e. solve for x in D*x = b.

			@param b	a vector of right-hand values (must be same size of D.)

			@return x the solution of D*x=b.

		*/
		Vector<SCALAR> operator()(const Vector<SCALAR> &b) const
		{
			int N = one_over_diag_.dim();
			Vector<SCALAR> x(N); 
			for (int i=0; i<N; i++)
				x[i]  = b[i] * one_over_diag_[i];

		  return x;
		}


	private:
		Vector<SCALAR> one_over_diag_;
};

/**
	Identity preconditioner solves the trivial equation I*x=b, where I is the identity matrix. It is
	used as a placeholder when using iterative methods without preconditioners.
	approximate the original matrix A in the equation by its diagonals.  It
	<p>
	This is a funciton object which is invoked using operator().  That is,
	its use appears like a function call, f(x), where x is a vector.

*/
template <class SCALAR>
class Identity_Preconditioner 
{

	public:


		Vector<SCALAR> operator()(const Vector<SCALAR> &b) const
		{
				return b;
		}
};

/**  
 	 Preconditioned Conjuate Gradient (CG) solves the symmetric positive 
	 definite linear system Ax=b using the Conjugate Gradient method.
   (See p. 15 of the SIAM Template book.)


		@param A 	(in) the matrix for which Ax=b is being solved.
		@param x  (in/out) on input, the initial solution for Ax=b; upon	
													return, the calculated value for the solution.
		@param b  (in)  the right hand side of the equation Ax=b.
		@param M  (in)  a function object that approximates the inverse of A.  Its
					use appears as M(y), to solve the system M*x = y.
		@param max_iter (in/out) on input, the maximum allowed number of
										iterations to perform, on return, the number of iterations
										actually performed.
		@param tol tolerance (in/out) in input, stop iteration when the scaled
							residual |(A*x-b)|/|b| is less than this number; on return, 
							actual value of this scaled residual after the final 
							iteration..
		@return 0 upon successful return, 1 if no convergence was achieved
				within max_iter iterations.
 */ 
template <class MATRIX, class VECTOR, class PRECONDITIONER, class REAL>
int PCG(const MATRIX &A, VECTOR &x, const VECTOR &b,
   const PRECONDITIONER &M, int &max_iter, REAL &tol)
{
  REAL residual;
  VECTOR p, z, q;
  typename VECTOR::value_type alpha, beta, rho, rho_old;

  REAL normb = norm(b);
  VECTOR r = b - A*x;

  if (normb == 0.0)
    normb = 1;

  if ((residual = norm(r) / normb) <= tol) 
	{
    tol = residual;
    max_iter = 0;
    return 0;
  }

  for (int i = 1; i <= max_iter; i++) 
	{
    z = M(r);
    rho = r * z;

    if (i == 1)
      p = z;
    else 
		{
      beta = rho / rho_old;
      p = z + beta * p;
    }

    q = A*p;
    alpha = rho / (p * q);

    x += alpha * p;
    r -= alpha * q;

		residual = norm(r)/ normb;
		//std::cout << "step["<< i << "], res = " << residual << "\n";
    if (residual <= tol) 
		{
      tol = residual;
      max_iter = i;
      return 0;
    }

    rho_old = rho;
  }

  tol = residual;
  return 1;
}




/**  
   PBiCG solves the unsymmetric linear system Ax = b
   using the Preconditioned BiConjugate Gradient method
   BiCG follows the algorithm described on p. 22 of the
   SIAM Templates book.

	 <p>
	 This algorithm requires a method for multiplying with A and the
	 transpose of A.

		@param A 	(in) the matrix for which Ax=b is being solved.
		@param x  (in/out) on input, the initial solution for Ax=b; upon	
													return, the calculated value for the solution.
		@param b  (in)  the right hand side of the equation Ax=b.
		@param M  (in)  a function object that approximates A.  Its
					use appears as M(y), to solve the system M*x = y.
		@param Mt  (in)  a function object that approximates the transpose of A.  
						Its use appears as Mt(y), to solve the system Mt*x = y.
		@param max_iter (in/out) on input, the maximum allowed number of
										iterations to perform, on return, the number of iterations
										actually performed.
		@param tol tolerance (in/out) in input, stop iteration when the scaled
							residual |(A*x-b)|/|b| is less than this number; on return, 
							actual value of this scaled residual after the final 
							iteration..
		@return 0 upon successful return, 1 if no convergence was achieved
				within max_iter iterations.
 */ 
template < class const_MATRIX, class VECTOR, class const_VECTOR, 
		class const_PRECONDITIONER, class const_TRANSPOSE_PRECONDITIONER,
class REAL >
int PBiCG(const_MATRIX &A, VECTOR &x, const_VECTOR &b,
     const_PRECONDITIONER &M,  const_TRANSPOSE_PRECONDITIONER &Mt, 
		 int &max_iter, REAL &tol)
{
  REAL resid;
  typename VECTOR::value_type rho, rho_old, alpha, beta;
  VECTOR z, ztilde, p, ptilde, q, qtilde;

  REAL normb = norm(b);
  VECTOR r = b - A * x;
  VECTOR rtilde = r;

  if (normb == 0.0)
    normb = 1;

  if ((resid = norm(r) / normb) <= tol) {
    tol = resid;
    max_iter = 0;
    return 0;
  }

  for (int i = 1; i <= max_iter; i++) {
    z = M(r);
    ztilde = Mt(rtilde);
    rho = dot_product(z, rtilde);
    if (rho == 0) {
      tol = norm(r) / normb;
      max_iter = i;
      return 2;
    }
    if (i == 1) {
      p = z;
      ptilde = ztilde;
    } else {
      beta = rho / rho_old;
      p = z + beta * p;
      ptilde = ztilde + beta * ptilde;
    }
    q = A * p;
    qtilde = transpose_mult(A, ptilde);
    alpha = rho / dot_product(ptilde, q);
    x += alpha * p;
    r -= alpha * q;
    rtilde -= alpha * qtilde;

    rho_old = rho;
    if ((resid = norm(r) / normb) < tol) {
      tol = resid;
      max_iter = i;
      return 0;
    }
  }

  tol = resid;
  return 1;
}

/**  
	 BiCGSTAB : Iterative Method for solving system of linear equations.

	 <p>
   PBiCG solves the unsymmetric linear system Ax = b
   using the Preconditioned BiConjugate Gradient Stabilized method. It
	 is a stabilized version of BiCG. This implementation follows the 
	 algorithm described on p. 27 of the SIAM Templates book.

	 <p>
	 This algorithm requires a method for multiplying with A and the
	 transpose of A.

		@param A 	(in) the matrix for which Ax=b is being solved.
		@param x  (in/out) on input, the initial solution for Ax=b; upon	
													return, the calculated value for the solution.
		@param b  (in)  the right hand side of the equation Ax=b.
		@param M  (in)  a function object that approximates A.  Its
					use appears as M(y), to solve the system M*x = y.
		@param max_iter (in/out) on input, the maximum allowed number of
										iterations to perform, on return, the number of iterations
										actually performed.
		@param tol tolerace (in/out) in input, stop iteration when the scaled
							residual |(A*x-b)|/|b| is less than this number; on return, 
							actual value of this scaled residual after the final 
							iteration..
		@return 0 upon successful return, 1 if no convergence was achieved
				within max_iter iterations.
 */ 
template < class const_MATRIX, class VECTOR, class const_VECTOR,
  class const_PRECONDITIONER, class REAL >
int BiCGSTAB(const_MATRIX &A, VECTOR &x, const_VECTOR &b,
         const_PRECONDITIONER &M, int &max_iter, REAL &tol)
{
  REAL resid;
  typename VECTOR::value_type  rho_1, rho_2, alpha, beta, omega;
  VECTOR p, phat, s, shat, t, v;

  REAL normb = norm(b);
  VECTOR r = b - A * x;
  VECTOR rtilde = r;

  if (normb == 0.0)
    normb = 1;

  if ((resid = norm(r) / normb) <= tol) {
    tol = resid;
    max_iter = 0;
    return 0;
  }

  for (int i = 1; i <= max_iter; i++) {
    rho_1 = dot_product(rtilde, r);
    if (rho_1 == 0) {
      tol = norm(r) / normb;
      return 2;
    }
    if (i == 1)
      p = r;
    else {
      beta = (rho_1/rho_2) * (alpha/omega);
      p = r + beta * (p - omega * v);
    }
    phat = M.solve(p);
    v = A * phat;
    alpha = rho_1 / dot_product(rtilde, v);
    s = r - alpha * v;
    if ((resid = norm(s)/normb) < tol) {
      x += alpha * phat;
      tol = resid;
      return 0;
    }
    shat = M.solve(s);
    t = A * shat;
    omega = dot_product(t,s) / dot_product(t,t);
    x += alpha * phat + omega * shat;
    r = s - omega * t;

    rho_2 = rho_1;
    if ((resid = norm(r) / normb) < tol) {
      tol = resid;
      max_iter = i;
      return 0;
    }
    if (omega == 0) {
      tol = norm(r) / normb;
      return 3;
    }
  }

  tol = resid;
  return 1;
}



/**  

   CGS solves the unsymmetric linear system Ax = b
   using the preconditioned Conjugate Gradient Squared method.
 
   <p>
   CGS follows the algorithm described on p. 26 of the
   SIAM Templates book.



		@param A 	(in) the matrix for which Ax=b is being solved.
		@param x  (in/out) on input, the initial solution for Ax=b; upon	
													return, the calculated value for the solution.
		@param b  (in)  the right hand side of the equation Ax=b.
		@param M  (in)  a function object that approximates A.  Its
					use appears as M(y), to solve the system M*x = y.
		@param max_iter (in/out) on input, the maximum allowed number of
										iterations to perform, on return, the number of iterations
										actually performed.
		@param tol tolerace (in/out) in input, stop iteration when the scaled
							residual |(A*x-b)|/|b| is less than this number; on return, 
							actual value of this scaled residual after the final 
							iteration..
		@return 0 upon successful return, 1 if no convergence was achieved
				within max_iter iterations.
 */ 
template < class const_MATRIX, class VECTOR, class const_VECTOR, 
			class const_PRECONDITIONER, class REAL >
int
CGS(const_MATRIX &A, VECTOR &x, const_VECTOR &b,
    const_PRECONDITIONER &M, int &max_iter, REAL &tol)
{
  REAL resid;
  typename VECTOR::value_type rho_1, rho_2, alpha, beta;
  VECTOR p, phat, q, qhat, vhat, u, uhat;

  REAL normb = norm(b);
  VECTOR r = b - A*x;
  VECTOR rtilde = r;

  if (normb == 0.0)
    normb = 1;

  if ((resid = norm(r) / normb) <= tol) {
    tol = resid;
    max_iter = 0;
    return 0;
  }

  for (int i = 1; i <= max_iter; i++) {
    rho_1 = dot_product(rtilde, r);
    if (rho_1 == 0) {
      tol = norm(r) / normb;
      return 2;
    }
    if (i == 1) {
      u = r;
      p = u;
    } else {
      beta = rho_1 / rho_2;
      u = r + beta * q;
      p = u + beta * (q + beta * p);
    }
    phat = M.solve(p);
    vhat = A*phat;
    alpha = rho_1 / dot_product(rtilde, vhat);
    q = u - alpha * vhat;
    uhat = M(u + q);
    x += alpha * uhat;
    qhat = A * uhat;
    r -= alpha * qhat;
    rho_2 = rho_1;
    if ((resid = norm(r) / normb) < tol) {
      tol = resid;
      max_iter = i;
      return 0;
    }
  }

  tol = resid;
  return 1;
}


/**  

  
   CHEBY solves the symmetric positive definite linear
   system Ax = b using the Preconditioned Chebyshev Method
	
	 <p>
   CHEBY follows the algorithm described on p. 30 of the
   SIAM Templates book.
  



		@param A 	(in) the matrix for which Ax=b is being solved.
		@param x  (in/out) on input, the initial solution for Ax=b; upon	
													return, the calculated value for the solution.
		@param b  (in)  the right hand side of the equation Ax=b.
		@param M  (in)  a function object that approximates A.  Its
					use appears as M(y), to solve the system M*x = y.
		@param max_iter (in/out) on input, the maximum allowed number of
										iterations to perform, on return, the number of iterations
										actually performed.
		@param tol tolerance (in/out) in input, stop iteration when the scaled
							residual |(A*x-b)|/|b| is less than this number; on return, 
							actual value of this scaled residual after the final 
							iteration..
		@param eigmin  minimum eigenvalue of A
		@param eigmax  maximum eigenvalue of A
		@return 0 upon successful return, 1 if no convergence was achieved
				within max_iter iterations.
 */ 
template < class const_MATRIX, class const_VECTOR, class VECTOR, 
				class const_PRECONDITIONER, class REAL, class SCALAR >
int
CHEBY(const_MATRIX &A, VECTOR &x, const_VECTOR &b,
      const_PRECONDITIONER &M, int &max_iter, REAL &tol,
      SCALAR eigmin, SCALAR eigmax)
{
  REAL resid;
  SCALAR alpha, beta, c, d;
  VECTOR p, q, z;

  REAL normb = norm(b);
  VECTOR r = b - A * x;

  if (normb == 0.0)
    normb = 1;

  if ((resid = norm(r) / normb) <= tol) {
    tol = resid;
    max_iter = 0;
    return 0;
  }

  c = (eigmax - eigmin) / 2.0;
  d = (eigmax + eigmin) / 2.0;

  for (int i = 1; i <= max_iter; i++) {
    z = M(r);                 // apply preconditioner

    if (i == 1) {
      p = z;
      alpha = 2.0 / d;
    } else {
      beta = c * alpha / 2.0;       // calculate new beta
      beta = beta * beta;
      alpha = 1.0 / (d - beta);     // calculate new alpha
      p = z + beta * p;             // update search direction
    }

    q = A * p;
    x += alpha * p;                 // update approximation vector
    r -= alpha * q;                 // compute residual

    if ((resid = norm(r) / normb) <= tol) {
      tol = resid;
      max_iter = i;
      return 0;                     // convergence
    }
  }

  tol = resid;
  return 1;                         // no convergence
}

template < class MATRIX, class VECTOR >
void
Update(VECTOR &x, int k, MATRIX &h, VECTOR &s, VECTOR v[])
{
  VECTOR y(s);

  // Backsolve:
  for (int i = k; i >= 0; i--) {
    y(i) /= h(i,i);
    for (int j = i - 1; j >= 0; j--)
      y(j) -= h(j,i) * y(i);
  }

  for (int j = 0; j <= k; j++)
    x += v[j] * y(j);
}


template < class REAL >
REAL
abs(REAL x)
{
  return (x > 0 ? x : -x);
}


/** 
   Iterative template routine -- GMRES
  
   GMRES solves the unsymmetric linear system Ax = b using the
   Generalized Minimum Residual method

	<p>
   GMRES follows the algorithm described on p. 20 of the
   SIAM Templates book.


		@param A 	(in) the matrix for which Ax=b is being solved.
		@param x  (in/out) on input, the initial solution for Ax=b; upon	
													return, the calculated value for the solution.
		@param b  (in)  the right hand side of the equation Ax=b.
		@param M  (in)  a function object that approximates A.  Its
					use appears as M(y), to solve the system M*x = y.

		@param H
		@param m
		@param max_iter (in/out) on input, the maximum allowed number of
										iterations to perform, on return, the number of iterations
										actually performed.
		@param tol tolerance (in/out) in input, stop iteration when the scaled
							residual |(A*x-b)|/|b| is less than this number; on return, 
							actual value of this scaled residual after the final 
							iteration..
		@return 0 upon successful return, 1 if no convergence was achieved
				within max_iter iterations.
  
  
   Upon successful return, output arguments have the following values:
  
 */ 
template < class Operator, class VECTOR, class PRECONDITIONER,
           class MATRIX, class REAL >
int
GMRES(const Operator &A, VECTOR &x, const VECTOR &b,
      const PRECONDITIONER &M, MATRIX &H, int &m, int &max_iter,
      REAL &tol)
{
  REAL resid;
  int i, j = 1, k;
  VECTOR s(m+1), cs(m+1), sn(m+1), w;

  REAL normb = norm(M(b));
  VECTOR r = M(b - A * x);
  REAL beta = norm(r);

  if (normb == 0.0)
    normb = 1;

  if ((resid = norm(r) / normb) <= tol) {
    tol = resid;
    max_iter = 0;
    return 0;
  }

  VECTOR *v = new VECTOR[m+1];

  while (j <= max_iter) {
    v[0] = r * (1.0 / beta);    // ??? r / beta
    s = 0.0;
    s = beta;

    for (i = 0; i < m && j <= max_iter; i++, j++) {
      w = M(A * v[i]);
      for (k = 0; k <= i; k++) {
        H(k, i) = dot_product(w, v[k]);
        w -= H(k, i) * v[k];
      }
      H(i+1, i) = norm(w);
      v[i+1] = w * (1.0 / H(i+1, i)); // ??? w / H(i+1, i)

      for (k = 0; k < i; k++)
        ApplyPlaneRotation(H(k,i), H(k+1,i), cs(k), sn(k));

      GeneratePlaneRotation(H(i,i), H(i+1,i), cs(i), sn(i));
      ApplyPlaneRotation(H(i,i), H(i+1,i), cs(i), sn(i));
      ApplyPlaneRotation(s(i), s(i+1), cs(i), sn(i));

      if ((resid = abs(s(i+1)) / normb) < tol) {
        Update(x, i, H, s, v);
        tol = resid;
        max_iter = j;
        delete [] v;
        return 0;
      }
    }
    Update(x, i - 1, H, s, v);
    r = M(b - A * x);
    beta = norm(r);
    if ((resid = beta / normb) < tol) {
      tol = resid;
      max_iter = j;
      delete [] v;
      return 0;
    }
  }

  tol = resid;
  delete [] v;
  return 1;
}


#include <math.h>


template<class REAL>
void GeneratePlaneRotation(REAL &dx, REAL &dy, REAL &cs, REAL &sn)
{
  if (dy == 0.0) {
    cs = 1.0;
    sn = 0.0;
  } else if (abs(dy) > abs(dx)) {
    REAL temp = dx / dy;
    sn = 1.0 / sqrt( 1.0 + temp*temp );
    cs = temp * sn;
  } else {
    REAL temp = dy / dx;
    cs = 1.0 / sqrt( 1.0 + temp*temp );
    sn = temp * cs;
  }
}


template<class REAL>
void ApplyPlaneRotation(REAL &dx, REAL &dy, REAL &cs, REAL &sn)
{
  REAL temp  =  cs * dx + sn * dy;
  dy = -sn * dx + cs * dy;
  dx = temp;
}

/**
 
	 Preconditioned Richardson Iteration (IR).
   IR solves the unsymmetric linear system Ax = b using
   Iterative Refinement (preconditioned Richardson iteration).

	 <p>

		@param A 	(in) the matrix for which Ax=b is being solved.
		@param x  (in/out) on input, the initial solution for Ax=b; upon	
													return, the calculated value for the solution.
		@param b  (in)  the right hand side of the equation Ax=b.
		@param M  (in)  a function object that approximates A.  Its
					use appears as M(y), to solve the system M*x = y.
		@param max_iter (in/out) on input, the maximum allowed number of
										iterations to perform, on return, the number of iterations
										actually performed.
		@param tol 	tolerance (in/out) in input, stop iteration when the scaled
							residual |(A*x-b)|/|b| is less than this number; on return, 
							actual value of this scaled residual after the final 
							iteration..
		@return 0 upon successful return, 1 if no convergence was achieved
				within max_iter iterations.

  
 */ 
template < class MATRIX, class VECTOR, class PRECONDITIONER, class REAL >
int
IR(const MATRIX &A, VECTOR &x, const VECTOR &b,
   const PRECONDITIONER &M, int &max_iter, REAL &tol)
{
  REAL resid;
  VECTOR z;

  REAL normb = norm(b);
  VECTOR r = b - A*x;

  if (normb == 0.0)
    normb = 1;

  if ((resid = norm(r) / normb) <= tol) {
    tol = resid;
    max_iter = 0;
    return 0;
  }

  for (int i = 1; i <= max_iter; i++) {
    z = M(r);
    x += z;
    r = b - A * x;

    if ((resid = norm(r) / normb) <= tol) {
      tol = resid;
      max_iter = i;
      return 0;
    }
  }

  tol = resid;
  return 1;
}


#include <math.h>

/** 
  
   QMR solves the unsymmetric linear system Ax = b using the
   Quasi-Minimal Residual method following the algorithm as described
   on p. 24 in the SIAM Templates book.
  
  


		@param A 	(in) the matrix for which Ax=b is being solved.
		@param x  (in/out) on input, the initial solution for Ax=b; upon	
													return, the calculated value for the solution.
		@param b  (in)  the right hand side of the equation Ax=b.
		@param M1  (in)  a function object that approximates A.  Its
					use appears as M(y), to solve the system M*x = y.
		@param M1t  (in)  a function object that approximates A.  Its
					use appears as M(y), to solve the system M*x = y.
		@param M2  (in)  a function object that approximates A.  Its
					use appears as M(y), to solve the system M*x = y.
		@param M2t  (in)  a function object that approximates A.  Its
					use appears as M(y), to solve the system M*x = y.
		@param max_iter (in/out) on input, the maximum allowed number of
										iterations to perform, on return, the number of iterations
										actually performed.
		@param tol tolerance (in/out) in input, stop iteration when the scaled
							residual |(A*x-b)|/|b| is less than this number; on return, 
							actual value of this scaled residual after the final 
							iteration..
		@return 0 upon successful return, 1 if no convergence reached after
				max_iter iterations, otherwise error codes
				are returned for breakdowns in the following algorithm parameters:
			<p>
			<center>
			<table border cellpadding=2 cellspacing=0>
			<tr>    <td> 0 : </td>  <td> successful return </td> </tr>
			<tr>    <td> 1 : </td>  <td> no convergence  </td> </tr>
			<tr>    <td> 2 : </td>  <td> rho <td>   </tr>
			<tr>    <td> 3 : </td>  <td> beta <td>   </tr>
			<tr>    <td> 4 : </td>  <td> gamma <td>   </tr>
			<tr>    <td> 5 : </td>  <td> delta <td>   </tr>
			<tr>    <td> 6 : </td>  <td> ep <td>   </tr>
			<tr>    <td> 7 : </td>  <td> xi <td>   </tr>
			</table>
			</center>
  
  
*/ 
template < class const_MATRIX, class const_VECTOR, class VECTOR, 
		class const_PRECONDITIONER1, class const_PRECONDITIONER1t,
		class const_PRECONDITIONER2, class const_PRECONDITIONER2t,
		class REAL >
int
QMR(const_MATRIX &A, VECTOR &x, const_VECTOR &b, 
		const_PRECONDITIONER1 &M1, const_PRECONDITIONER1t &M1t,
    const_PRECONDITIONER2 &M2, const_PRECONDITIONER2t &M2t,
		int &max_iter, REAL &tol)
{
  REAL resid;

  typename VECTOR::value_type rho, rho_1, xi, gamma;
  typename VECTOR::value_type gamma_1, theta, theta_1;
  typename VECTOR::value_type eta, delta, ep, beta;

  VECTOR r, v_tld, y, w_tld, z;
  VECTOR v, w, y_tld, z_tld;
  VECTOR p, q, p_tld, d, s;

  REAL normb = norm(b);

  r = b - A * x;

  if (normb == 0.0)
    normb = 1;

  if ((resid = norm(r) / normb) <= tol) {
    tol = resid;
    max_iter = 0;
    return 0;
  }

  v_tld = r;
  y = M1(v_tld);
  rho = norm(y);

  w_tld = r;
  z = M2(w_tld);
  xi = norm(z);

  gamma = 1.0;
  eta = -1.0;
  theta = 0.0;

  for (int i = 1; i <= max_iter; i++) {

    if (rho == 0.0)
      return 2;                        // return on breakdown

    if (xi == 0.0)
      return 7;                        // return on breakdown

    v = (1. / rho) * v_tld;
    y = (1. / rho) * y;

    w = (1. / xi) * w_tld;
    z = (1. / xi) * z;

    delta = dot_product(z, y);
    if (delta == 0.0)
      return 5;                        // return on breakdown

    y_tld = M2(y);               // apply preconditioners
    z_tld = M1t(z);

    if (i > 1) {
      p = y_tld - (xi * delta / ep) * p;
      q = z_tld - (rho * delta / ep) * q;
    } else {
      p = y_tld;
      q = z_tld;
    }

    p_tld = A * p;
    ep = dot_product(q, p_tld);
    if (ep == 0.0)
      return 6;                        // return on breakdown

    beta = ep / delta;
    if (beta == 0.0)
      return 3;                        // return on breakdown

    v_tld = p_tld - beta * v;
    y = M1.solve(v_tld);

    rho_1 = rho;
    rho = norm(y);
    w_tld = transpose_mult(A,q) - beta * w;
    z = M2t(w_tld);

    xi = norm(z);

    gamma_1 = gamma;
    theta_1 = theta;

    theta = rho / (gamma_1 * beta);
    gamma = 1.0 / sqrt(1.0 + theta * theta);

    if (gamma == 0.0)
      return 4;                        // return on breakdown

    eta = -eta * rho_1 * gamma * gamma /
      (beta * gamma_1 * gamma_1);

    if (i > 1) {
      d = eta * p + (theta_1 * theta_1 * gamma * gamma) * d;
      s = eta * p_tld + (theta_1 * theta_1 * gamma * gamma) * s;
    } else {
      d = eta * p;
      s = eta * p_tld;
    }

    x += d;                            // update approximation vector
    r -= s;                            // compute residual

    if ((resid = norm(r) / normb) <= tol) {
      tol = resid;
      max_iter = i;
      return 0;
    }
  }

  tol = resid;
  return 1;                            // no convergence
}

}  	/* namespace TNT::Linear_Algebra */
}		/* namespace TNT */

#endif 
//  TNT_IML_H
