
//$Header$
//------------------------------------------------------------------------------
//                             Line
//------------------------------------------------------------------------------
// FDTD Studio: Electromagnetic Analysis Tool.
//
// Author:
// Created:
//
/**
 *
 */
//------------------------------------------------------------------------------
#ifndef Line_h
#define Line_h

#include "emstudio/util/vector/Rvector3.h"

class Line {
public:
   Rvector3 P1;
   Rvector3 P2;

   Line();
   Line(Rvector3& v1, Rvector3& v2);
   Line(double X1, double Y1, double Z1, double X2, double Y2, double Z2);
   ~Line();

   double Length();
   bool Cross(int plane, Line& line);

   enum {
	   XY_PLANE = 0,
       YZ_PLANE,
       ZX_PLANE,
       LineParamCount
   };

};

#endif // Line_h
