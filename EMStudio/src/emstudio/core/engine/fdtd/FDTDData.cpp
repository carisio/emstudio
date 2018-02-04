/*
 * FDTDData.cpp
 *
 *  Created on: 26/02/2013
 *      Author: leandrocarisio
 */

#include "FDTDData.h"


FDTDData::FDTDData() {
}
void FDTDData::Initialize(Grid& grid, FDTDDTO& dto) {
	NxTOTAL = grid.GetNxTOTAL();
	NyTOTAL = grid.GetNyTOTAL();
	NzTOTAL = grid.GetNzTOTAL();
	Npml = dto.GetABC().GetNpml();
	pbcXaxis = dto.GetABC().IsPeriodic(xNeg);
	pbcZaxis = dto.GetABC().IsPeriodic(zNeg);

	// cout <<"\tNxTOTAL: " << NxTOTAL << endl;
	// cout <<"\tNyTOTAL: " << NyTOTAL << endl;
	// cout <<"\tNzTOTAL: " << NzTOTAL << endl;

	// cout <<"\tdto = " << &dto << endl;
	// cout <<"\tChamando dto.GetDeltaT() = ";
	// cout <<dto.GetDeltaT() << endl;

	double deltaT = dto.GetDeltaT();

	// cout <<"\tDefinicao dos campos E, D e H " << endl;
	Ex = Array3D<double>(NxTOTAL,NyTOTAL,NzTOTAL,0.0);
	Ey = Array3D<double>(NxTOTAL,NyTOTAL,NzTOTAL,0.0);
	Ez = Array3D<double>(NxTOTAL,NyTOTAL,NzTOTAL,0.0);

	Dx = Array3D<double>(NxTOTAL,NyTOTAL,NzTOTAL, 0.0);
	Dy = Array3D<double>(NxTOTAL,NyTOTAL,NzTOTAL, 0.0);
	Dz = Array3D<double>(NxTOTAL,NyTOTAL,NzTOTAL, 0.0);

	Hx = Array3D<double>(NxTOTAL,NyTOTAL,NzTOTAL, 0.0);
	Hy = Array3D<double>(NxTOTAL,NyTOTAL,NzTOTAL, 0.0);
	Hz = Array3D<double>(NxTOTAL,NyTOTAL,NzTOTAL, 0.0);

	// cout <<"\tDefinicao das matrizes i, idx, idy e idz " << endl;
	ix = Array3D<double>(NxTOTAL,NyTOTAL,NzTOTAL, 0.0);
	iy = Array3D<double>(NxTOTAL,NyTOTAL,NzTOTAL, 0.0);
	iz = Array3D<double>(NxTOTAL,NyTOTAL,NzTOTAL, 0.0);

	// cout <<"\t1" << endl;
	idxl = Array3D<double>(Npml, NyTOTAL, NzTOTAL, 0.0);
	ihxl = Array3D<double>(Npml, NyTOTAL, NzTOTAL, 0.0);
	idxh = Array3D<double>(Npml, NyTOTAL, NzTOTAL, 0.0);
	ihxh = Array3D<double>(Npml, NyTOTAL, NzTOTAL, 0.0);
	// cout <<"\t2" << endl;
	idyl = Array3D<double>(NxTOTAL, Npml, NzTOTAL, 0.0);
	ihyl = Array3D<double>(NxTOTAL, Npml, NzTOTAL, 0.0);
	idyh = Array3D<double>(NxTOTAL, Npml, NzTOTAL, 0.0);
	ihyh = Array3D<double>(NxTOTAL, Npml, NzTOTAL, 0.0);
	// cout <<"\t3" << endl;
	idzl = Array3D<double>(NxTOTAL, NyTOTAL, Npml, 0.0);
	ihzl = Array3D<double>(NxTOTAL, NyTOTAL, Npml, 0.0);
	idzh = Array3D<double>(NxTOTAL, NyTOTAL, Npml, 0.0);
	ihzh = Array3D<double>(NxTOTAL, NyTOTAL, Npml, 0.0);

	// Boundary conditions
	// cout <<"\tDefinicao dos vetores g e f" << endl;
	gi1 = Array1D<double>(NxTOTAL, 0.0);
	fi1 = Array1D<double>(NxTOTAL, 0.0);
	gi2 = Array1D<double>(NxTOTAL, 1.0);
	fi2 = Array1D<double>(NxTOTAL, 1.0);
	gi3 = Array1D<double>(NxTOTAL, 1.0);
	fi3 = Array1D<double>(NxTOTAL, 1.0);

	gj1 = Array1D<double>(NyTOTAL, 0.0);
	fj1 = Array1D<double>(NyTOTAL, 0.0);
	gj2 = Array1D<double>(NyTOTAL, 1.0);
	fj2 = Array1D<double>(NyTOTAL, 1.0);
	gj3 = Array1D<double>(NyTOTAL, 1.0);
	fj3 = Array1D<double>(NyTOTAL, 1.0);

	gk1 = Array1D<double>(NzTOTAL, 0.0);
	fk1 = Array1D<double>(NzTOTAL, 0.0);
	gk2 = Array1D<double>(NzTOTAL, 1.0);
	fk2 = Array1D<double>(NzTOTAL, 1.0);
	gk3 = Array1D<double>(NzTOTAL, 1.0);
	fk3 = Array1D<double>(NzTOTAL, 1.0);

	cax = Array1D<double>(NxTOTAL, 0.0);
	cay = Array1D<double>(NyTOTAL, 0.0);
	caz = Array1D<double>(NzTOTAL, 0.0);

	// cout <<"\tTodos os arrays foram criados" << endl;

	ia = (dto.GetABC().IsPML(xNeg) ? Npml : 0);
	ja = (dto.GetABC().IsPML(yNeg) ? Npml : 0);
	ka = (dto.GetABC().IsPML(zNeg) ? Npml : 0);
	ib = NxTOTAL - (dto.GetABC().IsPML(xPos) ? Npml + 1: 1);
	jb = NyTOTAL - (dto.GetABC().IsPML(yPos) ? Npml + 1: 1);
	kb = NzTOTAL - (dto.GetABC().IsPML(zPos) ? Npml + 1: 1);

	// cout <<"\tVariáveis definidas" << endl;
//	// cout <<"\tia, ja, ka = " << ia << ", " << ja << ", " << ka << endl;
//	// cout <<"\tib, jb, kb = " << ib << ", " << jb << ", " << kb << endl;

	double xn, xxn, xnum, xd;

	// COMEÇA AQUI
	for(int i = 0; i < ia; i++) {
		xnum = Npml - i;
		xd = Npml;
		xxn = xnum/xd;
		xn = 0.333*pow(xxn, 3.);
		fi1[i] = xn;
		gi2[i] = 1./(1. + xn);
		gi3[i] = (1. - xn)/(1. + xn);
		xxn = (xnum - 0.5)/xd;
		xn = 0.333*pow(xxn, 3.);
		gi1[i] = xn;
		fi2[i] = 1./(1. + xn);
		fi3[i] = (1. - xn)/(1. + xn);
	}
	for(int i = 0; i < Npml && dto.GetABC().IsPML(xPos); i++) {
		xnum = Npml - i;
		xd = Npml;
		xxn = xnum/xd;
		xn = 0.333*pow(xxn, 3.);
		fi1[NxTOTAL-1-i] = xn;
		gi2[NxTOTAL-1-i] = 1./(1. + xn);
		gi3[NxTOTAL-1-i] = (1. - xn)/(1. + xn);
		xxn = (xnum - 0.5)/xd;
		xn = 0.333*pow(xxn, 3.);
		gi1[NxTOTAL-i-2] = xn;
		fi2[NxTOTAL-i-2] = 1./(1. + xn);
		fi3[NxTOTAL-i-2] = (1. - xn)/(1. + xn);
	}
	for(int j = 0; j < ja; j++) {
		xnum = Npml - j;
		xd = Npml;
		xxn = xnum/xd;
		xn = 0.333*pow(xxn, 3.);
		fj1[j] = xn;
		gj2[j] = 1./(1. + xn);
		gj3[j] = (1. - xn)/(1. + xn);
		xxn = (xnum - 0.5)/xd;
		xn = 0.333*pow(xxn, 3.);
		gj1[j] = xn;
		fj2[j] = 1./(1. + xn);
		fj3[j] = (1. - xn)/(1. + xn);
	}
	for(int j = 0; j < Npml && dto.GetABC().IsPML(yPos); j++) {
		xnum = Npml - j;
		xd = Npml;
		xxn = xnum/xd;
		xn = 0.333*pow(xxn, 3.);
		fj1[NyTOTAL-1-j] = xn;
		gj2[NyTOTAL-1-j] = 1./(1. + xn);
		gj3[NyTOTAL-1-j] = (1. - xn)/(1. + xn);
		xxn = (xnum - 0.5)/xd;
		xn = 0.333*pow(xxn, 3.);
		gj1[NyTOTAL-j-2] = xn;
		fj2[NyTOTAL-j-2] = 1./(1. + xn);
		fj3[NyTOTAL-j-2] = (1. - xn)/(1. + xn);

	}
	for(int k = 0; k < ka; k++) {
		xnum = Npml - k;
		xd = Npml;
		xxn = xnum/xd;
		xn = 0.333*pow(xxn, 3.);
		fk1[k] = xn;
		gk2[k] = 1./(1. + xn);
		gk3[k] = (1. - xn)/(1. + xn);
		xxn = (xnum - 0.5)/xd;
		xn = 0.333*pow(xxn, 3.);
		gk1[k] = xn;
		fk2[k] = 1./(1. + xn);
		fk3[k] = (1. - xn)/(1. + xn);
	}
	for(int k = 0; k < Npml && dto.GetABC().IsPML(zPos); k++) {
		xnum = Npml - k;
		xd = Npml;
		xxn = xnum/xd;
		xn = 0.333*pow(xxn, 3.);
		fk1[NzTOTAL-1-k] = xn;
		gk2[NzTOTAL-1-k] = 1./(1. + xn);
		gk3[NzTOTAL-1-k] = (1. - xn)/(1. + xn);
		xxn = (xnum - 0.5)/xd;
		xn = 0.333*pow(xxn, 3.);
		gk1[NzTOTAL-k-2] = xn;
		fk2[NzTOTAL-k-2] = 1./(1. + xn);
		fk3[NzTOTAL-k-2] = (1. - xn)/(1. + xn);
	}

	for (int i = 0; i < NxTOTAL; i++)
		cax[i] = deltaT*SPEED_OF_LIGHT_VACUUM/grid.GetDx(i);
	for (int j = 0; j < NyTOTAL; j++)
		cay[j] = deltaT*SPEED_OF_LIGHT_VACUUM/grid.GetDy(j);
	for (int k = 0; k < NzTOTAL; k++)
		caz[k] = deltaT*SPEED_OF_LIGHT_VACUUM/grid.GetDz(k);
}

void FDTDData::CalculateDFields() {
    int i, j, k;
	double curl_h;

	// Calculate the Dx field
	for(i = 0; i < ia; i++) {
		for(j = 1; j < NyTOTAL; j++) {
			for(k = 1; k < NzTOTAL; k++) {
				curl_h = cay[j]*(Hz[i][j][k] - Hz[i][j-1][k]) -
						 caz[k]*(Hy[i][j][k] - Hy[i][j][k-1]);
				idxl[i][j][k] = idxl[i][j][k] + curl_h;
				Dx[i][j][k] = gj3[j]*gk3[k]*Dx[i][j][k] +
							  gj2[j]*gk2[k]*(curl_h + gi1[i]*idxl[i][j][k]);
			}
		}
	}
	for (i = ia; i <= ib; i++) {
		for (j = 1; j < NyTOTAL; j++) {
			for (k = 1; k < NzTOTAL; k++) {
				curl_h = cay[j]*(Hz[i][j][k] - Hz[i][j-1][k]) -
						 caz[k]*(Hy[i][j][k] - Hy[i][j][k-1]);
				Dx[i][j][k] = gj3[j]*gk3[k]*Dx[i][j][k] + gj2[j]*gk2[k]*curl_h;
    		}
    	}
    }
	for(i = ib+1; i < NxTOTAL; i++) {
		ixh = i - ib - 1;
		for(j = 1; j < NyTOTAL; j++) {
			for(k = 1; k < NzTOTAL; k++) {
				curl_h = cay[j]*(Hz[i][j][k] - Hz[i][j-1][k]) -
						 caz[k]*(Hy[i][j][k] - Hy[i][j][k-1]);
				idxh[ixh][j][k] = idxh[ixh][j][k] + curl_h;
				Dx[i][j][k] = gj3[j]*gk3[k]*Dx[i][j][k] +
							  gj2[j]*gk2[k]*(curl_h + gi1[i]*idxh[ixh][j][k]);
			}
		}
	}
	// Calculate the Dy field
	for(i = 1; i < NxTOTAL; i++) {
		for(j = 0; j < ja; j++) {
			for(k = 1; k < NzTOTAL; k++) {
				curl_h = caz[k]*(Hx[i][j][k] - Hx[i][j][k-1]) -
						 cax[i]*(Hz[i][j][k] - Hz[i-1][j][k]);
				idyl[i][j][k] = idyl[i][j][k] + curl_h;
				Dy[i][j][k] = gi3[i]*gk3[k]*Dy[i][j][k] +
						      gi2[i]*gk2[k]*(curl_h + gj1[j]*idyl[i][j][k]);
			}
		}
	}
	for (i = 1; i < NxTOTAL; i++) {
		for (j = ja; j <= jb; j++) {
			for (k = 1; k < NzTOTAL; k++) {
				curl_h = caz[k]*(Hx[i][j][k] - Hx[i][j][k-1]) -
						 cax[i]*(Hz[i][j][k] - Hz[i-1][j][k]);
    			Dy[i][j][k] = gi3[i]*gk3[k]*Dy[i][j][k] + gi2[i]*gk2[k]*curl_h;
       		}
       	}
    }
	for(i = 1; i < NxTOTAL; i++) {
		for(j = jb+1; j < NyTOTAL; j++) {
			jyh = j - jb - 1;
			for(k = 1; k < NzTOTAL; k++)
			{
				curl_h = caz[k]*(Hx[i][j][k] - Hx[i][j][k-1]) -
						 cax[i]*(Hz[i][j][k] - Hz[i-1][j][k]);
				idyh[i][jyh][k] = idyh[i][jyh][k] + curl_h;
				Dy[i][j][k] = gi3[i]*gk3[k]*Dy[i][j][k] +
						      gi2[i]*gk2[k]*(curl_h + gj1[j]*idyh[i][jyh][k]);
			}
		}
	}
	// Calculate the Dz field
	for(i = 1; i < NxTOTAL; i++) {
		for(j = 1; j < NyTOTAL; j++) {
			for(k = 0; k < ka; k++) {
				curl_h = cax[i]*(Hy[i][j][k] - Hy[i-1][j][k]) -
						 cay[j]*(Hx[i][j][k] - Hx[i][j-1][k]);
				idzl[i][j][k] = idzl[i][j][k] + curl_h;
				Dz[i][j][k] = gi3[i]*gj3[j]*Dz[i][j][k] +
						      gi2[i]*gj2[j]*(curl_h + gk1[k]*idzl[i][j][k]);
			}
		}
	}
	for (i = 1; i < NxTOTAL; i++) {
		for (j = 1; j < NyTOTAL; j++) {
			for (k = ka; k <= kb; k++) {
				curl_h = cax[i]*(Hy[i][j][k] - Hy[i-1][j][k]) -
						 cay[j]*(Hx[i][j][k] - Hx[i][j-1][k]);
    			Dz[i][j][k] = gi3[i]*gj3[j]*Dz[i][j][k] + gi2[i]*gj2[j]*curl_h;
    		}
    	}
    }
	for(i = 1; i < NxTOTAL; i++) {
		for(j = 1; j < NyTOTAL; j++) {
			for(k = kb+1; k < NzTOTAL; k++) {
				kzh = k - kb - 1;
				curl_h = cax[i]*(Hy[i][j][k] - Hy[i-1][j][k]) -
						 cay[j]*(Hx[i][j][k] - Hx[i][j-1][k]);
				idzh[i][j][kzh] = idzh[i][j][kzh] + curl_h;
				Dz[i][j][k] = gi3[i]*gj3[j]*Dz[i][j][k] +
						      gi2[i]*gj2[j]*(curl_h + gk1[k]*idzh[i][j][kzh]);
			}
		}
	}
}

void FDTDData::CalculateEFields(Mesh& mesh) {
	int i, j, k;
	for(i = 0; i < NxTOTAL; i++) {
		for(j = 0; j < NyTOTAL; j++) {
			for(k = 0; k < NzTOTAL; k++) {
				MaterialCoefficients mc = mesh.GetCoefficients(i, j, k);
				Ex[i][j][k] = mc.GetGax()*(Dx[i][j][k] - ix[i][j][k]);
				ix[i][j][k] = ix[i][j][k] + mc.GetGbx()*Ex[i][j][k];
				Ey[i][j][k] = mc.GetGay()*(Dy[i][j][k] - iy[i][j][k]);
				iy[i][j][k] = iy[i][j][k] + mc.GetGby()*Ey[i][j][k];
				Ez[i][j][k] = mc.GetGaz()*(Dz[i][j][k] - iz[i][j][k]);
				iz[i][j][k] = iz[i][j][k] + mc.GetGbz()*Ez[i][j][k];
			}
		}
	}
//
//	if(ia == 0) {
//		for(j = 1; j < NyTOTAL - 1; j++) {
//			for(k = 1; k < NzTOTAL-1; k++) {
//				MaterialCoefficients mc = mesh.GetCoefficients(ia, j, k);
//				Ex[ia][j][k] = mc.GetGax()*(Dx[ia][j][k] - ix[ia][j][k]);
//				ix[ia][j][k] = ix[ia][j][k] + mc.GetGbx()*Ex[ia][j][k];
//			}
//		}
//	}
//
//	if(ja == 0) {
//		for(i = 1; i < NxTOTAL - 1; i++) {
//			for(k = 1; k < NzTOTAL - 1; k++) {
//				MaterialCoefficients mc = mesh.GetCoefficients(i, ja, k);
//				Ey[i][ja][k] = mc.GetGay()*(Dy[i][ja][k] - iy[i][ja][k]);
//				iy[i][ja][k] = iy[i][ja][k] + mc.GetGby()*Ey[i][ja][k];
//			}
//		}
//	}
//
//	if(ka == 0) {
//		for(i = 1; i < NxTOTAL - 1; i++) {
//			for(j = 1; j < NyTOTAL - 1; j++) {
//				MaterialCoefficients mc = mesh.GetCoefficients(i, j, ka);
//				Ez[i][j][ka] = mc.GetGaz()*(Dz[i][j][ka] - iz[i][j][ka]);
//				iz[i][j][ka] = iz[i][j][ka] + mc.GetGbz()*Ez[i][j][ka];
//			}
//		}
//	}
}
void FDTDData::CalculateHFields() {
	int i, j, k;
		int ixh, jyh, kzh;

	    double curl_e;

		// Calculate the Hx field
		for(i = 0; i < ia; i++)	{
			for(j = 0; j < NyTOTAL - 1; j++) {
				for(k = 0; k < NzTOTAL - 1; k++) {
					curl_e = caz[k]*(Ey[i][j][k+1] - Ey[i][j][k]) -
							 cay[j]*(Ez[i][j+1][k] - Ez[i][j][k]);
					ihxl[i][j][k] = ihxl[i][j][k] + curl_e;
					Hx[i][j][k] = fj3[j]*fk3[k]*Hx[i][j][k] +
							      fj2[j]*fk2[k]*(curl_e + fi1[i]*ihxl[i][j][k]);
				}
			}
		}
		for (i = ia; i <= ib; i++) {
			for (j = 0; j < NyTOTAL - 1; j++) {
				for (k = 0; k < NzTOTAL - 1; k++) {
					curl_e = caz[k]*(Ey[i][j][k+1] - Ey[i][j][k]) -
							 cay[j]*(Ez[i][j+1][k] - Ez[i][j][k]);
	    			Hx[i][j][k] = fj3[j]*fk3[k]*Hx[i][j][k] + fj2[j]*fk2[k]*curl_e;
	    		}
	    	}
	    }
		for(i = ib + 1; i < NxTOTAL; i++) {
			ixh = i - ib - 1;
			for(j = 0; j < NyTOTAL - 1; j++) {
				for(k = 0; k < NzTOTAL - 1; k++) {
					curl_e = caz[k]*(Ey[i][j][k+1] - Ey[i][j][k]) -
							 cay[j]*(Ez[i][j+1][k] - Ez[i][j][k]);
					ihxh[ixh][j][k] = ihxh[ixh][j][k] + curl_e;
					Hx[i][j][k] = fj3[j]*fk3[k]*Hx[i][j][k] +
							      fj2[j]*fk2[k]*(curl_e + fi1[i]*ihxh[ixh][j][k]);
				}
			}
		}
		// Calculate the Hy field
		for(int i = 0; i < NxTOTAL - 1; i++) {
			for(int j = 0; j < ja; j++) {
				for(int k = 0; k < NzTOTAL - 1; k++) {
					curl_e = cax[i]*(Ez[i+1][j][k] - Ez[i][j][k]) -
							 caz[k]*(Ex[i][j][k+1] - Ex[i][j][k]);
					ihyl[i][j][k] = ihyl[i][j][k] + curl_e;
					Hy[i][j][k] = fi3[i]*fk3[k]*Hy[i][j][k] +
							      fi2[i]*fk2[k]*(curl_e + fj1[j]*ihyl[i][j][k]);
				}
			}
		}
		for (i = 0; i < NxTOTAL - 1; i++) {
			for (j = ja; j <= jb; j++) {
				for (k = 0; k < NzTOTAL - 1; k++) {
					curl_e = cax[i]*(Ez[i+1][j][k] - Ez[i][j][k]) -
							 caz[k]*(Ex[i][j][k+1] - Ex[i][j][k]);
	    			Hy[i][j][k] = fi3[i]*fk3[k]*Hy[i][j][k] + fi2[i]*fk2[k]*curl_e;
	 			}
	    	}
	    }
		for(i = 0; i < NxTOTAL - 1; i++) {
			for(j = jb + 1; j < NyTOTAL; j++) {
				jyh = j - jb - 1;
				for(k = 0; k < NzTOTAL - 1; k++) {
					curl_e = cax[i]*(Ez[i+1][j][k] - Ez[i][j][k]) -
							 caz[k]*(Ex[i][j][k+1] - Ex[i][j][k]);
					ihyh[i][jyh][k] = ihyh[i][jyh][k] + curl_e;
					Hy[i][j][k] = fi3[i]*fk3[k]*Hy[i][j][k] +
							      fi2[i]*fk2[k]*(curl_e + fj1[j]*ihyh[i][jyh][k]);
				}
			}
		}
		// Calculate the Hz field
		for(i = 0; i < NxTOTAL - 1; i++) {
			for(j = 0; j < NyTOTAL - 1; j++) {
				for(k = 0; k < ka; k++) {
					curl_e = cay[j]*(Ex[i][j+1][k] - Ex[i][j][k]) -
							 cax[i]*(Ey[i+1][j][k] - Ey[i][j][k]);
					ihzl[i][j][k] = ihzl[i][j][k] + curl_e;
					Hz[i][j][k] = fi3[i]*fj3[j]*Hz[i][j][k] +
							      fi2[i]*fj2[j]*(curl_e + fk1[k]*ihzl[i][j][k]);
				}
			}
		}
		for (i = 0; i < NxTOTAL - 1; i++) {
			for (j = 0; j < NyTOTAL - 1; j++) {
				for (k = ka; k <= kb; k++) {
					curl_e = cay[j]*(Ex[i][j+1][k] - Ex[i][j][k]) -
							 cax[i]*(Ey[i+1][j][k] - Ey[i][j][k]);
	    			Hz[i][j][k] = fi3[i]*fj3[j]*Hz[i][j][k] + fi2[i]*fj2[j]*curl_e;
	        	}
	        }
	    }
		for(i = 0; i < NxTOTAL - 1; i++) {
			for(j = 0; j < NyTOTAL - 1; j++) {
				for(k = kb + 1; k < NzTOTAL; k++) {
					kzh = k - kb - 1;
					curl_e = cay[j]*(Ex[i][j+1][k] - Ex[i][j][k]) -
							 cax[i]*(Ey[i+1][j][k] - Ey[i][j][k]);
					ihzh[i][j][kzh] = ihzh[i][j][kzh] + curl_e;
					Hz[i][j][k] = fi3[i]*fj3[j]*Hz[i][j][k] +
							      fi2[i]*fj2[j]*(curl_e + fk1[k]*ihzh[i][j][kzh]);
				}
			}
		}
}
