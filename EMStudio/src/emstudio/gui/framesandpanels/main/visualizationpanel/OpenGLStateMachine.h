/*
 * OpenGLStateMachine.h
 *
 *  Created on: 14/12/2011
 *      Author: leandrocarisio
 */

#ifndef OPENGLSTATEMACHINE_H_
#define OPENGLSTATEMACHINE_H_

#include "BasicOpenGLStateMachine.h"
#include "wx/glcanvas.h"
#include "wx/wx.h"
#include "emstudio/gui/elements/ElementManager.h"

#include <vector>
using std::vector;

class OpenGLStateMachine : public BasicOpenGLStateMachine {
private:
	ElementManagerSmartPointer elementsInProject;

	void DrawElementsInProject();
public:
	OpenGLStateMachine(wxGLCanvas *canvas, ElementManagerSmartPointer elementsInProject);
	virtual ~OpenGLStateMachine();

	virtual void GetProjectVolume(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
	virtual void DoDraw();
	virtual bool ShouldIDrawThisElement(ElementGUISmartPointer e);
};

#endif /* OPENGLSTATEMACHINE_H_ */
