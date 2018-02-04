/*
 * RectangularSheetFDTDCore.cpp
 *
 *  Created on: 21/12/2011
 *      Author: leandrocarisio
 */

#include "RectangularPECSheetFDTDCore.h"
#include "emstudio/util/constants/Constants.h"

RectangularPECSheetFDTDCore::RectangularPECSheetFDTDCore() {

}

RectangularPECSheetFDTDCore::~RectangularPECSheetFDTDCore() {
}

ElementCoreSmartPointer RectangularPECSheetFDTDCore::NewElementCore() {
	return ElementCoreSmartPointer(new RectangularPECSheetFDTDCore);
}

void RectangularPECSheetFDTDCore::DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr) {
	RectangularPECSheetDTO* rectangularSheetFDTD = static_cast<RectangularPECSheetDTO*>(elementDTOSmartPtr.get());
	dto = *rectangularSheetFDTD;

	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	class Grid grid = engine->GetGrid();
}

bool RectangularPECSheetFDTDCore::FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	xmin = dto.GetX0();
	ymin = dto.GetY0();
	zmin = dto.GetZ0();
	xmax = dto.GetX1();
	ymax = dto.GetY1();
	zmax = dto.GetZ1();

	return true;
}

void RectangularPECSheetFDTDCore::ElectricFieldsChanged(double t) {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	if (dto.IsCutAtZ()) {
		for (int i = imin; i < imax; i++) {
			for (int j = jmin; j <= jmax; j++) {
				engine->SetEx(i,j,kmin,0);
			}
		}
		for (int i = imin; i <= imax; i++) {
			for (int j = jmin; j < jmax; j++) {
				engine->SetEy(i,j,kmin,0);
			}
		}

	} else if (dto.IsCutAtX()) {
		for (int j = jmin; j < jmax; j++) {
			for (int k = kmin; k <= kmax; k++) {
				engine->SetEy(imin,j,k,0);
			}
		}
		for (int j = jmin; j <= jmax; j++) {
			for (int k = kmin; k < kmax; k++) {
				engine->SetEz(imin,j,k,0);
			}
		}

	} else if (dto.IsCutAtY()) {
		for (int i = imin; i < imax; i++) {
			for (int k = kmin; k <= kmax; k++) {
				engine->SetEx(i,jmin,k,0);
			}
		}
		for (int i = imin; i <= imax; i++) {
			for (int k = kmin; k < kmax; k++) {
				engine->SetEz(i,jmin,k,0);
			}
		}
	}
}

void RectangularPECSheetFDTDCore::SimulationWillStart() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	class Grid grid = engine->GetGrid();

	if (dto.IsCutAtZ()) {
		double xmin = dto.GetX0();
		double ymin = dto.GetY0();
		double zmin = dto.GetCutAt();
		double xmax = dto.GetX1();
		double ymax = dto.GetY1();

		imin = grid.GetXCell(xmin);
		imax = grid.GetXCell(xmax);
		jmin = grid.GetYCell(ymin);
		jmax = grid.GetYCell(ymax);
		kmin = grid.GetZCell(zmin);
		kmax = grid.GetZCell(zmin);

		if (dto.GetMatchWithPML().IsMatchedWithPML(xNeg)) {
			imin = 0;
		}
		if (dto.GetMatchWithPML().IsMatchedWithPML(xPos)) {
			imax = grid.GetNxTOTAL()-1;
		}
		if (dto.GetMatchWithPML().IsMatchedWithPML(yNeg)) {
			jmin = 0;
		}
		if (dto.GetMatchWithPML().IsMatchedWithPML(yPos)) {
			jmax = grid.GetNyTOTAL()-1;
		}

	} else if (dto.IsCutAtX()) {
		double ymin = dto.GetY0();
		double zmin = dto.GetZ0();
		double xmin = dto.GetCutAt();
		double ymax = dto.GetY1();
		double zmax = dto.GetZ1();

		imin = grid.GetXCell(xmin);
		imax = grid.GetXCell(xmin);
		jmin = grid.GetYCell(ymin);
		jmax = grid.GetYCell(ymax);
		kmin = grid.GetZCell(zmin);
		kmax = grid.GetZCell(zmax);

		if (dto.GetMatchWithPML().IsMatchedWithPML(yNeg)) {
			jmin = 0;
		}
		if (dto.GetMatchWithPML().IsMatchedWithPML(yPos)) {
			jmax = grid.GetNyTOTAL()-1;
		}
		if (dto.GetMatchWithPML().IsMatchedWithPML(zNeg)) {
			kmin = 0;
		}
		if (dto.GetMatchWithPML().IsMatchedWithPML(zPos)) {
			kmax = grid.GetNzTOTAL()-1;
		}
	} else if (dto.IsCutAtY()) {
		double xmin = dto.GetX0();
		double zmin = dto.GetZ0();
		double ymin = dto.GetCutAt();
		double xmax = dto.GetX1();
		double zmax = dto.GetZ1();

		imin = grid.GetXCell(xmin);
		imax = grid.GetXCell(xmax);
		jmin = grid.GetYCell(ymin);
		jmax = grid.GetYCell(ymin);
		kmin = grid.GetZCell(zmin);
		kmax = grid.GetZCell(zmax);

		if (dto.GetMatchWithPML().IsMatchedWithPML(xNeg)) {
			imin = 0;
		}
		if (dto.GetMatchWithPML().IsMatchedWithPML(xPos)) {
			imax = grid.GetNxTOTAL()-1;
		}
		if (dto.GetMatchWithPML().IsMatchedWithPML(zNeg)) {
			kmin = 0;
		}
		if (dto.GetMatchWithPML().IsMatchedWithPML(zPos)) {
			kmax = grid.GetNzTOTAL()-1;
		}
	}

	cout << "SWS ------------------" << endl;
	cout << "PECSheetFDTDCore" << endl;
	cout << "imin = " << imin << endl;
	cout << "jmin = " << jmin << endl;
	cout << "kmin = " << kmin << endl;
	cout << "imax = " << imax << endl;
	cout << "jmax = " << jmax << endl;
	cout << "kmax = " << kmax << endl;
	cout << "------------------" << endl;
}

bool RectangularPECSheetFDTDCore::IsElementConsistent() {
	bool elementOK = true;
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	/****************************************************************************/
	/* Se o box for casado com a PML, tem q verificar se tem PML no grid e se o */
	/* box foi posicionado tal que a posição que o usuário digitou coincide com */
	/* a posição do grid.                                                       */
	/****************************************************************************/
	// Se o elemento estiver casado, altera ele
	if (dto.GetMatchWithPML().IsMatchedWithPML(xNeg)) {
		if (engine->GetFDTDDTO().GetXmin() != dto.GetX0()) {
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
		if (engine->GetFDTDDTO().GetYmin() != dto.GetY0()) {
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
		if (engine->GetFDTDDTO().GetZmin() != dto.GetZ0()) {
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
		if (engine->GetFDTDDTO().GetXmax() != dto.GetX1()) {
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
		if (engine->GetFDTDDTO().GetYmax() != dto.GetY1()) {
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
		if (engine->GetFDTDDTO().GetZmax() != dto.GetZ1()) {
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
