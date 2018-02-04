/*
 * GenericPECSheetFDTDCore.cpp
 *
 *  Created on: 16/04/2013
 *      Author: Leandro
 */

#include "GenericPECSheetFDTDCore.h"
#include <iostream>

GenericPECSheetFDTDCore::GenericPECSheetFDTDCore() {

}

GenericPECSheetFDTDCore::~GenericPECSheetFDTDCore() {
}


ElementCoreSmartPointer GenericPECSheetFDTDCore::NewElementCore() {
	return ElementCoreSmartPointer(new GenericPECSheetFDTDCore);
}

void GenericPECSheetFDTDCore::DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr) {
	GenericPECSheetDTO* genericPECSheet = static_cast<GenericPECSheetDTO*>(elementDTOSmartPtr.get());
	dto = *genericPECSheet;
}

bool GenericPECSheetFDTDCore::FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	GenericSheet sheet = dto.GetGenericSheet();
	vector<pair<double, double> > coordinates = sheet.GetCoordinates();

	coord1Min = 1e30; coord1Max = -1e30; coord2Min = 1e30; coord2Max = -1e30;

	for (size_t i = 0; i < coordinates.size(); i++) {
		pair<double, double> p = coordinates[i];
		if (p.first < coord1Min) {
			coord1Min = p.first;
		}
		if (p.first > coord1Max) {
			coord1Max = p.first;
		}
		if (p.second < coord2Min) {
			coord2Min = p.second;
		}
		if (p.second > coord2Max) {
			coord2Max = p.second;
		}
	}

	if (sheet.IsCutAtZ()) {
		zmin = sheet.GetCutAt();
		zmax = sheet.GetCutAt();
		xmin = coord1Min;
		xmax = coord1Max;
		ymin = coord2Min;
		ymax = coord2Max;

	} else if (sheet.IsCutAtX()) {
		xmin = sheet.GetCutAt();
		xmax = sheet.GetCutAt();
		ymin = coord1Min;
		ymax = coord1Max;
		zmin = coord2Min;
		zmax = coord2Max;
	} else if (sheet.IsCutAtY()) {
		ymin = sheet.GetCutAt();
		ymax = sheet.GetCutAt();
		xmin = coord1Min;
		xmax = coord1Max;
		zmin = coord2Min;
		zmax = coord2Max;
	}

//	cout << "FillDimensions: " << endl;
//	cout << "xmin = " << xmin << endl;
//	cout << "xmax = " << xmax << endl;
//	cout << "ymin = " << ymin << endl;
//	cout << "ymay = " << ymax << endl;
//	cout << "zmin = " << zmin << endl;
//	cout << "zmaz = " << zmax << endl;
	return true;
}

void GenericPECSheetFDTDCore::ElectricFieldsChanged(double t) {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	GenericSheet sheet = dto.GetGenericSheet();

	if (sheet.IsCutAtZ()) {
		for (size_t i = 0; i < gridIndexEx.size(); i++) {
			engine->SetEx(gridIndexEx[i].first,gridIndexEx[i].second,cutAtIndex,0);
		}
		for (size_t i = 0; i < gridIndexEy.size(); i++) {
			engine->SetEy(gridIndexEy[i].first,gridIndexEy[i].second,cutAtIndex,0);
		}
	}
	if (sheet.IsCutAtX()) {
		for (size_t i = 0; i < gridIndexEy.size(); i++) {
			engine->SetEy(cutAtIndex,gridIndexEy[i].first,gridIndexEy[i].second,0);
		}
		for (size_t i = 0; i < gridIndexEz.size(); i++) {
			engine->SetEz(cutAtIndex,gridIndexEz[i].first,gridIndexEz[i].second,0);
		}
	}
	if (sheet.IsCutAtY()) {
		for (size_t i = 0; i < gridIndexEx.size(); i++) {
			engine->SetEx(gridIndexEx[i].first,cutAtIndex,gridIndexEx[i].second,0);
		}
		for (size_t i = 0; i < gridIndexEz.size(); i++) {
			engine->SetEz(gridIndexEz[i].first,cutAtIndex,gridIndexEz[i].second,0);
		}
	}
//	else if (sheet.IsCutAtX()) {
//		for (size_t i = 0; i < gridIndex.size(); i++) {
//			engine->SetEy(cutAtIndex, gridIndex[i].first, gridIndex[i].second,0);
//			engine->SetEz(cutAtIndex, gridIndex[i].first, gridIndex[i].second,0);
//		}
//	} else if (sheet.IsCutAtY()) {
//		for (size_t i = 0; i < gridIndex.size(); i++) {
//			engine->SetEy(gridIndex[i].first, cutAtIndex, gridIndex[i].second,0);
//			engine->SetEz(gridIndex[i].first, cutAtIndex, gridIndex[i].second,0);
//		}
//	}
}

void GenericPECSheetFDTDCore::SimulationWillStart() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	class Grid grid = engine->GetGrid();

	GenericSheet sheet = dto.GetGenericSheet();
	gridIndexEx = vector<pair<int, int> >();
	gridIndexEy = vector<pair<int, int> >();
	gridIndexEz = vector<pair<int, int> >();

	if (sheet.IsCutAtZ()) {
		cutAtIndex = grid.GetZCell(sheet.GetCutAt());

		int xCellMin = grid.GetXCell(coord1Min);
		int xCellMax = grid.GetXCell(coord1Max);
		int yCellMin = grid.GetYCell(coord2Min);
		int yCellMax = grid.GetYCell(coord2Max);

//		cout << "xCellMin = " << xCellMin << endl;
//		cout << "xCellMax = " << xCellMax << endl;
//		cout << "yCellMin = " << yCellMin << endl;
//		cout << "yCellMax = " << yCellMax << endl;

		for (int i = xCellMin; i < xCellMax; i++) {
			for (int j = yCellMin; j < yCellMax; j++) {
				/* No meio da célula */
				double px_2 = grid.GetAccumulatedDx(i) + grid.GetDx(i)/2;
				double py_2 = grid.GetAccumulatedDy(j) + grid.GetDy(i)/2;

				if (IsInside(px_2, py_2)) {
					AddPointToVector(gridIndexEx, i, j);
					AddPointToVector(gridIndexEx, i, j+1);
					AddPointToVector(gridIndexEy, i, j);
					AddPointToVector(gridIndexEy, i+1, j);
				}
			}
		}
	} else if (sheet.IsCutAtX()) {
		cutAtIndex = grid.GetXCell(sheet.GetCutAt());

		int yCellMin = grid.GetYCell(coord1Min);
		int yCellMax = grid.GetYCell(coord1Max);
		int zCellMin = grid.GetZCell(coord2Min);
		int zCellMax = grid.GetZCell(coord2Max);

		for (int j = yCellMin; j < yCellMax; j++) {
			for (int k = zCellMin; k < zCellMax; k++) {
				double py_2 = grid.GetAccumulatedDy(j) + grid.GetDy(j)/2;
				double pz_2 = grid.GetAccumulatedDz(k) + grid.GetDz(k)/2;

				if (IsInside(py_2, pz_2)) {
					AddPointToVector(gridIndexEy, j, k);
					AddPointToVector(gridIndexEy, j, k+1);
					AddPointToVector(gridIndexEz, j, k);
					AddPointToVector(gridIndexEz, j+1, k);
				}
			}
		}

	} else if (sheet.IsCutAtY()) {
		cutAtIndex = grid.GetYCell(sheet.GetCutAt());

		int xCellMin = grid.GetXCell(coord1Min);
		int xCellMax = grid.GetXCell(coord1Max);
		int zCellMin = grid.GetZCell(coord2Min);
		int zCellMax = grid.GetZCell(coord2Max);

		for (int i = xCellMin; i < xCellMax; i++) {
			for (int k = zCellMin; k < zCellMax; k++) {
				double px_2 = grid.GetAccumulatedDx(i) + grid.GetDx(i)/2;
				double pz_2 = grid.GetAccumulatedDz(k) + grid.GetDz(k)/2;

				if (IsInside(px_2, pz_2)) {
					AddPointToVector(gridIndexEx, i, k);
					AddPointToVector(gridIndexEx, i, k+1);
					AddPointToVector(gridIndexEz, i, k);
					AddPointToVector(gridIndexEz, i+1, k);
				}
			}
		}
	}

	cout << "Coordenadas de ex que serão zeradas";
	for (int i = 0; i < gridIndexEx.size(); i++) {
		cout << gridIndexEx[i].first << "\t" << gridIndexEx[i].second << endl;
	}
	cout << "Coordenadas de ey que serão zeradas";
	for (int i = 0; i < gridIndexEy.size(); i++) {
		cout << gridIndexEy[i].first << "\t" << gridIndexEy[i].second << endl;
	}
	cout << "Coordenadas de ez que serão zeradas";
	for (int i = 0; i < gridIndexEz.size(); i++) {
		cout << gridIndexEz[i].first << "\t" << gridIndexEz[i].second << endl;
	}

//	cout << "Índices que serão zerados Ex (i, j)" << endl;
//	for (size_t i = 0; i < gridIndexEx.size(); i++) {
//		cout << "\t" << gridIndexEx[i].first << " " << gridIndexEx[i].second << endl;
//	}
//	cout << "Índices que serão zerados Ey (i, j)" << endl;
//	for (size_t i = 0; i < gridIndexEy.size(); i++) {
//		cout << "\t" << gridIndexEy[i].first << " " << gridIndexEy[i].second << endl;
//	}
}

void GenericPECSheetFDTDCore::AddPointToVector(vector<pair<int, int> >& vec, int coord1, int coord2) {
	bool hasElement = false;
	for (size_t i = 0; i < vec.size(); i++) {
		if (vec[i].first == coord1 && vec[i].second == coord2) {
			hasElement = true;
			break;
		}
	}

	if (!hasElement) {
		vec.push_back(pair<double, double>(coord1, coord2));
	}

}
void GenericPECSheetFDTDCore::SortMinMax(double& min, double& max) {
	if (min > max) {
		double aux = min;
		min = max;
		max = aux;
	}
}

bool GenericPECSheetFDTDCore::IsInside(double x, double y) {
	bool crossLine;
	bool atTheBorderOfPolygon = false;
	bool atTheLine = false;

	int crossNumber = 0;
	vector<pair<double, double> > coordinates = dto.GetGenericSheet().GetCoordinates();

	for (size_t i = 1; i < coordinates.size(); i++) {
		CrossLine(x, y, coordinates[i-1].first, coordinates[i-1].second, coordinates[i].first, coordinates[i].second, crossLine, atTheLine);
		atTheBorderOfPolygon = atTheBorderOfPolygon || atTheLine;
		if (crossLine) {
			crossNumber++;
		}
	}
	size_t i = coordinates.size()-1;
	CrossLine(x, y, coordinates[i].first, coordinates[i].second, coordinates[0].first, coordinates[0].second, crossLine, atTheLine);
	atTheBorderOfPolygon = atTheBorderOfPolygon || atTheLine;
	if (crossLine) {
		crossNumber++;
	}
	/* No */
//	cout << "Número de cruzamentos: " << crossNumber << endl;
	return (crossNumber % 2 == 1) || atTheBorderOfPolygon;
}
/* Verifica se cruza uma linha pela direita. CrossLine apenas retorna corretamente se o ponto não estiver na linha. Se estiver, tem que verificar
 * a variável atTheLine.
 */
void GenericPECSheetFDTDCore::CrossLine(double x, double y, double v1_x, double v1_y, double v2_x, double v2_y, bool& cross, bool& atTheLine) {
	double ymin = v1_y;
	double ymax = v2_y;
	SortMinMax(ymin, ymax);

	// Dado y, calcula o valor de x na equação da linha conectando os pontos v1 e v2
	if (v2_y == v1_y)
		v1_y = v1_y - 1e-30;
	double x_Calculado = v1_x + (y-v1_y)*(v2_x-v1_x)/(v2_y-v1_y);

	bool isAtLeft = false;
	bool interceptSegment = false;

	/* Verifica se o valor de x está a esquerda do valor calculado. */
	if (x < x_Calculado) {
		isAtLeft = true;
	}
	if ((y >= ymin) && (y <= ymax)) {
		interceptSegment = true;

		/* Verifica se está na borda */
		if (x == x_Calculado) {
			atTheLine = true;
		} else {
			atTheLine = false;
		}
		/* Verifica os casos de nan no cálculo do x_Calculado */
		if (v1_y == v2_y) {
			if (v1_x < v2_x) {
				atTheLine = (x >= v1_x) && (x <= v2_x);
			} else {
				atTheLine = (x >= v2_x) && (x <= v1_x);
			}
		}
	}

//	if (x > -0.001 && y > -0.001 && x < 1.001 && y < 1.001) {
//	if (y >= (20-0.8)*0.001 && y <= (20+0.8)*0.001) {
//		cout << "X, Y bateu" << endl;
//		cout << "\t x = " << x << endl;
//		cout << "\t y = " << y << endl;
//		cout << "\t v1_x = " << v1_x << endl;
//		cout << "\t v1_y = " << v1_y << endl;
//		cout << "\t v2_x = " << v2_x << endl;
//		cout << "\t v2_y = " << v2_y << endl;
//		cout << "\t ymin  = " << ymin << endl;
//		cout << "\t ymax = " << ymax << endl;
//		cout << "\t x_calculado = " << x_Calculado << endl;
//		cout << "\t isAtLeft = " << isAtLeft << endl;
//		cout << "\t interceptSegment = " << interceptSegment << endl;
//		cout << "\t atTheLine = " << atTheLine << endl;
//	}
	cross = interceptSegment && isAtLeft;
}

bool GenericPECSheetFDTDCore::IsElementConsistent() {
	bool elementOK = true;
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	return elementOK;
}
