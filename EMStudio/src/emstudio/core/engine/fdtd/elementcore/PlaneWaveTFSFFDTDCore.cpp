/*
 * PlaneWaveTFSFFDTDCore.cpp
 *
 *  Created on: 27/03/2013
 *      Author: Leandro
 */

#include "PlaneWaveTFSFFDTDCore.h"

/**
 * Observação importante.
 *
 * Nesse código foi utilizado tanto o operator() quanto o operator[] do Array1D.
 * Existe uma diferença entre ambos. Usando [] o índice é acessado começando de 0. Usando (), começando de 1.
 */
PlaneWaveTFSFFDTDCore::PlaneWaveTFSFFDTDCore() {

}

PlaneWaveTFSFFDTDCore::~PlaneWaveTFSFFDTDCore() {
}

ElementCoreSmartPointer PlaneWaveTFSFFDTDCore::NewElementCore() {
	return ElementCoreSmartPointer(new PlaneWaveTFSFFDTDCore);
}

void PlaneWaveTFSFFDTDCore::DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr) {
	PlaneWaveDTO* planeWaveDTO = static_cast<PlaneWaveDTO*>(elementDTOSmartPtr.get());

	dto = *planeWaveDTO;
}
bool PlaneWaveTFSFFDTDCore::FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	xmin = dto.GetXmin(); ymin = dto.GetYmin(); zmin = dto.GetZmin();
	xmax = dto.GetXmax(); ymax = dto.GetYmax(); zmax = dto.GetZmax();
	return true;
}

void PlaneWaveTFSFFDTDCore::SimulationWillStart() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	class Grid grid = engine->GetGrid();

	dt = engine->GetDeltaT();
	c_times_dt = SPEED_OF_LIGHT_VACUUM * dt;
	c_space = SPEED_OF_LIGHT_VACUUM;
	Z_space = ETA0;

//	cout << "\t c_space = " << c_space << endl;
//	cout << "\t Z_space = " << Z_space << endl;

	THETA_INC = dto.GetTheta()*PI/180;
	PHI_INC = dto.GetPhi()*PI/180;
	PSI = dto.GetPsi()*PI/180;
	SinT = sin(THETA_INC); CosT = cos(THETA_INC);
	SinP = sin(PHI_INC); CosP = cos(PHI_INC);
	SinPsi = sin(PSI); CosPsi = cos(PSI);

	//Unit vector in the direction of incidence
	k_inc = Array1D<double>(3,0.0);
	k_inc[0] = -CosP*SinT;
	k_inc[1] = -SinP*SinT;
	k_inc[2] = -CosT;
	k_inc_x = k_inc[0];
	k_inc_y = k_inc[1];
	k_inc_z = k_inc[2];

	//Lateral unit vector in the direction of incidence
	k_inc_lateral = Array1D<double>(3,0.0);
	if (SinT >= 0) {//theta=0 or pi results in the same direction as theta=eps or pi-eps,
		            // where eps is positive and arbitrarily small (document this!!)
		k_inc_lateral[0] = -CosP;
		k_inc_lateral[1] = -SinP;
		k_inc_lateral[2] = 0;
	} else {
		k_inc_lateral[0] = CosP;
		k_inc_lateral[1] = SinP;
		k_inc_lateral[2] = 0;
	}

//	PWBackX = NPML+Data.PWMarginBackX+1;
//	PWFrontX = NCELLS_X+NPML-Data.PWMarginFrontX-2;
//
//	PWLeftY = NPML+Data.PWMarginLeftY+1;
//	PWRightY = NCELLS_Y+NPML-Data.PWMarginRightY-2;
//
//	PWLowerZ = NPML+Data.PWMarginLowerZ+1;
//	PWUpperZ = NCELLS_Z+NPML-Data.PWMarginUpperZ-2;
	PWBackX = grid.GetXCell(dto.GetXmin()) + 1;
	PWFrontX = grid.GetXCell(dto.GetXmax()) - 2;

	PWLeftY = grid.GetYCell(dto.GetYmin()) + 1;
	PWRightY = grid.GetYCell(dto.GetYmax()) - 2;

	PWLowerZ = grid.GetZCell(dto.GetZmin()) + 1;
	PWUpperZ = grid.GetZCell(dto.GetZmax()) - 2;

//	cout << "\t PWBackX = " << PWBackX << endl;
//	cout << "\t PWFrontX = " << PWFrontX << endl;
//	cout << "\t PWLeftY = " << PWLeftY << endl;
//	cout << "\t PWRightY = " << PWRightY << endl;
//	cout << "\t PWLowerZ = " << PWLowerZ << endl;
//	cout << "\t PWUpperZ = " << PWUpperZ << endl;

	TFSF_min_x = PWBackX;
	TFSF_max_x = PWFrontX;
	TFSF_min_y = PWLeftY;
	TFSF_max_y = PWRightY;
	TFSF_min_z = PWLowerZ;
	TFSF_max_z = PWUpperZ;
//	cout << "\t TFSF_min_x = " << TFSF_min_x << endl;
//	cout << "\t TFSF_max_x = " << TFSF_max_x << endl;
//	cout << "\t TFSF_min_y = " << TFSF_min_y << endl;
//	cout << "\t TFSF_max_y = " << TFSF_max_y << endl;
//	cout << "\t TFSF_min_z = " << TFSF_min_z << endl;
//	cout << "\t TFSF_max_z = " << TFSF_max_z << endl;

	// cpw_fs.cpp
	//Unit vector that points in the direction of the E-field vector
	k_E = Array1D<double>(3,0.);
	k_E[0] = CosPsi*k_inc_lateral[1] - SinPsi*k_inc_lateral[0]*k_inc[2];
	k_E[1] = -CosPsi*k_inc_lateral[0] - SinPsi*k_inc_lateral[1]*k_inc[2];
	k_E[2] = SinPsi*(k_inc_lateral[0]*k_inc[0] + k_inc_lateral[1]*k_inc[1]);
	k_Ex = k_E[0];
	k_Ey = k_E[1];
	k_Ez = k_E[2];

	//Unit vector that points in the direction of the H-field vector
	k_H = Array1D<double>(3, 0.);
	k_H[0] = k_inc[1]*k_E[2]  - k_inc[2]*k_E[1];
	k_H[1] = k_inc[2]*k_E[0]  - k_inc[0]*k_E[2];
	k_H[2] = k_inc[0]*k_E[1]  - k_inc[1]*k_E[0];
	k_Hx = k_H[0];
	k_Hy = k_H[1];
	k_Hz = k_H[2];

	//find the grid spacing for the 1-D auxiliary grid (approximate MND method - 5.69 in Taflove 2005)
	dx = 2*SPEED_OF_LIGHT_VACUUM*dt;
	dx_over_dx_g = 1/sqrt(pow(sin(THETA_INC),4)*(pow(cos(PHI_INC),4)+pow(sin(PHI_INC),4))+pow(cos(THETA_INC),4));
	dx_g = dx/dx_over_dx_g;

//	cout << "\t dx = " << dx << endl;
//	cout << "\t dx_over_dx_g = " << dx_over_dx_g << endl;
//	cout << "\t dx_g = " << dx_g << endl;

	//Length of the 1-D grid (in grid cells)
	//adjusted for worst case: incident direction coincident with diagonal
	AuxGridLength = (int)ceil(sqrt(pow((double)(PWFrontX-PWBackX+1),2)+pow((double)(PWRightY-PWLeftY+1),2)+pow((double)(PWUpperZ-PWLowerZ+1),2))
								*dx_over_dx_g);	//convert to 1-D auxiliary-grid cells

//	cout << "\t AuxGridLength = " << AuxGridLength << endl;

	//extra cells at the top and bottom of the 1-D grid (since H-field positions are 1/2 cell outside the TF/SF box)
	extra_top = 2;	    //in 1-D grid cells (dx_g)
	extra_bottom = 2;	//in 1-D grid cells (dx_g)

	extra_distance = Array1D<double>(3,0.);
	extra_distance[0] = -extra_top*k_inc[0]/dx_over_dx_g;
	extra_distance[1] = -extra_top*k_inc[1]/dx_over_dx_g;
	extra_distance[2] = -extra_top*k_inc[2]/dx_over_dx_g;

	//Lower and upper limits of the 1-D grid are fixed
	AuxGridLower = 0;
	AuxGridUpper = AuxGridLength+extra_top+extra_bottom;

//	cout << "\t AuxGridLower = " << AuxGridLower << endl;
//	cout << "\t AuxGridUpper = " << AuxGridUpper << endl;

	//hard-source and absorption points
	AbsorbIndexLower = AuxGridLower;	  //E-field absorption point (lower)
	HardSourcePoint = AuxGridUpper - 1;	  //E-field hard-source point is right at uppermost E-field position
//
//	cout << "\t AbsorbIndexLower = " << AbsorbIndexLower << endl;
//	cout << "\t HardSourcePoint = " << HardSourcePoint << endl;

	//the coordinates of the plane-wave origin
	//(measured from the back-left-bottom point of the grid)
	PWOriginationPoint = Array1D<double>(3, 0.);

	//Determine the coordinates of the plane-wave origination point
	//(measured from the back-left-bottom point of the grid)
	//if incident from upper hemisphere:
	if ((k_inc[0]<=0)&&(k_inc[1]<=0)&&(k_inc[2]<=0)) {
		PWOriginationPoint[0] = PWFrontX;
		PWOriginationPoint[1] = PWRightY;
		PWOriginationPoint[2] = PWUpperZ;
		PWOriginationPoint[0] += extra_distance[0];
		PWOriginationPoint[1] += extra_distance[1];
		PWOriginationPoint[2] += extra_distance[2];
	} else if ((k_inc[0]>0)&&(k_inc[1]<=0)&&(k_inc[2]<=0)) {
		PWOriginationPoint[0] = PWBackX-1;
		PWOriginationPoint[1] = PWRightY;
		PWOriginationPoint[2] = PWUpperZ;
		PWOriginationPoint[0] += extra_distance[0];
		PWOriginationPoint[1] += extra_distance[1];
		PWOriginationPoint[2] += extra_distance[2];
	} else if ((k_inc[0]>0)&&(k_inc[1]>0)&&(k_inc[2]<=0)) {
		PWOriginationPoint[0] = PWBackX-1;
		PWOriginationPoint[1] = PWLeftY-1;
		PWOriginationPoint[2] = PWUpperZ;
		PWOriginationPoint[0] += extra_distance[0];
		PWOriginationPoint[1] += extra_distance[1];
		PWOriginationPoint[2] += extra_distance[2];
	} else if ((k_inc[0]<=0)&&(k_inc[1]>0)&&(k_inc[2]<=0)) {
		PWOriginationPoint[0] = PWFrontX;
		PWOriginationPoint[1] = PWLeftY-1;
		PWOriginationPoint[2] = PWUpperZ;
		PWOriginationPoint[0] += extra_distance[0];
		PWOriginationPoint[1] += extra_distance[1];
		PWOriginationPoint[2] += extra_distance[2];
	}
	//if incident from lower hemisphere:
	if ((k_inc[0]<=0)&&(k_inc[1]<=0)&&(k_inc[2]>0)) {
		PWOriginationPoint[0] = PWFrontX;
		PWOriginationPoint[1] = PWRightY;
		PWOriginationPoint[2] = PWLowerZ-1;
		PWOriginationPoint[0] += extra_distance[0];
		PWOriginationPoint[1] += extra_distance[1];
		PWOriginationPoint[2] += extra_distance[2];
	} else if ((k_inc[0]>0)&&(k_inc[1]<=0)&&(k_inc[2]>0)) {
		PWOriginationPoint[0] = PWBackX-1;
		PWOriginationPoint[1] = PWRightY;
		PWOriginationPoint[2] = PWLowerZ-1;
		PWOriginationPoint[0] += extra_distance[0];
		PWOriginationPoint[1] += extra_distance[1];
		PWOriginationPoint[2] += extra_distance[2];
	} else if ((k_inc[0]>0)&&(k_inc[1]>0)&&(k_inc[2]>0)) {
		PWOriginationPoint[0] = PWBackX-1;
		PWOriginationPoint[1] = PWLeftY-1;
		PWOriginationPoint[2] = PWLowerZ-1;
		PWOriginationPoint[0] += extra_distance[0];
		PWOriginationPoint[1] += extra_distance[1];
		PWOriginationPoint[2] += extra_distance[2];
	} else  if ((k_inc[0]<=0)&&(k_inc[1]>0)&&(k_inc[2]>0)) {
		PWOriginationPoint[0] = PWFrontX;
		PWOriginationPoint[1] = PWLeftY-1;
		PWOriginationPoint[2] = PWLowerZ-1;
		PWOriginationPoint[0] += extra_distance[0];
		PWOriginationPoint[1] += extra_distance[1];
		PWOriginationPoint[2] += extra_distance[2];
	}

	//components of PWOriginationPoint
	PWOriginationPoint_x = PWOriginationPoint[0];
	PWOriginationPoint_y = PWOriginationPoint[1];
	PWOriginationPoint_z = PWOriginationPoint[2];

	cout << "\t PWOriginationPoint_x = " << PWOriginationPoint_x << endl;
	cout << "\t PWOriginationPoint_y = " << PWOriginationPoint_y << endl;
	cout << "\t PWOriginationPoint_z = " << PWOriginationPoint_z << endl;

	//aux-grid-coordinate contributions at different x,y,and z positions
	CoordinateOnAuxGrid_x_fullint = Array1D<double>(grid.GetNxTOTAL()+1, 0.);
	CoordinateOnAuxGrid_y_fullint = Array1D<double>(grid.GetNyTOTAL()+1, 0.);
	CoordinateOnAuxGrid_z_fullint = Array1D<double>(grid.GetNzTOTAL()+1, 0.);
	CoordinateOnAuxGrid_x_halfint = Array1D<double>(grid.GetNxTOTAL(), 0.);
	CoordinateOnAuxGrid_y_halfint = Array1D<double>(grid.GetNyTOTAL(), 0.);
	CoordinateOnAuxGrid_z_halfint = Array1D<double>(grid.GetNzTOTAL(), 0.);

	//aux-grid-coordinate contributions at different x,y,and z positions
	for (int i=0; i<grid.GetNxTOTAL()+1; i++)	{
		CoordinateOnAuxGrid_x_fullint[i] = (i-PWOriginationPoint_x)*k_inc_x*dx_over_dx_g;
	}
	for (int j=0; j<grid.GetNyTOTAL()+1; j++)	{
		CoordinateOnAuxGrid_y_fullint[j] = (j-PWOriginationPoint_y)*k_inc_y*dx_over_dx_g;
	}
	for (int k=0; k<grid.GetNzTOTAL()+1; k++)	{
		CoordinateOnAuxGrid_z_fullint[k] = (k-PWOriginationPoint_z)*k_inc_z*dx_over_dx_g;
	}
	for (int i=0; i<grid.GetNxTOTAL(); i++) {
		CoordinateOnAuxGrid_x_halfint[i] = (i+0.5-PWOriginationPoint_x)*k_inc_x*dx_over_dx_g;
	}
	for (int j=0; j<grid.GetNyTOTAL(); j++) {
		CoordinateOnAuxGrid_y_halfint[j] = (j+0.5-PWOriginationPoint_y)*k_inc_y*dx_over_dx_g;
	}
	for (int k=0; k<grid.GetNzTOTAL(); k++) {
		CoordinateOnAuxGrid_z_halfint[k] = (k+0.5-PWOriginationPoint_z)*k_inc_z*dx_over_dx_g;
	}

	//coefficients for the E update
	Ca = 1.0;
//	Cb = dt/dx_g/(epsilon_r_space*epsilon_0);	//note the use of dx_g instead of dx
	Cb = (dt/dx_g)*c_space;//*Z_space;

	//coefficients for the H update
	Da = 1.0;
//	Db = dt/dx_g/mu_0;		//note the use of dx_g instead of dx
	Db = (dt/dx_g)*c_space;///Z_space;		//note the use of dx_g instead of dx

	//Auxiliary 1-D grids for incident field computation
	AuxGrid_E = Array1D<double>(AuxGridUpper+1, 0.);
	AuxGrid_H = Array1D<double>(AuxGridUpper, 0.);
	//x,y,z components
	AuxGrid_Ex = Array1D<double>(AuxGridUpper+1, 0.);
	AuxGrid_Ey = Array1D<double>(AuxGridUpper+1, 0.);
	AuxGrid_Ez = Array1D<double>(AuxGridUpper+1, 0.);
	AuxGrid_Hx = Array1D<double>(AuxGridUpper, 0.);
	AuxGrid_Hy = Array1D<double>(AuxGridUpper, 0.);
	AuxGrid_Hz = Array1D<double>(AuxGridUpper, 0.);

	//effective courant number for 1D grid:
	Sc_1D_lower = c_space*dt/dx_g;		//note the use of dx_g instead of dx
//	cout << "\t" << "Sc_1D_lower = " << Sc_1D_lower << endl;

	//resize and initialize ABC storage variables PreviousEeLower(k,n) etc.
	//NOTE: k=0,n=0 need not be used, since this is the current value of the E-field at the boundary of the auxiliary grid.
	//However, it will still be used for symmetry (see Schneider course notes on 2nd order ABC).
	PreviousELower = Array2D<double>(3,2, 0.0);


	dto.GetExcitation().Init();
}

void PlaneWaveTFSFFDTDCore::DFieldsChanged(double t) {
	UpdateIncidentH(0);	//update Einc and Hinc until Hinc is at n+1/2
	ApplyCorrectionE();
}

void PlaneWaveTFSFFDTDCore::MagneticFieldsChanged(double t) {
	UpdateIncidentE(0);	  //update Einc and Hinc until Einc is at n+1
	ApplyCorrectionH();	  //apply correction to the main-grid H-field (using Einc at n+1) by projection
}

void PlaneWaveTFSFFDTDCore::UpdateIncidentH(const int& n) {
	//H-field is already at time n+1/2, since 1-D grid has the same dt as the main grid
	//no update necessary
}

void PlaneWaveTFSFFDTDCore::UpdateIncidentE(const int& n) {
	//update incident E and H until E-field is at time n+1
	UpdateE(n); //Update the E-field
	UpdateH(n); //Update the H-field
}
void PlaneWaveTFSFFDTDCore::SimulationWillFinish() {

}
void PlaneWaveTFSFFDTDCore::UpdateH(const int& n) {
	//updates the H-field components at time index n
	for (int k = AbsorbIndexLower; k < AuxGridUpper; k++) {
		AuxGrid_H[k] = Da*AuxGrid_H[k] + Db*(AuxGrid_E[k+1]-AuxGrid_E[k]);
		//See note in UpdateE regarding the "+" sign
	}

	//calculate the x,y,z components separately
	for(int i = AbsorbIndexLower; i < AuxGridUpper; i++) {
		AuxGrid_Hx[i] = k_Hx*AuxGrid_H[i];
		AuxGrid_Hy[i] = k_Hy*AuxGrid_H[i];
		AuxGrid_Hz[i] = k_Hz*AuxGrid_H[i];
	}
}
void PlaneWaveTFSFFDTDCore::UpdateE(const int& n) {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	double t = engine->GetDeltaT() * engine->GetCurrentInterationNumber();

	//updates the E-field components at time index n
	for (int k = AbsorbIndexLower+1; k < AuxGridUpper; k++) {
		AuxGrid_E[k] = Ca*AuxGrid_E[k] + Cb*(AuxGrid_H[k]-AuxGrid_H[k-1]);
		//Note the "+" sign before Cb, instead of "-" in Cpw_fs_update.cpp
		//In the multilayered version, the characteristic impedance of the line did not matter,
		//since the directions of the field components in the 1-D grid were well-defined in the main grid.
		//We only had to make sure that the updates were consistent with the TL equations.
		//The rest was taken care of by the 1-D TF/SF corrections in the 1-D grid.
		//Here, however, we want the characteristic impedance to be positive for a wave that is propagating
		//downward in the 1-D grid (which is our assumption). Otherwise, the H-field in the 1-D grid would
		//have the opposite sign relative to the E-field for a downward-propagating wave, which is
		//inconsistent with the desired plane wave in the  main grid.
	}

	//Apply hard-source for Einc
	AuxGrid_E[HardSourcePoint] = dto.GetExcitation().GetExcitationValue(t);// + OriginDelay*dt);//waveformE_value(n);

	//Apply 2nd order ABC
	//NOTE: PreviousELower(0,0) need not be used, since it is equal to AuxGrid_E(AbsorbIndexLower)
	//[before the update], but it is used for symmetry.
	//Lower absorbing point
	AuxGrid_E[AbsorbIndexLower] = (-1/(1/Sc_1D_lower+2+Sc_1D_lower))*(
		(1/Sc_1D_lower-2+Sc_1D_lower)*(AuxGrid_E[AbsorbIndexLower+2]+PreviousELower[0][0])
		+ 2*(Sc_1D_lower-1/Sc_1D_lower)*(PreviousELower[0][1]+PreviousELower[2][1]-AuxGrid_E[AbsorbIndexLower+1]-PreviousELower[1][0])
		- 4*(1/Sc_1D_lower+Sc_1D_lower)*PreviousELower[1][1]) - PreviousELower[2][0];

	//update the field history values
	//shift toward the future by one step
	//record the current values as history
	PreviousELower[0][0] = PreviousELower[0][1];
	PreviousELower[1][0] = PreviousELower[1][1];
	PreviousELower[2][0] = PreviousELower[2][1];
	PreviousELower[0][1] = AuxGrid_E[AbsorbIndexLower];
	PreviousELower[1][1] = AuxGrid_E[AbsorbIndexLower+1];
	PreviousELower[2][1] = AuxGrid_E[AbsorbIndexLower+2];
	//calculate the x,y,z components separately
	for(int i = AbsorbIndexLower; i <= AuxGridUpper; i++) {
		AuxGrid_Ex[i] = k_Ex*AuxGrid_E[i];
		AuxGrid_Ey[i] = k_Ey*AuxGrid_E[i];
		AuxGrid_Ez[i] = k_Ez*AuxGrid_E[i];
	}
}
void PlaneWaveTFSFFDTDCore::ApplyCorrectionE() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	class Grid grid = engine->GetGrid();

	//NOTE: If a TF/SF E-field position is included in the node, it must be updated,
	//whether or not it is at the boundary of the node. However, a TF/SF H-field position
	//at the boundary of the node (immediately outside the outer E-field shell of the node)
	//need not be updated, since it will soon be overwritten by the H-field from the next node.
	int i, j, k;
	double value;
	int n =  0;

	//Bottom face of the plane-wave source TF/SF box
	k=PWLowerZ;
	//Correct Ex
	for (i=TFSF_min_x;i<TFSF_max_x;i++) {
		for (j=TFSF_min_y;j<=TFSF_max_y;j++) {
			Hinc = IncidentHy(i,j,k-1,n);		//calculate incident Hy by projection
			value = engine->GetDx(i,j,k) +
					c_times_dt/grid.GetDz(k)*Hinc;
			engine->SetDx(i,j,k, value);
		}
	}

	//Correct Ey
	for (i=TFSF_min_x;i<=TFSF_max_x;i++) {
		for (j=TFSF_min_y;j<TFSF_max_y;j++) {
			Hinc = IncidentHx(i,j,k-1,n);		//calculate incident Hx by projection
			value = engine->GetDy(i,j,k) -
					c_times_dt/grid.GetDz(k)*Hinc;
			engine->SetDy(i,j,k, value);
		}
	}

	//Upper face of the plane-wave source TF/SF box
	k=PWUpperZ;
	//Correct Ex
	for (i=TFSF_min_x;i<TFSF_max_x;i++) {
		for (j=TFSF_min_y;j<=TFSF_max_y;j++) {
			Hinc = IncidentHy(i,j,k,n);		//calculate incident Hy by projection
			value = engine->GetDx(i,j,k) -
					c_times_dt/grid.GetDz(k)*Hinc;
			engine->SetDx(i,j,k, value);
		}
	}

	//Correct Ey
	for (i=TFSF_min_x;i<=TFSF_max_x;i++) {
		for (j=TFSF_min_y;j<TFSF_max_y;j++) {
			Hinc = IncidentHx(i,j,k,n);		//calculate incident Hx by projection
			value = engine->GetDy(i,j,k) +
					c_times_dt/grid.GetDz(k)*Hinc;
			engine->SetDy(i,j,k, value);
		}
	}

	//Back face of the plane-wave source TF/SF box
	i=PWBackX;
	//Correct Ey
	for (j=TFSF_min_y;j<TFSF_max_y;j++)	{
		for (k=TFSF_min_z;k<=TFSF_max_z;k++) {
			Hinc = IncidentHz(i-1,j,k,n);		//calculate incident Hz by projection
			value = engine->GetDy(i,j,k) +
					c_times_dt/grid.GetDx(i)*Hinc;
			engine->SetDy(i,j,k, value);
		}
	}

	//Correct Ez
	for (j=TFSF_min_y;j<=TFSF_max_y;j++) {
		for (k=TFSF_min_z;k<TFSF_max_z;k++) {
			Hinc = IncidentHy(i-1,j,k,n);		//calculate incident Hy by projection
			value = engine->GetDz(i,j,k) -
					c_times_dt/grid.GetDx(i)*Hinc;
			engine->SetDz(i,j,k, value);
		}
	}

	//Front face of the plane-wave source TF/SF box
	i=PWFrontX;
	//Correct Ey
	for (j=TFSF_min_y;j<TFSF_max_y;j++) {
		for (k=TFSF_min_z;k<=TFSF_max_z;k++) {
			Hinc = IncidentHz(i,j,k,n);		//calculate incident Hz by projection
			value = engine->GetDy(i,j,k) -
					c_times_dt/grid.GetDx(i)*Hinc;
			engine->SetDy(i,j,k, value);
		}
	}

	//Correct Ez
	for (j=TFSF_min_y;j<=TFSF_max_y;j++) {
		for (k=TFSF_min_z;k<TFSF_max_z;k++)	{
			Hinc = IncidentHy(i,j,k,n);		//calculate incident Hy by projection
			value = engine->GetDz(i,j,k) +
					c_times_dt/grid.GetDx(i)*Hinc;
			engine->SetDz(i,j,k, value);
		}
	}

	//Left face of the plane-wave source TF/SF box
	j=PWLeftY;
	//Correct Ex
	for (i=TFSF_min_x;i<TFSF_max_x;i++) {
		for (k=TFSF_min_z;k<=TFSF_max_z;k++) {
			Hinc = IncidentHz(i,j-1,k,n);		//calculate incident Hz by projection
			value = engine->GetDx(i,j,k) -
					c_times_dt/grid.GetDy(j)*Hinc;
			engine->SetDx(i,j,k, value);
		}
	}

	//Correct Ez
	for (i=TFSF_min_x;i<=TFSF_max_x;i++) {
		for (k=TFSF_min_z;k<TFSF_max_z;k++) {
			Hinc = IncidentHx(i,j-1,k,n);		//calculate incident Hx by projection
			value = engine->GetDz(i,j,k) +
					c_times_dt/grid.GetDy(j)*Hinc;
			engine->SetDz(i,j,k, value);
		}
	}

	//Right face of the plane-wave source TF/SF box
	j=PWRightY;
	//Correct Ex
	for (i=TFSF_min_x;i<TFSF_max_x;i++)	{
		for (k=TFSF_min_z;k<=TFSF_max_z;k++) {
			Hinc = IncidentHz(i,j,k,n);		//calculate incident Hz by projection
			value = engine->GetDx(i,j,k) +
					c_times_dt/grid.GetDy(j)*Hinc;
			engine->SetDx(i,j,k, value);
		}
	}

	//Correct Ez
	for (i=TFSF_min_x;i<=TFSF_max_x;i++) {
		for (k=TFSF_min_z;k<TFSF_max_z;k++) {
			Hinc = IncidentHx(i,j,k,n);		//calculate incident Hx by projection
			value = engine->GetDz(i,j,k) -
					c_times_dt/grid.GetDy(j)*Hinc;
			engine->SetDz(i,j,k, value);
		}
	}
}

void PlaneWaveTFSFFDTDCore::ApplyCorrectionH() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	class Grid grid = engine->GetGrid();

	int i, j, k;
	double value;
	int n = engine->GetCurrentInterationNumber();

	//Bottom face of the plane-wave source TF/SF box
	k=PWLowerZ-1;
	//Correct Hx
	for (i=TFSF_min_x;i<=TFSF_max_x;i++) {
		for (j=TFSF_min_y;j<TFSF_max_y;j++) {
			Einc = IncidentEy(i,j,k+1,n);		//calculate incident Ey by projection
			value = engine->GetHx(i,j,k) -
					c_times_dt/grid.GetDz(k)*Einc;
			engine->SetHx(i,j,k, value);

		}
	}
	//Correct Hy
	for (i=TFSF_min_x;i<TFSF_max_x;i++)	{
		for (j=TFSF_min_y;j<=TFSF_max_y;j++) {
			Einc = IncidentEx(i,j,k+1,n);		//calculate incident Ex by projection
			value = engine->GetHy(i,j,k) +
					c_times_dt/grid.GetDz(k)*Einc;
			engine->SetHy(i,j,k, value);
		}
	}

	//Upper face of the plane-wave source TF/SF box
	k=PWUpperZ;
	//Correct Hx
	for (i=TFSF_min_x;i<=TFSF_max_x;i++) {
		for (j=TFSF_min_y;j<TFSF_max_y;j++)	{
			Einc = IncidentEy(i,j,k,n);		//calculate incident Ey by projection
			value = engine->GetHx(i,j,k) +
					c_times_dt/grid.GetDz(k)*Einc;
			engine->SetHx(i,j,k, value);
		}
	}
	//Correct Hy
	for (i=TFSF_min_x;i<TFSF_max_x;i++)	{
		for (j=TFSF_min_y;j<=TFSF_max_y;j++) {
			Einc = IncidentEx(i,j,k,n);		//calculate incident Ex by projection
			value = engine->GetHy(i,j,k) -
					c_times_dt/grid.GetDz(k)*Einc;
			engine->SetHy(i,j,k, value);
		}
	}

	//Back face of the plane-wave source TF/SF box
	i=PWBackX-1;
	//Correct Hy
	for (j=TFSF_min_y;j<=TFSF_max_y;j++) {
		for (k=TFSF_min_z;k<TFSF_max_z;k++)	{
			Einc = IncidentEz(i+1,j,k,n);		//calculate incident Ez by projection
			value = engine->GetHy(i,j,k) -
					c_times_dt/grid.GetDx(i)*Einc;
			engine->SetHy(i,j,k, value);
		}
	}
	//Correct Hz
	for (j=TFSF_min_y;j<TFSF_max_y;j++)	{
		for (k=TFSF_min_z;k<=TFSF_max_z;k++) {
			Einc = IncidentEy(i+1,j,k,n);		//calculate incident Ey by projection
			value = engine->GetHz(i,j,k) +
					c_times_dt/grid.GetDx(i)*Einc;
			engine->SetHz(i,j,k, value);
		}
	}

	//Front face of the plane-wave source TF/SF box
	i=PWFrontX;
	//Correct Hy
	for (j=TFSF_min_y;j<=TFSF_max_y;j++) {
		for (k=TFSF_min_z;k<TFSF_max_z;k++)	{
			Einc = IncidentEz(i,j,k,n);		//calculate incident Ez by projection
			value = engine->GetHy(i,j,k) +
					c_times_dt/grid.GetDx(i)*Einc;
			engine->SetHy(i,j,k, value);
		}
	}
	//Correct Hz
	for (j=TFSF_min_y;j<TFSF_max_y;j++)	{
		for (k=TFSF_min_z;k<=TFSF_max_z;k++) {
			Einc = IncidentEy(i,j,k,n);		//calculate incident Ey by projection
			value = engine->GetHz(i,j,k) -
					c_times_dt/grid.GetDx(i)*Einc;
			engine->SetHz(i,j,k, value);
		}
	}

	//Left face of the plane-wave source TF/SF box
	j=PWLeftY-1;
	//Correct Hx
	for (i=TFSF_min_x;i<=TFSF_max_x;i++) {
		for (k=TFSF_min_z;k<TFSF_max_z;k++)	{
			Einc = IncidentEz(i,j+1,k,n);		//calculate incident Ez by projection
			value = engine->GetHx(i,j,k) +
					c_times_dt/grid.GetDy(j)*Einc;
			engine->SetHx(i,j,k, value);
		}
	}
	//Correct Hz
	for (i=TFSF_min_x;i<TFSF_max_x;i++)	{
		for (k=TFSF_min_z;k<=TFSF_max_z;k++) {
			Einc = IncidentEx(i,j+1,k,n);		//calculate incident Ex by projection
			value = engine->GetHz(i,j,k) -
					c_times_dt/grid.GetDy(j)*Einc;
			engine->SetHz(i,j,k, value);
		}
	}

	//Right face of the plane-wave source TF/SF box
	j=PWRightY;
	//Correct Hx
	for (i=TFSF_min_x;i<=TFSF_max_x;i++) {
		for (k=TFSF_min_z;k<TFSF_max_z;k++)	{
			Einc = IncidentEz(i,j,k,n);		//calculate incident Ez by projection
			value = engine->GetHx(i,j,k) -
					c_times_dt/grid.GetDy(j)*Einc;
			engine->SetHx(i,j,k, value);
		}
	}
	//Correct Hz
	for (i=TFSF_min_x;i<TFSF_max_x;i++)	{
		for (k=TFSF_min_z;k<=TFSF_max_z;k++) {
			Einc = IncidentEx(i,j,k,n);		//calculate incident Ex by projection
			value = engine->GetHz(i,j,k) +
					c_times_dt/grid.GetDy(j)*Einc;
			engine->SetHz(i,j,k, value);
		}
	}
}

//******************************************************************
//  PLANE-WAVE INCIDENCE IN LAYERED MEDIUM (PROJECTION ON 1-D GRID)
//******************************************************************
//These inline functions have to be in the same file as the functions
//(ApplyCorrectionE,H) from which they are called.
//---------------------------------------------------------------------------
inline double PlaneWaveTFSFFDTDCore::IncidentEx(const int& i, const int& j, const int& k, const int& n) {
	//projected position on the 1-D grid (note the conversion to 1-D grid cells)
	PositionOnAuxGrid = AuxGridUpper-(CoordinateOnAuxGrid_x_halfint[i] +
			CoordinateOnAuxGrid_y_fullint[j] + CoordinateOnAuxGrid_z_fullint[k]);
	IntegerPositionOnAuxGrid = int(PositionOnAuxGrid);
	a = PositionOnAuxGrid - IntegerPositionOnAuxGrid;
	return ((1-a)*AuxGrid_Ex[IntegerPositionOnAuxGrid] + a*AuxGrid_Ex[IntegerPositionOnAuxGrid+1]);
}

inline double PlaneWaveTFSFFDTDCore::IncidentEy(const int& i, const int& j, const int& k, const int& n) {
	//projected position on the 1-D grid (note the conversion to 1-D grid cells)
	PositionOnAuxGrid = AuxGridUpper-(CoordinateOnAuxGrid_x_fullint[i] +
			CoordinateOnAuxGrid_y_halfint[j] + CoordinateOnAuxGrid_z_fullint[k]);
	IntegerPositionOnAuxGrid = int(PositionOnAuxGrid);
	a = PositionOnAuxGrid - IntegerPositionOnAuxGrid;
	return ((1-a)*AuxGrid_Ey[IntegerPositionOnAuxGrid] + a*AuxGrid_Ey[IntegerPositionOnAuxGrid+1]);
}

inline double PlaneWaveTFSFFDTDCore::IncidentEz(const int& i, const int& j, const int& k, const int& n) {
	//projected position on the 1-D grid (note the conversion to 1-D grid cells)
	PositionOnAuxGrid = AuxGridUpper-(CoordinateOnAuxGrid_x_fullint[i] +
			CoordinateOnAuxGrid_y_fullint[j] + CoordinateOnAuxGrid_z_halfint[k]);
	IntegerPositionOnAuxGrid = int(PositionOnAuxGrid);
	a = PositionOnAuxGrid - IntegerPositionOnAuxGrid;
	return ((1-a)*AuxGrid_Ez[IntegerPositionOnAuxGrid] + a*AuxGrid_Ez[IntegerPositionOnAuxGrid+1]);
}

inline double PlaneWaveTFSFFDTDCore::IncidentHx(const int& i, const int& j, const int& k, const int& n) {
	//projected position on the 1-D grid (note the conversion to 1-D grid cells)
	PositionOnAuxGrid =AuxGridUpper-0.5-(CoordinateOnAuxGrid_x_fullint[i] +
			CoordinateOnAuxGrid_y_halfint[j] + CoordinateOnAuxGrid_z_halfint[k]);
	IntegerPositionOnAuxGrid = int(PositionOnAuxGrid);
	a = PositionOnAuxGrid - IntegerPositionOnAuxGrid;
	return ((1-a)*AuxGrid_Hx[IntegerPositionOnAuxGrid] + a*AuxGrid_Hx[IntegerPositionOnAuxGrid+1]);
}

inline double PlaneWaveTFSFFDTDCore::IncidentHy(const int& i, const int& j, const int& k, const int& n) {
	//projected position on the 1-D grid (note the conversion to 1-D grid cells)
	PositionOnAuxGrid = AuxGridUpper-0.5-(CoordinateOnAuxGrid_x_halfint[i] +
			CoordinateOnAuxGrid_y_fullint[j] + CoordinateOnAuxGrid_z_halfint[k]);
	IntegerPositionOnAuxGrid = int(PositionOnAuxGrid);
	a = PositionOnAuxGrid - IntegerPositionOnAuxGrid;
	return ((1-a)*AuxGrid_Hy[IntegerPositionOnAuxGrid] + a*AuxGrid_Hy[IntegerPositionOnAuxGrid+1]);
}

inline double PlaneWaveTFSFFDTDCore::IncidentHz(const int& i, const int& j, const int& k, const int& n) {
	//projected position on the 1-D grid (note the conversion to 1-D grid cells)
	PositionOnAuxGrid = AuxGridUpper-0.5-(CoordinateOnAuxGrid_x_halfint[i] +
				CoordinateOnAuxGrid_y_halfint[j] + CoordinateOnAuxGrid_z_fullint[k]);
	IntegerPositionOnAuxGrid = int(PositionOnAuxGrid);
	a = PositionOnAuxGrid - IntegerPositionOnAuxGrid;
	return ((1-a)*AuxGrid_Hz[IntegerPositionOnAuxGrid] + a*AuxGrid_Hz[IntegerPositionOnAuxGrid+1]);
}
