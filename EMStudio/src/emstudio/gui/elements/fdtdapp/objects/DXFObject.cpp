/*
 * DXFObject.cpp
 *
 *  Created on: 09/05/2013
 *      Author: leandrocarisio
 */

#include "DXFObject.h"
#include "emstudio/util/resources/UtilResource.h"
#include "emstudio/gui/framesandpanels/main/visualizationpanel/OpenGLStateMachine.h"

DXFObject::DXFObject()
	: ElementsWithFacets(ElementTypeSmartPointer(new Object3DType())) ,
	  oldTx(0), oldTy(0), oldTz(0),
	  oldNormalize(false),
	  oldRx(0), oldRy(0), oldRz(0),
	  oldScale(0) {

	BaseTypeValidatorSmartPointer mathExpressionDiffFrom0Validator(new MathExpressionDifferentFromValidator(0));
	BaseTypeValidatorSmartPointer validadorInvalidPoint3D(new InvalidPoint3DMEValidator);

	scaleFactor.SetExpression("1");
	normalize.SetValue(false);
	solid.SetValue(true);
	visible.SetValue(true);

	AddPriorityProperty(MINIMUM);
	AddProperty(Property("File", &file));
	AddProperty(Property("Normalize", &normalize));
	AddProperty(Property("Scale factor", &scaleFactor, mathExpressionDiffFrom0Validator));
	AddProperty(Property("Rotate", &rotateAxis, validadorInvalidPoint3D));
	AddProperty(Property("Translate to", &translateTo, validadorInvalidPoint3D));
	AddMaterialProperty("Material", "PEC");
	AddProperty(Property("Solid?", &solid));
	AddProperty(Property("Visible?", &visible));
}

DXFObject::~DXFObject() {
}

ElementGUISmartPointer DXFObject::NewElementGUI() {
	return ElementGUISmartPointer(new DXFObject());
}

wxString DXFObject::GetRegisteredName() {
	return "DXF Object";
}

wxIcon DXFObject::GetIcon() {
	return UtilResource::GetIcon("box");
}

ElementDTOSmartPointer DXFObject::NewElementDTO() {
	DXFObjectDTO* result = new DXFObjectDTO;

	return ElementDTOSmartPointer(result);
}

bool DXFObject::FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	if (!visible.IsValue())
		return false;

	/* Verifica se, por algum motivo, o objeto contido no DXFObject não corresponde mais ao DXFParser.
	 */
	double scaleFactor_dbl = scaleFactor.ForceEval();
	translateTo.EvalExpressions();
	rotateAxis.EvalExpressions();

	bool changeObject = !(parser.GetDXFEntityList().size() == file.GetEntityList().size());
	changeObject = changeObject || (oldTx != translateTo.GetX() || oldTy != translateTo.GetY() || oldTz != translateTo.GetZ());
	changeObject = changeObject || (oldRx != rotateAxis.GetX() || oldRy != rotateAxis.GetY() || oldRz != rotateAxis.GetZ());
	changeObject = changeObject || (oldNormalize != normalize.IsValue());
	changeObject = changeObject || (oldScale != scaleFactor_dbl);

	if (changeObject) {
		oldTx = translateTo.GetX();
		oldTy = translateTo.GetY();
		oldTz = translateTo.GetZ();

		oldRx = rotateAxis.GetX();
		oldRy = rotateAxis.GetY();
		oldRz = rotateAxis.GetZ();

		oldNormalize = normalize.IsValue();

		oldScale = scaleFactor_dbl;

		parser = file.GetParser();
		parser.Transform(normalize.IsValue(), rotateAxis.GetX(), rotateAxis.GetY(), rotateAxis.GetZ(),
			translateTo.GetX(), translateTo.GetY(), translateTo.GetZ(), scaleFactor_dbl);
	}

	FillApproximateDimensionsWithFacets(xmin, ymin, zmin, xmax, ymax, zmax);
	return true;
}

void DXFObject::Draw(OpenGLStateMachine* opengl) {
	if (!visible.IsValue())
	  return;

	/* Verifica se, por algum motivo, o objeto contido no DXFObject não corresponde mais ao DXFParser.
	 * Isso pode acontecer, por exemplo, ao abrir um novo arquivo. Nesse caso, o DXFObject::parser não estará inicializado corretamente
	 */
	double scaleFactor_dbl = scaleFactor.ForceEval();
	translateTo.EvalExpressions();
	rotateAxis.EvalExpressions();

	bool changeObject = !(parser.GetDXFEntityList().size() == file.GetEntityList().size());
	changeObject = changeObject || (oldTx != translateTo.GetX() || oldTy != translateTo.GetY() || oldTz != translateTo.GetZ());
	changeObject = changeObject || (oldRx != rotateAxis.GetX() || oldRy != rotateAxis.GetY() || oldRz != rotateAxis.GetZ());
	changeObject = changeObject || (oldNormalize != normalize.IsValue());
	changeObject = changeObject || (oldScale != scaleFactor_dbl);

	if (changeObject) {
		oldTx = translateTo.GetX();
		oldTy = translateTo.GetY();
		oldTz = translateTo.GetZ();

		oldRx = rotateAxis.GetX();
		oldRy = rotateAxis.GetY();
		oldRz = rotateAxis.GetZ();

		oldNormalize = normalize.IsValue();

		oldScale = scaleFactor_dbl;

		parser = file.GetParser();
		parser.Transform(normalize.IsValue(), rotateAxis.GetX(), rotateAxis.GetY(), rotateAxis.GetZ(),
			translateTo.GetX(), translateTo.GetY(), translateTo.GetZ(), scaleFactor_dbl);
	}

	bool fill = solid.IsValue();
	DXFEntityList m_entities = parser.GetDXFEntityList();
    for (DXFEntityList::compatibility_iterator node = m_entities.GetFirst(); node; node = node->GetNext())
    {
        DXFEntity *p = node->GetData();
        wxColour c = ACIColourToRGB(p->colour);
        if (p->type == DXFEntity::Line)
        {
            DXFLine *line = (DXFLine *)p;
            glBegin(GL_LINES);
            glColor3f(c.Red()/255.0,c.Green()/255.0,c.Blue()/255.0);
            glVertex3f(line->v0.X, line->v0.Y, line->v0.Z);
            glVertex3f(line->v1.X, line->v1.Y, line->v1.Z);
            glEnd();
        }
        else if (p->type == DXFEntity::Face)
        {
            DXFFace *face = (DXFFace *)p;

        	GLenum mode = fill ? GL_POLYGON : GL_LINE_LOOP;
        	if (fill)
        		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        	else
        		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

        	glLineWidth(2.0f);
            glBegin(mode);
            glColor3f(c.Red()/255.0,c.Green()/255.0,c.Blue()/255.0);
            glNormal3f(face->n.X, face->n.Y, face->n.Z);
            glVertex3f(face->v0.X, face->v0.Y, face->v0.Z);
            glVertex3f(face->v1.X, face->v1.Y, face->v1.Z);
            glVertex3f(face->v2.X, face->v2.Y, face->v2.Z);
            glEnd();
        }
    }
}

bool DXFObject::IsAllPropertiesTogetherValid() {
	// Copia o parser da variável file
	parser = file.GetParser();
	DXFEntityList list = parser.GetDXFEntityList();
	if (list.size() == 0) {
		wxString errorMessage;
		errorMessage.Append("File \"").Append(file.GetUserFriendlyStringRepresentation()).Append("\" is empty.\n");
		SetAllPropertiesTogetherErrorMessage(errorMessage);
		return false;
	}

	/*
	 * O método IsAllPropertiesTogetherValid é executado sempre que o usuário fecha a caixa de propriedades.
	 * Nesse ponto, DXFObject::parser será uma cópia de file.GetParser().
	 * Parser guardará os dados do DXF já transformados. Note que os dados originais continuam guardados na propriedade DXFFile
	 */

	// Se estiver tudo OK, atualiza o parser se acordo com as configurações de
	// normalize, rotate, translate e scale, nessa ordem.
	double scaleFactor_dbl = scaleFactor.ForceEval();
	translateTo.EvalExpressions();
	rotateAxis.EvalExpressions();
	parser.Transform(normalize.IsValue(), rotateAxis.GetX(), rotateAxis.GetY(), rotateAxis.GetZ(),
			translateTo.GetX(), translateTo.GetY(), translateTo.GetZ(), scaleFactor_dbl);

	oldTx = translateTo.GetX();
	oldTy = translateTo.GetY();
	oldTz = translateTo.GetZ();

	oldRx = rotateAxis.GetX();
	oldRy = rotateAxis.GetY();
	oldRz = rotateAxis.GetZ();

	oldNormalize = normalize.IsValue();

	oldScale = scaleFactor.ForceEval();


	return true;
}

vector<Facet> DXFObject::BuildFacets() {
	return parser.GetFacets();
}
void DXFObject::DoMove(Point3DME p) {
	wxString px = p.GetXExpression(); wxString py = p.GetYExpression(); wxString pz = p.GetZExpression();
	wxString x = "(" + translateTo.GetXExpression() + ") + " + px;
	wxString y = "(" + translateTo.GetYExpression() + ") + " + py;
	wxString z = "(" + translateTo.GetZExpression() + ") + " + pz;
	translateTo.SetXExpression(x);
	translateTo.SetYExpression(y);
	translateTo.SetZExpression(z);
}
