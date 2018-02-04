/*
 * BasicOpenGLStateMachine.cpp
 *
 *  Created on: 12/06/2014
 *      Author: leandrocarisio
 */

#include "BasicOpenGLStateMachine.h"
#include "emstudio/util/time/TicTac.h"
#include <iostream>
using namespace::std;
#include "emstudio/util/constants/Constants.h"
#include "emstudio/util/triangulate/Triangulate.h"

BasicOpenGLStateMachine::BasicOpenGLStateMachine(wxGLCanvas *canvas)
	:  wxGLContext(canvas),
	   cameraMode(CAM_AUTO),
	   zoomFactor(1) {
	    SetCurrent(*canvas);

	    // set up the parameters we want to use
	    glEnable(GL_DEPTH_TEST);
	//    glDisable(GL_DEPTH_TEST); // Precisa pro alpha funcionar (glColor4f)

	    //////// LUZ ////////
	    glEnable(GL_LIGHTING);
	    glEnable(GL_LIGHT0);

	    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE) ;
	    glEnable(GL_COLOR_MATERIAL) ;

	    GLfloat ambient[] = { 0.4, 0.4, 0.4, 1 };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	    GLfloat specularLight[] = {0.5, 0.5, 0.5, 1.0};
	    GLfloat difuse[] = {1,1,1, 1.0};
	    GLfloat lightPosition0[] = {1e10, 1e10, 1e10, 1.0};


	    glLightfv(GL_LIGHT0, GL_DIFFUSE, difuse);
	    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight );
	    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0 );

		glEnable(GL_NORMALIZE);

	    GLfloat specMat[] = {0.8, 0.8, 0.8, 1.0};
	    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specMat);
	    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 100);
	    //////// LUZ ////////

	    glClearColor(1, 1, 1, 0);

	    // set viewing projection
	    GetProjectVolume(xmin, ymin, zmin, xmax, ymax, zmax);
	    InitializeVisualizationArea();
	    SetProjection(canvas->GetClientSize());

}
void BasicOpenGLStateMachine::Draw(wxSize clientSize) {
//	cout << "Chamando BasicOpenGLStateMachine::Draw" << endl;
//	cout << "\t Endereço de BasicOpenGLStateMachine = " << this << endl;

	this->clientSize = clientSize;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Atribui às variáveis xmin...zmax o tamanho aproximado do projeto
    GetProjectVolume(xmin, ymin, zmin, xmax, ymax, zmax);

    // Recalcula os parametros left, right, bottom e top, se a camera estiver em um dos modos automático.
    SetCameraMode(cameraMode);
    //////////////////////////
    // Volume de visuzalição
    SetProjection(clientSize);
    //////////////////////////

    InitializeModelViewMatrix();
    SetCamera();
    DrawAxis();

    DoDraw();

    glFlush();
}
void BasicOpenGLStateMachine::DoDraw() {

}
/**
 * Desenha uma miniatura dos eixos
 * O ponto (0,0) de tela é representado pelas variáveis (iX, iY)
 *
 *      Z  => ponto de tela: (iX, iY - axisLength)
 *      |
 *      |
 *      |______ Y => ponto de tela: (iX + axisLength, iY)
 *     /
 *    /
 *   / X => ponto de tela: (iX - 0.707*axisLength, iY + 0.707*axisLength) (o certo seria 0.707, mas o código foi implementado com 0.6 pra ficar visualmente melhor)
 */
void BasicOpenGLStateMachine::DrawDC(wxPaintDC& dc) {
	// TODO: PAREI AQUI. ARRUMAR ESSE CÓDIGO PARA MOSTRAR UMA MINIATURA DOS EIXOS!

	// X = vermelho
	// Y = verde
	// Z = azul
	int axisLength = 30;
	int emptySpace = 20;
	int xScreen = dc.GetSize().x;
	int yScreen = dc.GetSize().y;
	int iX = xScreen - axisLength - emptySpace;
	int iY = yScreen - 0.707*axisLength - emptySpace;
	cout << "iX = " << iX << endl;
	cout << "iY = " << iY << endl;
	cout << "iX-a = " << iX-0.707*axisLength << endl;
	cout << "iY+a = " << iY+0.707*axisLength << endl;

//	wxBrush brush(wxColour(255, 255, 255), wxTRANSPARENT);
//	dc.SetBrush(wxBrush(*wxGREEN, wxSOLID));
//	dc.SetBackgroundMode(wxTRANSPARENT);

	// Draw x axis
	dc.SetPen(wxPen(*wxRED,1));
	// Por algum motivo, no windows 7 o desenho dessa linha mostra um fundo cinza
	// Então a solução seria desenhar cada pixel da linha, mas também não funciona no windows 7 (a linha só aparece quando o zoom rectangle é mostrado)
	// Assim, a solução foi desenhar em vez de um pixel, um retângulo de lado 2 na posição de cada pixel.
	//	dc.DrawLine(iX, iY, iX - 0.707*axisLength, iY + 0.707*axisLength);
	for (int i = iX; i > iX - 0.6*axisLength; i--) {
		wxPoint point(i -1, -i+iX+iY -1);
		dc.DrawRectangle(point.x, point.y,2,2);
	}
	wxPen pp(*wxRED, 1, wxTRANSPARENT);
	wxBrush bb(*wxWHITE);
	dc.SetPen(pp);
	dc.SetBrush(bb);
	dc.SetBackgroundMode(wxTRANSPARENT);
	dc.SetTextForeground(*wxRED);
	dc.ResetBoundingBox();
	dc.DrawText("X", iX-0.6*axisLength+5, iY+0.6*axisLength);
	dc.DrawRectangle(wxRect(wxPoint(dc.MinX(), dc.MinY()), wxPoint(dc.MaxX(), dc.MaxY())));
	dc.DrawText("X", iX-0.6*axisLength+5, iY+0.6*axisLength);

	// Draw y axis
	dc.SetPen(wxPen(*wxGREEN,2));
	dc.DrawLine(iX, iY, iX + axisLength, iY);
	dc.SetPen(pp);
	dc.SetBrush(bb);
	dc.SetBackgroundMode(wxTRANSPARENT);
	dc.SetTextForeground(*wxGREEN);
	dc.ResetBoundingBox();
	dc.DrawText("Y", iX + axisLength, iY+5);
	dc.DrawRectangle(wxRect(wxPoint(dc.MinX(), dc.MinY()), wxPoint(dc.MaxX(), dc.MaxY())));
	dc.DrawText("Y", iX + axisLength, iY+5);

	// Draw z axis
	dc.SetPen(wxPen(*wxBLUE,2));
	dc.DrawLine(iX, iY, iX, iY - axisLength);
	dc.SetPen(pp);
	dc.SetBrush(bb);
	dc.SetBackgroundMode(wxTRANSPARENT);
	dc.SetTextForeground(*wxBLUE);
	dc.ResetBoundingBox();
	dc.DrawText("Z", iX+5, iY - axisLength);
	dc.DrawRectangle(wxRect(wxPoint(dc.MinX(), dc.MinY()), wxPoint(dc.MaxX(), dc.MaxY())));
	dc.DrawText("Z", iX+5, iY - axisLength);
}

void BasicOpenGLStateMachine::InitializeVisualizationArea() {
	GetProjectVolume(xmin, ymin, zmin, xmax, ymax, zmax);
    double dist_camera_project = max(max(xmax-xmin, ymax-ymin), zmax-zmin);
    double maxDimension = max(xmax-xmin, ymax-ymin);
    maxDimension = dist_camera_project;

	left = -maxDimension;
	right = maxDimension;
	bottom = -maxDimension;
	top = maxDimension;
}
/**
 * Retorna o volume do projeto.
 */
void BasicOpenGLStateMachine::GetProjectVolume(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
   	xmin = 0;
   	xmax = 1;
   	ymin = 0;
   	ymax = 1;
   	zmin = 0;
   	zmax = 1;
}
/**
 * Seta a projeção automaticamente com base no volume do projeto
 */
void BasicOpenGLStateMachine::SetProjection(wxSize clientSize) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    double dist_camera_project = max(max(xmax-xmin, ymax-ymin), zmax-zmin);
    double maxDimension = max(xmax-xmin, ymax-ymin);
    maxDimension = dist_camera_project;
    double zDimension = zmax-zmin;
    float w = clientSize.x;
    float h = clientSize.y;

    if (w <= h) {
   		glOrtho(left*zoomFactor, right*zoomFactor, bottom*h/w*zoomFactor, top*h/w*zoomFactor, -3*(zDimension+dist_camera_project), 3*(zDimension+dist_camera_project));
    } else {
   		glOrtho(left*w/h*zoomFactor, right*w/h*zoomFactor, bottom*zoomFactor, top*zoomFactor, -3*(zDimension+dist_camera_project), 3*(zDimension+dist_camera_project));
    }

}

/**
 * Altera os vários parametros da camera.
 */
void BasicOpenGLStateMachine::SetCamera() {
    double dist_camera_project = max(max(xmax-xmin, ymax-ymin), zmax-zmin);
    dist_camera_project = max(xmax-xmin, ymax-ymin);

    double xCam = 0, yCam = 0, zCam = 0;
    double xObj = 0, yObj = 0, zObj = 0;
    double upX = 0, upY = 0, upZ = 1;

    if (cameraMode == CAM_AUTO) {
    	xCam = xmin+dist_camera_project;
		yCam = ymin+dist_camera_project;
		zCam = zmin+dist_camera_project;

		xObj = xmin;
		yObj = ymin;
		zObj = zmin+dist_camera_project*0.4;

		upX = 0; upY = 0; upZ = 1;

		gluLookAt (xCam, yCam, zCam, xObj, yObj, zObj, upX, upY, upZ);
	} else if (cameraMode == CAM_XY) {
		xCam = xmin + (xmax-xmin) / 2;
		yCam = ymin + (ymax-ymin) / 2;
		zCam = 1.0001*zmax;

		xObj = xmin + (xmax-xmin) / 2;
		yObj = ymin + (ymax-ymin) / 2;
		zObj = zmin;

		upX = 0; upY = 1; upZ = 0;

		gluLookAt (xCam, yCam, zCam, xObj, yObj, zObj, upX, upY, upZ);
	} else if (cameraMode == CAM_YZ) {
		xCam = 1.0001*xmax;
		yCam = ymin + (ymax-ymin) / 2;
		zCam = zmin + (zmax-zmin) / 2;

		xObj = xmin;
		yObj = ymin + (ymax-ymin) / 2;
		zObj = zmin + (zmax-zmin) / 2;

		upX = 0; upY = 0; upZ = 1;

		gluLookAt (xCam, yCam, zCam, xObj, yObj, zObj, upX, upY, upZ);
	} else if (cameraMode == CAM_XZ) {
		xCam = xmin + (xmax-xmin) / 2;
		yCam = ymin - (0.9999*abs(ymin));
		zCam = zmin + (zmax-zmin) / 2;

		xObj = xmin + (xmax-xmin) / 2;
		yObj = ymax;
		zObj = zmin + (zmax-zmin) / 2;

		upX = 0; upY = 0; upZ = 1;


		gluLookAt (xCam, yCam, zCam, xObj, yObj, zObj, upX, upY, upZ);
	} else if (cameraMode == CAM_FREE) {
		glMatrixMode(GL_MODELVIEW_MATRIX);
		glLoadMatrixf(currentModelViewMatrix);
	}
}
void BasicOpenGLStateMachine::SetCameraMode(int mode) {
	cameraMode = mode;

	if (mode != CAM_FREE) {
		// Inicializa o zoom e a área de visualização;
		InitializeVisualizationArea();
		zoomFactor = 1;
	}

	glGetFloatv(GL_MODELVIEW_MATRIX, currentModelViewMatrix);
}
int BasicOpenGLStateMachine::GetCameraMode() {
	return cameraMode;
}
/**
 * Usado para rotacionar a camera no modo livre.
 * Gira a matrix modelview.
 * Caso a camera esteja no modo livre, tem que salvar novamente a matriz. A chamada a SetCameraMode(CAM_FREE) faz esse salvamento.
 */
void BasicOpenGLStateMachine::Rotate(double angle, double x, double y, double z) {
	SetCameraMode(CAM_FREE);

	glMatrixMode(GL_MODELVIEW_MATRIX);
	glLoadIdentity();
	glRotated(angle, x, y, z);
	glMultMatrixf( (GLfloat *) currentModelViewMatrix);

	// Salva a nova posição da camera
	SetCameraMode(CAM_FREE);
}
/**
 * Usado com a função de PAN
 * Recebe os dx e dy em coordenadas de tela. Converte para o mundo que representa.
 */
void BasicOpenGLStateMachine::Translate(double dx, double dy) {
	// dx e dy foram passados em coordenadas de tela. É necessário normalizar para o cálculo das coordenadas corretas.
	double Dx = (right - left)*dx;
	double Dy = (top - bottom)*dy;
	left += Dx; right += Dx;
	top += Dy; bottom += Dy;

	SetCameraMode(CAM_FREE);
}
/**
 * Usado para movimentar a camera no modo livre.
 * Gira a matrix modelview.
 * Caso a camera esteja no modo livre, tem que salvar novamente a matriz. A chamada a SetCameraMode(CAM_FREE) faz esse salvamento.
 */
void BasicOpenGLStateMachine::Translate(double x, double y, double z) {
	SetCameraMode(CAM_FREE);

	double translateFactor = (left-right);
	translateFactor = (top-bottom) < translateFactor ? (top-bottom) : translateFactor;
	translateFactor *= zoomFactor;

	glMatrixMode(GL_MODELVIEW_MATRIX);
	glLoadIdentity();
	glTranslated(x*translateFactor, y*translateFactor, z*translateFactor);
	glMultMatrixf( (GLfloat *) currentModelViewMatrix);

	// Salva a nova posição da camera
	SetCameraMode(CAM_FREE);
}

void BasicOpenGLStateMachine::ZoomOut() {
	Zoom(2);
}
void BasicOpenGLStateMachine::ZoomIn() {
	Zoom(0.5);
}
void BasicOpenGLStateMachine::Zoom(double zoomFactor) {
	this->zoomFactor *= zoomFactor;
	SetCameraMode(CAM_FREE);
}
void BasicOpenGLStateMachine::ZoomInto(double dx, double dy, double normalizedWidth, double normalizedHeight) {
	// Para não distorcer, o zoom tem que ser igual nas duas direções:
	if (normalizedHeight > normalizedWidth) {
		/*
		 *  Como o usuário quer uma altura maior, a largura também terá que ser maior.
		 *  É necessário reajustar também o espaçamento.
		 */
		dx = dx - (normalizedHeight-normalizedWidth)/2;
		normalizedWidth = normalizedHeight;
	} else {
		dy = dy - (normalizedWidth-normalizedHeight)/2;
		normalizedHeight = normalizedWidth;
	}
//	cout << "BasicOpenGLStateMachine::ZoomInto" << endl;
//	cout << "\t" << "dx = " << dx << endl;
//	cout << "\t" << "dy = " << dy << endl;
//	cout << "\t" << "normalizedWidth = " << normalizedWidth << endl;
//	cout << "\t" << "normalizedHeight = " << normalizedHeight << endl;

	double width = right-left;
	double height = top-bottom;

//	cout << "\t" << "left = " << left << endl;
//	cout << "\t" << "right = " << right << endl;
//	cout << "\t" << "top = " << top << endl;
//	cout << "\t" << "bottom = " << bottom << endl;

	/* Obs.: right tem que ser calculado antes de left e top antes de bottom, pois os valores antigos de left e bottom é que estão sendo considerados */
	right = left + (dx+normalizedWidth)*width;
	left = left + dx*width;
	top = bottom + (dy+normalizedHeight)*height;
	bottom = bottom + dy*height;

	SetCameraMode(CAM_FREE);

//	cout << "\t" << "left = " << left << endl;
//	cout << "\t" << "right = " << right << endl;
//	cout << "\t" << "top = " << top << endl;
//	cout << "\t" << "bottom = " << bottom << endl;

	// Tem que alterar a visualização usando left, right, bottom e top.
	// Fazer isso em casa.
	// Algo parecido com:
	// 	 Project->vxmin=min+MPosX*(max-min)/OpenGLAPPanel1->Width;
	//   Project->vxmax=min+X*(max-min)/OpenGLAPPanel1->Width;

//	Translate(dx, dy);
//	Zoom(zoomfactor);
}
void BasicOpenGLStateMachine::DrawAxisArrow(double x, double y, double z, bool xOriented, bool yOriented) {
	/* Desenha, usando tubo circular, a seta no eixo x. Orientado em z */
	double bottomRadius = (xmax-xmin)*0.01; // Poderia ser a diferença entre os y ou z.
	double topRadius = 0;
	double segments = 16;
	double thickness = 0;
	double zi = z;
	double zf = zi + 2*bottomRadius;

	vector<Facet> facets;
	for (int i = 0; i < segments; i++) {
		double theta = 2*PI*i/segments;
		double x1 = x+(bottomRadius+thickness)*sin(theta);
		double y1 = y+(bottomRadius+thickness)*cos(theta);
		double x3 = x+bottomRadius*sin(theta);
		double y3 = y+bottomRadius*cos(theta);
		double x5 = x+(topRadius+thickness)*sin(theta);
		double y5 = y+(topRadius+thickness)*cos(theta);
		double x7 = x+topRadius*sin(theta);
		double y7 = y+topRadius*cos(theta);
		theta = 2*PI*(i+1)/segments;
		double x2 = x+(bottomRadius+thickness)*sin(theta);
		double y2 = y+(bottomRadius+thickness)*cos(theta);
		double x4 = x+bottomRadius*sin(theta);
		double y4 = y+bottomRadius*cos(theta);
		double x6 = x+(topRadius+thickness)*sin(theta);
		double y6 = y+(topRadius+thickness)*cos(theta);
		double x8 = x+topRadius*sin(theta);
		double y8 = y+topRadius*cos(theta);

		double z2 = zf;
		double z1 = zi;
		Facet face = Facet();
		face.Add(Rvector3(x1,y1,z1));
		face.Add(Rvector3(x2,y2,z1));
		face.Add(Rvector3(x6,y6,z2));
		face.Add(Rvector3(x5,y5,z2));
		facets.push_back(face);
		face = Facet();
		face.Add(Rvector3(x3,y3,z1));
		face.Add(Rvector3(x4,y4,z1));
		face.Add(Rvector3(x8,y8,z2));
		face.Add(Rvector3(x7,y7,z2));
		facets.push_back(face);
		face = Facet();
		face.Add(Rvector3(x1,y1,z1));
		face.Add(Rvector3(x2,y2,z1));
		face.Add(Rvector3(x4,y4,z1));
		face.Add(Rvector3(x3,y3,z1));
		facets.push_back(face);
		face = Facet();
		face.Add(Rvector3(x5,y5,z2));
		face.Add(Rvector3(x6,y6,z2));
		face.Add(Rvector3(x8,y8,z2));
		face.Add(Rvector3(x7,y7,z2));
		facets.push_back(face);
	}
	if (xOriented) {
		RotateFacets(facets, Rvector3(x, y, z), 0, 90, 0);
	}
	if (yOriented) {
		RotateFacets(facets, Rvector3(x, y, z), -90, 0, 0);
	}

	for (size_t i = 0; i < facets.size(); i++) {
		DrawPolygon(facets[i], true);
	}
}
void BasicOpenGLStateMachine::DrawAxis() {
//	cout << "BasicOpenGLStateMachine::DrawAxis()" << endl;
	double x0, y0, z0;
	double x1, y1, z1;
	x0 = xmin;
	y0 = ymin;
	z0 = zmin;

//	x0 = (xmax-xmin)/2;
//	y0 = (ymax-ymin)/2;
//	z0 = (zmax-zmin)/2;
	x1 = 1.1*xmax;
	y1 = 1.1*ymax;
	z1 = 1.1*zmax;

//	cout << "x0 = " << x0 << endl;
//	cout << "y0 = " << y0 << endl;
//	cout << "z0 = " << z0 << endl;
//	cout << "x1 = " << x1 << endl;
//	cout << "y1 = " << y1 << endl;
//	cout << "z1 = " << z1 << endl;

	glLineWidth(3.0f);
	glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex3f(x0,y0,z0);
		glVertex3f(x1,y0,z0);

		glColor3f(0, 1, 0);
		glVertex3f(x0,y0,z0);
		glVertex3f(x0,y1,z0);

		glColor3f(0, 0, 1);
		glVertex3f(x0,y0,z0);
		glVertex3f(x0,y0,z1);
	glEnd();
	glColor3f(1, 0, 0); DrawAxisArrow(x1, y0, z0, true, false);
	glColor3f(0, 1, 0); DrawAxisArrow(x0, y1, z0, false, true);
	glColor3f(0, 0, 1); DrawAxisArrow(x0, y0, z1, false, false);


// http://stackoverflow.com/questions/5898922/i-have-a-problem-about-opengl-glut-glutstrokecharacter-the-code-did-not-work
//	glTranslatef(x1, y0, z0);
//	glutStrokeCharacter(GLUT_STROKE_ROMAN, 'X');
//	glTranslatef(x0, y1, z0);
//	glutStrokeCharacter(GLUT_STROKE_ROMAN, 'Y');
//	glTranslatef(x0, y0, z1);
//	glutStrokeCharacter(GLUT_STROKE_ROMAN, 'Z');
}

BasicOpenGLStateMachine::~BasicOpenGLStateMachine() {
}

void SetColor(wxColour color) {
//	glDisable(GL_BLEND);
	glColor3f((float)color.Red() / 255.0, (float)color.Green() / 255.0, (float)color.Blue() / 255.0);
}
//  Não funciona. Tem que habilitar o GL_DEPTH_TEST, mas parece que tem que desenhar na ordem certa. Ainda não sei como faz isso.
//	Se usar esse código com o GL_DEPTH_TEST habilitado, tem que desenhar na ordem certa. Como o programa ainda não faz isso,
//  dá pau em todos os outros desenhos.
void SetColor(wxColour color, double alpha) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f((float)color.Red() / 255.0, (float)color.Green() / 255.0, (float)color.Blue() / 255.0, alpha);
//	glColor3f((float)color.Red() / 255.0, (float)color.Green() / 255.0, (float)color.Blue() / 255.0);
}
void InitializeModelViewMatrix() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void DrawCylinder(double length, double radius, double transx, double transy, double transz, double angle, double rotx, double roty, double rotz, bool fill) {
	glPushMatrix();

	if (length < 0) {
		angle += 180;
		length *= -1;
	}

	glTranslated(transx, transy, transz);
	glRotated(angle, rotx, roty, rotz);

	GLUquadric* quadric = gluNewQuadric();
	if (fill) {
		gluQuadricDrawStyle(quadric, GLU_FILL);
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	} else {
		gluQuadricDrawStyle(quadric, GLU_LINE);
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	}
	gluCylinder(quadric, radius, radius, length, 32, 1);
	/* TODO: TIRAR AS PRÓXIMAS 2 LINHAS QUANDO O SISTEMA ESTIVER DESENHANDO O CILINDRO PREENCHIDO CORRETAMENTE */
	gluQuadricDrawStyle(quadric, GLU_LINE);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	gluCylinder(quadric, radius, radius, length, 32, 1);
	gluDeleteQuadric(quadric);

	glPopMatrix();
}
void DrawBox(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax, bool fill) {
	DrawPlaneX(ymin, zmin, ymax, zmax, xmin, fill);
	DrawPlaneX(ymin, zmin, ymax, zmax, xmax, fill);
	DrawPlaneY(xmin, zmin, xmax, zmax, ymin, fill);
	DrawPlaneY(xmin, zmin, xmax, zmax, ymax, fill);
	DrawPlaneZ(xmin, ymin, xmax, ymax, zmin, fill);
	DrawPlaneZ(xmin, ymin, xmax, ymax, zmax, fill);
}
void DrawSphere(double radius, double transx, double transy, double transz, double angle, double rotx, double roty, double rotz, bool fill) {
	glPushMatrix();

	glTranslated(transx, transy, transz);
	glRotated(angle, rotx, roty, rotz);

	GLUquadric* quadric = gluNewQuadric();
	if (fill) {
		gluQuadricDrawStyle(quadric, GLU_FILL);
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	} else {
		gluQuadricDrawStyle(quadric, GLU_LINE);
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	}
	gluSphere(quadric, radius, 32, 32);
	gluDeleteQuadric(quadric);

	glPopMatrix();
}

void DrawPoint(double x, double y, double z, float pointSize) {
	glEnable(GL_POINT_SMOOTH);
	glPointSize(pointSize);
	glBegin(GL_POINTS);
		glVertex3f(x,y,z);
	glEnd();
}
void DrawPolygon(Facet face, bool fill) {
	GLenum mode = fill ? GL_POLYGON : GL_LINE_LOOP;

//	DisableLight();
	if (fill)
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	else
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	glLineWidth(2.0f);
	glNormal3f(face.GetNormal().X, face.GetNormal().Y, face.GetNormal().Z);
	glBegin(mode);
		vector<Rvector3> vertex = face.GetVertex();
		for (size_t i = 0; i < vertex.size(); i++) {
			glVertex3d(vertex[i].X, vertex[i].Y, vertex[i].Z);
		}
	glEnd();
//	EnableLight();
}

void DrawPolygon2D(GenericSheet sheet, bool fill) {
	// Se é preenchido tem que fazer a triangulação dos polígonos
	if (fill) {
		Triangulate t;
		CoordinatesVector triangles;
		t.Process(sheet.GetCoordinates(), triangles);

		GLenum mode = fill ? GL_POLYGON : GL_LINE_LOOP;
		if (fill)
			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		else
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

		glLineWidth(2.0f);
		int nTriangles = triangles.size()/3;
		for (int i = 0; i < nTriangles; i++) {
			const std::pair<double, double> &p1 = triangles[i*3+0];
			const std::pair<double, double> &p2 = triangles[i*3+1];
			const std::pair<double, double> &p3 = triangles[i*3+2];

			glBegin(mode);
			if (sheet.IsCutAtX()) {
				glVertex3d(sheet.GetCutAt(), p1.first, p1.second);
				glVertex3d(sheet.GetCutAt(), p2.first, p2.second);
				glVertex3d(sheet.GetCutAt(), p3.first, p3.second);
			} else if (sheet.IsCutAtY()) {
				glVertex3d(p1.first, sheet.GetCutAt(), p1.second);
				glVertex3d(p2.first, sheet.GetCutAt(), p2.second);
				glVertex3d(p3.first, sheet.GetCutAt(), p3.second);
			} else if (sheet.IsCutAtZ()) {
				glVertex3d(p1.first, p1.second, sheet.GetCutAt());
				glVertex3d(p2.first, p2.second, sheet.GetCutAt());
				glVertex3d(p3.first, p3.second, sheet.GetCutAt());
			}
			glEnd();
		}
	} else {
		GLenum mode = fill ? GL_POLYGON : GL_LINE_LOOP;
		if (fill)
			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		else
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		glLineWidth(2.0f);
		glBegin(mode);
		vector<pair<double, double> > vertex = sheet.GetCoordinates();
		for (size_t i = 0; i < vertex.size(); i++) {
			if (sheet.IsCutAtX()) {
				glVertex3d(sheet.GetCutAt(), vertex[i].first, vertex[i].second);
			} else if (sheet.IsCutAtY()) {
				glVertex3d(vertex[i].first, sheet.GetCutAt(), vertex[i].second);
			} else if (sheet.IsCutAtZ()) {
				glVertex3d(vertex[i].first, vertex[i].second, sheet.GetCutAt());
			}
		}
		glEnd();
	}
}
void DrawSegment(double x1, double y1, double z1, double x2, double y2, double z2, double radius, bool fill) {
	// Baseado no código: http://pastebin.com/KSeay7x4
	float vx = x2-x1;
	float vy = y2-y1;
	float vz = z2-z1;
	//handle the degenerate case with an approximation
	if(vz == 0)
	vz = .00000001;
	float v = sqrt( vx*vx + vy*vy + vz*vz );
	float ax = 57.2957795*acos( vz/v );
	if ( vz < 0.0 )
	ax = -ax;
	float rx = -vy*vz;
	float ry = vx*vz;

	GLUquadricObj *quadric=gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);

	if (!fill)
		gluQuadricDrawStyle(quadric, GLU_LINE);

	glPushMatrix();
	glTranslatef(x1,y1,z1);
	glRotatef(ax, rx, ry, 0.0);
	//draw the cylinder
	gluCylinder(quadric, radius, radius, v, 16, 1);
	gluQuadricOrientation(quadric,GLU_INSIDE);
	//draw the first cap
	gluDisk( quadric, 0.0, radius, 16, 1);
	glTranslatef( 0,0,v );
	//draw the second cap
	gluQuadricOrientation(quadric,GLU_OUTSIDE);
	gluDisk( quadric, 0.0, radius, 16, 1);
	glPopMatrix();

	gluDeleteQuadric(quadric);
	//	DrawLine(s.GetP1(), s.GetP2(), 10);
}
void DrawSegment(Segment& s, bool fill) {
	DrawSegment(s.GetP1().X, s.GetP1().Y, s.GetP1().Z, s.GetP2().X, s.GetP2().Y, s.GetP2().Z, s.GetRadius(), fill);
}
void DrawSegments(Segments& ss, bool fill) {
	// Replicar o código de DrawSegment aqui em vez de chamar diretamente DrawSegment é ligeiramente mais rápido (cerca de 3%),
	// pois não precisa ficar criando e apagando quadric toda hora.
	GLUquadricObj *quadric=gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);

	if (!fill)
		gluQuadricDrawStyle(quadric, GLU_LINE);

	for (size_t i = 0; i < ss.size(); i++) {
		Segment s = ss[i];
		float vx = s.GetP2().X-s.GetP1().X;
		float vy = s.GetP2().Y-s.GetP1().Y;
		float vz = s.GetP2().Z-s.GetP1().Z;
		//handle the degenerate case with an approximation
		if(vz == 0)
		vz = .00000001;
		float v = sqrt( vx*vx + vy*vy + vz*vz );
		float ax = 57.2957795*acos( vz/v );
		if ( vz < 0.0 )
		ax = -ax;
		float rx = -vy*vz;
		float ry = vx*vz;

		glPushMatrix();
		glTranslatef(s.GetP1().X, s.GetP1().Y, s.GetP1().Z);
		glRotatef(ax, rx, ry, 0.0);
		//draw the cylinder
		gluCylinder(quadric, s.GetRadius(), s.GetRadius(), v, 16, 1);
		gluQuadricOrientation(quadric,GLU_INSIDE);
		//draw the first cap
		gluDisk( quadric, 0.0, s.GetRadius(), 16, 1);
		glTranslatef( 0,0,v );
		//draw the second cap
		gluQuadricOrientation(quadric,GLU_OUTSIDE);
		gluDisk( quadric, 0.0, s.GetRadius(), 16, 1);
		glPopMatrix();
	}
	gluDeleteQuadric(quadric);
}
void DrawPolygons(vector<Facet> faces, bool fill) {
	for (size_t i = 0; i < faces.size(); i++) {
		DrawPolygon(faces[i], fill);
	}
}
void DrawLine(Rvector3 p1, Rvector3 p2, float lineWidth) {
	DrawLine(p1.X, p1.Y, p1.Z, p2.X, p2.Y, p2.Z, lineWidth);
}
void DrawLine(double x1, double y1, double z1, double x2, double y2, double z2, float lineWidth) {
//	glDisable(GL_LIGHT0);
	glLineWidth(lineWidth);
	glBegin(GL_LINES);
		glVertex3f(x1, y1, z1);
		glVertex3f(x2, y2, z2);
	glEnd();
//	glEnable(GL_LIGHT0);
}


void DrawPlaneX(double ymin, double zmin, double ymax, double zmax, double x, bool fill) {
	GLenum mode = fill ? GL_POLYGON : GL_LINE_LOOP;

	if (fill)
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	else
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	glLineWidth(2.0f);
	glBegin(mode);
		glVertex3d(x,ymin,zmin);
		glVertex3d(x,ymin,zmax);
		glVertex3d(x,ymax,zmax);
		glVertex3d(x,ymax,zmin);
	glEnd();
}
void DrawPlaneY(double xmin, double zmin, double xmax, double zmax, double y, bool fill) {
	GLenum mode = fill ? GL_POLYGON : GL_LINE_LOOP;

	if (fill)
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	else
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);


	glLineWidth(2.0f);
	glBegin(mode);
		glVertex3d(xmin,y,zmin);
		glVertex3d(xmin,y,zmax);
		glVertex3d(xmax,y,zmax);
		glVertex3d(xmax,y,zmin);
	glEnd();
}
void DrawPlaneZ(double xmin, double ymin, double xmax, double ymax, double z, bool fill) {
	GLenum mode = fill ? GL_POLYGON : GL_LINE_LOOP;

	if (fill)
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	else
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);


	glLineWidth(2.0f);
	glBegin(mode);
		glVertex3d(xmin,ymin,z);
		glVertex3d(xmin,ymax,z);
		glVertex3d(xmax,ymax,z);
		glVertex3d(xmax,ymin,z);
	glEnd();
}
