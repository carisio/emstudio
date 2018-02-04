/*
 * BasicOpenGLStateMachine.h
 *
 *  Created on: 12/06/2014
 *      Author: leandrocarisio
 */

#ifndef BASICOPENGLSTATEMACHINE_H_
#define BASICOPENGLSTATEMACHINE_H_

#include "wx/glcanvas.h"
#include "wx/wx.h"
#include <GL/glut.h>
#include "emstudio/util/facet/Facet.h"
#include "emstudio/util/vector/Rvector3.h"
#include "emstudio/util/nec/Segment.h"
#include "emstudio/gui/basetypes/GenericSheet.h"

#include <vector>
using std::vector;

enum CamaraPosition{CAM_AUTO, CAM_XY, CAM_XZ, CAM_YZ, CAM_FREE};

class BasicOpenGLStateMachine : public wxGLContext {
private:
	wxSize clientSize;

	double left;
	double right;
	double top;
	double bottom;
//	double dx, dy;

	int cameraMode;
	double zoomFactor;

	GLfloat currentModelViewMatrix[16];
	GLfloat currentProjectionMatrix[16];

	double xmin, ymin, zmin, xmax, ymax, zmax;
	void DrawAxisArrow(double x, double y, double z, bool xOriented, bool yOriented);
	void DrawAxis();
	void SetCamera();
	void SetProjection(wxSize clientSize);

	void ConfigureLight();
	void ConfigureMaterial();

	void InitializeVisualizationArea();

public:
	BasicOpenGLStateMachine(wxGLCanvas *canvas);
	virtual ~BasicOpenGLStateMachine();

	void Draw(wxSize clientSize);
	virtual void DoDraw();
	virtual void DrawDC(wxPaintDC& dc);

	virtual void GetProjectVolume(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);

	void SetCameraMode(int mode);
	int GetCameraMode();

	void Rotate(double angle, double x, double y, double z);
	void Translate(double x, double y);
	void Translate(double x, double y, double z);
	void ZoomOut();
	void ZoomIn();
	void Zoom(double zoomFactor);
	void ZoomInto(double dx, double dy, double normalizedWidth, double normalizedHeight);
};

void InitializeModelViewMatrix();
void SetColor(wxColour color);
void SetColor(wxColour color, double alpha);
void DrawCylinder(double length, double radius, double transx, double transy, double transz, double angle, double rotx, double roty, double rotz, bool fill = false);
void DrawBox(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax, bool fill = false);
void DrawSphere(double radius, double transx, double transy, double transz, double angle, double rotx, double roty, double rotz, bool fill = false);
void DrawPoint(double x, double y, double z, float pointSize = 1.0f);
void DrawPolygon2D(GenericSheet sheet, bool fill = false);
void DrawPolygon(Facet face, bool fill = false);
void DrawPolygons(vector<Facet> faces, bool fill = false);
void DrawSegment(double x1, double y1, double z1, double x2, double y2, double z2, double radius, bool fill = false);
void DrawSegment(Segment& s, bool fill = false);
void DrawSegments(Segments& ss, bool fill = false);
void DrawLine(Rvector3 p1, Rvector3 p2, float lineWidth = 2.0f);
void DrawLine(double x1, double y1, double z1, double x2, double y2, double z2, float lineWidth = 2.0f);
void DrawPlaneX(double ymin, double zmin, double ymax, double zmax, double x, bool fill = false);
void DrawPlaneY(double xmin, double zmin, double xmax, double zmax, double y, bool fill = false);
void DrawPlaneZ(double xmin, double ymin, double xmax, double ymax, double z, bool fill = false);


#endif /* BASICOPENGLSTATEMACHINE_H_ */
