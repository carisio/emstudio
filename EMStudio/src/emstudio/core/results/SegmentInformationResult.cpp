/*
 * SegmentInformationResult.cpp
 *
 *  Created on: 10/07/2014
 *      Author: leandrocarisio
 */

#include "SegmentInformationResult.h"

#include "emstudio/util/resources/UtilResource.h"

namespace mom {

SegmentInformationResult::SegmentInformationResult(wxString title, GenericTable data)
		: TableResult(title, data) {
	SetCanBeInterpretedAsChart(false);
	AddProperty(Property("Frequency unit", &this->freqUnit));
}

SegmentInformationResult::~SegmentInformationResult() {
}
/**
 * Os campos são organizados em um GenericTable. Na tabela as colunas 0...13 representam:
 * 0 - frequency
 * 1 - X1
 * 2 - Y1
 * 3 - Z1
 * 4 - X2
 * 5 - Y2
 * 6 - Z2
 * 7 - Radius
 * 8 - InfoReal
 * 9 - InfoImag
 */
void SegmentInformationResult::SetData(GenericTable::ColumnDataRepresentation frequency,
		GenericTable::ColumnDataRepresentation x1, GenericTable::ColumnDataRepresentation y1, GenericTable::ColumnDataRepresentation z1,
		GenericTable::ColumnDataRepresentation x2, GenericTable::ColumnDataRepresentation y2, GenericTable::ColumnDataRepresentation z2,
		GenericTable::ColumnDataRepresentation radius,
		GenericTable::ColumnDataRepresentation infoReal, wxString infoRealLabel,
		GenericTable::ColumnDataRepresentation infoImag, wxString infoImagLabel,
		wxString unitFrequency, wxString unitLength) {

	GenericTable table;
	std::vector<wxString> columnsLabel;

	table.AddColumn(frequency);	columnsLabel.push_back("Frequency (" + unitFrequency + ")");
	table.AddColumn(x1);			columnsLabel.push_back("X1 (" + unitLength + ")");
	table.AddColumn(y1);			columnsLabel.push_back("Y1 (" + unitLength + ")");
	table.AddColumn(z1);			columnsLabel.push_back("Z1 (" + unitLength + ")");
	table.AddColumn(x2);			columnsLabel.push_back("X2 (" + unitLength + ")");
	table.AddColumn(y2);			columnsLabel.push_back("Y2 (" + unitLength + ")");
	table.AddColumn(z2);			columnsLabel.push_back("Z2 (" + unitLength + ")");
	table.AddColumn(radius);		columnsLabel.push_back("Radius (" + unitLength + ")");
	table.AddColumn(infoReal);		columnsLabel.push_back(infoRealLabel);
	table.AddColumn(infoImag);		columnsLabel.push_back(infoImagLabel);

	table.SetColumnsLabel(columnsLabel);
	TableResult::SetData(table);

	SetFrequencyUnit(unitFrequency);
}
void SegmentInformationResult::SetFrequencyUnit(wxString frequencyUnit) {
	freqUnit.SetValue(frequencyUnit);
}
wxString SegmentInformationResult::GetFrequencyUnit() {
	return freqUnit.GetValue();
}
GenericTable::ColumnDataRepresentation SegmentInformationResult::GetFrequency() {
	return GetData().GetColumns()[0];
}
GenericTable::ColumnDataRepresentation SegmentInformationResult::GetX1() {
	return GetData().GetColumns()[1];
}
GenericTable::ColumnDataRepresentation SegmentInformationResult::GetY1() {
	return GetData().GetColumns()[2];
}
GenericTable::ColumnDataRepresentation SegmentInformationResult::GetZ1() {
	return GetData().GetColumns()[3];
}
GenericTable::ColumnDataRepresentation SegmentInformationResult::GetX2() {
	return GetData().GetColumns()[4];
}
GenericTable::ColumnDataRepresentation SegmentInformationResult::GetY2() {
	return GetData().GetColumns()[5];
}
GenericTable::ColumnDataRepresentation SegmentInformationResult::GetZ2() {
	return GetData().GetColumns()[6];
}
GenericTable::ColumnDataRepresentation SegmentInformationResult::GetRadius() {
	return GetData().GetColumns()[7];
}
GenericTable::ColumnDataRepresentation SegmentInformationResult::GetInfoReal() {
	return GetData().GetColumns()[8];
}
GenericTable::ColumnDataRepresentation SegmentInformationResult::GetInfoImag() {
	return GetData().GetColumns()[9];
}

wxString SegmentInformationResult::GetResultClassName() {
	return "SegmentInformationResult";
}
ResultSmartPointer SegmentInformationResult::NewResult() {
	return ResultSmartPointer(new SegmentInformationResult);
}
bool SegmentInformationResult::ExportData(wxString fileName) {
	SetCanBeInterpretedAsChart(true);
	bool result = TableResult::ExportData(fileName);
	SetCanBeInterpretedAsChart(false);
	return result;
}
wxString SegmentInformationResult::GetMatlabFileContents(wxString dataFileName) {
	std::vector<GenericTable::ColumnDataRepresentation>& columns = GetData().GetColumns();
	std::vector<wxString>& columnsLabel = GetData().GetColumnsLabel();

	wxString contentsMatlabFile;
	contentsMatlabFile.Append("clear all;\n").Append("close all;\n").Append("clc;\n\n");
	contentsMatlabFile.Append("dataFile = load('").Append(dataFileName).Append("');\n\n");
	contentsMatlabFile.Append("% Change this line to show the current for other frequency\n");
	contentsMatlabFile.Append("f=").Append(Converter::DoubleToFormattedString_MaxPrecision(GetFrequency()[0])).Append(";\n");
	contentsMatlabFile.Append("% Change seg to increase precision of the segment\n");
	contentsMatlabFile.Append("seg = 8;\n");
	contentsMatlabFile.Append("% Change this to set the radius multiplier\n");
	contentsMatlabFile.Append("mult = 16;\n");
	contentsMatlabFile.Append("% Change this value if you want to plot a different variable\n");
	contentsMatlabFile.Append("% real = 0\n");
	contentsMatlabFile.Append("% imag = 1\n");
	contentsMatlabFile.Append("% amplitude = 2\n");
	contentsMatlabFile.Append("% phase = 3\n");
	contentsMatlabFile.Append("value = 2;\n\n");
	contentsMatlabFile.Append("% Separate data\n");
	contentsMatlabFile.Append("frequency = dataFile(:,1);\n");
	contentsMatlabFile.Append("X1 = dataFile(:,2);\n");
	contentsMatlabFile.Append("Y1 = dataFile(:,3);\n");
	contentsMatlabFile.Append("Z1 = dataFile(:,4);\n");
	contentsMatlabFile.Append("X2 = dataFile(:,5);\n");
	contentsMatlabFile.Append("Y2 = dataFile(:,6);\n");
	contentsMatlabFile.Append("Z2 = dataFile(:,7);\n");
	contentsMatlabFile.Append("radius = dataFile(:,8);\n");
	contentsMatlabFile.Append("info_re = dataFile(:,9);\n");
	contentsMatlabFile.Append("info_imag = dataFile(:,10);\n\n");
	contentsMatlabFile.Append("found = 0;\n");
	contentsMatlabFile.Append("minValue = 3e30;\n");
	contentsMatlabFile.Append("maxValue = -3e30;\n");
	contentsMatlabFile.Append("for i = 1:length(frequency)\n");
	contentsMatlabFile.Append("\tif (frequency(i) == f)\n");
	contentsMatlabFile.Append("\t\tfound = found+1;\n");
	contentsMatlabFile.Append("\t\tdata(found,:) = [X1(i) Y1(i) Z1(i) X2(i) Y2(i) Z2(i) radius(i) info_re(i) info_imag(i)];\n");
	contentsMatlabFile.Append("\t\tif (value == 0)\n");
	contentsMatlabFile.Append("\t\t\taux = info_re(i);\n");
	contentsMatlabFile.Append("\t\telseif (value == 1)\n");
	contentsMatlabFile.Append("\t\t\taux = info_imag(i);\n");
	contentsMatlabFile.Append("\t\telseif (value == 2)\n");
	contentsMatlabFile.Append("\t\t\taux = sqrt(info_re(i)*info_re(i) + info_imag(i)*info_imag(i));\n");
	contentsMatlabFile.Append("\t\telseif (value == 3)\n");
	contentsMatlabFile.Append("\t\t\taux = atan(info_imag(i)/info_re(i));\n");
	contentsMatlabFile.Append("\t\tend\n");
	contentsMatlabFile.Append("\t\tif (aux < minValue)\n");
	contentsMatlabFile.Append("\t\t\tminValue = aux;\n");
	contentsMatlabFile.Append("\t\tend\n");
	contentsMatlabFile.Append("\t\tif (aux > maxValue)\n");
	contentsMatlabFile.Append("\t\t\tmaxValue = aux;\n");
	contentsMatlabFile.Append("\t\tend\n");
	contentsMatlabFile.Append("\telse\n");
	contentsMatlabFile.Append("\t\tif (found > 0)\n");
	contentsMatlabFile.Append("\t\t\tbreak;\n");
	contentsMatlabFile.Append("\t\tend\n");
	contentsMatlabFile.Append("\tend\n");
	contentsMatlabFile.Append("end\n\n");
	contentsMatlabFile.Append("figure(1);\n");
	contentsMatlabFile.Append("hold on;\n");
	contentsMatlabFile.Append("[row col] = size(data);\n");
	contentsMatlabFile.Append("colormap = hsv;\n");
	contentsMatlabFile.Append("caxis([minValue maxValue]);\n");
	contentsMatlabFile.Append("for i = 1:row\n");
	contentsMatlabFile.Append("\txtop = data(i,1); ytop = data(i,2); ztop = data(i,3);\n");
	contentsMatlabFile.Append("\txbase = data(i,4); ybase = data(i,5); zbase = data(i,6);\n");
	contentsMatlabFile.Append("\tr = data(i,7) * mult;\n");
	contentsMatlabFile.Append("\tif (value == 0)\n");
	contentsMatlabFile.Append("\t\tcolor = data(i,8);\n");
	contentsMatlabFile.Append("\telseif (value == 1)\n");
	contentsMatlabFile.Append("\t\tcolor = data(i,9);\n");
	contentsMatlabFile.Append("\telseif (value == 2)\n");
	contentsMatlabFile.Append("\t\tcolor = sqrt(data(i,8)*data(i,8) + data(i,9)*data(i,9));\n");
	contentsMatlabFile.Append("\telseif (value == 3)\n");
	contentsMatlabFile.Append("\t\tcolor = atan(data(i,9)/data(i,8));\n");
	contentsMatlabFile.Append("\tend\n\n");
	contentsMatlabFile.Append("\tp1 = [xtop, ytop, ztop];\n");
	contentsMatlabFile.Append("\tp0 = [xbase, ybase, zbase];\n");
	contentsMatlabFile.Append("\tn = p1-p0;\n");
	contentsMatlabFile.Append("\td = n(1)*p0(1) + n(2)*p0(2) + n(3)*p0(3);\n");
	contentsMatlabFile.Append("\tpp = [0 0 0];\n");
	contentsMatlabFile.Append("\tif (n(1) ~= 0)\n");
	contentsMatlabFile.Append("\t\tpp(2) = p0(2)+1;\n");
	contentsMatlabFile.Append("\t\tpp(3) = p0(3)+1;\n");
	contentsMatlabFile.Append("\t\tpp(1) = (d - n(2) * pp(2) - n(3) * pp(3)) / n(1);\n");
	contentsMatlabFile.Append("\telseif (n(2) ~= 0)\n");
	contentsMatlabFile.Append("\t\tpp(1) = p0(1)+1;\n");
	contentsMatlabFile.Append("\t\tpp(3) = p0(3)+1;\n");
	contentsMatlabFile.Append("\t\tpp(2) = (d - n(1) * pp(1) - n(3) * pp(3)) / n(2);\n");
	contentsMatlabFile.Append("\telseif (n(3) ~= 0)\n");
	contentsMatlabFile.Append("\t\tpp(1) = p0(1)+1;\n");
	contentsMatlabFile.Append("\t\tpp(2) = p0(2)+1;\n");
	contentsMatlabFile.Append("\t\tpp(3) = (d - n(1) * pp(1) - n(2) * pp(2)) / n(3);\n");
	contentsMatlabFile.Append("\tend\n\n");
	contentsMatlabFile.Append("\tv1 = pp-p0;\n");
	contentsMatlabFile.Append("\tv2 = [(n(3)*v1(2)-n(2)*v1(3)) (n(1)*v1(3)-n(3)*v1(1)) (n(2)*v1(1)-n(1)*v1(2))];\n\n");
	contentsMatlabFile.Append("\tu1 = v1 / (sqrt(v1(1)^2 + v1(2)^2 + v1(3)^2));\n");
	contentsMatlabFile.Append("\tu2 = v2 / (sqrt(v2(1)^2 + v2(2)^2 + v2(3)^2));\n\n");
	contentsMatlabFile.Append("\tfor j = 0:seg-1\n");
	contentsMatlabFile.Append("\t\tthetaI = 2*pi*j/seg;\n");
	contentsMatlabFile.Append("\t\tthetaIplus1 = 2*pi*(j+1)/seg;\n\n");
	contentsMatlabFile.Append("\t\tcos_theta = cos(thetaI);\n");
	contentsMatlabFile.Append("\t\tsin_theta = sin(thetaI);\n");
	contentsMatlabFile.Append("\t\tcos_theta_plus1 = cos(thetaIplus1);\n");
	contentsMatlabFile.Append("\t\tsin_theta_plus1 = sin(thetaIplus1);\n\n");
	contentsMatlabFile.Append("\t\tauxTetaX = cos_theta * u1(1) + sin_theta * u2(1);\n");
	contentsMatlabFile.Append("\t\tauxTetaY = cos_theta * u1(2) + sin_theta * u2(2);\n");
	contentsMatlabFile.Append("\t\tauxTetaZ = cos_theta * u1(3) + sin_theta * u2(3);\n");
	contentsMatlabFile.Append("\t\tauxTetaPlus1X = cos_theta_plus1 * u1(1) + sin_theta_plus1 * u2(1);\n");
	contentsMatlabFile.Append("\t\tauxTetaPlus1Y = cos_theta_plus1 * u1(2) + sin_theta_plus1 * u2(2);\n");
	contentsMatlabFile.Append("\t\tauxTetaPlus1Z = cos_theta_plus1 * u1(3) + sin_theta_plus1 * u2(3);\n\n");
	contentsMatlabFile.Append("\t\tx1 = p0(1) + auxTetaX * r;\n");
	contentsMatlabFile.Append("\t\ty1 = p0(2) + auxTetaY * r;\n");
	contentsMatlabFile.Append("\t\tz1 = p0(3) + auxTetaZ * r;\n\n");
	contentsMatlabFile.Append("\t\tx2 = p0(1);\n");
	contentsMatlabFile.Append("\t\ty2 = p0(2);\n");
	contentsMatlabFile.Append("\t\tz2 = p0(3);\n\n");
	contentsMatlabFile.Append("\t\tx3 = p0(1);\n");
	contentsMatlabFile.Append("\t\ty3 = p0(2);\n");
	contentsMatlabFile.Append("\t\tz3 = p0(3);\n\n");
	contentsMatlabFile.Append("\t\tx4 = p0(1) + auxTetaPlus1X * r;\n");
	contentsMatlabFile.Append("\t\ty4 = p0(2) + auxTetaPlus1Y * r;\n");
	contentsMatlabFile.Append("\t\tz4 = p0(3) + auxTetaPlus1Z * r;\n\n");
	contentsMatlabFile.Append("\t\tx5 = p1(1) + auxTetaX * r;\n");
	contentsMatlabFile.Append("\t\ty5 = p1(2) + auxTetaY * r;\n");
	contentsMatlabFile.Append("\t\tz5 = p1(3) + auxTetaZ * r;\n\n");
	contentsMatlabFile.Append("\t\tx6 = p1(1);\n");
	contentsMatlabFile.Append("\t\ty6 = p1(2);\n");
	contentsMatlabFile.Append("\t\tz6 = p1(3);\n\n");
	contentsMatlabFile.Append("\t\tx7 = p1(1);\n");
	contentsMatlabFile.Append("\t\ty7 = p1(2);\n");
	contentsMatlabFile.Append("\t\tz7 = p1(3);\n\n");
	contentsMatlabFile.Append("\t\tx8 = p1(1) + auxTetaPlus1X * r;\n");
	contentsMatlabFile.Append("\t\ty8 = p1(2) + auxTetaPlus1Y * r;\n");
	contentsMatlabFile.Append("\t\tz8 = p1(3) + auxTetaPlus1Z * r;\n\n");
	contentsMatlabFile.Append("\t\tface1X = [x1 x2 x3 x4];\n");
	contentsMatlabFile.Append("\t\tface1Y = [y1 y2 y3 y4];\n");
	contentsMatlabFile.Append("\t\tface1Z = [z1 z2 z3 z4];\n");
	contentsMatlabFile.Append("\t\th = fill3(face1X, face1Y, face1Z, color);\n");
	contentsMatlabFile.Append("\t\tset(h,'EdgeColor','None');\n\n");
	contentsMatlabFile.Append("\t\tface2X = [x1 x4 x8 x5];\n");
	contentsMatlabFile.Append("\t\tface2Y = [y1 y4 y8 y5];\n");
	contentsMatlabFile.Append("\t\tface2Z = [z1 z4 z8 z5];\n");
	contentsMatlabFile.Append("\t\th = fill3(face2X, face2Y, face2Z, color);\n");
	contentsMatlabFile.Append("\t\tset(h,'EdgeColor','None');\n\n");
	contentsMatlabFile.Append("\t\tface3X = [x5 x6 x7 x8];\n");
	contentsMatlabFile.Append("\t\tface3Y = [y5 y6 y7 y8];\n");
	contentsMatlabFile.Append("\t\tface3Z = [z5 z6 z7 z8];\n");
	contentsMatlabFile.Append("\t\th = fill3(face3X, face3Y, face3Z, color);\n");
	contentsMatlabFile.Append("\t\tset(h,'EdgeColor','None');\n\n");
	contentsMatlabFile.Append("\t\tface4X = [x2 x3 x7 x6];\n");
	contentsMatlabFile.Append("\t\tface4Y = [y2 y3 y7 y6];\n");
	contentsMatlabFile.Append("\t\tface4Z = [z2 z3 z7 z6];\n");
	contentsMatlabFile.Append("\t\th = fill3(face4X, face4Y, face4Z, color);\n");
	contentsMatlabFile.Append("\t\tset(h,'EdgeColor','None');\n");
	contentsMatlabFile.Append("\tend\n");
	contentsMatlabFile.Append("end\n\n");
	contentsMatlabFile.Append("view([30 40 60]);\n\n");
	contentsMatlabFile.Append("oldAxis = axis;\n");
	contentsMatlabFile.Append("oldDiffX = oldAxis(2)-oldAxis(1);\n");
	contentsMatlabFile.Append("oldDiffY = oldAxis(4)-oldAxis(3);\n");
	contentsMatlabFile.Append("oldDiffZ = oldAxis(6)-oldAxis(5);\n");
	contentsMatlabFile.Append("oldDiffMax = max(oldDiffX, max(oldDiffY, oldDiffZ));\n\n");
	contentsMatlabFile.Append("newDiffX = oldDiffMax-oldDiffX;\n");
	contentsMatlabFile.Append("newDiffY = oldDiffMax-oldDiffY;\n");
	contentsMatlabFile.Append("newDiffZ = oldDiffMax-oldDiffZ;\n\n");
	contentsMatlabFile.Append("newAxis = [oldAxis(1)-newDiffX/2 oldAxis(2)+newDiffX/2 oldAxis(3)-newDiffY/2 oldAxis(4)+newDiffY/2 oldAxis(5)+newDiffZ/2 oldAxis(6)+newDiffZ/2];\n");
	contentsMatlabFile.Append("axis(newAxis);\n\n");
	contentsMatlabFile.Append("colorbar;\n");
	contentsMatlabFile.Append("xlabel('x'); ylabel('y'); zlabel('z');\n");

	return contentsMatlabFile;
}
wxIcon SegmentInformationResult::GetIcon() {
	return UtilResource::GetIcon("chart");
}
} /* namespace mom */
