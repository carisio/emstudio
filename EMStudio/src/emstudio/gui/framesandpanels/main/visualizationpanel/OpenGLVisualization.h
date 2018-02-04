/*
 * OpenGLVisualization.h
 *
 *  Created on: 14/12/2011
 *      Author: leandrocarisio
 */

#ifndef OPENGLVISUALIZATION_H_
#define OPENGLVISUALIZATION_H_

#include "wx/wx.h"
#include "wx/glcanvas.h"
#include "OpenGLStateMachine.h"
#include "emstudio/util/vector/Rvector3.h"

enum MouseMoveFunction{NONE, MOVE, ZOOM, ROTATE};

class OpenGLVisualization : public wxGLCanvas {
private:
	int mouseMoveFunction;
	OpenGLStateMachine* openGLStateMachine;

	Rvector3 lastPoint3D;
	Rvector3 leftButtonDownPosition3D;
	wxPoint leftButtonDownPosition;
	wxPoint lastPoint;
	void ProcessMouseEvents(wxMouseEvent& event);
	void ChangeMouseCursor(wxMouseEvent& event);
	Rvector3 TrackBallMapping(wxPoint point);

	/* Informações do retângulo para mostrar o zoom */
	int xP1, yP1, xP2, yP2;
	bool showZoomRectangule;
	void HideZoomRectangle();
public:
	OpenGLVisualization(wxWindow *parent);
	virtual ~OpenGLVisualization();

	void SetOpenGLStateMachine(OpenGLStateMachine* stateMachine);
	void OnPaint(wxPaintEvent& event);

	void SetCameraMode(int cameraMode);
	void SetMouseMoveFuncion(int function);
};

#endif /* OPENGLVISUALIZATION_H_ */
