/*
 * PolarChartBuilder.cpp
 *
 *  Created on: 18/04/2013
 *      Author: leandrocarisio
 */

#include "PolarChartBuilder.h"
#include <iostream>
using namespace::std;


mpTextAbsolutPostion::mpTextAbsolutPostion(wxString name, double x, double y, double rotationAngleRadian) {
    SetName(name);

    this->x = x;
    this->y = y;
    this->rotationAngleDegree = rotationAngleRadian*180/3.14159265358979323846264338327950288419716939937511;
    m_type = mpLAYER_INFO;
}

/** mpText Layer plot handler.
This implementation will plot the text adjusted to the visible area.
*/

void mpTextAbsolutPostion::Plot(wxDC & dc, mpWindow & w)
{
	if (m_visible) {
		dc.SetPen(m_pen);
		dc.SetFont(m_font);

		wxCoord tw=0, th=0;
		dc.GetTextExtent( GetName(), &tw, &th);

	//     int left = -dc.LogicalToDeviceX(0);
	//     int width = dc.LogicalToDeviceX(0) - left;
	//     int bottom = dc.LogicalToDeviceY(0);
	//     int height = bottom - -dc.LogicalToDeviceY(0);

	/*    dc.DrawText( GetName(),
		(int)((((float)width/100.0) * m_offsety) + left - (tw/2)),
		(int)((((float)height/100.0) * m_offsetx) - bottom) );*/
		int px = w.x2p(x);
		int py = w.y2p(y);
		if (rotationAngleDegree == 0)
			dc.DrawText(GetName(), px, py);
		else
			dc.DrawRotatedText(GetName(), px, py, rotationAngleDegree);
	}
}


PolarChartBuilder::PolarChartBuilder() {
	horizontalAxisLabel = "";
	verticalAxisLabel = "";
	clockwise = 1;
	initialAngleRadian = 30*3.141592/180;
	nCircles = 5;
	theta = 30;
	penInnerCircle = wxPen(*wxBLACK, 1, wxPENSTYLE_DOT);
	penOutterCircle = wxPen(*wxBLACK, 1, wxPENSTYLE_SOLID);
	defaultDataPen = wxPen(*wxBLUE, 2, wxPENSTYLE_SOLID);
	defaultDataName = "";
	showLabel = true;
	penLabel = *wxBLACK_PEN;
	autoYAxisLength = true;
	yAxisLength = 60;
}

PolarChartBuilder::~PolarChartBuilder() {
}

vector<mpLayer*> PolarChartBuilder::CreateDefaultLayers(vector<DataXY> data, vector<wxString> vecNames) {
	vector<mpLayer*> result;

	SetData(data);

	/* Cria os eixos */
	vector<mpLayer*> layers = CreateAxisLayer();
	Insert(result, layers);

	/* Cria um mpFXYVector para cada DataXY correspondente. Nesse caso, considera que x contém os angulos em graus */
	layers = CreateDataLayers(vecNames);
	Insert(result, layers);

	return result;
}

void PolarChartBuilder::SetAutoYAxisLength(bool autoYAxisLength) {
	this->autoYAxisLength = autoYAxisLength;
}
void PolarChartBuilder::SetYAxisLength(double yAxisLength) {
	SetAutoYAxisLength(false);
	this->yAxisLength = yAxisLength;
}

void PolarChartBuilder::SetData(vector<DataXY> data) {
	this->data = data;

	/* Calcula o valor mínimo e máximo do eixo y considerando o conjunto de dados dos layers de entrada */
	CalculateyMinMax();

	/* Normaliza o eixo y dos vetores de entrada de forma que o menor valor corresponda a 0 e o maior, a 'a' */
	NormalizeYData();

}

void PolarChartBuilder::SetTickAngle(int theta) {
	if (theta <= 5) {
		theta = 30;
	}
	this->theta = theta;
}
void PolarChartBuilder::SetShowLabel(bool slabel) {
	showLabel = slabel;
}
void PolarChartBuilder::SetAxisLabel(wxString hLabel, wxString vLabel) {
	horizontalAxisLabel = hLabel;
	verticalAxisLabel = vLabel;
}
void PolarChartBuilder::SetAxisDirection(bool clockwise) {
	if (clockwise)
		this->clockwise = -1;
	else
		this->clockwise = 1;
}
void PolarChartBuilder::SetInitialAngle(double initialAngleDegree) {
	this->initialAngleRadian = initialAngleDegree*3.14159265358979323846264338327950288419716939937511/180;
}
void PolarChartBuilder::SetNumberOfCircles(int nCircles) {
	if (nCircles >= 1 && nCircles <= 10) {
		this->nCircles = nCircles;
	} else {
		this->nCircles = 5;
	}
}
void PolarChartBuilder::SetPenForCircles(wxPen penInnerCircle, wxPen penOutterCircle) {
	this->penInnerCircle = penInnerCircle;
	this->penOutterCircle = penOutterCircle;
}

vector<mpLayer*> PolarChartBuilder::CreateAxisLayer() {
	vector<mpLayer*> destination;

	/* Desenha círculos concentricos */
	for (int i = 1; i <= nCircles; i++) {
		DoubleVec vectorx;
		DoubleVec vectory;

		double radius = ((double)i)/((double)nCircles);

		for (size_t ang = 0; ang <= 360; ang = ang + (nCircles-i+1)) {
			double x, y;
			ToScreenPosition(radius, ang, x, y);

			vectorx.push_back(x);
			vectory.push_back(y);
		}

		mpFXYVector* vectorLayer = new mpFXYVector;
		vectorLayer->SetData(vectorx, vectory);
		vectorLayer->SetContinuity(true);

		if (i == nCircles) {
			vectorLayer->SetPen(penOutterCircle);
		} else {
			vectorLayer->SetPen(penInnerCircle);
		}
		vectorLayer->SetDrawOutsideMargins(false);

		destination.push_back(vectorLayer);

		if (showLabel) {
			float circleValue = (yMin + radius*deltaY);
			wxString str = wxString::Format(wxT("%.1f"), circleValue);

			mpTextAbsolutPostion* txtInfo = new mpTextAbsolutPostion(str, radius*1.05, 0.1);
			txtInfo->SetPen(penLabel);
			destination.push_back(txtInfo);
		}
	}

	/* Desenha indicação dos ângulos */
	for (int ang = 0; ang < 360; ang = ang + theta) {

		DoubleVec vectorx;
		DoubleVec vectory;

		int nPontos = 10;
		for (int i = 0; i <= nPontos; i++) {
			double radius = ((double)i)/((double)nPontos);

			double x, y;
			ToScreenPosition(radius, ang, x, y);
			vectorx.push_back(x);
			vectory.push_back(y);
		}

		mpFXYVector* vectorLayer = new mpFXYVector;
		vectorLayer->SetData(vectorx, vectory);
		vectorLayer->SetContinuity(true);
		vectorLayer->SetPen(penInnerCircle);
		vectorLayer->SetDrawOutsideMargins(false);

		destination.push_back(vectorLayer);

		if (showLabel) {
			wxString str = wxString::Format(wxT("%i"), ang);

			double radius = 1.05;
			if (ang < 270)
				radius = 1.15;

			double x, y;
			ToScreenPosition(radius, ang, x, y);
			mpTextAbsolutPostion* txtInfo = new mpTextAbsolutPostion(str, x, y);
			txtInfo->SetPen(penLabel);
			destination.push_back(txtInfo);
		}
	}

	/* Desenha o label dos eixos */
	double xHorizontalAxis, yHorizontalAxis, xVerticalAxis, yVerticalAxis;
	double radius = 1.2;
	ToScreenPosition(radius, 0, xHorizontalAxis, yHorizontalAxis);
	ToScreenPosition(radius, 90, xVerticalAxis, yVerticalAxis);
	mpTextAbsolutPostion* txtHorizontalAxisInfo = new mpTextAbsolutPostion(horizontalAxisLabel, xHorizontalAxis, yHorizontalAxis,  clockwise*initialAngleRadian);
	mpTextAbsolutPostion* txtVerticalAxisInfo = new mpTextAbsolutPostion(verticalAxisLabel, xVerticalAxis, yVerticalAxis, clockwise*initialAngleRadian);
	destination.push_back(txtHorizontalAxisInfo);
	destination.push_back(txtVerticalAxisInfo);

	return destination;
}
void PolarChartBuilder::SetDefaultDataPen(wxPen pen) {
	defaultDataPen = pen;
}
void PolarChartBuilder::SetPenLabel(wxPen pen) {
	penLabel = pen;
}
void PolarChartBuilder::SetDefaultDataName(wxString name) {
	defaultDataName = name;
}

vector<mpLayer*> PolarChartBuilder::CreateDataLayers(vector<wxString> dataNames,  vector<wxPen> pens) {
	vector<mpLayer*> destination;

	bool defaultName = dataNames.size() == data.size() ? false: true;
	bool defaultPen = pens.size() == data.size() ? false: true;

	for (size_t i = 0; i < data.size(); i++) {
		DataXY& xyData = data[i];

		DoubleVec vectorx = xyData.first;
		DoubleVec vectory = xyData.second;

		for (size_t j = 0; j < vectorx.size(); j++) {
			double ang = vectorx[j];
			double radius = vectory[j];
			ToScreenPosition(radius, ang, vectorx[j], vectory[j]);
		}

		wxString name = defaultName ? defaultDataName : dataNames[i];
		wxPen pen = defaultPen ? defaultDataPen : pens[i];

		mpFXYVector* vectorLayer = new mpFXYVector(name);
		vectorLayer->SetData(vectorx, vectory);
		vectorLayer->SetContinuity(true);
		vectorLayer->SetPen(pen);
		vectorLayer->SetDrawOutsideMargins(false);
		destination.push_back(vectorLayer);
	}

	return destination;
}
void PolarChartBuilder::ToScreenPosition(double normalizedRadius, double angleDegree, double& x, double& y) {
	/* Raio está normalizado. Então basta pegar o valor que chegou aqui*/
	double phase = clockwise * (angleDegree*3.14159265358979323846264338327950288419716939937511/180 + initialAngleRadian);
	x = normalizedRadius*cos(phase);
	y = normalizedRadius*sin(phase);
}
void PolarChartBuilder::NormalizeYData() {
	for (size_t i = 0; i < data.size(); i++) {
		DataXY& xyData = data[i];

		DoubleVec& oldYData = xyData.second;
		for (size_t j = 0; j < oldYData.size(); j++) {
//			cout << "A\t" << oldYData[i]  << "\t" << yMin << endl;
			if (oldYData[j] < yMin) {
				oldYData[j] = yMin; // Necessário porque yMin pode ter sido alterado em CalculateyMinMax() para reduzir/aumentar tamanho do eixo
				cout << "D\t" << oldYData[j]  << "\t" << yMin << endl;
			}
			oldYData[j] = (oldYData[j] - (yMin))/deltaY;
		}
	}
}

void PolarChartBuilder::CalculateyMinMax() {
	yMin = 1e30;
	yMax = -1e30;

	for (size_t i = 0; i < data.size(); i++) {
		DataXY xyData = data[i];
		DoubleVec yData = xyData.second;

		for (size_t j = 0; j < yData.size(); j++) {
			double y = yData[j];
			if (yMin > y) {
				yMin = y;
			}
			if (yMax < y) {
				yMax = y;
			}
		}
	}

	deltaY = yMax-yMin;

	if (!autoYAxisLength) {
		deltaY = yAxisLength;
		yMin = yMax - deltaY;
	}
//	cout << "yMin, yMax = " << yMin << " , " << yMax << endl;
//	cout << "ydeltaY = " << deltaY << endl;
}

void Insert(vector<mpLayer*>& to, vector<mpLayer*>& from) {
	to.insert(to.end(), from.begin(), from.end());
}
