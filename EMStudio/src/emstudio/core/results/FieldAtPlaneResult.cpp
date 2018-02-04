/*
 * FieldAtPlaneResult.cpp
 *
 *  Created on: 24/04/2013
 *      Author: Leandro
 */

#include "FieldAtPlaneResult.h"
#include "emstudio/util/file/FileManager.h"

FieldAtPlaneResult::FieldAtPlaneResult(wxString fieldName, DoubleVector positionDim1,
	DoubleVector positionDim2, wxString spaceUnit, Sheet plane,	DoubleVector timeVector, wxString timeUnit, DoubleMatrix3D field) :
		positionDim1(positionDim1),
		positionDim2(positionDim2),
		plane(plane),
		timeVector(timeVector),
		field(field) {

	this->SetName(fieldName);
	this->spaceUnit.SetUserFriendlyStringRepresentation(spaceUnit);
	this->timeUnit.SetUserFriendlyStringRepresentation(timeUnit);

//	cout << "Position Dimension 1 tem " << positionDim1.GetData().dim() << " lugares" << endl;
	AddProperty(Property("Position Dimension 1", &this->positionDim1));
	AddProperty(Property("Position Dimension 2", &this->positionDim2));
	AddProperty(Property("Space Unit", &this->spaceUnit));
	AddProperty(Property("Plane", &this->plane));
	AddProperty(Property("Time Vector", &this->timeVector));
	AddProperty(Property("Time Unit", &this->timeUnit));
	AddProperty(Property("Field", &this->field));
}

FieldAtPlaneResult::~FieldAtPlaneResult() {
}

wxString FieldAtPlaneResult::GetResultClassName() {
	return "FieldAtPlaneResult";
}
ResultSmartPointer FieldAtPlaneResult::NewResult() {
	return ResultSmartPointer(new FieldAtPlaneResult);
}

wxIcon FieldAtPlaneResult::GetIcon() {
	return UtilResource::GetIcon("chart");
}
wxString FieldAtPlaneResult::GetFieldName() {
	return GetName();
}
DoubleVector FieldAtPlaneResult::GetPositionDim1() {
	return positionDim1;
}
DoubleVector FieldAtPlaneResult::GetPositionDim2() {
	return positionDim2;
}
wxString FieldAtPlaneResult::GetSpaceUnit() {
	return spaceUnit.GetValue();
}
Sheet FieldAtPlaneResult::GetPlane() {
	return plane;
}
DoubleVector FieldAtPlaneResult::GetTimeVector() {
	return timeVector;
}
wxString FieldAtPlaneResult::GetTimeUnit() {
	return timeUnit.GetValue();
}
DoubleMatrix3D FieldAtPlaneResult::GetField() {
	return field;
}
bool FieldAtPlaneResult::ExportData(wxString fileName) {
	bool saveOk = true;

	wxString path = FileManager::GetFolder(fileName);
	wxString baseFileName = FileManager::GetFileNameWithoutExtension(fileName);

	/* Salva os vetores de posição e tempo */
	Array1D<double> posDim1 = positionDim1.GetData();
	Array1D<double> posDim2 = positionDim2.GetData();
	Array1D<double> time = timeVector.GetData();
	wxString contentsPosDim1File;
	wxString contentsPosDim2File;
	wxString contentsTimeFile;
	for (int i = 0; i < posDim1.dim(); i++) {
		contentsPosDim1File.Append(Converter::DoubleToString(posDim1[i])).Append("\n");
	}
	for (int i = 0; i < posDim2.dim(); i++) {
		contentsPosDim2File.Append(Converter::DoubleToString(posDim2[i])).Append("\n");
	}
	for (int i = 0; i < time.dim(); i++) {
		contentsTimeFile.Append(Converter::DoubleToString(time[i])).Append("\n");
	}
	wxString pos1FileName = path; pos1FileName.Append(baseFileName).Append("-dim1.txt");
	wxString pos2FileName = path; pos2FileName.Append(baseFileName).Append("-dim2.txt");
	wxString timeFileName = path; timeFileName.Append(baseFileName).Append("-time.txt");
	saveOk &= FileManager::SaveFile(pos1FileName, contentsPosDim1File);
	saveOk &= FileManager::SaveFile(pos2FileName, contentsPosDim2File);
	saveOk &= FileManager::SaveFile(timeFileName, contentsTimeFile);

	cout << "space and time \t" << saveOk << endl;

	/* Salva os arquivos com o vídeo */
	Array3D<double>& fieldData = field.GetData();
	wxString dataFileName = path; dataFileName.Append(baseFileName).Append("-data.bin");
	saveOk &= FileManager::SaveBinaryFile(dataFileName, fieldData);

	/* Salva o arquivo de informação */
	wxString infoFileContents;
	infoFileContents.Append("Field: ").Append(GetFieldName()).Append("\n");

	wxString dim1Info;
	wxString dim2Info;
	wxString dim1Direction;
	wxString dim2Direction;
	if (plane.IsCutAtX()) {
		double x = plane.GetCutAt();
		double yInit = posDim1[0];
		double yEnd  = posDim1[posDim1.dim1()-1];
		double zInit = posDim2[0];
		double zEnd  = posDim2[posDim1.dim1()-1];
		infoFileContents.Append("Plane: YZ\n");
		infoFileContents.Append("\t x = ").Append(Converter::DoubleToString(x)).Append("\n");
		infoFileContents.Append("\t From y = ").Append(Converter::DoubleToString(yInit)).Append(" to y = ").Append(Converter::DoubleToString(yEnd)).Append("\n");
		infoFileContents.Append("\t From z = ").Append(Converter::DoubleToString(zInit)).Append(" to z = ").Append(Converter::DoubleToString(zEnd)).Append("\n\n");
		dim1Info = "y file: ";
		dim1Info.Append(FileManager::GetFileName(pos1FileName));
		dim2Info = "z file: ";
		dim2Info.Append(FileManager::GetFileName(pos2FileName));
		dim1Direction = "Y";
		dim2Direction = "Z";
	} else if(plane.IsCutAtY()) {
		double xInit = posDim1[0];
		double xEnd  = posDim1[posDim1.dim1()-1];
		double y = plane.GetCutAt();
		double zInit = posDim2[0];
		double zEnd  = posDim2[posDim1.dim1()-1];
		infoFileContents.Append("Plane: XZ\n");
		infoFileContents.Append("\t From x = ").Append(Converter::DoubleToString(xInit)).Append(" to x = ").Append(Converter::DoubleToString(xEnd)).Append("\n");
		infoFileContents.Append("\t y = ").Append(Converter::DoubleToString(y)).Append("\n");
		infoFileContents.Append("\t From z = ").Append(Converter::DoubleToString(zInit)).Append(" to z = ").Append(Converter::DoubleToString(zEnd)).Append("\n\n");
		dim1Info = "x file: ";
		dim1Info.Append(FileManager::GetFileName(pos1FileName));
		dim2Info = "z file: ";
		dim2Info.Append(FileManager::GetFileName(pos2FileName));
		dim1Direction = "X";
		dim2Direction = "Y";
	} else if (plane.IsCutAtZ()) {
		double xInit = posDim1[0];
		double xEnd  = posDim1[posDim1.dim1()-1];
		double yInit = posDim2[0];
		double yEnd  = posDim2[posDim1.dim1()-1];
		double z = plane.GetCutAt();
		infoFileContents.Append("Plane: XY\n");
		infoFileContents.Append("\t From x = ").Append(Converter::DoubleToString(xInit)).Append(" to x = ").Append(Converter::DoubleToString(xEnd)).Append("\n");
		infoFileContents.Append("\t From y = ").Append(Converter::DoubleToString(yInit)).Append(" to y = ").Append(Converter::DoubleToString(yEnd)).Append("\n");
		infoFileContents.Append("\t z = ").Append(Converter::DoubleToString(z)).Append("\n\n");
		dim1Info = "x file: ";
		dim1Info.Append(FileManager::GetFileName(pos1FileName));
		dim2Info = "y file: ";
		dim2Info.Append(FileManager::GetFileName(pos2FileName));
		dim1Direction = "X";
		dim2Direction = "Y";
	}
	infoFileContents.Append("Time unit: ").Append(timeUnit.GetValue()).Append("\n");
	infoFileContents.Append("Space unit: ").Append(spaceUnit.GetValue()).Append("\n\n");

	infoFileContents.Append(dim1Info).Append("\n");
	infoFileContents.Append(dim2Info).Append("\n");
	infoFileContents.Append("Time file: ").Append(FileManager::GetFileName(timeFileName)).Append("\n");
	infoFileContents.Append("Data file: ").Append(FileManager::GetFileName(dataFileName)).Append("\n");

	wxString infoFileName = path; infoFileName.Append(baseFileName).Append("-info.txt");
	saveOk &= FileManager::SaveFile(infoFileName, infoFileContents);

	cout << "info \t" << saveOk << endl;

	/* Gera arquivo do matlab */
	wxString matlabContentsFile;
	matlabContentsFile.Append("clear all;\n");
	matlabContentsFile.Append("close all;\n");
	matlabContentsFile.Append("clc;\n");
	matlabContentsFile.Append("\n");
	matlabContentsFile.Append("figure(1);\n");
	matlabContentsFile.Append("\n");
	matlabContentsFile.Append("dim1 = load('").Append(FileManager::GetFileName(pos1FileName)).Append("');\n");
	matlabContentsFile.Append("dim2 = load('").Append(FileManager::GetFileName(pos2FileName)).Append("');\n");
	matlabContentsFile.Append("time = load('").Append(FileManager::GetFileName(timeFileName)).Append("');\n");
	matlabContentsFile.Append("\n");
	matlabContentsFile.Append("rawDataID = fopen('").Append(FileManager::GetFileName(dataFileName)).Append("');\n");
	matlabContentsFile.Append("rawData = fread(rawDataID, inf, 'double', 'n');\n");
	matlabContentsFile.Append("fclose(rawDataID);\n");
	matlabContentsFile.Append("data = zeros(length(dim1)-1, length(dim2)-1, length(time));\n");
	matlabContentsFile.Append("\n");
	matlabContentsFile.Append("aux = 1;\n");
	matlabContentsFile.Append("for i=1:length(dim1)-1\n");
	matlabContentsFile.Append("\tfor j=1:length(dim2)-1\n");
	matlabContentsFile.Append("\t\tfor k=1:length(time)\n");
	matlabContentsFile.Append("\t\t\tdata(i,j,k) = rawData(aux);\n");
	matlabContentsFile.Append("\t\t\taux = aux+1;\n");
	matlabContentsFile.Append("\t\tend;\n");
	matlabContentsFile.Append("\tend;\n");
	matlabContentsFile.Append("end;\n");
	matlabContentsFile.Append("\n");
	matlabContentsFile.Append("axis1 = zeros(1,length(dim1)-1);\n");
	matlabContentsFile.Append("axis2 = zeros(1,length(dim2)-1);\n");
	matlabContentsFile.Append("\n");
	matlabContentsFile.Append("% Center between adjacent cells\n");
	matlabContentsFile.Append("for i=1:length(dim1)-1\n");
	matlabContentsFile.Append("\taxis1(i) = (dim1(i)+dim1(i+1))/2;\n");
	matlabContentsFile.Append("end\n");
	matlabContentsFile.Append("\n");
	matlabContentsFile.Append("for i=1:length(dim2)-1\n");
	matlabContentsFile.Append("\taxis2(i) = (dim2(i)+dim2(i+1))/2;\n");
	matlabContentsFile.Append("end\n");
	matlabContentsFile.Append("\n");
	matlabContentsFile.Append("for i=1:1:length(time)\n");
	matlabContentsFile.Append("\thPlot = surf(axis2, axis1, data(:,:,i),'EdgeColor','none','LineStyle','none','FaceLighting','phong');\n");
	matlabContentsFile.Append("\thColorBar = colorbar;\n");
	matlabContentsFile.Append("\tshading interp;\n");
	matlabContentsFile.Append("\tview(0, 90);\n");
	matlabContentsFile.Append("\taxis([axis2(1) axis2(length(axis2)) axis1(1) axis1(length(axis1))]);\n");
	matlabContentsFile.Append("\t\n");
	matlabContentsFile.Append("\thxLabel = xlabel('").Append(dim2Direction).Append(" (").Append(spaceUnit.GetValue()).Append(")');\n");
	matlabContentsFile.Append("\thyLabel = ylabel('").Append(dim1Direction).Append(" (").Append(spaceUnit.GetValue()).Append(")');\n");
	matlabContentsFile.Append("\tset(hxLabel,'FontSize', 11);\n");
	matlabContentsFile.Append("\tset(hyLabel,'FontSize', 11);\n");
	matlabContentsFile.Append("\tset(hyLabel,'FontSize', 11);\n");
	matlabContentsFile.Append("\n");
	matlabContentsFile.Append("\tplotTitle = ['").Append(GetName()).Append(". Frame = ' int2str(i+1) '. Time = ' num2str(time(i+1)) ' ").Append(timeUnit.GetValue()).Append("'];\n");
	matlabContentsFile.Append("\ttitle(plotTitle);\n");
	matlabContentsFile.Append("\t\n");
	matlabContentsFile.Append("\tpause(0.3);\n");
	matlabContentsFile.Append("end\n");

	wxString matlabFileName = path; matlabFileName.Append(baseFileName).Append(".m");
	saveOk &= FileManager::SaveFile(matlabFileName, matlabContentsFile);

	return saveOk;
}
