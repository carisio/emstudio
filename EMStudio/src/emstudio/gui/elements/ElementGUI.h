/*
 * ElementGUI.h
 *
 *  Created on: 24/08/2011
 *      Author: Leandro
 */

#ifndef ELEMENTGUI_H_
#define ELEMENTGUI_H_

#include "wx/wx.h"
#include "ElementType.h"
#include "emstudio/dto/ElementDTO.h"
#include "Propertyable.h"
#include "emstudio/gui/basetypes/StringWrapper.h"
#include "emstudio/gui/basetypes/Point3DME.h"
#include "ElementManager.h"
#include <tr1/memory>

class ElementManager;
class ElementGUI;
class OpenGLStateMachine;
typedef std::tr1::shared_ptr<ElementManager> ElementManagerSmartPointer;
typedef std::tr1::shared_ptr<ElementGUI> ElementGUISmartPointer;

class ElementGUI : public Propertyable {
private:
	static ElementManagerSmartPointer elementsInProjectSmartPointer;
	ElementTypeSmartPointer type;
	StringWrapper name;

public:
	ElementGUI(ElementTypeSmartPointer type);
	virtual ~ElementGUI();

	static void SetElementsInProject(ElementManagerSmartPointer em);
	static ElementManagerSmartPointer GetElementsInProject();
	virtual void ProjectChanged(); // Esse método é chamado sempre que algum elemento do projeto foi alterado

	virtual void Draw(OpenGLStateMachine* opengl);
	virtual bool FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax);
	void Move(Point3DME p);
	virtual void DoMove(Point3DME p) = 0;
	virtual ElementGUISmartPointer NewElementGUI() = 0;
	virtual PropertyableSmartPointer NewPropertyable();
    virtual ElementTypeSmartPointer GetType();
    virtual wxString GetRegisteredName() = 0;
    virtual wxIcon GetIcon() = 0;

    ElementDTOSmartPointer GetDTO();
    virtual ElementDTOSmartPointer NewElementDTO() = 0;
    virtual void DoPopulateDTO(ElementDTOSmartPointer p);

    /* Essas são propriedades */
    wxString GetUserDefinedName();
    void SetUserDefinedName(wxString name);
};

#endif /* ELEMENTGUI_H_ */
