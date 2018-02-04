//$Header$
//------------------------------------------------------------------------------
//                                Rvector3
//------------------------------------------------------------------------------
// FDTD Studio: Electromagnetic Analysis Tool
//
// Author: 
// Created: 
//
/**
 * Provides definitions for the Rvector3 class, providing linear algebra
 * operations for the 3-element double vector.
 */
//------------------------------------------------------------------------------
#include "Rvector3.h"

//---------------------------------------------------------------------------
Rvector3::Rvector3() {
   X = 0;
   Y = 0;
   Z = 0;
}

//---------------------------------------------------------------------------
Rvector3::Rvector3(Rvector3 *v1) {
  X = v1->X;
  Y = v1->Y;
  Z = v1->Z;
}

//---------------------------------------------------------------------------
Rvector3::Rvector3(double vX, double vY, double vZ) {
  X = vX;
  Y = vY;
  Z = vZ;
}

//------------------------------------------------------------------------------
//  ~Rvector3()
//------------------------------------------------------------------------------
Rvector3::~Rvector3() {
}


//------------------------------------------------------------------------------
//  bool operator==(const Rvector3 &v1) const
//------------------------------------------------------------------------------
bool Rvector3::operator==(const Rvector3 &v1) const {
   if(v1.X == X && v1.Y == Y && v1.Z == Z)
	   return true;
   else
       return false;
}


//------------------------------------------------------------------------------
//  bool operator!=(const Rvector3 &v1) const
//------------------------------------------------------------------------------
bool Rvector3::operator!=(const Rvector3 &v1) const {
   return !(operator==(v1));
}

//------------------------------------------------------------------------------
//  Rvector3& operator=(const Rvector3 &v)
//------------------------------------------------------------------------------
Rvector3& Rvector3::operator=(const Rvector3 v1) {
   if ( this == &v1) return *this;
   X = v1.X;
   Y = v1.Y;
   Z = v1.Z;
   return *this;
}

//---------------------------------------------------------------------------
Rvector3& Rvector3::operator =(int v1) {
   X = v1;
   Y = v1;
   Z = v1;
   return *this;
}

//------------------------------------------------------------------------------
//  Rvector3 operator*(double s) const
//------------------------------------------------------------------------------
Rvector3 Rvector3::operator*(double v1) const {
   return Rvector3(X*v1, Y*v1, Z*v1);
}

double Rvector3::Length() {
	return sqrt(X*X + Y*Y + Z*Z);
}
//---------------------------------------------------------------------------
void Rvector3::Move(double dx, double dy, double dz) {
   X += dx;
   Y += dy;
   Z += dz;
}


//---------------------------------------------------------------------------
/*
 * Observação: O método não funciona se for chamado com Rx, Ry e Rz != 0
 * Deve ser chamado apenas para uma direção, depois para a outra e por fim para a última.
 * Obviamente, a ordem em que é feita a rotação altera o resultado
 */
void Rvector3::Rotate(Rvector3 Orig, double Rx, double Ry, double Rz) {
   double Xt,Yt,Zt;

   Xt = X-Orig.X;
   Yt = Y-Orig.Y;
   Zt = Z-Orig.Z;

   //Rotacao em X
   if (Rx != 0)
   {
      Y = Yt*cos(Rx)-Zt*sin(Rx)+Orig.Y;
      Z = Yt*sin(Rx)+Zt*cos(Rx)+Orig.Z;

      /* Recalcula */
      Xt = X-Orig.X;
      Yt = Y-Orig.Y;
      Zt = Z-Orig.Z;
   }
   //Rotacao em Y
   if (Ry != 0)
   {
      X =  Xt*cos(Ry)+Zt*sin(Ry)+Orig.X;
      Z = -Xt*sin(Ry)+Zt*cos(Ry)+Orig.Z;

      /* Recalcula */
      Xt = X-Orig.X;
      Yt = Y-Orig.Y;
      Zt = Z-Orig.Z;
   }
   //Rotacao em Z
   if (Rz != 0)
   {
      X = Xt*cos(Rz)-Yt*sin(Rz)+Orig.X;
      Y = Xt*sin(Rz)+Yt*cos(Rz)+Orig.Y;

      /* Recalcula */
      Xt = X-Orig.X;
      Yt = Y-Orig.Y;
      Zt = Z-Orig.Z;
   }

}

//---------------------------------------------------------------------------
void Rvector3::Rotate(Rvector3 Orig, double *q) {

	Rvector3 T;

	T.X = X-Orig.X;
	T.Y = Y-Orig.Y;
	T.Z = Z-Orig.Z;

	Rvector3 R;
	R.X = q[3]*q[3]*T.X + 2*q[1]*q[3]*T.Z - 2*q[2]*q[3]*T.Y + 
		q[0]*q[0]*T.X + 2*q[1]*q[0]*T.Y + 2*q[2]*q[0]*T.Z - q[2]*q[2]*T.X - q[1]*q[1]*T.X;
	R.Y = 2*q[0]*q[1]*T.X + q[1]*q[1]*T.Y + 2*q[2]*q[1]*T.Z + 
		2*q[3]*q[2]*T.X - q[2]*q[2]*T.Y + q[3]*q[3]*T.Y - 2*q[0]*q[3]*T.Z - q[0]*q[0]*T.Y;
	R.Z = 2*q[0]*q[2]*T.X + 2*q[1]*q[2]*T.Y + q[2]*q[2]*T.Z - 
		2*q[3]*q[1]*T.X - q[1]*q[1]*T.Z + 2*q[3]*q[0]*T.Y - q[0]*q[0]*T.Z + q[3]*q[3]*T.Z;
	X = R.X+Orig.X;
	Y = R.Y+Orig.Y;
	Z = R.Z+Orig.Z;
}
//---------------------------------------------------------------------------
void Rvector3::Normalize() {
    // calculate the length of the vector
    float len = (float)(sqrt((X * X) + (Y * Y) + (Z * Z)));

    // avoid division by 0
    if (len == 0.0f)
        len = 1.0f;

    // reduce to unit size
    X /= len;
    Y /= len;
    Z /= len;
}

