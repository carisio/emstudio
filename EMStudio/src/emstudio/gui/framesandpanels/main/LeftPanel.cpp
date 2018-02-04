/*
 * LeftPanel.cpp
 *
 *  Created on: 14/08/2011
 *      Author: Leandro
 */
#include "emstudio/util/file/FileManager.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/editorsframes/Point3DMEFrame.h"
#include "LeftPanel.h"

/*
 * Classe LeftPanel
 */
LeftPanel::LeftPanel(wxWindow* parent, wxWindowID id, ElementManagerSmartPointer elementsAvailables, ElementManagerSmartPointer elementsInProject, RenderersAndEditorsManagerSmartPointer renderersAndEditorsManager, VisualizationPanel* visualization, std::tr1::shared_ptr<InformProjectHasChangedCommand> prjHasChangedCommand)
	: wxPanel(parent, id, wxDefaultPosition, wxDefaultSize,  wxTAB_TRAVERSAL | wxBORDER_NONE) {

	horizontalSplitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	projectTree = new ProjectTree(horizontalSplitter, wxID_ANY, elementsInProject, prjHasChangedCommand, renderersAndEditorsManager, visualization);
	availableItemsTree = new AvailableItemsTree(horizontalSplitter, wxID_ANY, elementsAvailables, projectTree);

	projectTree->ExpandAll();
	availableItemsTree->ExpandAll();

	horizontalSplitter->SplitHorizontally(projectTree, availableItemsTree);

	Connect(this->GetId(), wxEVT_SIZE, wxSizeEventHandler(LeftPanel::Resize));

}
LeftPanel::~LeftPanel() {
	/* UpadtaMessageCommand é compartilhado em vários lugares. O central é que apagará ele*/
	// delete updateMessageCommand;
}
void LeftPanel::RebuildProjectTree() {
	projectTree->BuildTree();
}

void LeftPanel::Resize(wxSizeEvent& event) {
	wxSize newSize = event.GetSize();
	horizontalSplitter->SetSize(newSize);
	horizontalSplitter->SetSashPosition(newSize.y/2);
}
void LeftPanel::CloneSelectedElement() {
	projectTree->CloneSelectedElement();
}
void LeftPanel::DeleteSelectedElement() {
	projectTree->DeleteSelectedElement();
}

/*
 * Classe AvailableItemsTree
 */
AvailableItemsTree::AvailableItemsTree(wxWindow* parent, wxWindowID id, ElementManagerSmartPointer em,ProjectTree* prjTree)
	: wxTreeCtrl(parent, id, wxDefaultPosition, wxDefaultSize) {
	this->elementManager = em;
	this->icons = new wxImageList(16, 16, 0);
	this->projectTree = prjTree;

	SetImageList(icons);
	BuildTree();

	Connect(this->GetId(), wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler(AvailableItemsTree::DoubleClick));
}

void AvailableItemsTree::BuildTree() {
	root = new ItemsTree("Available items");
	wxTreeItemId rootId = this->AddRoot("Available items", -1, -1, root);

	// Build leafs
	ElementManager::ElementTypeList typeList = elementManager->GetElementTypeList();
    ElementManager::ElementTypeList::const_iterator iterator = typeList.begin();

    while (iterator != typeList.end()) {
    	// Pega a chave (type) e a lista (elementsInCategory) que está no mapa.
    	ElementTypeSmartPointer type = *iterator;
    	ElementManager::ElementList elementsInCategory = elementManager->GetElementList(type);

    	// Para cada chave (categoria), vincula à raiz
    	int index = icons->Add(type->GetIcon());
    	wxTreeItemId categoryItemId = this->AppendItem(rootId, type->GetName(), index, index, new ItemsTree(type->GetName()));

    	// Pega a lista de elementos vinculados à esta categoria
    	ElementManager::ElementList::const_iterator iteratorList = elementsInCategory.begin();

    	// Percorre a lista de elementos
    	while (iteratorList != elementsInCategory.end()) {
    		ElementGUISmartPointer element = *iteratorList;
    		index = icons->Add(element->GetIcon());
    		this->AppendItem(categoryItemId, element->GetRegisteredName(), index, index, new ItemsTree(element));

    		iteratorList++;
    	}

    	iterator++;
    }
}

void AvailableItemsTree::DoubleClick(wxTreeEvent& event) {
	/*
	 * A chamada a GetUserDefinedName aqui é uma gambiarra que não pode ser retirada.
	 * Todos elementos tem uma propriedade name, que é por padrão fazia. Essa propriedade é obtida através da chamada ao método
	 * GetUserDefinedName(). Por padrão, ao inicializar um objeto, a propriedade name deveria ser igual ao nome da classe que aparece
	 * na lista de elementos disponíveis (método virtual GetRegisteredName()).
	 *
	 * Como não é possível fazer uma chamada à um metodo virtual no construtor, em algum lugar esse valor padrão deve ser atribuído.
	 * Se o objeto for adicionado primeiro e depois disso sua lista de propriedades for aberta, não é necessário fazer essa chamada
	 * explícita, pois ProjectTree::BuildTree() já faz isso. No entanto, se for abrir a lista de propriedades para depois adicionar o
	 * elemento ao projeto, é necessário deixar a chamada explícita.
	 *
	 * O efeito de retirar essa chamada e continuar chamando a tela de propriedade ANTES de adicionar é que GetRegisteredName() não
	 * inicializará a variável name através de inicialização tardia (lazy inicialization), fazendo com que ElementGUI::name seja
	 * sempre "", ou seja, a propriedade nome ficará vazia ao entrar na tela.
	 *
	 */

    wxTreeItemId itemId = event.GetItem();
    ItemsTree *item = (ItemsTree *)GetItemData(itemId);
    if (item->IsLeaf()) {
    	ElementGUISmartPointer e = item->GetElement()->NewElementGUI();
    	e->GetUserDefinedName();  	// VER COMENTÁRIO ACIMA
    	if (projectTree->EditElement(e))
    		projectTree->AddElement(e);
    }
}

AvailableItemsTree::~AvailableItemsTree() {
	if (icons)
		delete icons;
	/* UpadtaMessageCommand é compartilhado em vários lugares. O central é que apagará ele*/
	// delete updateMessageCommand;

	/* elementManager foi criado em outro lugar e populado em outro lugar. O outro lugar apaga*/
	// delete elementManager;
}
/*
 * Classe ProjectTree
 */
int ProjectTree::ID_EDIT_ELEMENT = wxID_HIGHEST + 1;
int ProjectTree::ID_DELETE_ELEMENT = wxID_HIGHEST + 2;
int ProjectTree::ID_CLONE_ELEMENT = wxID_HIGHEST + 3;
int ProjectTree::ID_MOVE_ELEMENT = wxID_HIGHEST + 4;

ProjectTree::ProjectTree(wxWindow* parent, wxWindowID id, ElementManagerSmartPointer elementsInProject, std::tr1::shared_ptr<InformProjectHasChangedCommand> prjHasChangedCommand, RenderersAndEditorsManagerSmartPointer renderersAndEditors, VisualizationPanel* visualizationPanel)
	: wxTreeCtrl(parent, id, wxDefaultPosition, wxDefaultSize),
	  prjHasChangedCommand(prjHasChangedCommand),
	  visualizationPanel(visualizationPanel) {

	this->elementManager = elementsInProject;
	this->icons = new wxImageList(16, 16, 0);
	this->propertiesFrame = 0;
	this->renderersAndEditorsManager = renderersAndEditors;

	SetImageList(icons);

	BuildTree();

	popUpMenu.Append(ID_EDIT_ELEMENT, "Edit", "Edit element");
	popUpMenu.Append(ID_DELETE_ELEMENT, "Delete", "Delete element");
	popUpMenu.Append(ID_CLONE_ELEMENT, "Clone", "Clone element");
	popUpMenu.Append(ID_MOVE_ELEMENT, "Move", "Move element");

	Connect(this->GetId(), wxEVT_COMMAND_TREE_ITEM_ACTIVATED, wxTreeEventHandler(ProjectTree::DoubleClick));
	Connect(this->GetId(), wxEVT_COMMAND_TREE_ITEM_RIGHT_CLICK, wxTreeEventHandler(ProjectTree::RightClick));
	Connect(this->GetId(), wxEVT_COMMAND_TREE_KEY_DOWN, wxTreeEventHandler(ProjectTree::KeyDown));
	Connect(ID_EDIT_ELEMENT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(ProjectTree::EditElement));
	Connect(ID_DELETE_ELEMENT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(ProjectTree::DeleteElement));
	Connect(ID_CLONE_ELEMENT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(ProjectTree::CloneElement));
	Connect(ID_MOVE_ELEMENT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(ProjectTree::MoveElement));
}
void ProjectTree::BuildTree() {
	bool hasScrollV = HasScrollbar(wxVERTICAL);
	bool hasScrollH = HasScrollbar(wxHORIZONTAL);
	int scrollPosV = GetScrollPos(wxVERTICAL);
	int scrollPosH = GetScrollPos(wxHORIZONTAL);

	DeleteAllItems();
	icons->RemoveAll();

	root = new ItemsTree("Project");
	wxTreeItemId rootId = this->AddRoot("Project", -1, -1, root);

	// Build leafs
	ElementManager::ElementTypeList typeList = elementManager->GetElementTypeList();
	ElementManager::ElementTypeList::const_iterator iterator = typeList.begin();

	while (iterator != typeList.end()) {
		// Pega a chave (type) e a lista (elementsInCategory) que está no mapa.
		ElementTypeSmartPointer type = *iterator;
		ElementManager::ElementList elementsInCategory = elementManager->GetElementList(type);

		// Para cada chave (categoria), vincula à raiz
		int index = icons->Add(type->GetIcon());
		wxTreeItemId categoryItemId = this->AppendItem(rootId, type->GetName(), index, index, new ItemsTree(type->GetName()));

		// Pega a lista de elementos vinculados à esta categoria
		ElementManager::ElementList::const_iterator iteratorList = elementsInCategory.begin();

		// Percorre a lista de elementos
		while (iteratorList != elementsInCategory.end()) {
			ElementGUISmartPointer element = *iteratorList;
			index = icons->Add(element->GetIcon());
			this->AppendItem(categoryItemId, element->GetUserDefinedName(), index, index, new ItemsTree(element));

			iteratorList++;
		}

		iterator++;
	}
	ExpandAll();
	cout << "hasScrollV = " << hasScrollV << "\tscrollPosV = " << scrollPosV << endl;
	cout << "hasScrollH = " << hasScrollH << "\tscrollPosH = " << scrollPosH << endl;
	SetScrollPos(wxVERTICAL, scrollPosV);
	SetScrollPos(wxHORIZONTAL, scrollPosH);

	visualizationPanel->Refresh();
}
void ProjectTree::BuildTreeAndInformProjectHasChanged() {
	cout << "ProjectTree::BuildTreeAndInformProjectHasChanged() " << endl;
	BuildTree();
	prjHasChangedCommand->Execute();
	cout << "END ProjectTree::BuildTreeAndInformProjectHasChanged() " << endl;
}
void ProjectTree::AddElement(ElementGUISmartPointer element) {
	cout << "ProjectTree::AddElement(ElementGUISmartPointer elemen) " << endl;
	elementManager->RegisterElement(element);
	BuildTreeAndInformProjectHasChanged();
	cout << "END ProjectTree::AddElement(ElementGUISmartPointer elemen) " << endl;
}
// Eventos do popup
void ProjectTree::RightClick(wxTreeEvent& event) {
	cout << "----------------------" << endl;
	cout << "ProjectTree::RightClick(wxTreeEvent& event)" << endl;
	wxTreeItemId itemId = event.GetItem();
	itemSelectedInPopupMenu = (ItemsTree *)GetItemData(itemId);
	if (itemSelectedInPopupMenu->IsLeaf()) {
		PopupMenu(&popUpMenu, event.GetPoint().x, event.GetPoint().y);
	}
	cout << "END ProjectTree::RightClick(wxTreeEvent& event)" << endl;
}
void ProjectTree::CloneElement(wxCommandEvent& event) {
	cout << "----------------------" << endl;
	cout << "ProjectTree::CloneElement(wxCommandEvent& event)" << endl;
	CloneItemTree(itemSelectedInPopupMenu);
	cout << "END ProjectTree::CloneElement(wxTreeEvent& event)" << endl;
}
void ProjectTree::EditElement(wxCommandEvent& event) {
	cout << "----------------------" << endl;
	cout << "ProjectTree::EditElement(wxCommandEvent& event)" << endl;
	EditItemTree(itemSelectedInPopupMenu);
	cout << "END ProjectTree::EditElement(wxTreeEvent& event)" << endl;
}
void ProjectTree::MoveElement(wxCommandEvent& event) {
	cout << "----------------------" << endl;
	cout << "ProjectTree::MoveElement(wxCommandEvent& event)" << endl;
	Point3DME point;
	point.SetXExpression("0"); point.SetYExpression("0"); point.SetZExpression("0");
	Point3DMEFrame dialog(NULL, Point3DME(), wxID_ANY, "Move");
	dialog.SetPoint3DME(point);
	if (dialog.ShowModal() == wxID_OK) {
		point = dialog.GetPoint3DME();
		if (point.isPointValid())
			MoveItemTree(itemSelectedInPopupMenu, point);
		else
			UtilDialog::ShowErrorMessage("Enter a valid point", "Invalid point");
	}
	cout << "END ProjectTree::MoveElement(wxTreeEvent& event)" << endl;
}
void ProjectTree::MoveItemTree(ItemsTree* item, Point3DME point) {
	cout << "----------------------" << endl;
	cout << "ProjectTree::MoveItemTree(ItemsTree* item, Point3DME point)" << endl;
	cout << "Movendo objeto " << item->GetName() << endl;
	item->GetElement()->Move(point);
	BuildTreeAndInformProjectHasChanged();
	cout << "END ProjectTree::MoveItemTree(ItemsTree* item, Point3DME point)" << endl;
}
void ProjectTree::DeleteElement(wxCommandEvent& event) {
	cout << "----------------------" << endl;
	cout << "ProjectTree::DeleteElement(wxCommandEvent& event)" << endl;
	DeleteItemTree(itemSelectedInPopupMenu);
	cout << "END ProjectTree::DeleteElement(wxTreeEvent& event)" << endl;
}
// Fim dos eventos do popup
void ProjectTree::DoubleClick(wxTreeEvent& event) {
	cout << "----------------------" << endl;
	cout << "ProjectTree::DoubleClick(wxTreeEvent& event)" << endl;
	wxTreeItemId itemId = GetFocusedItem();
	if (itemId.IsOk()) {
		ItemsTree *item = (ItemsTree *)GetItemData(itemId);
		EditItemTree(item);
	}
	cout << "END ProjectTree::DoubleClick(wxTreeEvent& event)" << endl;
}
void ProjectTree::KeyDown(wxTreeEvent& event) {
	cout << "----------------------" << endl;
	cout << "ProjectTree::KeyDown(wxTreeEvent& event)" << endl;
	int keyCode = event.GetKeyCode();
	if (keyCode == WXK_DELETE) {
		DeleteSelectedElement();
	} else if (keyCode == WXK_INSERT) {
		CloneSelectedElement();
	}
	cout << "END ProjectTree::KeyDown(wxTreeEvent& event)" << endl;
}
void ProjectTree::CloneSelectedElement() {
	cout << "----------------------" << endl;
	cout << "ProjectTree::CloneSelectedElement()" << endl;
	wxTreeItemId itemId = GetFocusedItem();
	if (itemId.IsOk()) {
		ItemsTree *item = (ItemsTree *)GetItemData(itemId);
		CloneItemTree(item);
	}
	cout << "END ProjectTree::CloneSelectedElement()" << endl;
}
void ProjectTree::CloneItemTree(ItemsTree *item) {
	cout << "----------------------" << endl;
	cout << "ProjectTree::CloneItemTree(ItemsTree *item)" << endl;
	if (!(item->IsLeaf()))
		return;

	wxString msg = "Do you want to clone ";
	msg.Append(item->GetElement()->GetUserDefinedName()).Append("?");
	if (UtilDialog::ShowYesNoMessage("Clone item?", msg) == wxID_YES) {
		ElementGUISmartPointer clone = item->GetElement()->NewElementGUI();
		clone->TransferDataFrom(item->GetElement());
		elementManager->RegisterElement(clone);
		BuildTreeAndInformProjectHasChanged();
	}
	cout << "END ProjectTree::CloneItemTree(ItemsTree *item)" << endl;
}
void ProjectTree::DeleteSelectedElement() {
	cout << "----------------------" << endl;
	cout << "ProjectTree::DeleteSelectedElement()" << endl;
	wxTreeItemId itemId = GetFocusedItem();

	if (itemId.IsOk()) {
		ItemsTree *item = (ItemsTree *)GetItemData(itemId);
		DeleteItemTree(item);
	}
	cout << "END ProjectTree::DeleteSelectedElement()" << endl;
}
void ProjectTree::DeleteItemTree(ItemsTree *item) {
	cout << "----------------------" << endl;
	cout << "ProjectTree::DeleteItemTree(ItemsTree *item)" << endl;
	if (!(item->IsLeaf()))
		return;

	wxString msg = "Do you want to delete ";
	msg.Append(item->GetElement()->GetUserDefinedName()).Append("?");
	if (UtilDialog::ShowYesNoMessage("Delete item?", msg) == wxID_YES) {
		elementManager->Remove(item->GetElement());
		BuildTreeAndInformProjectHasChanged();
	}
	cout << "END ProjectTree::DeleteItemTree(ItemsTree *item)" << endl;
}
void ProjectTree::EditItemTree(ItemsTree* item) {
	cout << "----------------------" << endl;
	cout << "ProjectTree::EditItemTree(ItemsTree *item)" << endl;
	if (!(item->IsLeaf()))
		return;

	if (EditElement(item->GetElement())) {
		BuildTreeAndInformProjectHasChanged();
	}
	cout << "END ProjectTree::EditItemTree(ItemsTree *item)" << endl;
}
bool ProjectTree::EditElement(ElementGUISmartPointer element) {
//	cout << "ProjectTree::EditElement" << endl;
	propertiesFrame = new PropertiesFrame(this, std::tr1::static_pointer_cast<Propertyable>(element), renderersAndEditorsManager);
//	cout << "propertiesFrame = new PropertiesFrame..." << endl;
	propertiesFrame->SetPosition(wxPoint(50,50));
//	cout << "propertiesFrame->SetPosition(wxPoint(50,50));" << endl;

	int returnCode = propertiesFrame->ShowModal();
//	cout << "int returnCode = propertiesFrame->ShowModal();" << endl;
	propertiesFrame->SetFocus();
	propertiesFrame->Destroy();
//	cout << "propertiesFrame->Destroy();" << endl;

	delete propertiesFrame;
	propertiesFrame = 0;

	return returnCode == wxID_OK;
}

ProjectTree::~ProjectTree() {
	// O MEDIATOR APAGA ELE.
//	if (elementManager)
//		delete elementManager;
	if (icons)
		delete icons;

	if (propertiesFrame)
		propertiesFrame->Destroy();

	/* UpadtaMessageCommand é compartilhado em vários lugares. O central é que apagará ele*/
	// delete updateMessageCommand;
}

/*
 * Classe ItemsTree
 */
ItemsTree::ItemsTree(ElementGUISmartPointer element) {
	this->element = element;
	leaf = true;
}

ElementGUISmartPointer ItemsTree::GetElement() const {
    return element;
}

wxString ItemsTree::GetName() const {
    return name;
}

ItemsTree::ItemsTree(wxString name) {
	this->name = name;
	leaf = false;
}

bool ItemsTree::IsLeaf() const {
	return leaf;
}

ItemsTree::~ItemsTree() {
	/* Não é necessário deletar o element, pois ele já está armazenado no Manager, que é
	 * o responsável pela vida de element. */
}
