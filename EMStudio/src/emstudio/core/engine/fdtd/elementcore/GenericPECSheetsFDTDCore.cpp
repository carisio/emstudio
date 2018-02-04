/*
 * GenericPECSheetsFDTDCore.cpp
 *
 *  Created on: 16/12/2013
 *      Author: leandrocarisio
 */

#include "GenericPECSheetsFDTDCore.h"
#include "GenericPECSheetFDTDCore.h"

GenericPECSheetsFDTDCore::GenericPECSheetsFDTDCore() {

}

GenericPECSheetsFDTDCore::~GenericPECSheetsFDTDCore() {
}

ElementCoreSmartPointer GenericPECSheetsFDTDCore::NewElementCore() {
	return ElementCoreSmartPointer(new GenericPECSheetsFDTDCore);
}

void GenericPECSheetsFDTDCore::DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr) {
	GenericPECSheetsDTO* genericPECSheet = static_cast<GenericPECSheetsDTO*>(elementDTOSmartPtr.get());
	std::vector<GenericSheet> sheets = genericPECSheet->GetGenericSheets();

	for (size_t i = 0; i < sheets.size(); i++) {
		GenericPECSheetDTO* gsDTO = new GenericPECSheetDTO;
		gsDTO->SetGenericSheet(sheets[i]);

		GenericPECSheetFDTDCore* gsFDTDCore = new GenericPECSheetFDTDCore;
		gsFDTDCore->SetEngine(GetEngine());
		gsFDTDCore->DoConfigure(ElementDTOSmartPointer(gsDTO));

		individualSheets.push_back(ElementCoreSmartPointer(gsFDTDCore));
	}
	dto = *genericPECSheet;
}
bool GenericPECSheetsFDTDCore::FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	double xminTemp, yminTemp, zminTemp, xmaxTemp, ymaxTemp, zmaxTemp;

	if (individualSheets.size() == 0) return false;

	static_cast<GenericPECSheetFDTDCore*>(individualSheets[0].get())->FillDimensions(xmin, ymin, zmin, xmax, ymax, zmax);

	for (size_t i = 1; i < individualSheets.size(); i++) {
		static_cast<GenericPECSheetFDTDCore*>(individualSheets[i].get())->FillDimensions(xminTemp, yminTemp, zminTemp, xmaxTemp, ymaxTemp, zmaxTemp);

		if (xminTemp < xmin) xmin = xminTemp;
		if (yminTemp < ymin) ymin = yminTemp;
		if (zminTemp < zmin) zmin = zminTemp;

		if (xmaxTemp < xmax) xmax = xmaxTemp;
		if (ymaxTemp < ymax) ymax = ymaxTemp;
		if (zmaxTemp < zmax) zmax = zmaxTemp;
	}
	return true;
}

void GenericPECSheetsFDTDCore::ElectricFieldsChanged(double t) {
	for (size_t i = 0; i < individualSheets.size(); i++) {
		static_cast<GenericPECSheetFDTDCore*>(individualSheets[i].get())->ElectricFieldsChanged(t);
	}
}

void GenericPECSheetsFDTDCore::SimulationWillStart() {
	for (size_t i = 0; i < individualSheets.size(); i++) {
		static_cast<GenericPECSheetFDTDCore*>(individualSheets[i].get())->SimulationWillStart();
	}
}
bool GenericPECSheetsFDTDCore::IsElementConsistent() {
	bool elementOK = true;
	for (size_t i = 0; i < individualSheets.size(); i++) {
		elementOK = elementOK && static_cast<GenericPECSheetFDTDCore*>(individualSheets[i].get())->IsElementConsistent();
	}
	return elementOK;
}
