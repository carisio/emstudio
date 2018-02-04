/*
 * PropertiesGridTable.cpp
 *
 *  Created on: 07/09/2011
 *      Author: Leandro
 */

#include "PropertiesGridTable.h"

PropertiesGridTable::PropertiesGridTable(PropertyableSmartPointer propertyable) {
	this->object = propertyable;

	/*
	 * TODO: Não lembro pra que escrevi o código abaixo.
	 * Deve ter sido apenas para testar a operação ConvertFromString(ConvertToString()).
	 * Deixar aqui até a versão final. Facilita pegar erros quando um novo BaseType foi criado.
	 */
//	Propertyable::Iterator i = object->GetPropertiesList()->begin();
//	Propertyable::Iterator iEnd = object->GetPropertiesList()->end();
//	while (i != iEnd) {
//		wxString s = i->GetValue()->ConvertToString();
//		i->GetValue()->ConvertFromString(s);
//		i++;
//	}
}

PropertiesGridTable::~PropertiesGridTable() {
	// Não tem que apagar nada.
}

int PropertiesGridTable::GetNumberRows() {
	return object->GetPropertiesList()->size();
}

int PropertiesGridTable::GetNumberCols() {
	return 1;
}

bool PropertiesGridTable::IsEmptyCell(int row, int col) {
	return false;
}

Propertyable::Iterator PropertiesGridTable::GetPropertyAtRow(int row) {
	Propertyable::Iterator i = object->GetPropertiesList()->begin();
	for (int aux = 0; aux < row; aux++)
		i++;
	return i;
}

wxString PropertiesGridTable::GetTypeName(int row, int col) {
	return GetPropertyAtRow(row)->GetBaseTypeClassName();
}

/* Row and col labels */
wxString PropertiesGridTable::GetRowLabelValue(int row) {
	return GetPropertyAtRow(row)->GetName();
}

wxString PropertiesGridTable::GetColLabelValue(int row) {
	return "Value";
}

/* Get and Set methods */
wxString PropertiesGridTable::GetValue(int row, int col) {
	// Serve para qualquer classe que pode ser bem representada por uma string;
	Propertyable::Iterator p = GetPropertyAtRow(row);
	return p->GetValue()->GetUserFriendlyStringRepresentation();
}
void PropertiesGridTable::SetValue( int row, int col, const wxString& value) {
	// Serve para qualquer classe que pode ser bem representada por uma string;
	Propertyable::Iterator p = GetPropertyAtRow(row);
	p->GetValue()->SetUserFriendlyStringRepresentation(value);
}

BaseType* PropertiesGridTable::GetValueAsBaseType(int row, int col) {
	Propertyable::Iterator p = GetPropertyAtRow(row);
	return p->GetValue();
}

void PropertiesGridTable::SetValueAsBaseType(int row, int col, BaseType* baseType) {
	Propertyable::Iterator p = GetPropertyAtRow(row);
	p->SetValue(baseType);
}
