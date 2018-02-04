/*
 * OpenGLVisualization.cpp
 *
 *  Created on: 14/12/2011
 *      Author: leandrocarisio
 */

#include "OpenGLVisualization.h"
#include "emstudio/util/resources/UtilResource.h"

#include <iostream>
using namespace::std;

OpenGLVisualization::OpenGLVisualization(wxWindow *parent)
		: wxGLCanvas(parent, wxID_ANY, NULL /* attribs */,
        wxDefaultPosition, wxDefaultSize,
        wxFULL_REPAINT_ON_RESIZE) {

	Connect(this->GetId(), wxEVT_PAINT, wxPaintEventHandler(OpenGLVisualization::OnPaint));
	Connect(this->GetId(), wxEVT_MOTION, wxMouseEventHandler(OpenGLVisualization::ProcessMouseEvents));
	Connect(this->GetId(), wxEVT_MOUSEWHEEL, wxMouseEventHandler(OpenGLVisualization::ProcessMouseEvents));
	Connect(this->GetId(), wxEVT_LEFT_DOWN, wxMouseEventHandler(OpenGLVisualization::ProcessMouseEvents));
	Connect(this->GetId(), wxEVT_LEFT_UP, wxMouseEventHandler(OpenGLVisualization::ProcessMouseEvents));
	Connect(this->GetId(), wxEVT_ENTER_WINDOW, wxMouseEventHandler(OpenGLVisualization::ChangeMouseCursor));
}

void OpenGLVisualization::OnPaint(wxPaintEvent& WXUNUSED(event)) {
//	cout << "-------------" << endl;
//	cout << "Chamando OpenGLVisualization::OnPaint" << endl;
//	cout << "\t Endereço de OpenGLVisualization = " << this << endl;
//	cout << "\t Endereço de OpenGLStateMachine = " << openGLStateMachine << endl;

    // Necessário, mesmo que não usado.
	wxPaintDC dc(this);

	const wxSize ClientSize = GetClientSize();

	// Render the graphics and swap the buffers.
	openGLStateMachine->SetCurrent(*this);
	glViewport(0, 0, ClientSize.x, ClientSize.y);
	openGLStateMachine->Draw(ClientSize);

	SwapBuffers();

//	cout << "showZoomRectangule = " << showZoomRectangule << endl;
	if (showZoomRectangule) {
		wxPen pen;
		pen.SetColour(0,0,0);
		pen.SetWidth(1);
		pen.SetStyle(wxSOLID);
		dc.SetPen(pen);
		// DrawRectangle desenha ele preenchido. Desenhar linhas.
		dc.DrawLine(xP1, yP1, xP1, yP2);
		dc.DrawLine(xP1, yP2, xP2, yP2);
		dc.DrawLine(xP2, yP2, xP2, yP1);
		dc.DrawLine(xP1, yP1, xP2, yP1);
	}
	openGLStateMachine->DrawDC(dc);
//	cout << "\t ClienteSize = " << ClientSize.x << "\t" << ClientSize.y << endl;
//	cout << "-------------" << endl;
}
void OpenGLVisualization::ChangeMouseCursor(wxMouseEvent& event) {
	wxCursor cursor(wxCURSOR_ARROW);
	if (mouseMoveFunction == MOVE) {
		cursor = wxCursor(wxCURSOR_HAND);
	} else if (mouseMoveFunction == ZOOM) {
		cursor = wxCursor(wxCURSOR_MAGNIFIER);
		wxBitmap icon = UtilResource::GetBitmapFromIcon("zoom");
		cursor = wxCursor(icon.ConvertToImage());
	} else if (mouseMoveFunction == ROTATE) {
		wxBitmap icon = UtilResource::GetBitmapFromIcon("rotate");
		cursor = wxCursor(icon.ConvertToImage());
	}
	SetCursor(cursor);
}
void OpenGLVisualization::ProcessMouseEvents(wxMouseEvent& event) {
//	cout << "VisualizationPanel::MouseMove" << endl;
//	cout << "\tIsDraging: " << event.Dragging() << endl;
//	cout << "\tIsButton: " << event.IsButton() << endl;
//	cout << "\tGetButton: " << event.GetButton() << endl;
//	cout << "\tWheelRotation: " << event.GetWheelRotation() << endl;
//	cout << "\tLeftDown: " << event.LeftDown() << endl;
//	cout << "\tLeftUp: " << event.LeftUp() << endl;

	// Movimento de rotação da camera
	// Salva o último ponto
	if (event.LeftDown()) {
		SetFocus();
		lastPoint = event.GetPosition();
		lastPoint3D = TrackBallMapping(lastPoint);
		leftButtonDownPosition3D = lastPoint3D;
		leftButtonDownPosition = event.GetPosition();
	}

	Rvector3 direction;
//	float pixel_diff;
//	float zoom_factor;
	float rot_angle;
	Rvector3 curPoint3D;
	wxPoint curPoint = event.GetPosition();
	double m_ROTSCALE = 100;

	if (event.Dragging()) {
		curPoint3D = TrackBallMapping(curPoint); // Map the mouse position to a logical
		// sphere location.
		direction.X = curPoint3D.X - lastPoint3D.X;
		direction.Y = curPoint3D.Y - lastPoint3D.Y;
		direction.Z = curPoint3D.Z - lastPoint3D.Z;
		float velocity = direction.Length();


		// If little movement - do nothing.
		if( velocity > 0.0001 ) {
			Rvector3 rotAxis = CrossProduct(lastPoint3D, curPoint3D);
			rot_angle = velocity * m_ROTSCALE;

			if (mouseMoveFunction == MOVE) {
				direction = direction * -1;
//				openGLStateMachine->Translate(direction.X, direction.Y, direction.Z);
				double dx = lastPoint.x - curPoint.x; dx /= +(GetClientSize().x);
				double dy = lastPoint.y - curPoint.y; dy /= -(GetClientSize().y);

//				cout << "\t\tdx = " << dx << endl;
//				cout << "\t\tdy = " << dy << endl;

				openGLStateMachine->Translate(dx, dy);


			} else if (mouseMoveFunction == ROTATE) {
				openGLStateMachine->Rotate(rot_angle, rotAxis.X, rotAxis.Y, rotAxis.Z);
			} else if (mouseMoveFunction == ZOOM) {
				wxPoint leftUp = event.GetPosition();

				/* Desenha um retângulo mostrando onde o usuário quer dar o zoom */
				xP1 = leftButtonDownPosition.x;
				yP1 = leftButtonDownPosition.y;
				xP2 = leftUp.x;
				yP2 = leftUp.y;
				showZoomRectangule = true;
			}

			Refresh();
		}

		lastPoint3D = curPoint3D;
		lastPoint = event.GetPosition();
	}

	if (event.LeftUp()) {
		showZoomRectangule = false;
	}

	if (event.LeftUp() && mouseMoveFunction == ZOOM) {
		double x1 = min(curPoint.x, leftButtonDownPosition.x);
		double x2 = max(curPoint.x, leftButtonDownPosition.x);
		double y1 = min(curPoint.y, leftButtonDownPosition.y);
		double y2 = max(curPoint.y, leftButtonDownPosition.y);

//		cout << "OpenGLVisualization::ZOOMINTO" << endl;
//		cout << "\t" << "x1 = "<< x1 << endl;
//		cout << "\t" << "x2 = "<< x2 << endl;
//		cout << "\t" << "y1 = "<< y1 << endl;
//		cout << "\t" << "y2 = "<< y2 << endl;
//		cout << "\t" << "GetClientSize().y = "<< GetClientSize().y << endl;
//		cout << "\t" << "GetClientSize().x = "<< GetClientSize().x << endl;

		double dx = x1/GetClientSize().x;
		double dy = (GetClientSize().y - y2)/GetClientSize().y;
		double normalized_width = (x2-x1)/GetClientSize().x;
		double normalized_height = (y2-y1)/GetClientSize().y;

		// Se o usuário tiver clicado por engano, dá um zoom de 2x, movendo o foco pra onde ele clicou
		if (normalized_height < 0.01 && normalized_width < 0.01) {
			normalized_height = 0.5;
			normalized_width = 0.5;
			dx -= 0.25;
			dy -= 0.25;
		}
		openGLStateMachine->ZoomInto(dx, dy, normalized_width, normalized_height);

		Refresh();
	}
	// Independente do modo da camera, se acionar a roda do mouse o zoom tem que funcionar, passando o modo para CAM_FREE
	if (event.GetWheelRotation() > 0) {
		openGLStateMachine->ZoomOut();
		Refresh();
	} else if (event.GetWheelRotation() < 0) {
		openGLStateMachine->ZoomIn();
		Refresh();
	}
}
void OpenGLVisualization::SetOpenGLStateMachine(OpenGLStateMachine* stateMachine) {
	this->openGLStateMachine = stateMachine;
}

OpenGLVisualization::~OpenGLVisualization() {
}



/*
 * Rotina extraída de http://www.cse.ohio-state.edu/~crawfis/Graphics/VirtualTrackball.html
 *
 * We want grab a sphere with the mouse and drag it. What we want is the intersection of the ray going
 * through the pixel with a sphere centered on the image plane. This sphere will have a finite extent.
 * If the ray does not intersect it, we will find the closest point on the sphere that does.
 * This will lie on the 2D circle in the image plane (z=0). The mouse point lies within this circle,
 * then it needs to be pulled up to the surface. If we consider the sphere as having a unit radius, then we simple
 * add a z component to our point to make it a unit length vector from the center.
 */
Rvector3 OpenGLVisualization::TrackBallMapping(wxPoint point) {
	wxSize windowSize = GetClientSize();
	Rvector3 v;
	float d;
	v.X = (2.0*point.x - windowSize.x) / windowSize.x;
	v.Y = (windowSize.y - 2.0*point.y) / windowSize.y;
	v.Z = 0.0;
	d = v.Length();
	d = (d<1.0) ? d : 1.0;
	v.Z = sqrtf(1.001 - d*d);
	v.Normalize(); // Still need to normalize, since we only capped d, not v.
	return v;
}

void OpenGLVisualization::SetCameraMode(int cameraMode) {
	if (cameraMode != CAM_FREE)
		mouseMoveFunction = NONE;

	openGLStateMachine->SetCameraMode(cameraMode);
	Refresh();
}
void OpenGLVisualization::SetMouseMoveFuncion(int function) {
	if (function != NONE)
		SetCameraMode(CAM_FREE);
	mouseMoveFunction = function;
}
