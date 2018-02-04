//$Header$
//------------------------------------------------------------------------------
//                             Rvector3
//------------------------------------------------------------------------------
// FDTD Studio: Electromagnetic Analysis Tool.
//
// Author: 
// Created: 
//
/**
 * Declares Rvector3.
 */
//------------------------------------------------------------------------------
#ifndef Rvector3_h
#define Rvector3_h

#include <cmath>

class Rvector3
{

public:		// User declarations
   double X;
   double Y;
   double Z;
   Rvector3();
   Rvector3(Rvector3 *v1);
   Rvector3(double vX, double vY, double vZ);
   virtual ~Rvector3();
   bool operator==(const Rvector3 &v1)const;
   bool operator!=(const Rvector3 &v1)const;
   Rvector3& operator=(Rvector3 v1);
   Rvector3& operator=(int v1);
   Rvector3 operator*(double v1) const;
   double Length();
   void Move(double dx, double dy, double dz);
   void Rotate(Rvector3 Orig, double Rx, double Ry, double Rz);
   void Rotate(Rvector3 Orig, double *q);
   void Normalize();
};

inline Rvector3 CrossProduct(Rvector3 v1, Rvector3 v2) {
	Rvector3 result;

	result.X = v1.Y*v2.Z - v1.Z*v2.Y;
	result.Y = v1.Z*v2.X - v1.X*v2.Z;
	result.Z = v1.X*v2.Y - v1.Y*v2.X;

	result.Normalize();

	return result;
}

inline double DotProduct(Rvector3 v1, Rvector3 v2) {
	double result;

	result = v1.X*v2.X + v1.Y*v2.Y + v1.Z*v2.Z;

	return result;
}
#endif
