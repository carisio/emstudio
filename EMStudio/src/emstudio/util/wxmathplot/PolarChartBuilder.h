/*
 * PolarChartBuilder.h
 *
 *  Created on: 18/04/2013
 *      Author: leandrocarisio
 */

#ifndef POLARCHARTBUILDER_H_
#define POLARCHARTBUILDER_H_

#include "mathplot.h"
#include <vector>
using namespace::std;

class  mpTextAbsolutPostion : public mpLayer {
public:
    /** @param name text to be drawn in the plot */
	mpTextAbsolutPostion(wxString name = wxT(""), double xPosition = 0, double yPosition = 0, double rotationAngleDegree = 0);

    /** Text Layer plot handler.
        This implementation will plot text adjusted to the visible area. */
    virtual void Plot(wxDC & dc, mpWindow & w);

    /** mpText should not be used for scaling decisions. */
    virtual bool HasBBox() { return FALSE; }

private:
    double x;
    double y;
    double rotationAngleDegree;
};

class PolarChartBuilder {
public:
	typedef vector<double> DoubleVec;
	typedef pair<DoubleVec, DoubleVec> DataXY;

private:
	/* Vari�veis relacionadas aos eixos */
	int clockwise;
	double initialAngleRadian;
	wxString horizontalAxisLabel, verticalAxisLabel;
	int nCircles; // N�mero de c�rculos
	int theta; //
	wxPen penOutterCircle; // Estilo do c�rculo externo
	wxPen penInnerCircle; // Estilo dos c�rculos internos
	bool showLabel;
	wxPen penLabel;

	/* Caneta default para o desenho das curvas */
	wxPen defaultDataPen;
	wxString defaultDataName;

	/* */
	bool autoYAxisLength;
	double yAxisLength;
	double yMin;
	double yMax;
	double deltaY;
	vector<DataXY> data;

	void CalculateyMinMax();
	void NormalizeYData();
	void ToScreenPosition(double radius, double angleDegree, double& x, double& y);
public:
	/* M�todos para a cria��o dos eixos */
	void SetAxisDirection(bool clockwise);
	void SetAxisLabel(wxString hLabel, wxString vLabel);
	void SetInitialAngle(double initialAngleDegree);
	void SetNumberOfCircles(int nCircles);
	void SetPenForCircles(wxPen penInnerCircle, wxPen penOutterCircle);
	void SetTickAngle(int theta = 30);
	void SetShowLabel(bool slabel);

	/* M�todo para a cria��o do layer com os dados */
	void SetDefaultDataPen(wxPen pen);
	void SetDefaultDataName(wxString name);
	void SetPenLabel(wxPen pen);

	/* Dist�ncia m�nima entre os eixos */
	void SetAutoYAxisLength(bool autoYAxisLength);
	void SetYAxisLength(double yAxisLength);

	/* Os m�todos Create devem ser chamados ap�s o PreConfigureBuilder */
	void SetData(vector<DataXY> data);
	vector<mpLayer*> CreateAxisLayer();
	vector<mpLayer*> CreateDataLayers(vector<wxString> dataNames = vector<wxString>(),  vector<wxPen> pen = vector<wxPen>());

	PolarChartBuilder();
	vector<mpLayer*> CreateDefaultLayers(vector<DataXY> data, vector<wxString> vecNames = vector<wxString>());

	virtual ~PolarChartBuilder();
};

void Insert(vector<mpLayer*>& to, vector<mpLayer*>& from);
#endif /* POLARCHARTBUILDER_H_ */
