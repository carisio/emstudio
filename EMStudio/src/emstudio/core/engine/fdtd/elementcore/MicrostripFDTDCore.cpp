/*
 * MicrostripFDTDCore.cpp
 *
 *  Created on: 08/02/2012
 *      Author: Leandro
 */

#include "MicrostripFDTDCore.h"
#include "BoxFDTDCore.h"
#include "emstudio/gui/basetypes/Material.h"
#include "RectangularPECSheetFDTDCore.h"
#include "emstudio/gui/basetypes/GenericTable.h"
#include "emstudio/core/results/TableResult.h"
#include <iostream>
#include <complex>

using namespace::std;

#include "wx/log.h"

MicrostripFDTDCore::MicrostripFDTDCore() {

}

MicrostripFDTDCore::~MicrostripFDTDCore() {
}


ElementCoreSmartPointer MicrostripFDTDCore::NewElementCore() {
	return ElementCoreSmartPointer(new MicrostripFDTDCore);
}

/*
 * Observação: O método DoConfigure pode alterar a face do objeto para entrar na PML. Isso faz com que o projeto dê erro, pois o método FillDimensions implementado
 * em FDTDElementCore irá pesquisar as faces do objeto e retornar os pontos de máximos e mínimos de acordo com elas. Assim, a FDTDEngine irá verificar o retorno e
 * verá que, sempre que o box for casado com a PML, seu tamanho será estendido para dentro dela, gerando erro, pois a face sairá do grid.
 * Entretanto, o erro deve ser gerado apenas se o usuário digitar o box fora do grid. Por isso, é necessário alterar a implementação padrão do FillDimensions do Box
 * para retornar apenas o que o usuário digitou, e não a alteração feita do DoConfigure.
 */
bool MicrostripFDTDCore::FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	xmin = dto.GetX1();
	ymin = dto.GetY1();
	zmin = dto.GetZ1();
	xmax = dto.GetX2();
	ymax = dto.GetY2();
	zmax = dto.GetZ2();

	std::vector<pair<double, double> > portsCoordinates = dto.GetPorts().GetCoordinates();
	for (size_t i = 0; i < portsCoordinates.size(); i++) {
		xmin = portsCoordinates[i].first < xmin ? portsCoordinates[i].first : xmin;
		xmax = portsCoordinates[i].first > xmax ? portsCoordinates[i].first : xmax;
		ymin = portsCoordinates[i].second < ymin ? portsCoordinates[i].second : ymin;
		ymax = portsCoordinates[i].second > ymax ? portsCoordinates[i].second : ymax;
	}
	return true;
}
void MicrostripFDTDCore::DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr) {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	MicrostripDTO* microstripDTO = static_cast<MicrostripDTO*>(elementDTOSmartPtr.get());

	/*
	 * Dimensões do box, caso seja necessário alterá-lo em caso de estar casado com a PML
	 */
	double xmin = microstripDTO->GetX1();
	double ymin = microstripDTO->GetY1();
	double zmin = microstripDTO->GetZ1();
	double xmax = microstripDTO->GetX2();
	double ymax = microstripDTO->GetY2();
	double zmax = microstripDTO->GetZ2();
	bool matched = false;

	// Se o elemento estiver casado, altera ele
	if (microstripDTO->GetMatchWithPML().IsMatchedWithPML(xNeg)) {
		matched = true;
		xmin = engine->GetGrid().GetAccumulatedDx(0);
	}
	if (microstripDTO->GetMatchWithPML().IsMatchedWithPML(yNeg)) {
		matched = true;
		ymin = engine->GetGrid().GetAccumulatedDy(0);
	}
	if (microstripDTO->GetMatchWithPML().IsMatchedWithPML(zNeg)) {
		matched = true;
		zmin = engine->GetGrid().GetAccumulatedDz(0);
	}
	if (microstripDTO->GetMatchWithPML().IsMatchedWithPML(xPos)) {
		matched = true;
		xmax = engine->GetGrid().GetAccumulatedDx(engine->GetGrid().GetNxTOTAL()-1);
	}
	if (microstripDTO->GetMatchWithPML().IsMatchedWithPML(yPos)) {
		matched = true;
		ymax = engine->GetGrid().GetAccumulatedDy(engine->GetGrid().GetNyTOTAL()-1);
	}
	if (microstripDTO->GetMatchWithPML().IsMatchedWithPML(zPos)) {
		matched = true;
		zmax = engine->GetGrid().GetAccumulatedDz(engine->GetGrid().GetNzTOTAL()-1);
	}

	if (matched) {
		vector<Facet> facets;

		Facet f1;
		f1.Add(Rvector3(xmin, ymin, zmin));
		f1.Add(Rvector3(xmax,ymin,zmin));
		f1.Add(Rvector3(xmax,ymax,zmin));
		f1.Add(Rvector3(xmin,ymax,zmin));
		facets.push_back(f1);

		Facet f2;
		f2.Add(Rvector3(xmin, ymin, zmin));
		f2.Add(Rvector3(xmin,ymax,zmin));
		f2.Add(Rvector3(xmin,ymax,zmax));
		f2.Add(Rvector3(xmin,ymin,zmax));
		facets.push_back(f2);

		Facet f3;
		f3.Add(Rvector3(xmin, ymin, zmin));
		f3.Add(Rvector3(xmax,ymin,zmin));
		f3.Add(Rvector3(xmax,ymin,zmax));
		f3.Add(Rvector3(xmin,ymin,zmax));
		facets.push_back(f3);

		Facet f4;
		f4.Add(Rvector3(xmax, ymax, zmax));
		f4.Add(Rvector3(xmin,ymax,zmax));
		f4.Add(Rvector3(xmin,ymin,zmax));
		f4.Add(Rvector3(xmax,ymin,zmax));
		facets.push_back(f4);

		Facet f5;
		f5.Add(Rvector3(xmax, ymax, zmax));
		f5.Add(Rvector3(xmax,ymin,zmax));
		f5.Add(Rvector3(xmax,ymin,zmin));
		f5.Add(Rvector3(xmax,ymax,zmin));
		facets.push_back(f5);

		Facet f6;
		f6.Add(Rvector3(xmax, ymax, zmax));
		f6.Add(Rvector3(xmin,ymax,zmax));
		f6.Add(Rvector3(xmin,ymax,zmin));
		f6.Add(Rvector3(xmax,ymax,zmin));
		facets.push_back(f6);

		/*
		 * A partir de agora as faces contém o box até o último elemento do grid.
		 * Os elementos x1, y1, z1 e x2, y2 e z2 do DTO continuam com o que o usuário digitou.
		 */
		microstripDTO->SetFacets(facets);
	}

	dto = *microstripDTO;
}

bool MicrostripFDTDCore::IsElementConsistent() {
	bool elementOK = true;
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	/****************************************************************************/
	/* Se o box e a PEC embaixo do substrato for casado com a PML,              */
	/* tem q verificar se tem PML no grid e se o                                */
	/* box foi posicionado tal que a posição que o usuário digitou coincide com */
	/* a posição do grid. Ao verificar o box a PEC embaixo dele (se houver) já  */
	/* é verificada.                                                            */
	/* As verificações que estão aqui foram copiadas do BoxFDTDCore. Na prática,*/
	/* como o algoritmo sempre considera que a microfita está distribuída no    */
	/* plano z, não seria necessário verificar isso tudo. Entretanto, se        */
	/* futuramente essas funções forem implementadas, já está pronto.           */
	/****************************************************************************/
	if (dto.GetMatchWithPML().IsMatchedWithPML(xNeg)) {
		if (engine->GetFDTDDTO().GetXmin() != dto.GetX1()) {
			wxString errorMessage = "Lower boundary (X) of " + GetName() + " should be equal the lower boundary of the grid (X)";
			AppendErrorMessage(errorMessage);
			elementOK = false;
		}
		if (!(engine->GetFDTDDTO().GetABC().IsPML(xNeg))) {
			wxString errorMessage = GetName() + " cannot match with PML. Grid (-X) is ";
			errorMessage.Append(engine->GetFDTDDTO().GetABC().GetABCXNeg());
			AppendErrorMessage(errorMessage);
			elementOK = false;
		}
	}
	if (dto.GetMatchWithPML().IsMatchedWithPML(yNeg)) {
		if (engine->GetFDTDDTO().GetYmin() != dto.GetY1()) {
			wxString errorMessage = "Lower boundary (Y) of " + GetName() + " should be equal the lower boundary of the grid (Y)";
			AppendErrorMessage(errorMessage);
			elementOK = false;
		}
		if (!(engine->GetFDTDDTO().GetABC().IsPML(yNeg))) {
			wxString errorMessage = GetName() + " cannot match with PML. Grid (-Y) is ";
			errorMessage.Append(engine->GetFDTDDTO().GetABC().GetABCYNeg());
			AppendErrorMessage(errorMessage);
			elementOK = false;
		}
	}
	if (dto.GetMatchWithPML().IsMatchedWithPML(zNeg)) {
		if (engine->GetFDTDDTO().GetZmin() != dto.GetZ1()) {
			wxString errorMessage = "Lower boundary (Z) of " + GetName() + " should be equal the lower boundary of the grid (Z)";
			AppendErrorMessage(errorMessage);
			elementOK = false;
		}
		if (!(engine->GetFDTDDTO().GetABC().IsPML(zNeg))) {
			wxString errorMessage = GetName() + " cannot match with PML. Grid (-Z) is ";
			errorMessage.Append(engine->GetFDTDDTO().GetABC().GetABCZNeg());
			AppendErrorMessage(errorMessage);
			elementOK = false;
		}
	}
	if (dto.GetMatchWithPML().IsMatchedWithPML(xPos)) {
		if (engine->GetFDTDDTO().GetXmax() != dto.GetX2()) {
			wxString errorMessage = "Upper boundary (X) of " + GetName() + " should be equal the upper boundary of the grid (X)";
			AppendErrorMessage(errorMessage);
			elementOK = false;
		}
		if (!(engine->GetFDTDDTO().GetABC().IsPML(xPos))) {
			wxString errorMessage = GetName() + " cannot match with PML. Grid (+X) is ";
			errorMessage.Append(engine->GetFDTDDTO().GetABC().GetABCXPos());
			AppendErrorMessage(errorMessage);
			elementOK = false;
		}
	}
	if (dto.GetMatchWithPML().IsMatchedWithPML(yPos)) {
		if (engine->GetFDTDDTO().GetYmax() != dto.GetY2()) {
			wxString errorMessage = "Upper boundary (Y) of " + GetName() + " should be equal the upper boundary of the grid (Y)";
			AppendErrorMessage(errorMessage);
			elementOK = false;
		}
		if (!(engine->GetFDTDDTO().GetABC().IsPML(yPos))) {
			wxString errorMessage = GetName() + " cannot match with PML. Grid (+Y) is ";
			errorMessage.Append(engine->GetFDTDDTO().GetABC().GetABCYPos());
			AppendErrorMessage(errorMessage);
			elementOK = false;
		}
	}
	if (dto.GetMatchWithPML().IsMatchedWithPML(zPos)) {
		if (engine->GetFDTDDTO().GetZmax() != dto.GetZ2()) {
			wxString errorMessage = "Upper boundary (Z) of " + GetName() + " should be equal the upper boundary of the grid (Z)";
			AppendErrorMessage(errorMessage);
			elementOK = false;
		}
		if (!(engine->GetFDTDDTO().GetABC().IsPML(zPos))) {
			wxString errorMessage = GetName() + " cannot match with PML. Grid (+Z) is ";
			errorMessage.Append(engine->GetFDTDDTO().GetABC().GetABCZPos());
			AppendErrorMessage(errorMessage);
			elementOK = false;
		}
	}

	return elementOK;
}

void MicrostripFDTDCore::SimulationWillStart() {
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//////// INICIALIZA O BOX E AS PECS.
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	// Não é necessário fazer nada com o Box, já que é automático, usando faces.

	/////////////////////////////////////////////////////////////////////////////////////////////////
	/* Ao invés de fazer o cálculo da PEC , instancia uma PEC e deixa ela fazer o cálculo */
	Plane planeXY;
	planeXY.SetValue(XY);

	pecUnderSubstrateCore = ElementCoreSmartPointer(new RectangularPECSheetFDTDCore);
	lineCore = ElementCoreSmartPointer(new RectangularPECSheetFDTDCore);

	if (dto.IsPecUnderSubstrate()) {
		cout << "Tem PEC embaixo do substrato " << endl;

		RectangularPECSheetDTO* pecUSDTO = new RectangularPECSheetDTO;
		pecUSDTO->SetCutAtZ(true);
		pecUSDTO->SetCutAt(dto.GetZ1());
		pecUSDTO->SetX0(dto.GetX1());
		pecUSDTO->SetY0(dto.GetY1());
		pecUSDTO->SetX1(dto.GetX2());
		pecUSDTO->SetY1(dto.GetY2());
		pecUSDTO->SetMatchWithPML(dto.GetMatchWithPML());
		RectangularPECSheetFDTDCore* ptr = static_cast<RectangularPECSheetFDTDCore*>(pecUnderSubstrateCore.get());
		ptr->SetEngine(GetEngine());
		ptr->DoConfigure(ElementDTOSmartPointer(pecUSDTO));

		cout << "Coordenadas da PEC" << endl;
		cout << "Corte em z? " << pecUSDTO->IsCutAtZ() << "\t em: " << pecUSDTO->GetCutAt() << endl;
		cout << "x0" << pecUSDTO->GetX0() << "\t x1: " << pecUSDTO->GetX1() << endl;
		cout << "y0" << pecUSDTO->GetY0() << "\t y1: " << pecUSDTO->GetY1() << endl;
	}
	RectangularPECSheetDTO* linePECDTO = new RectangularPECSheetDTO;
	linePECDTO->SetCutAtZ(true);
	linePECDTO->SetCutAt(dto.GetZ2());
	linePECDTO->SetX0(dto.GetLinePositionX()-dto.GetLineWidth()/2);
	linePECDTO->SetY0(dto.GetY1());
	linePECDTO->SetX1(linePECDTO->GetX0() + dto.GetLineWidth());
	linePECDTO->SetY1(linePECDTO->GetY0() + dto.GetLineLength());
	// TODO: 29.09.2015: Até a versão atual não tinha o código abaixo. Não deveria ser colocado?
//	linePECDTO->SetMatchWithPML(dto.GetMatchWithPML());

	cout << "Coordenadas da lilnha" << endl;
	cout << "Corte em z? " << linePECDTO->IsCutAtZ() << "\t em: " << linePECDTO->GetCutAt() << endl;
	cout << "x0" << linePECDTO->GetX0() << "\t x1: " << linePECDTO->GetX1() << endl;
	cout << "y0" << linePECDTO->GetY0() << "\t y1: " << linePECDTO->GetY1() << endl;

	RectangularPECSheetFDTDCore* ptr = static_cast<RectangularPECSheetFDTDCore*>(lineCore.get());
	ptr->SetEngine(GetEngine());
	ptr->DoConfigure(ElementDTOSmartPointer(linePECDTO));

	if (dto.IsPecUnderSubstrate()) {
		RectangularPECSheetFDTDCore* ptrUnderSubstrate = static_cast<RectangularPECSheetFDTDCore*>(pecUnderSubstrateCore.get());
		ptrUnderSubstrate->SimulationWillStart();
	}
	ptr->SimulationWillStart();
	///////////////////////////////////////////////////////////////////////////////////////////////////////

	// Configura os índices da alimentação
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	Grid grid = engine->GetGrid();

	i1 = grid.GetXCell(dto.GetLinePositionX()-dto.GetLineWidth()/2);
	i2 = grid.GetXCell(dto.GetLinePositionX()+dto.GetLineWidth()/2);
	j1 = grid.GetYCell(dto.GetY1());
	j2 = grid.GetYCell(dto.GetY1());
	k1 = grid.GetZCell(dto.GetZ1());
	k2 = grid.GetZCell(dto.GetZ2());

	V = Array1D<double>(dto.GetLinePoints(),0.0);
	I = Array1D<double>(dto.GetLinePoints(),0.0);
	Voff = Array1D<double>(dto.GetLinePoints(),0.0);
	Ioff = Array1D<double>(dto.GetLinePoints(),0.0);

	int T = engine->GetTimeSteps();
	excitationValue = Array1D<double>(T,0.0);
	time = Array1D<double>(T,0.0);
	VOut = Array1D<double>(T,0.0);
	IOut = Array1D<double>(T,0.0);
	VInc = Array1D<double>(T,0.0);
	VRef = Array1D<double>(T,0.0);

	dx = grid.GetDx(i1);
	dy = grid.GetDy(j1);
	dz = grid.GetDz(k1);
	dl = grid.GetDy(j1);

	Z0 = dto.GetLineImpedance();
	double d = (k2-k1)*dz;
	double W = (i2-i1)*dx;
	double Eef = (dto.GetMaterial().GetEx()+1)/2 + (dto.GetMaterial().GetEx()-1)/2/sqrt(1+12*d/W);
	if(W/d <= 1.)
		Z0 = 60.*log(8.*d/W + W/4.*d)/sqrt(Eef);
	else
		Z0 = 120.*PI/sqrt(Eef)/(W/d + 1.393 + 0.667*log(W/d+1.444));

	c_times_dt = SPEED_OF_LIGHT_VACUUM * engine->GetDeltaT()/sqrt(Eef);

	int Nfreq = dto.GetNFrequency();
	RD1 = Array1D<double>(Nfreq,0.0);
	RD2 = Array1D<double>(Nfreq,0.0);
	VF1 = Array1D<double>(Nfreq,0.0);
	VF2 = Array1D<double>(Nfreq,0.0);
	IF1 = Array1D<double>(Nfreq,0.0);
	IF2 = Array1D<double>(Nfreq,0.0);
	VI1 = Array1D<double>(Nfreq,0.0);
	VI2 = Array1D<double>(Nfreq,0.0);
	VR1 = Array1D<double>(Nfreq,0.0);
	VR2 = Array1D<double>(Nfreq,0.0);

	Zout1 = Array1D<double>(Nfreq,0.0);
	Zout2 = Array1D<double>(Nfreq,0.0);
	VSWR = Array1D<double>(Nfreq,0.0);
	S11 = Array1D<double>(Nfreq,0.0);

	Sc_1D_lower = c_times_dt/dl;
	PreviousVLower = Array2D<double>(3,2, 0.0);
	PreviousVoffLower = Array2D<double>(3,2, 0.0);
	PreviousVoffUpper = Array2D<double>(3,2, 0.0);

	omega = Array1D<double>(Nfreq,0.0);
	frequency = Array1D<double>(Nfreq,0.0);
	double FInit = dto.GetInitialFrequency();
	double FStep = dto.GetFrequencyStep();

	for (int f = 0; f < Nfreq; f++) {
		frequency[f] = FInit + f*FStep;
		omega[f] = 2.0*PI*(FInit + f*FStep);
	}

	portsXYindex.clear();
	std::vector<pair<double, double> > portsCoordinates = dto.GetPorts().GetCoordinates();

	cout << "------------------------------------" << endl;
	cout << "Coordenadas das portas: " << endl;
	cout << "Total de portas: " << portsCoordinates.size() << endl;
	for (size_t i = 0; i < portsCoordinates.size(); i++) {
		portsXYindex.push_back(pair<int, int>(grid.GetXCell(portsCoordinates[i].first), grid.GetYCell(portsCoordinates[i].second)));
		cout << portsXYindex[i].first << "\t" << portsXYindex[i].second << endl;
	}
	cout << "------------------------------------" << endl;

	VPorts = Array2D<double>(portsXYindex.size(), T, 0.0);
	VPortsF1 = Array2D<double>(portsXYindex.size(), Nfreq,0.0);
	VPortsF2 = Array2D<double>(portsXYindex.size(), Nfreq,0.0);
	dto.GetExcitation().Init();
}
void MicrostripFDTDCore::DFieldsChanged(double t) {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	double S;
	int T = engine->GetCurrentInterationNumber();
	int linePoints = dto.GetLinePoints();
	int sourcePoints = dto.GetSourcePoint();
	S = dto.GetExcitation().GetExcitationValue(t);
	excitationValue[T] = S;

	for (int l = 1; l < linePoints; l++) {
		V[l] = V[l] - c_times_dt*Z0*(I[l]-I[l-1])/dl;
	}
	V[sourcePoints] = V[sourcePoints] - Z0*c_times_dt*(I[sourcePoints]-I[sourcePoints-1])/dl
			+ c_times_dt*S/dl;

	for (int l = 1; l < linePoints; l++)
	{
		Voff[l] = Voff[l] - Sc_1D_lower*Z0*(Ioff[l] - Ioff[l-1]);
	}
	Voff[sourcePoints] = Voff[sourcePoints] - Z0*Sc_1D_lower*(Ioff[sourcePoints]-Ioff[sourcePoints-1])
						+ Sc_1D_lower*S;

	//Apply 2nd order ABC
	//NOTE: PreviousELower(0,0) need not be used, since it is equal to AuxGrid_E(AbsorbIndexLower)
	//[before the update], but it is used for symmetry.
	//Lower absorbing point
	V[0] = (-1/(1/Sc_1D_lower+2+Sc_1D_lower))*((1/Sc_1D_lower-2+Sc_1D_lower)*(V[2]+PreviousVLower[0][0])
		    +2*(Sc_1D_lower-1/Sc_1D_lower)*(PreviousVLower[0][1]+PreviousVLower[2][1]-V[1]-PreviousVLower[1][0])
		    -4*(1/Sc_1D_lower+Sc_1D_lower)*PreviousVLower[1][1])-PreviousVLower[2][0];

	//update the field history values
	PreviousVLower[0][0] = PreviousVLower[0][1];
	PreviousVLower[1][0] = PreviousVLower[1][1];
	PreviousVLower[2][0] = PreviousVLower[2][1];
	PreviousVLower[0][1] = V[0];
	PreviousVLower[1][1] = V[1];
	PreviousVLower[2][1] = V[2];

	// Aply 2nd order ABC
	Voff[0] = (-1/(1/Sc_1D_lower+2+Sc_1D_lower))*(
		(1/Sc_1D_lower-2+Sc_1D_lower)*(Voff[2]+PreviousVoffLower[0][0])
		+ 2*(Sc_1D_lower-1/Sc_1D_lower)*(PreviousVoffLower[0][1]
		 +PreviousVoffLower[2][1]-Voff[1]-PreviousVoffLower[1][0])
		- 4*(1/Sc_1D_lower+Sc_1D_lower)*PreviousVoffLower[1][1]) - PreviousVoffLower[2][0];

	//update the field history values
	PreviousVoffLower[0][0] = PreviousVoffLower[0][1];
	PreviousVoffLower[1][0] = PreviousVoffLower[1][1];
	PreviousVoffLower[2][0] = PreviousVoffLower[2][1];
	PreviousVoffLower[0][1] = Voff[0];
	PreviousVoffLower[1][1] = Voff[1];
	PreviousVoffLower[2][1] = Voff[2];

	Voff[linePoints-1] = (-1/(1/Sc_1D_lower+2+Sc_1D_lower))*(
		(1/Sc_1D_lower-2+Sc_1D_lower)*(Voff[linePoints-3]+PreviousVoffUpper[0][0])

		+ 2*(Sc_1D_lower-1/Sc_1D_lower)*(PreviousVoffUpper[0][1]
		+PreviousVoffUpper[2][1]-Voff[linePoints-2]-PreviousVoffUpper[1][0])

		- 4*(1/Sc_1D_lower+Sc_1D_lower)*PreviousVoffUpper[1][1])

		- PreviousVoffUpper[2][0];

	//update the field history values
	PreviousVoffUpper[0][0] = PreviousVoffUpper[0][1];
	PreviousVoffUpper[1][0] = PreviousVoffUpper[1][1];
	PreviousVoffUpper[2][0] = PreviousVoffUpper[2][1];
	PreviousVoffUpper[0][1] = Voff[linePoints-1];
	PreviousVoffUpper[1][1] = Voff[linePoints-2];
	PreviousVoffUpper[2][1] = Voff[linePoints-3];

	VInc[T] = Voff[linePoints-1];
	VRef[T] = V[linePoints-1] - VInc[T];
	VOut[T] = V[linePoints-1];

	time[T] = t;

	for (int f = 0; f < dto.GetNFrequency(); f++) {
		RD1[f] = cos(-omega[f]*t);
		RD2[f] = sin(-omega[f]*t);
		VF1[f] += V[linePoints-1]*RD1[f];
		VF2[f] += V[linePoints-1]*RD2[f];
		VI1[f] += VInc[T]*RD1[f];
		VI2[f] += VInc[T]*RD2[f];
		VR1[f] += VRef[T]*RD1[f];
		VR2[f] += VRef[T]*RD2[f];
	}
}

void MicrostripFDTDCore::ElectricFieldsChanged(double t) {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	double value;
	int linePoints = dto.GetLinePoints();
	//	Campo E
	for(int i = i1; i <= i2; i++) {
		for(int k = k1; k < k2; k++) {
			value = V[linePoints-1]/engine->GetGrid().GetDz(k)/(k2-k1);
			engine->SetEz(i,j1,k, value);
		}
	}
	if (dto.IsPecUnderSubstrate()) {
		RectangularPECSheetFDTDCore* ptr = static_cast<RectangularPECSheetFDTDCore*>(pecUnderSubstrateCore.get());
		ptr->ElectricFieldsChanged(t);
	}
	RectangularPECSheetFDTDCore* ptr = static_cast<RectangularPECSheetFDTDCore*>(lineCore.get());
	ptr->ElectricFieldsChanged(t);

	int T = engine->GetCurrentInterationNumber();
	// IMPLEMENTAR PORTAS
	for (size_t nPorts = 0; nPorts < portsXYindex.size(); nPorts++) {
		int i = portsXYindex[nPorts].first;
		int j = portsXYindex[nPorts].second;
		for(int k = k1; k < k2; k++) {
			VPorts[nPorts][T] += engine->GetEz(i,j,k)*engine->GetGrid().GetDz(k); // Calcula tensão
		}
	}
	for (int f = 0; f < dto.GetNFrequency(); f++) {
		RD1[f] = cos(-omega[f]*t);
		RD2[f] = sin(-omega[f]*t);
		for (size_t nPorts = 0; nPorts < portsXYindex.size(); nPorts++) {
			VPortsF1[nPorts][f] += VPorts[nPorts][T]*RD1[f];
			VPortsF2[nPorts][f] += VPorts[nPorts][T]*RD2[f];
		}
	}
}

void MicrostripFDTDCore::MagneticFieldsChanged(double t) {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	Grid grid = engine->GetGrid();

	int T = engine->GetCurrentInterationNumber();
	int linePoints = dto.GetLinePoints();
	int sourcePoints = dto.GetSourcePoint();
	double S = dto.GetExcitation().GetExcitationValue(t);

	for (int l = 0; l < linePoints-1; l++) {
		I[l] = I[l] - c_times_dt*(V[l+1] - V[l])/dl/Z0;
		Ioff[l] = Ioff[l] - Sc_1D_lower*(Voff[l+1] - Voff[l])/Z0;
	}
	I[sourcePoints] = I[sourcePoints] - c_times_dt*(V[sourcePoints+1] - V[sourcePoints])/dl/Z0
			+ c_times_dt*S/Z0/dl;

	Ioff[sourcePoints] = Ioff[sourcePoints] - Sc_1D_lower*(Voff[sourcePoints+1] - Voff[sourcePoints])/Z0
			+ Sc_1D_lower*S/Z0;

	I[linePoints-1] = 0.;
	//Acoplamento 3D -> 1D
	// CÓDIGO ABAIXO FUNCIONA APENAS PARA PLANO XY!
	for (int i = i1; i < i2; i++)
		I[linePoints-1] += grid.GetDx(i)*engine->GetHx(i, j1, k2-1);

	I[linePoints-1] += grid.GetDx(i2)*engine->GetHx(i2, j1, k2-1)/2;

	for (int i = i1; i < i2; i++)
		I[linePoints-1] -= grid.GetDx(i)*engine->GetHx(i, j1-1, k2-1);

	I[linePoints-1] -= grid.GetDx(i2)*engine->GetHx(i2, j1-1, k2-1)/2;
	I[linePoints-1] += grid.GetDy(j1)*(engine->GetHy(i1-1, j1, k2-1)-engine->GetHy(i2, j1, k2-1));

	I[linePoints-1] = I[linePoints-1]/ETA0;
	IOut[T] = I[linePoints-1];

	for (int f = 0; f < dto.GetNFrequency(); f++) {
    	RD1[f] = cos(-omega[f]*t);
    	RD2[f] = sin(-omega[f]*t);
    	IF1[f] += I[linePoints-1]*RD1[f];
    	IF2[f] += I[linePoints-1]*RD2[f];
    }
}


void MicrostripFDTDCore::SimulationWillFinish() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	int Nfreq = dto.GetNFrequency();
	std::complex<double> Vf, Vi, Vr;
	std::complex<double> If;
	std::complex<double> Zf;
	std::complex<double> ejkt;
	double  s11;

	for (int f = 0; f < Nfreq; f++) {
		Vf = std::complex<double>(VF1[f],VF2[f]);
		If = std::complex<double>(IF1[f],IF2[f]);
		Vi = std::complex<double>(VI1[f],VI2[f]);
		Vr = std::complex<double>(VR1[f],VR2[f]);

		//correção no coeficiente de reflexão para a entrada da antena
		//ejkt = polar<double>(1, -omega[f]*engine->GetDeltaT());

		Zf = Vf/If;
		Zout1[f] = real(Zf);
		Zout2[f] = imag(Zf);

		s11 = abs(Vr/Vi);
		if (s11 < 1e-5) s11 = 1e-5;
		S11[f] = 20*log10(s11);
		VSWR[f] = (1. + s11)/(1. - s11);

//		s21 = abs(Vp/Vi);
//		if (s21 < 1e-5) s21 = 1e-5;
//			S21[f] = 20*log10(s21);

//		Pin[f] = (real(Vf)*real(If)+imag(Vf)*imag(If))/2.;
	}

}

bool MicrostripFDTDCore::HasResults() {
	return true;
}

ElementResults MicrostripFDTDCore::GetElementsResults() {

	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	int steps = engine->GetTimeSteps();
	int NFreq = dto.GetNFrequency();

	/* Pega o rótulo para as variáveis de tempo e frequência, e seu multiplicador */
	wxString normalized_time_label = engine->GetUnits()->GetUserDefinedTimeUnit().first;
	double normalized_time_factor = engine->GetUnits()->GetUserDefinedTimeUnit().second;
	wxString normalized_frequency_label = engine->GetUnits()->GetUserDefinedFrequencyUnit().first;
	double normalized_frequency_factor = engine->GetUnits()->GetUserDefinedFrequencyUnit().second;

	/* Colunas */
	GenericTable::ColumnDataRepresentation timeData;
	GenericTable::ColumnDataRepresentation frequencyData;
	GenericTable::ColumnDataRepresentation vData;
	GenericTable::ColumnDataRepresentation iData;
	GenericTable::ColumnDataRepresentation zrData;
	GenericTable::ColumnDataRepresentation ziData;
	GenericTable::ColumnDataRepresentation s11Data;
	GenericTable::ColumnDataRepresentation vswrData;
	std::vector<GenericTable::ColumnDataRepresentation> portsData;
	GenericTable::ColumnDataRepresentation excitationData;

	// Preenche portsData com nPorts de GenericTable::ColumnDataRepresentation vazios
	for (size_t nPorts = 0; nPorts < portsXYindex.size(); nPorts++) {
		GenericTable::ColumnDataRepresentation portN;
		portsData.push_back(portN);
	}

	/* Monta a tabela */
	for (int T = 0; T < steps; T++) {
		timeData.push_back(time[T]/normalized_time_factor);
		vData.push_back(VOut[T]);
		iData.push_back(IOut[T]*1000);
		excitationData.push_back(excitationValue[T]);
	}

	for (int f = 0; f < NFreq; f++) {
		frequencyData.push_back(frequency[f]/normalized_frequency_factor);
		zrData.push_back(Zout1[f]);
		ziData.push_back(Zout2[f]);
		s11Data.push_back(S11[f]);
		vswrData.push_back(VSWR[f]);

		for (size_t nPorts = 0; nPorts < portsXYindex.size(); nPorts++) {
			std::complex<double> Vn = std::complex<double>(VPortsF1[nPorts][f],VPortsF2[nPorts][f]);
			std::complex<double> V1 = std::complex<double>(VI1[f],VI2[f]);

			double sn1 = abs(Vn)/abs(V1);
			if (sn1 < 1e-5) sn1 = 1e-5;
			portsData[nPorts].push_back(20*log10(sn1));
		}

	}
	/* Cria as tabelas e adiciona os dados */
	GenericTable vTable;
	GenericTable iTable;
	GenericTable zTable;
	GenericTable s11Table;
	GenericTable vswrTable;
	GenericTable excitationTable;

	vTable.AddColumn(timeData);
	vTable.AddColumn(vData);

	iTable.AddColumn(timeData);
	iTable.AddColumn(iData);

	zTable.AddColumn(frequencyData);
	zTable.AddColumn(zrData);
	zTable.AddColumn(ziData);

	s11Table.AddColumn(frequencyData);
	s11Table.AddColumn(s11Data);

	vswrTable.AddColumn(frequencyData);
	vswrTable.AddColumn(vswrData);

	excitationTable.AddColumn(timeData);
	excitationTable.AddColumn(excitationData);

	BoolWrapper canBeInterpretedAsChart;
	canBeInterpretedAsChart.SetValue(true);

	/* Adiciona o rótulo das colunas das tabelas */
	wxString timeColumnLabel("Time (");
	timeColumnLabel.Append(normalized_time_label).Append(")");
	wxString frequencyColumnLabel("Frequency (");
	frequencyColumnLabel.Append(normalized_frequency_label).Append(")");

	vector<wxString> outputVoltageColunsLabel;
	outputVoltageColunsLabel.push_back(timeColumnLabel);
	outputVoltageColunsLabel.push_back("Voltage (V)");
	vTable.SetColumnsLabel(outputVoltageColunsLabel);

	vector<wxString> outputCurrentColunsLabel;
	outputCurrentColunsLabel.push_back(timeColumnLabel);
	outputCurrentColunsLabel.push_back("Current (mA)");
	iTable.SetColumnsLabel(outputCurrentColunsLabel);

	vector<wxString> impedanceColunsLabel;
	impedanceColunsLabel.push_back(frequencyColumnLabel);
	impedanceColunsLabel.push_back("Impedance - real (ohms)");
	impedanceColunsLabel.push_back("Impedance - imaginary (ohms)");
	zTable.SetColumnsLabel(impedanceColunsLabel);

	vector<wxString> s11ColumnsLabel;
	s11ColumnsLabel.push_back(frequencyColumnLabel);
	s11ColumnsLabel.push_back("S11 (dB)");
	s11Table.SetColumnsLabel(s11ColumnsLabel);

	vector<wxString> vswrColumnsLabel;
	vswrColumnsLabel.push_back(frequencyColumnLabel);
	vswrColumnsLabel.push_back("VSWR");
	vswrTable.SetColumnsLabel(vswrColumnsLabel);

	vector<wxString> excitationColumnsLabel;
	excitationColumnsLabel.push_back(timeColumnLabel);
	excitationColumnsLabel.push_back("Excitation value");
	excitationTable.SetColumnsLabel(excitationColumnsLabel);

	list<ResultSmartPointer> result;
	result.push_back(ResultSmartPointer(new TableResult("Output voltage", vTable, canBeInterpretedAsChart)));
	result.push_back(ResultSmartPointer(new TableResult("Output current", iTable, canBeInterpretedAsChart)));
	result.push_back(ResultSmartPointer(new TableResult("Impedance", zTable, canBeInterpretedAsChart)));
	result.push_back(ResultSmartPointer(new TableResult("VSWR", vswrTable, canBeInterpretedAsChart)));
	result.push_back(ResultSmartPointer(new TableResult("S11", s11Table, canBeInterpretedAsChart)));
	result.push_back(ResultSmartPointer(new TableResult("Excitation", excitationTable, canBeInterpretedAsChart)));

	/* Adiciona as portas */
	for (size_t nPorts = 0; nPorts < portsXYindex.size(); nPorts++) {
		// A porta começa do número 2
		wxString Sn1Label = "S"; Sn1Label.Append(Converter::IntToFormattedString(nPorts+2)).Append("1");
		wxString Sn1LabelDb = Sn1Label;  Sn1LabelDb.Append(" (dB)");
		GenericTable Sn1Table;
		Sn1Table.AddColumn(frequencyData);
		Sn1Table.AddColumn(portsData[nPorts]);

		vector<wxString> sn1ColumnsLabel;
		sn1ColumnsLabel.push_back(frequencyColumnLabel);
		sn1ColumnsLabel.push_back(Sn1LabelDb);
		Sn1Table.SetColumnsLabel(sn1ColumnsLabel);

		result.push_back(ResultSmartPointer(new TableResult(Sn1Label, Sn1Table, canBeInterpretedAsChart)));
	}

	return ElementResults(dto.GetDTOClassName(), dto.GetName(), result);
}
