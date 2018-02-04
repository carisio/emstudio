#include "emstudio/util/tnt/tnt.h"

#include "emstudio/dto/fdtdapp/FDTDDTO.h"
#include "emstudio/core/engine/fdtd/Grid.h"
#include "emstudio/core/engine/fdtd/Mesh.h"

using namespace TNT;

struct FDTDData {
	int NxTOTAL;
	int NyTOTAL;
	int NzTOTAL;
	int Npml;

	bool pbcXaxis;
	bool pbcZaxis;

	/* Índices que delimitam a região computacional de cálculo */
	int ia, ja, ka;
	int ib, jb, kb;

	/* Índices auxiliares para ajudar no cálculo do D */
	int ixh, jyh, kzh;

	Array3D<double> Ex;
	Array3D<double> Ey;
	Array3D<double> Ez;
	Array3D<double> Dx;
	Array3D<double> Dy;
	Array3D<double> Dz;
	Array3D<double> Hx;
	Array3D<double> Hy;
	Array3D<double> Hz;

	Array3D<double> ix;
	Array3D<double> iy;
	Array3D<double> iz;

	Array3D<double> idxl;
	Array3D<double> idyl;
	Array3D<double> idzl;
	Array3D<double> ihxl;
	Array3D<double> ihyl;
	Array3D<double> ihzl;
	Array3D<double> idxh;
	Array3D<double> idyh;
	Array3D<double> idzh;
	Array3D<double> ihxh;
	Array3D<double> ihyh;
	Array3D<double> ihzh;

	Array1D<double> gi1;
	Array1D<double> fi1;
	Array1D<double> gi2;
	Array1D<double> fi2;
	Array1D<double> gi3;
	Array1D<double> fi3;

	Array1D<double> gj1;
	Array1D<double> fj1;
	Array1D<double> gj2;
	Array1D<double> fj2;
	Array1D<double> gj3;
	Array1D<double> fj3;

	Array1D<double> gk1;
	Array1D<double> fk1;
	Array1D<double> gk2;
	Array1D<double> fk2;
	Array1D<double> gk3;
	Array1D<double> fk3;

	Array1D<double> cax;
	Array1D<double> cay;
	Array1D<double> caz;

	FDTDData();
	void Initialize(Grid& grid, FDTDDTO& dto);
	void CalculateDFields();
	void CalculateEFields(Mesh& mesh);
	void CalculateHFields();
};
