/*
 * Propertyable.cpp
 *
 *  Created on: 03/09/2011
 *      Author: Leandro
 */

#include "Propertyable.h"

#include <iostream>
using namespace::std;
Propertyable::Propertyable() {
	propertyList = list<Property>();
	SetChanged(true);
}

Propertyable::~Propertyable() {

}

list<Property>* Propertyable::GetPropertiesList() {
	return &propertyList;
}
void Propertyable::WriteProperties(OutputBuffer& buffer) {
	int size = propertyList.size();
	buffer.WriteInt(size);

	Propertyable::Iterator itProperties = propertyList.begin();
	Propertyable::Iterator end = propertyList.end();

	while (itProperties != end) {
		wxString name = itProperties->GetName();
		buffer.WriteString(name);
		itProperties->GetValue()->Write(buffer);

		itProperties++;
	}
}
void Propertyable::ReadProperties(InputBuffer& buffer) throw(BaseTypeIncompatibleException, PropertyNotFoundException) {
	cout << "Lendo propriedades do elemento" << endl;
	int nProperties = buffer.ReadInt();
	cout << "Qtd de propriedades = " << nProperties << endl;

	for (int i = 0; i < nProperties; i++) {
		wxString name = buffer.ReadString();
		cout << "Lendo propriedade " << name << endl;
		GetProperty(name).GetValue()->Read(buffer);
	}
}
Property& Propertyable::GetProperty(wxString name) throw(PropertyNotFoundException) {
	Iterator it = GetPropertiesList()->begin();
	Iterator end = GetPropertiesList()->end();
	while (it != end) {
		if (it->GetName() == name)
			return *it;
		it++;
	}

	throw PropertyNotFoundException(name);
}
void Propertyable::AddProperty(Property p) {
	propertyList.push_back(p);
}

void Propertyable::TransferDataFrom(PropertyableSmartPointer objectFrom) {
	Iterator thisObjectIterator = GetPropertiesList()->begin();
	Iterator end = GetPropertiesList()->end();
	Iterator otherObjectIterator = objectFrom->GetPropertiesList()->begin();

	while (thisObjectIterator != end) {
		thisObjectIterator->SetValue(otherObjectIterator->GetValue());
		thisObjectIterator->SetValidator(otherObjectIterator->GetValidator());

		thisObjectIterator++;
		otherObjectIterator++;
	}
	SetChanged(true);
}

bool Propertyable::IsPropertiesValid() {
	Iterator it = GetPropertiesList()->begin();
	Iterator end = GetPropertiesList()->end();
	while (it != end) {
		if (! (it->IsValid())) {
			return false;
		}
		it++;
	}
	return true;
}
wxString Propertyable::GetPropertiesErrorMessage() {
	wxString result;

	Iterator it = GetPropertiesList()->begin();
	Iterator end = GetPropertiesList()->end();
	while (it != end) {
		wxString erroDeUmaPropriedade = it->GetErrorMessage();
		if (erroDeUmaPropriedade != "") {
			result.Append(erroDeUmaPropriedade).Append("\n");
		}
		it++;
	}
	return result;
}

bool Propertyable::IsAllPropertiesTogetherValid() {
	return true;
}
void Propertyable::SetAllPropertiesTogetherErrorMessage(wxString msg) {
	allPropertiesTogetherErrorMessage = msg;
}
wxString Propertyable::GetAllPropertiesTogetherErrorMessage() {
	return allPropertiesTogetherErrorMessage;
}
// Informa se houve alguma alteração no objeto
bool Propertyable::IsChanged() {
	return changed;
}
void Propertyable::SetChanged(bool c) {
	changed = c;
}
