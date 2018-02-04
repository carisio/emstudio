/*
 * Facet.cpp
 *
 *  Created on: 23/04/2012
 *      Author: leandrocarisio
 */

#include "Facet.h"
#include "emstudio/util/constants/Constants.h"
#include <iostream>

using namespace::std;

Facet::Facet()
	: BoundMax(-1e30, -1e30, -1e30),
	  BoundMin(+1e30, +1e30, +1e30) {
}

Facet::~Facet() {
}

Rvector3 Facet::GetBoundMax() {
	return BoundMax;
}
Rvector3 Facet::GetBoundMin() {
	return BoundMin;
}
void Facet::MultiplyVertex(double scale) {
	for (size_t i = 0; i < face.size(); i++) {
		face[i] = face[i] * scale;
	}
	BoundMin = BoundMin * scale;
	BoundMax = BoundMax * scale;
	Normal = Normal * scale;
}
vector<Rvector3> Facet::GetVertex() {
	return face;
}
void Facet::Add(Rvector3 v) {
	face.push_back(v);

	if (BoundMax.X < v.X)
		BoundMax.X = v.X;
	if (BoundMax.Y < v.Y)
	    BoundMax.Y = v.Y;
	if (BoundMax.Z < v.Z)
	    BoundMax.Z = v.Z;
	if (BoundMin.X > v.X)
	    BoundMin.X = v.X;
	if (BoundMin.Y > v.Y)
	    BoundMin.Y = v.Y;
	if (BoundMin.Z > v.Z)
	    BoundMin.Z = v.Z;
	if (face.size() == 3)
		BuildNormal();

}

void Facet::BuildNormal() {
	Rvector3 a, b;
	Rvector3 v0, v1, v2;

	v0 = face.at(0);
	v1 = face.at(1);
	v2 = face.at(2);

	// calculate the vectors A and B
	// note that v[3] is defined with counterclockwise winding in mind
	// a
	a.X = v0.X - v1.X;
	a.Y = v0.Y - v1.Y;
	a.Z = v0.Z - v1.Z;
	// b
	b.X = v1.X - v2.X;
	b.Y = v1.Y - v2.Y;
	b.Z = v1.Z - v2.Z;

	// calculate the cross product and place the resulting vector
	// into the address specified by vertex_t *normal
	Normal.X = (a.Y * b.Z) - (a.Z * b.Y);
	Normal.Y = (a.Z * b.X) - (a.X * b.Z);
	Normal.Z = (a.X * b.Y) - (a.Y * b.X);

	// normalize
	Normal.Normalize();
}

bool Facet::IsFaceCrossXYPlaneAt(double z) {
	return ((BoundMin.Z <= z) &&
		   (BoundMax.Z >= z) &&
		   (BoundMin.Z != BoundMax.Z));
}

void Facet::GetCrossLineXYPlane(double z, Rvector3& v1, Rvector3& v2) {
	Rvector3 vcross[2];
	Rvector3 vertex1;
	Rvector3 vertex2;
	double xx, yy;

	int v = 0;

	int nVertex = face.size();

	for (int i = 0; i < nVertex; i++) {
		vertex1 = face.at(i);
		if (i < nVertex-1) {
			vertex2 = face.at(i+1);
		} else {
		   vertex2 = face.at(0);
		}

	   // Se um dos vertices da linha estiver sobre o plano, desloca levemente,
	   // para evitar singularidades (possibilidade de mais de dois pontos de contato)
	   if (vertex1.Z == z)
		   vertex1.Z += 1e-15;
	   if (vertex2.Z == z)
		   vertex2.Z += 1e-15;

	   if ((((z < vertex1.Z) && (z > vertex2.Z)) ||
			((z < vertex2.Z) && (z > vertex1.Z)))) {
		   // Calcula o ponto de contado da face com o plano
		   xx = vertex1.X+(z-vertex1.Z)*
			   (vertex2.X-vertex1.X)/(vertex2.Z-vertex1.Z);
		   yy = vertex1.Y+(z-vertex1.Z)*
			   (vertex2.Y-vertex1.Y)/(vertex2.Z-vertex1.Z);
		   vcross[v] = Rvector3(xx,yy,z);
		   v++;
	   }
	   if (v==2) break;
	}
	v1.X = vcross[0].X; v1.Y = vcross[0].Y; v1.Z = vcross[0].Z;
	v2.X = vcross[1].X; v2.Y = vcross[1].Y; v2.Z = vcross[1].Z;
}

Rvector3 Facet::GetNormal() {
	return Normal;
}
void Facet::Translate(double Tx, double Ty, double Tz) {
   Rvector3 v;

   for (size_t i = 0; i < face.size(); i++) {
	   face[i].Move(Tx, Ty, Tz);
   }
// Por algum motivo ao usar rotate está dando pau no desenho. Tem que usar BuildNormal de novo.
   BuildNormal();
   /* Recalcula BoundMax e BoundMin */
   BoundMax = Rvector3(-1e30, -1e30, -1e30);
   BoundMin = Rvector3(+1e30, +1e30, +1e30);
   for (size_t i = 0; i < face.size(); i++) {
	   v = face[i];
	   if (BoundMax.X < v.X)
		   BoundMax.X = v.X;
	   if (BoundMax.Y < v.Y)
		   BoundMax.Y = v.Y;
	   if (BoundMax.Z < v.Z)
		   BoundMax.Z = v.Z;
	   if (BoundMin.X > v.X)
		   BoundMin.X = v.X;
	   if (BoundMin.Y > v.Y)
		   BoundMin.Y = v.Y;
	   if (BoundMin.Z > v.Z)
		   BoundMin.Z = v.Z;
   }
}
void Facet::Rotate(Rvector3 Orig, double Rx, double Ry, double Rz) {
   Rvector3 v;

   for (size_t i = 0; i < face.size(); i++) {
	   face[i].Rotate(Orig, Rx,Ry,Rz);
//	   if (Rx != 0)
//		   face[i].Rotate(Orig, Rx,0,0);
//	   if (Ry != 0)
//		   face[i].Rotate(Orig, 0,Ry,0);
//	   if (Rz != 0)
//		   face[i].Rotate(Orig, 0,0,Rz);
   }
// Por algum motivo ao usar rotate está dando pau no desenho. Tem que usar BuildNormal de novo.
//   Normal.Rotate(Orig, Rx,Ry,Rz);
   BuildNormal();
   /* Recalcula BoundMax e BoundMin */
   BoundMax = Rvector3(-1e30, -1e30, -1e30);
   BoundMin = Rvector3(+1e30, +1e30, +1e30);
   for (size_t i = 0; i < face.size(); i++) {
	   v = face[i];
	   if (BoundMax.X < v.X)
		   BoundMax.X = v.X;
	   if (BoundMax.Y < v.Y)
		   BoundMax.Y = v.Y;
	   if (BoundMax.Z < v.Z)
		   BoundMax.Z = v.Z;
	   if (BoundMin.X > v.X)
		   BoundMin.X = v.X;
	   if (BoundMin.Y > v.Y)
		   BoundMin.Y = v.Y;
	   if (BoundMin.Z > v.Z)
		   BoundMin.Z = v.Z;
   }
}
void RotateFacets(vector<Facet>& v, double RxDegree, double RyDegree, double RzDegree) {
	if (RxDegree == 0 && RyDegree == 0 && RzDegree == 0)
		return;


	Rvector3 max;
	Rvector3 min;

	FillBoundaries(v,min,max);

	Rvector3 center((max.X+min.X)/2, (max.Y+min.Y)/2, (max.Z+min.Z)/2);

	RotateFacets(v,center,RxDegree,RyDegree,RzDegree);
}
void RotateFacets(vector<Facet>& v, Rvector3 Orig, double RxDegree, double RyDegree, double RzDegree) {
	for (size_t i = 0; i < v.size(); i++) {
		v[i].Rotate(Orig, PI*RxDegree/180.0,PI*RyDegree/180.0,PI*RzDegree/180.0);
	}
}
void TranslateFacets(vector<Facet>& v, double Tx, double Ty, double Tz) {
	for (size_t i = 0; i < v.size(); i++) {
		v[i].Translate(Tx, Ty, Tz);
	}

}
void FillBoundaries(vector<Facet>& v, Rvector3& min, Rvector3& max) {
	Rvector3 maxBoundary(-1e30, -1e30, -1e30);
	Rvector3 minBoundary(+1e30, +1e30, +1e30);

	for (size_t i = 0; i < v.size(); i++) {
	   Rvector3 maxTemp = v[i].GetBoundMax();
	   Rvector3 minTemp = v[i].GetBoundMin();

	   maxBoundary.X = maxBoundary.X > maxTemp.X ? maxBoundary.X : maxTemp.X;
	   maxBoundary.Y = maxBoundary.Y > maxTemp.Y ? maxBoundary.Y : maxTemp.Y;
	   maxBoundary.Z = maxBoundary.Z > maxTemp.Z ? maxBoundary.Z : maxTemp.Z;
	   minBoundary.X = minBoundary.X < minTemp.X ? minBoundary.X : minTemp.X;
	   minBoundary.Y = minBoundary.Y < minTemp.Y ? minBoundary.Y : minTemp.Y;
	   minBoundary.Z = minBoundary.Z < minTemp.Z ? minBoundary.Z : minTemp.Z;
	}
	max = maxBoundary;
	min = minBoundary;
}
