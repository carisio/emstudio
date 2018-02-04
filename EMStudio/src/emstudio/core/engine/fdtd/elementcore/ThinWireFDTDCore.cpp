/*
 * ThinWireFDTDCore.cpp
 *
 *  Created on: 07/11/2011
 *      Author: leandrocarisio
 */

#include "ThinWireFDTDCore.h"

ThinWireFDTDCore::ThinWireFDTDCore() {
}

ThinWireFDTDCore::~ThinWireFDTDCore() {
}

ElementCoreSmartPointer ThinWireFDTDCore::NewElementCore() {
	return ElementCoreSmartPointer(new ThinWireFDTDCore);
}

void ThinWireFDTDCore::DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr) {
	ThinWireDTO* thinWireDTO = static_cast<ThinWireDTO*>(elementDTOSmartPtr.get());

	dto = *thinWireDTO;
}

void ThinWireFDTDCore::SimulationWillStart() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	XCell = engine->GetGrid().GetXCell(dto.GetX());
	YCell = engine->GetGrid().GetYCell(dto.GetY());
	ZCell = engine->GetGrid().GetZCell(dto.GetZ());
	int initCell = 0;

	switch(dto.GetOrientation().GetValue()) {

	case (X):
		LengthCell = engine->GetGrid().GetXCell(dto.GetX() + dto.GetLength());
		initCell = XCell;
		break;

	case (Y):
		LengthCell = engine->GetGrid().GetYCell(dto.GetY() + dto.GetLength());
		initCell = YCell;
		break;

	case (Z):
		LengthCell = engine->GetGrid().GetZCell(dto.GetZ() + dto.GetLength());
		initCell = ZCell;
		break;
	}

	HLeft   = Array1D<double>(LengthCell-initCell+1,0.0);
	HRight  = Array1D<double>(LengthCell-initCell+1,0.0);
	HFront  = Array1D<double>(LengthCell-initCell+1,0.0);
	HBottom = Array1D<double>(LengthCell-initCell+1,0.0);

	c_times_dt = SPEED_OF_LIGHT_VACUUM * engine->GetDeltaT();
}
void ThinWireFDTDCore::ElectricFieldsChanged(double t) {
	// Modelamento do Fio

	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	switch(dto.GetOrientation().GetValue()) {
	case (X):
		for(int x = XCell; x < LengthCell; x++)
			engine->SetEx(x, YCell, ZCell, 0.0);
		break;

	case (Y):
		for(int y = YCell; y < LengthCell; y++)
			engine->SetEy(XCell, y, ZCell, 0.0);
		break;

	case (Z):
		for(int z = ZCell; z < LengthCell; z++)
			engine->SetEz(XCell, YCell, z, 0.0);
		break;
	}

}

void ThinWireFDTDCore::MagneticFieldsChanged(double t) {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	double value;

	if(dto.GetOrientation().GetValue() == Z) {
		for (int k = ZCell; k < LengthCell; k++)
		{
			value = HRight[k-ZCell] - c_times_dt/engine->GetGrid().GetDz(k)*
					(engine->GetEx(XCell, YCell, k+1) -
					 engine->GetEx(XCell, YCell, k))
					 + c_times_dt/engine->GetGrid().GetDx(XCell)*2/
					   log(engine->GetGrid().GetDx(XCell)/dto.GetRadius())*
					   engine->GetEz(XCell+1, YCell, k);
			engine->SetHy(XCell, YCell, k, value);

			value = HLeft[k-ZCell] - c_times_dt/engine->GetGrid().GetDz(k)*
					(engine->GetEx(XCell-1, YCell, k+1) -
					engine->GetEx(XCell-1, YCell, k))
					 - c_times_dt/engine->GetGrid().GetDx(XCell-1)*2/
					 log(engine->GetGrid().GetDx(XCell-1)/dto.GetRadius())*
					 engine->GetEz(XCell-1, YCell, k);
			engine->SetHy(XCell-1, YCell, k, value);

			value = HFront[k-ZCell] + c_times_dt/engine->GetGrid().GetDz(k)*
					(engine->GetEy(XCell, YCell, k+1) -
					 engine->GetEy(XCell, YCell, k))
					 - c_times_dt/engine->GetGrid().GetDy(YCell)*2/
					 log(engine->GetGrid().GetDy(YCell)/dto.GetRadius())*
					 engine->GetEz(XCell, YCell+1, k);
			engine->SetHx(XCell, YCell, k, value);

			value = HBottom[k-ZCell] + c_times_dt/engine->GetGrid().GetDz(k)*
					(engine->GetEy(XCell, YCell-1, k+1) -
					 engine->GetEy(XCell, YCell-1, k))
					 + c_times_dt/engine->GetGrid().GetDy(YCell-1)*2/
					 log(engine->GetGrid().GetDy(YCell-1)/dto.GetRadius())*
					 engine->GetEz(XCell, YCell-1, k);
			engine->SetHx(XCell, YCell-1, k, value);

			HRight[k-ZCell]  = engine->GetHy(XCell, YCell, k);
			HLeft[k-ZCell]   = engine->GetHy(XCell-1, YCell, k);
			HFront[k-ZCell]  = engine->GetHx(XCell, YCell, k);
			HBottom[k-ZCell] = engine->GetHx(XCell, YCell-1, k);
		}
	} else if (dto.GetOrientation().GetValue() == Y) {
		for (int j = YCell; j < LengthCell; j++)
		{
			value = HRight[j-YCell] + c_times_dt/engine->GetGrid().GetDy(j)*
					(engine->GetEx(XCell-1, j+1, ZCell) -
					 engine->GetEx(XCell-1, j, ZCell))
					 + c_times_dt/engine->GetGrid().GetDx(XCell-1)*2/
					   log(engine->GetGrid().GetDx(XCell-1)/dto.GetRadius())*
					   engine->GetEy(XCell-1, j, ZCell);
			engine->SetHz(XCell-1, j, ZCell, value);

			value = HLeft[j-YCell] + c_times_dt/engine->GetGrid().GetDy(j)*
					(engine->GetEx(XCell, j+1, ZCell) -
					 engine->GetEx(XCell, j, ZCell))
					 - c_times_dt/engine->GetGrid().GetDx(XCell)*2/
					   log(engine->GetGrid().GetDx(XCell)/dto.GetRadius())*
					   engine->GetEy(XCell+1, j, ZCell);
			engine->SetHz(XCell, j, ZCell, value);

			value = HFront[j-YCell] + c_times_dt/engine->GetGrid().GetDy(j)*
					(engine->GetEz(XCell, j, ZCell-1) -
					 engine->GetEz(XCell, j+1, ZCell-1))
					 - c_times_dt/engine->GetGrid().GetDz(ZCell-1)*2/
					   log(engine->GetGrid().GetDz(ZCell-1)/dto.GetRadius())*
					   engine->GetEy(XCell, j, ZCell-1);
			engine->SetHx(XCell, j, ZCell-1, value);

			value = HBottom[j-YCell] + c_times_dt/engine->GetGrid().GetDy(j)*
					(engine->GetEz(XCell, j, ZCell) -
					 engine->GetEz(XCell, j+1, ZCell))
					 + c_times_dt/engine->GetGrid().GetDz(ZCell)*2/
					   log(engine->GetGrid().GetDz(ZCell)/dto.GetRadius())*
					   engine->GetEy(XCell, j, ZCell+1);
			engine->SetHx(XCell, j, ZCell, value);

			HRight[j-YCell]  = engine->GetHz(XCell-1, j, ZCell);
			HLeft[j-YCell]   = engine->GetHz(XCell, j, ZCell);
			HFront[j-YCell]  = engine->GetHx(XCell, j, ZCell-1);
			HBottom[j-YCell] = engine->GetHx(XCell, j, ZCell);

	   }
	} else if (dto.GetOrientation().GetValue() == X) {
		for (int i = XCell; i < LengthCell; i++)
		{
			value = HRight[i-XCell] + c_times_dt/engine->GetGrid().GetDx(i)*
					(engine->GetEz(i+1, YCell, ZCell-1) -
					 engine->GetEz(i, YCell, ZCell-1))
					 + c_times_dt/engine->GetGrid().GetDz(ZCell-1)*2/
					   log(engine->GetGrid().GetDz(ZCell-1)/dto.GetRadius())*
					   engine->GetEx(i, YCell, ZCell-1);
			engine->SetHy(i, YCell, ZCell-1, value);

			value = HLeft[i-XCell] + c_times_dt/engine->GetGrid().GetDx(i)*
					(engine->GetEz(i+1, YCell, ZCell) -
					 engine->GetEz(i, YCell, ZCell))
					 - c_times_dt/engine->GetGrid().GetDz(ZCell)*2/
					   log(engine->GetGrid().GetDz(ZCell)/dto.GetRadius())*
					   engine->GetEx(i, YCell, ZCell+1);

			engine->SetHy(i, YCell, ZCell, value);

			value = HFront[i-XCell] + c_times_dt/engine->GetGrid().GetDx(i)*
					(engine->GetEy(i, YCell-1, ZCell) -
					 engine->GetEy(i+1, YCell-1, ZCell))
					 - c_times_dt/engine->GetGrid().GetDy(YCell-1)*2/
					   log(engine->GetGrid().GetDy(YCell-1)/dto.GetRadius())*
					   engine->GetEx(i, YCell-1, ZCell);
			engine->SetHz(i, YCell-1, ZCell, value);

			value = HBottom[i-XCell] + c_times_dt/engine->GetGrid().GetDx(i)*
					(engine->GetEy(i, YCell, ZCell) -
					 engine->GetEy(i+1, YCell, ZCell))
					 + c_times_dt/engine->GetGrid().GetDy(YCell)*2/
					   log(engine->GetGrid().GetDy(YCell)/dto.GetRadius())*
					   engine->GetEx(i, YCell+1, ZCell);

			engine->SetHz(i, YCell, ZCell, value);

			HRight[i-XCell]  = engine->GetHy(i, YCell, ZCell-1);
			HLeft[i-XCell]   = engine->GetHy(i, YCell, ZCell);
			HFront[i-XCell]  = engine->GetHz(i, YCell-1, ZCell);
			HBottom[i-XCell] = engine->GetHz(i, YCell, ZCell);
		}
	}
}

bool ThinWireFDTDCore::FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	int orientation = dto.GetOrientation().GetValue();
	xmin = dto.GetX();
	ymin = dto.GetY();
	zmin = dto.GetZ();
	xmax = dto.GetX();
	ymax = dto.GetY();
	zmax = dto.GetZ();

	if (orientation == X) {
		xmax += dto.GetLength();
	} else if (orientation == Y) {
		ymax += dto.GetLength();
	} else if (orientation == Z) {
		zmax += dto.GetLength();
	}
	return true;
}

bool ThinWireFDTDCore::IsElementConsistent() {
	bool elementOK = true;
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	Grid grid = engine->GetGrid();

	double radius = dto.GetRadius();
	int orientation = dto.GetOrientation().GetValue();

	int iEx = engine->GetGrid().GetXCell(dto.GetX());
	int jEx = engine->GetGrid().GetYCell(dto.GetY());
	int kEx = engine->GetGrid().GetZCell(dto.GetZ());

	cout << "i1 = " << iEx << endl;
	cout << "j1 = " << jEx << endl;
	cout << "k1 = " << kEx << endl;

	if (orientation == Z) {
		if (radius > grid.GetDx(iEx)/2) {
			elementOK = false;
			wxString errorMessage = GetName();
			errorMessage.Append(wxT(": the wire radius should be lower than \u0394x/2"));
			AppendErrorMessage(errorMessage);
		}
		if (radius > grid.GetDy(jEx)/2) {
			elementOK = false;
			wxString errorMessage = GetName();
			errorMessage.Append(wxT(": the wire radius should be lower than \u0394y/2"));
			AppendErrorMessage(errorMessage);
		}
	}
	if (orientation == X) {
		if (radius > grid.GetDy(jEx)/2) {
			elementOK = false;
			wxString errorMessage = GetName();
			errorMessage.Append(wxT(": the wire radius should be lower than \u0394y/2"));
			AppendErrorMessage(errorMessage);
		}
		if (radius > grid.GetDz(kEx)/2) {
			elementOK = false;
			wxString errorMessage = GetName();
			errorMessage.Append(wxT(": the wire radius should be lower than \u0394z/2"));
			AppendErrorMessage(errorMessage);
		}
	}
	if (orientation == Y) {
		if (radius > grid.GetDx(iEx)/2) {
			elementOK = false;
			wxString errorMessage = GetName();
			errorMessage.Append(wxT(": the wire radius should be lower than \u0394x/2"));
			AppendErrorMessage(errorMessage);
		}
		if (radius > grid.GetDz(kEx)/2) {
			elementOK = false;
			wxString errorMessage = GetName();
			errorMessage.Append(wxT(": the wire radius should be lower than \u0394z/2"));
			AppendErrorMessage(errorMessage);
		}
	}
	return elementOK;
}
