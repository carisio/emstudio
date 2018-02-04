/*
 * PlaneWaveTFSFFDTDCore.h
 *
 *  Created on: 27/03/2013
 *      Author: Leandro
 */

#ifndef PLANEWAVETFSFFDTDCORE_H_
#define PLANEWAVETFSFFDTDCORE_H_


#include <complex>
#include "emstudio/core/engine/fdtd/FDTDEngine.h"
#include "emstudio/gui/basetypes/Orientation.h"
#include "emstudio/gui/basetypes/Excitation.h"
#include "FDTDElementCore.h"
#include "emstudio/util/constants/Constants.h"
#include "emstudio/core/ElementCore.h"
#include "emstudio/util/tnt/tnt.h"
#include "emstudio/util/file/FileManager.h"
#include "emstudio/util/vector/Rvector3.h"
#include "emstudio/dto/fdtdapp/PlaneWaveDTO.h"
#include "wx/wx.h"

class PlaneWaveTFSFFDTDCore  : public FDTDElementCore {
private:
	PlaneWaveDTO dto;

	double dt;
	double c_times_dt;
	double c_space;
	double Z_space;


	/* unit vectors that point in the direction of incident E and H */
	Array1D<double> k_E,k_H;
	/* components of the above unit vectors */
	double k_Ex,k_Ey,k_Ez,k_Hx,k_Hy,k_Hz;

	double Hinc, Einc;	//temporary incident field values

	/* incident field information */
	double THETA_INC, PHI_INC;		//direction of the incident field (z-component always downward-directed)
	double SinT,CosT,SinP,CosP,SinPsi,CosPsi;	//necessary sines and cosines
	/*
	 * (for LP incident field, if applicable) angle of linearly polarized incident electric field w.r.t.
	 * (k_inc)x(z) in clockwise direction (k_inc points away from the clock surface)
	 */
	double PSI;

	/* unit vector in the direction of incidence */
	Array1D<double> k_inc;
	/* lateral unit vector in the direction of incidence */
	Array1D<double> k_inc_lateral;
	double k_inc_x,k_inc_y,k_inc_z;	//x,y,z components of k_inc

	//grid spacing for the 1-D auxiliary grid (different from the 3-D grid)
	//found using the matched numerical dispersion (MND) method (approximate version - 5.69 in Taflove 2005)
	double dx;
	double dx_g;
	double dx_over_dx_g;	//ratio of dx to dx_g

	/* length of the 1-D grid (in grid cells)*/
	int AuxGridLength;
	/* limits of the 1-D grid (indices of the outermost grid cells) */
	int AuxGridLower,AuxGridUpper;

	/* Indices of the cells right inside the plane-wave boundary */
	int PWBackX,PWFrontX,PWLeftY,PWRightY,PWLowerZ,PWUpperZ;
	//Minimum and maximum indices cells contained in the TFSF box and in the current node
	int TFSF_min_x,TFSF_max_x,TFSF_min_y,TFSF_max_y,TFSF_min_z,TFSF_max_z;

	/* extra cells at the top and bottom of the 1-D grid (since H-field positions are 1/2 cell outside the TF/SF box) */
	int extra_top,extra_bottom;	//in 1-D grid cells (dx_g)
	Array1D<double> extra_distance;	//vectorial position of the final E-field position on the 1-D grid,
									//measured from the corner of the TF/SF box in 3-D grid cells (dx)
									//note the conversion factor dx_over_dx_g to convert from 1-D grid cells to 3-D grid cells

	int HardSourcePoint,AbsorbIndexLower;	//hard-source point and lower absorbing point for the plane wave in 1-D grid

	// TODO: O COMENTÁRIO FALA QUE A COMPONENTE Z É FIXA, MAS NÃO ESTÁ ASSIM NA INICIALIZAÇÃO.
	Array1D<double> PWOriginationPoint;	//coordinates of the point that the plane wave originates from
							//(measured from the back-left-bottom point of the grid)
							//(not the same as PWContactPoint, since the z component of PWOriginationPoint is fixed)
	double PWOriginationPoint_x,PWOriginationPoint_y,PWOriginationPoint_z;	//x,y,z components of k_inc

	//aux-grid-coordinate contributions at different x,y,and z positions
	//these are pre-computed arrays for the efficient projection on the 1-D auxiliary grid
	Array1D<double> CoordinateOnAuxGrid_x_fullint,CoordinateOnAuxGrid_y_fullint,CoordinateOnAuxGrid_z_fullint,
	 				CoordinateOnAuxGrid_x_halfint,CoordinateOnAuxGrid_y_halfint,CoordinateOnAuxGrid_z_halfint;

	//update coefficients for E and H updates
	double Ca,Cb,Da,Db;

	//1-D grids for incident field calculation
	Array1D<double> AuxGrid_E;		//E-field
	Array1D<double> AuxGrid_H;		//H-field
	Array1D<double> AuxGrid_Ex,AuxGrid_Ey,AuxGrid_Ez;	//components of the E-field
	Array1D<double> AuxGrid_Hx,AuxGrid_Hy,AuxGrid_Hz;	//components of the H-field

	double PositionOnAuxGrid,Einc_interp,Hinc_interp;	//intermediate values during incident field calculation
	int IntegerPositionOnAuxGrid;	//integer position on the 1-D grid = int(PositionOnAuxGrid). Always use this instead of using int(PositionOnAuxGrid) everywhere, because if PositionOnAuxGrid is infinitesimally smaller than an integer, int(PositionOnAuxGrid) might yield DIFFERENT results depending on where it is used (for example, if int(PositionOnAuxGrid) is passed as an index parameter to a Blitz++ array, the result is sometimes 1 larger than the correct answer - this has been observed in Linux builds, not in VS2005)

	double a;	//interpolation parameter

	// TODO: PRA QUE Sc_1D_upper?
	Array2D<double> PreviousELower;	//lower storage values for the 2nd-order ABC used in the 1-D grid (1st dimension: upward on the auxiliary grid, 2nd dimension: backward in time)
	double Sc_1D_upper,Sc_1D_lower;	//effective courant numbers for the 1-D grid


	// TODO: PARECE QUE TEM UMA DEFINIÇÃO DE UNIT_Z QUE NÃO É UTILIZADA

private:
	//Auxiliary grid updates
	void UpdateIncidentE(const int& n);
	void UpdateIncidentH(const int& n);

	void UpdateE(const int& n);	//update incident E field at time index n
	void UpdateH(const int& n);	//update incident H field at time index n

	//Given the coordinates of the field component on the TF/SF boundary, the functions below calculate the incident field by projection onto the 1-D grid
	inline double IncidentHx(const int& i, const int& j, const int& k, const int& n);
	inline double IncidentHy(const int& i, const int& j, const int& k, const int& n);
	inline double IncidentHz(const int& i, const int& j, const int& k, const int& n);
	inline double IncidentEx(const int& i, const int& j, const int& k, const int& n);
	inline double IncidentEy(const int& i, const int& j, const int& k, const int& n);
	inline double IncidentEz(const int& i, const int& j, const int& k, const int& n);

	//These methods apply field corrections in the main grid (by projection onto the auxiliary grid or any other method)
	void ApplyCorrectionE();
	void ApplyCorrectionH();

public:
	PlaneWaveTFSFFDTDCore();

	virtual ElementCoreSmartPointer NewElementCore();
	virtual void DoConfigure(ElementDTOSmartPointer dto);

	virtual bool FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);

	virtual void SimulationWillStart();
	virtual void DFieldsChanged(double t);
	virtual void MagneticFieldsChanged(double t);
	virtual void SimulationWillFinish();

	virtual ~PlaneWaveTFSFFDTDCore();
};

#endif /* PLANEWAVETFSFFDTDCORE_H_ */
