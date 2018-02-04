/*
 * ElementDTO.cpp
 *
 *  Created on: 29/08/2011
 *      Author: Leandro
 */

#include "ElementDTO.h"
ElementDTO::ElementDTO() {

}

wxString ElementDTO::GetName() const {
    return name;
}

void ElementDTO::SetName(wxString name) {
    this->name = name;
}

ElementDTO::~ElementDTO() {

}

void ElementDTO::Unnormalize(Units units) {
	DoUnnormalize(units);
}
void ElementDTO::DoUnnormalize(Units units) {

}

