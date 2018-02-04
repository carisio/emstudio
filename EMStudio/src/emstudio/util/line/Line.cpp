
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
#include "Line.h"
#include <cmath>

Line::Line(Rvector3& v1, Rvector3& v2){
	P1 = v1;
    P2 = v2;
}

Line::Line(double X1, double Y1, double Z1, double X2, double Y2, double Z2) {
   P1.X = X1;
   P1.Y = Y1;
   P1.Z = Z1;
   P2.X = X2;
   P2.Y = Y2;
   P2.Z = Z2;
}

Line::Line() {
   P1.X = 0;
   P1.Y = 0;
   P1.Z = 0;
   P2.X = 1;
   P2.Y = 1;
   P2.Z = 1;

}

Line::~Line() {

}

double Line::Length() {
   return sqrt((P1.X-P2.X)*(P1.X-P2.X) + (P1.Y-P2.Y)*(P1.Y-P2.Y) + (P1.Z-P2.Z)*(P1.Z-P2.Z));
}

//---------------------------------------------------------------------------
#include <iostream>
bool Line::Cross(int Plane, Line& line)
{
   double CrossPoint;

   // Verifica se determinada linha cruza outra linha no mesmo plano
   //
   // As linhas devem estar contidas no mesmo plano
   //
   // Para o plano XY a linha deve ter Z1=Z2
   // Para o plano YZ a linha deve ter X1=X2
   // Para o plano ZX a linha deve ter Y1=Y2
   //
   switch (Plane)
   {
	   case XY_PLANE:
		   if (line.P1.Z != P1.Z) {
//			   std::cout << "Não coincide " << std::endl;
			   return false;
		   }

           // Se um dos vértices coincide com o raio, desloca ligeiramente
           if (line.P1.Y == P1.Y)
               P1.Y += 1e-15;
           if (line.P1.Y == P2.Y)
               P2.Y += 1e-15;

//           std::cout << "line.P1.X = "  << line.P1.X << std::endl;
//           std::cout << "line.P1.Y = "  << line.P1.Y << std::endl;
//           std::cout << "line.P2.X = "  << line.P2.X << std::endl;
//           std::cout << "line.P2.Y = "  << line.P2.Y << std::endl;
//           std::cout << "P1.X = "  << P1.X << std::endl;
//           std::cout << "P1.Y = "  << P1.Y << std::endl;
//           std::cout << "P2.X = "  << P2.X << std::endl;
//           std::cout << "P2.Y = "  << P2.Y << std::endl;
           if (((line.P1.Y > P1.Y) && (line.P1.Y < P2.Y)) ||
               ((line.P1.Y > P2.Y) && (line.P1.Y < P1.Y)))
           {
			   CrossPoint = P1.X + (line.P2.Y-P1.Y)*(P2.X-P1.X)/(P2.Y-P1.Y);
//			   std::cout << "CrossPoint = " << CrossPoint << std::endl;
//			   std::cout << "(CrossPoint <= line.P2.X) && (CrossPoint >= line.P1.X) = " << ((CrossPoint <= line.P2.X) && (CrossPoint >= line.P1.X)) << std::endl;
               if ((CrossPoint <= line.P2.X) &&
                   (CrossPoint >= line.P1.X))
				    return true;
               else
                   return false;
            }
            else
				return false;

 	   case YZ_PLANE:

		    if (line.P1.X != P1.X)
				return false;

			// Se um dos vértices coincide com o raio, desloca ligeiramente
			if (line.P1.Z==P1.Z)
				P1.Z += 1e-15;
			if (line.P1.Z==P2.Z)
			    P2.Z += 1e-15;

			if (((line.P1.Z > P1.Z) && (line.P1.Z < P2.Z)) ||
				((line.P1.Z > P2.Z) && (line.P1.Z < P1.Z)))
			{
				CrossPoint = P1.Y + (line.P2.Z-P1.Z)*(P2.Y-P1.Y)/(P2.Z-P1.Z);
				if ((CrossPoint <= line.P2.Y) &&
					(CrossPoint >= line.P1.Y))
					return true;
				else
					return false;
			}
			else
				return false;

	   case ZX_PLANE:

			// Se um dos vértices coincide com o raio, desloca ligeiramente
			if (line.P1.X == P1.X)
				P1.X += 1e-15;
			if (line.P1.X==P2.X)
			    P2.X += 1e-15;

			if (((line.P1.X > P1.X) && (line.P1.X < P2.X)) ||
				((line.P1.X > P2.X) && (line.P1.X < P1.X)))
			{
				CrossPoint = P1.Z + (line.P2.X-P1.X)*(P2.Z-P1.Z)/(P2.X-P1.X);
				if ((CrossPoint <= line.P2.Z) &&
				    (CrossPoint >= line.P1.Z))
					return true;
				else
					return false;
			}
			else
				return false;
   }
   return true;
}
//---------------------------------------------------------------------------

