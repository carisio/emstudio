/*
 * OpenGLStateMachine.cpp
 *
 *  Created on: 14/12/2011
 *      Author: leandrocarisio
 */

#include "OpenGLStateMachine.h"
//#include "GL/glut.h"
#include "emstudio/util/time/TicTac.h"
#include <iostream>
using namespace::std;
#include "emstudio/util/constants/Constants.h"
#include "emstudio/util/triangulate/Triangulate.h"

OpenGLStateMachine::OpenGLStateMachine(wxGLCanvas *canvas, ElementManagerSmartPointer elementsInProject)
	: BasicOpenGLStateMachine(canvas),
	  elementsInProject(elementsInProject) {
}
void OpenGLStateMachine::DrawElementsInProject() {
	ElementManager::ElementTypeList typeList = elementsInProject->GetElementTypeList();
    ElementManager::ElementTypeList::const_iterator iterator = typeList.begin();

    while (iterator != typeList.end()) {
    	ElementTypeSmartPointer type = *iterator;
    	ElementManager::ElementList elementsInCategory = elementsInProject->GetElementList(type);

    	ElementManager::ElementList::const_iterator iteratorList = elementsInCategory.begin();
    	while (iteratorList != elementsInCategory.end()) {
    		ElementGUISmartPointer element = *iteratorList;
    		if (ShouldIDrawThisElement(element)) {
    			element->Draw(this);
    		}
    		iteratorList++;
    	}
    	iterator++;
    }
}
bool OpenGLStateMachine::ShouldIDrawThisElement(ElementGUISmartPointer e) {
	return true;
}
void OpenGLStateMachine::DoDraw() {
	DrawElementsInProject();
}
/**
 * Retorna o volume do projeto.
 */
void OpenGLStateMachine::GetProjectVolume(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	double xminTemp, yminTemp, zminTemp;
	double xmaxTemp, ymaxTemp, zmaxTemp;

	xmin = ymin = zmin = 1e30;
	xmax = ymax = zmax = -1e30;

	ElementManager::ElementTypeList typeList = elementsInProject->GetElementTypeList();
    ElementManager::ElementTypeList::const_iterator iterator = typeList.begin();

    while (iterator != typeList.end()) {
    	ElementTypeSmartPointer type = *iterator;
    	ElementManager::ElementList elementsInCategory = elementsInProject->GetElementList(type);

    	ElementManager::ElementList::const_iterator iteratorList = elementsInCategory.begin();
    	while (iteratorList != elementsInCategory.end()) {
    		ElementGUISmartPointer element = *iteratorList;

    		if (element->FillApproximateDimensions(xminTemp, yminTemp, zminTemp, xmaxTemp, ymaxTemp, zmaxTemp)) {
    			if (xmin > xminTemp)
    				xmin = xminTemp;
    			if (ymin > yminTemp)
    			    ymin = yminTemp;
    			if (zmin > zminTemp)
    			    zmin = zminTemp;
    			if (xmax < xmaxTemp)
    				xmax = xmaxTemp;
    			if (ymax < ymaxTemp)
    			    ymax = ymaxTemp;
    			if (zmax < zmaxTemp)
    			    zmax = zmaxTemp;
    		}

    		iteratorList++;
    	}
    	iterator++;
    }

    if (xmin > xmax) {
    	xmin = 0;
    	xmax = 1;
    }
    if (ymin > ymax) {
    	ymin = 0;
    	ymax = 1;
    }
    if (zmin > zmax) {
    	zmin = 0;
    	zmax = 1;
    }
}
OpenGLStateMachine::~OpenGLStateMachine() {
}
