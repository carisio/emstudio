/*
 * FieldAtPlaneFDTDCore.cpp
 *
 *  Created on: 13/03/2013
 *      Author: leandrocarisio
 */

#include "FieldAtPlaneFDTDCore.h"
#include "emstudio/core/results/FieldAtPlaneResult.h"

#include <iostream>
using std::cout;
using std::endl;

FieldAtPlaneFDTDCore::FieldAtPlaneFDTDCore() {

}

FieldAtPlaneFDTDCore::~FieldAtPlaneFDTDCore() {
}

ElementCoreSmartPointer FieldAtPlaneFDTDCore::NewElementCore() {
	return ElementCoreSmartPointer(new FieldAtPlaneFDTDCore);
}

void FieldAtPlaneFDTDCore::DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr) {
	FieldAtPlaneDTO* fieldAtPlaneDTO = static_cast<FieldAtPlaneDTO*>(elementDTOSmartPtr.get());
	dto = *fieldAtPlaneDTO;

	cout << "FieldAtPlaneFDTDCore::DoConfigure()" << endl;
	cout << "\tNumber of samples: " << dto.GetNumberOfSamples() << endl;
}

void FieldAtPlaneFDTDCore::SimulationWillStart() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	class Grid grid = engine->GetGrid();

//	dim1; // Se em XY, X. Se YZ, Y. Se XZ, X.
//	dim2; // Se em XY, Y. Se YZ, Z. Se XZ, Z.

	dim3 = dto.GetNumberOfSamples(); // Essa dimensão sempre é o tempo
	sampleAtEach = engine->GetTimeSteps() / dto.GetNumberOfSamples();
	currentSample = -1;

	double xmin = dto.GetX0();
	double ymin = dto.GetY0();
	double zmin = dto.GetZ0();
	double xmax = dto.GetX1();
	double ymax = dto.GetY1();
	double zmax = dto.GetZ1();

	imin = grid.GetXCell(xmin);
	imax = grid.GetXCell(xmax);
	jmin = grid.GetYCell(ymin);
	jmax = grid.GetYCell(ymax);
	kmin = grid.GetZCell(zmin);
	kmax = grid.GetZCell(zmax);
	cout << "FieldAtPlaneFDTDCore::SimulationWillStart()" << endl;
	cout << "imin = " << imin << endl;
	cout << "jmin = " << jmin << endl;
	cout << "kmin = " << kmin << endl;
	cout << "imax = " << imax << endl;
	cout << "jmax = " << jmax << endl;
	cout << "kmax = " << kmax << endl;
	cout << "_____________" << endl;

	/* Os métodos grid.Get_Cell retornam a célula para determinado valor de entrada.
	 *
	 * Suponha o seguinte grid com tamanho de [0, 10] e 10 células:
	 *
	 * | 0  |  1 |  2 |  3 |   |  9 |
	 * |----|----|----|----|...|----|
	 *
	 * Se o usuário fizer uma chamada para grid.Get_Cell(x), em que x > 10-delta_/2, o método vai retornar:
	 *     - o índice 10 para PEC e PML
	 *     - o índice 9 para PBC
	 *
	 * Isso acontece porque para PEC e PML existem células depois do grid, e para PBC não. E o grid sempre retorna a célula
	 * que está entre -delta/2 e +delta/2 ao redor dela.
	 *
	 * Pensando nisso, toda a lógica nessa classe foi feita para calcular os campos de _min até _max, não incluindo _max.
	 * Por isso, no caso da PBC, caso o usuário entre com um valor que é maior que o valor máximo do grid menos a metade de um delta,
	 * é necessário somar uma célula, para que a última célula também seja considerada.
	 *
	 * Note que a lógica também poderia ser o contrário, ou seja, calcular o campo de _min até _max e, no caso da PEC ou PML,
	 * reduzir uma célula se o valor retornado por grid.Get_Cell for maior do que o que o usuário digitou.
	 *
	 */
	/**
	 * TODO: Isso daqui só vale se não inserir outra célula na PBC. Na versão do Grid encaminhada pelo Martins em 29.12.2013 foi
	 * inserida uma nova célula na PBC. */
	/*
	if (engine->GetFDTDDTO().GetABC().IsPeriodic(xNeg)) {
		if (xmax > engine->GetFDTDDTO().GetXmax() - grid.GetDx(engine->GetFDTDDTO().GetXcells()-1)/2) {
			imax++;
		}
	}
	if (engine->GetFDTDDTO().GetABC().IsPeriodic(zNeg)) {
		if (zmax > engine->GetFDTDDTO().GetZmax() - grid.GetDz(engine->GetFDTDDTO().GetZcells()-1)/2) {
			kmax++;
		}
	}
*/
	cout << "imin = " << imin << endl;
	cout << "jmin = " << jmin << endl;
	cout << "kmin = " << kmin << endl;
	cout << "imax = " << imax << endl;
	cout << "jmax = " << jmax << endl;
	cout << "kmax = " << kmax << endl;

	if (dto.IsCutAtZ()) { // Plano XY
		cout << "Corte em z" << endl;

		dim1 = imax-imin; // Se em XY, X. Se YZ, Y. Se XZ, X.
		dim2 = jmax-jmin; // Se em XY, Y. Se YZ, Z. Se XZ, Z.

		positionDimension1 = Array1D<double>(dim1+1);
		positionDimension2 = Array1D<double>(dim2+1);

		cout << "dim1 = " << dim1 << endl;
		cout << "dim2 = " << dim2 << endl;

		for (int i = imin; i <= imax; i++) {
			positionDimension1[i-imin] = grid.GetAccumulatedDx(i);
		}
		for (int j = jmin; j <= jmax; j++) {
			positionDimension2[j-jmin] = grid.GetAccumulatedDy(j);
		}

	} else if (dto.IsCutAtX()) { // Plano YZ
		cout << "Corte em x" << endl;
		dim1 = jmax-jmin;
		dim2 = kmax-kmin;
		cout << "dim1 = " << dim1 << endl;
		cout << "dim2 = " << dim2 << endl;

		positionDimension1 = Array1D<double>(dim1+1);
		positionDimension2 = Array1D<double>(dim2+1);

		for (int j = jmin; j <= jmax; j++) {
			positionDimension1[j-jmin] = grid.GetAccumulatedDy(j);
		}
		for (int k = kmin; k <= kmax; k++) {
			positionDimension2[k-kmin] = grid.GetAccumulatedDz(k);
		}

	} else if (dto.IsCutAtY()) { // Plano XZ
		cout << "Corte em Y" << endl;
		dim1 = imax-imin;
		dim2 = kmax-kmin;
		cout << "dim1 = " << dim1 << endl;
		cout << "dim2 = " << dim2 << endl;

		positionDimension1 = Array1D<double>(dim1+1);
		positionDimension2 = Array1D<double>(dim2+1);

		for (int i = imin; i <= imax; i++) {
			positionDimension1[i-imin] = grid.GetAccumulatedDx(i);
		}
		for (int k = kmin; k <= kmax; k++) {
			positionDimension2[k-kmin] = grid.GetAccumulatedDz(k);
		}
	}

	int field = dto.GetField().GetValue();

	showEx = false; showEy = false; showEz = false;
	showHx = false; showHy = false; showHz = false;
	if (field == SelectField::EX || field == SelectField::ALL_E_FIELDS || field == SelectField::ALL_FIELDS) {
		showEx = true;
		Ex = Array3D<double>(dim1, dim2, dim3);
	}
	if (field == SelectField::EY || field == SelectField::ALL_E_FIELDS || field == SelectField::ALL_FIELDS) {
		showEy = true;
		Ey = Array3D<double>(dim1, dim2, dim3);
	}
	if (field == SelectField::EZ || field == SelectField::ALL_E_FIELDS || field == SelectField::ALL_FIELDS) {
		showEz = true;
		Ez = Array3D<double>(dim1, dim2, dim3);
	}
	if (field == SelectField::HX || field == SelectField::ALL_H_FIELDS || field == SelectField::ALL_FIELDS) {
		showHx = true;
		Hx = Array3D<double>(dim1, dim2, dim3);
	}
	if (field == SelectField::HY || field == SelectField::ALL_H_FIELDS || field == SelectField::ALL_FIELDS) {
		showHy = true;
		Hy = Array3D<double>(dim1, dim2, dim3);
	}
	if (field == SelectField::HZ || field == SelectField::ALL_H_FIELDS || field == SelectField::ALL_FIELDS) {
		showHz = true;
		Hz = Array3D<double>(dim1, dim2, dim3);
	}

	cout << "showEx = " << showEx << endl;
	cout << "showEy = " << showEy << endl;
	cout << "showEz = " << showEz << endl;
	cout << "showHx = " << showHx << endl;
	cout << "showHy = " << showHy << endl;
	cout << "showHz = " << showHz << endl;

	timeVector = Array1D<double>(dim3);

	cout << "dim3 = " << dim3 << endl;
	cout << "SampleAtEach = " << sampleAtEach<< endl;
}

void FieldAtPlaneFDTDCore::ElectricFieldsChanged(double t) {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	if (engine->GetCurrentInterationNumber() % sampleAtEach != 0)
		return;

	currentSample++;

//	cout << "\t currentIterationNumber() = " << engine->GetCurrentInterationNumber() << endl;
//	cout << "\t currentSample = " << currentSample << endl;
	if (currentSample >= dim3)
		return;


	timeVector[currentSample] = t;

	if (dto.IsCutAtZ()) {
		for (int i = imin; i < imax; i++) {
			for (int j = jmin; j < jmax; j++) {

				if (showEx) {
					Ex[i-imin][j-jmin][currentSample] = engine->GetEx(i, j, kmin);
				}
				if (showEy) {
					Ey[i-imin][j-jmin][currentSample] = engine->GetEy(i, j, kmin);
				}
				if (showEz) {
					Ez[i-imin][j-jmin][currentSample] = engine->GetEz(i, j, kmin);
				}
			}
		}
	} else if (dto.IsCutAtX()) {

		for (int j = jmin; j < jmax; j++) {
			for (int k = kmin; k < kmax; k++) {
				if (showEx) {
					Ex[j-jmin][k-kmin][currentSample] = engine->GetEx(imin, j, k);
				}
				if (showEy) {
					Ey[j-jmin][k-kmin][currentSample] = engine->GetEy(imin, j, k);
				}
				if (showEz) {
					Ez[j-jmin][k-kmin][currentSample] = engine->GetEz(imin, j, k);
				}
			}
		}

	} else if (dto.IsCutAtY()) {

		for (int i = imin; i < imax; i++) {
			for (int k = kmin; k < kmax; k++) {
				if (showEx) {
					Ex[i-imin][k-kmin][currentSample] = engine->GetEx(i, jmin, k);
				}
				if (showEy) {
					Ey[i-imin][k-kmin][currentSample] = engine->GetEy(i, jmin, k);
				}
				if (showEz) {
					Ez[i-imin][k-kmin][currentSample] = engine->GetEz(i, jmin, k);
				}
			}
		}

	}
}

void FieldAtPlaneFDTDCore::MagneticFieldsChanged(double t) {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	if (engine->GetCurrentInterationNumber() % sampleAtEach != 0)
			return;

	if (currentSample >= dim3)
		return;

	if (dto.IsCutAtZ()) {
		for (int i = imin; i < imax; i++) {
			for (int j = jmin; j < jmax; j++) {

				if (showHx) {
					Hx[i-imin][j-jmin][currentSample] = engine->GetHx(i, j, kmin);
				}
				if (showHy) {
					Hy[i-imin][j-jmin][currentSample] = engine->GetHy(i, j, kmin);
				}
				if (showHz) {
					Hz[i-imin][j-jmin][currentSample] = engine->GetHz(i, j, kmin);
				}
			}
		}
	} else if (dto.IsCutAtX()) {

		for (int j = jmin; j < jmax; j++) {
			for (int k = kmin; k < kmax; k++) {
				if (showHx) {
					Hx[j-jmin][k-kmin][currentSample] = engine->GetHx(imin, j, k);
				}
				if (showHy) {
					Hy[j-jmin][k-kmin][currentSample] = engine->GetHy(imin, j, k);
				}
				if (showHz) {
					Hz[j-jmin][k-kmin][currentSample] = engine->GetHz(imin, j, k);
				}
			}
		}

	} else if (dto.IsCutAtY()) {

		for (int i = imin; i < imax; i++) {
			for (int k = kmin; k < kmax; k++) {
				if (showHx) {
					Hx[i-imin][k-kmin][currentSample] = engine->GetHx(i, jmin, k);
				}
				if (showHy) {
					Hy[i-imin][k-kmin][currentSample] = engine->GetHy(i, jmin, k);
				}
				if (showHz) {
					Hz[i-imin][k-kmin][currentSample] = engine->GetHz(i, jmin, k);
				}
			}
		}

	}
}

bool FieldAtPlaneFDTDCore::IsElementConsistent() {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	bool elementOK = true;

	// Verifica se o número de snapshots é zero
	if (dto.GetNumberOfSamples() == 0) {
		wxString errorMessage = GetName() + ": snapshot number can not be 0";
		AppendErrorMessage(errorMessage);
		elementOK = false;
	}
	// Verifica se o número de snapshots é maior do que o número de iterações
	if (dto.GetNumberOfSamples() > engine->GetTimeSteps()) {
		cout << "dto.GetNumberOfSamples() = " << dto.GetNumberOfSamples() << endl;
		cout << "engine->GetTimeSteps() = " << engine->GetTimeSteps() << endl;
		wxString errorMessage = GetName() + ": Number of snapshots is greater than the total iteration number";
		AppendErrorMessage(errorMessage);
		elementOK = false;
	}

	return elementOK;
}
void FieldAtPlaneFDTDCore::SimulationWillFinish() {
//	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
}

bool FieldAtPlaneFDTDCore::FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	xmin = dto.GetX0();
	ymin = dto.GetY0();
	zmin = dto.GetZ0();
	xmax = dto.GetX1();
	ymax = dto.GetY1();
	zmax = dto.GetZ1();

	return true;
}

bool FieldAtPlaneFDTDCore::HasResults() {
	return true;
}

ElementResults FieldAtPlaneFDTDCore::GetElementsResults() {
	cout << "GetElementsResults" << endl;

	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	wxString normalized_time_label = engine->GetUnits()->GetUserDefinedTimeUnit().first;
	double normalized_time_factor = engine->GetUnits()->GetUserDefinedTimeUnit().second;
	wxString normalized_space_label = engine->GetUnits()->GetUserDefinedSpaceUnit().first;
	double normalized_space_factor = engine->GetUnits()->GetUserDefinedSpaceUnit().second;

	list<ResultSmartPointer> results;

	/* Desnormaliza as dimensões */
	cout << "Dimensão de tempo: " << endl;
	for (int i = 0; i < dim3; i++) {
		timeVector[i] = timeVector[i]/normalized_time_factor;
//		cout << timeVector[i] << endl;
	}
	cout << "Dimensão 1: " << endl;
	for (int i = 0; i < dim1+1; i++) {
		positionDimension1[i] = positionDimension1[i]/normalized_space_factor;
		cout << positionDimension1[i] << endl;
	}
	cout << "Dimensão 2: " << endl;
	for (int i = 0; i < dim2+1; i++) {
		positionDimension2[i] = positionDimension2[i]/normalized_space_factor;
		cout << positionDimension2[i] << endl;
	}

	/* Constroi um objeto Sheet desnormalizado */
	Sheet plane;
	plane.SetX0(dto.GetX0()/normalized_space_factor);
	plane.SetX1(dto.GetX1()/normalized_space_factor);
	plane.SetY0(dto.GetY0()/normalized_space_factor);
	plane.SetY1(dto.GetY1()/normalized_space_factor);
	plane.SetZ0(dto.GetZ0()/normalized_space_factor);
	plane.SetZ1(dto.GetZ1()/normalized_space_factor);

	if (dto.IsCutAtZ()) { // Plano XY
		plane.SetCutAtZ(dto.GetCutAt()/normalized_space_factor);
	} else if (dto.IsCutAtY()) { // Plano XZ
		plane.SetCutAtY(dto.GetCutAt()/normalized_space_factor);
	} else if (dto.IsCutAtX()) { // Plano XZ
		plane.SetCutAtX(dto.GetCutAt()/normalized_space_factor);
	}

	/* Monta os resultados */
	if (showEx) {
		DoubleVector posDim1;
		DoubleVector posDim2;
		DoubleVector timeVec;
		DoubleMatrix3D field;

		posDim1.SetData(positionDimension1);
		posDim2.SetData(positionDimension2);
		timeVec.SetData(timeVector);
		field.SetData(Ex);

		ResultSmartPointer result(new FieldAtPlaneResult(wxT("Ex"), posDim1, posDim2, normalized_space_label, plane, timeVec, normalized_time_label, field));
		results.push_back(result);
	}
	if (showEy) {
		DoubleVector posDim1;
		DoubleVector posDim2;
		DoubleVector timeVec;
		DoubleMatrix3D field;

		posDim1.SetData(positionDimension1);
		posDim2.SetData(positionDimension2);
		timeVec.SetData(timeVector);
		field.SetData(Ey);

		ResultSmartPointer result(new FieldAtPlaneResult(wxT("Ey"), posDim1, posDim2, normalized_space_label, plane, timeVec, normalized_time_label, field));
		results.push_back(result);
	}
	if (showEz) {
		DoubleVector posDim1;
		DoubleVector posDim2;
		DoubleVector timeVec;
		DoubleMatrix3D field;

		posDim1.SetData(positionDimension1);
		posDim2.SetData(positionDimension2);
		timeVec.SetData(timeVector);
		field.SetData(Ez);

		ResultSmartPointer result(new FieldAtPlaneResult(wxT("Ez"), posDim1, posDim2, normalized_space_label, plane, timeVec, normalized_time_label, field));
		results.push_back(result);
	}
	if (showHx) {
		DoubleVector posDim1;
		DoubleVector posDim2;
		DoubleVector timeVec;
		DoubleMatrix3D field;

		posDim1.SetData(positionDimension1);
		posDim2.SetData(positionDimension2);
		timeVec.SetData(timeVector);
		field.SetData(Hx);

		ResultSmartPointer result(new FieldAtPlaneResult(wxT("Hx"), posDim1, posDim2, normalized_space_label, plane, timeVec, normalized_time_label, field));
		results.push_back(result);
	}
	if (showHy) {
		DoubleVector posDim1;
		DoubleVector posDim2;
		DoubleVector timeVec;
		DoubleMatrix3D field;

		posDim1.SetData(positionDimension1);
		posDim2.SetData(positionDimension2);
		timeVec.SetData(timeVector);
		field.SetData(Hy);

		ResultSmartPointer result(new FieldAtPlaneResult(wxT("Hy"), posDim1, posDim2, normalized_space_label, plane, timeVec, normalized_time_label, field));
		results.push_back(result);
	}
	if (showHz) {
		DoubleVector posDim1;
		DoubleVector posDim2;
		DoubleVector timeVec;
		DoubleMatrix3D field;

		posDim1.SetData(positionDimension1);
		posDim2.SetData(positionDimension2);
		timeVec.SetData(timeVector);
		field.SetData(Hz);

		ResultSmartPointer result(new FieldAtPlaneResult(wxT("Hz"), posDim1, posDim2, normalized_space_label, plane, timeVec, normalized_time_label, field));
		results.push_back(result);
	}

	return ElementResults(dto.GetDTOClassName(), dto.GetName(), results);
}
