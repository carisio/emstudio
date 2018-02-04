/*
 * MatchWithPMLRenderer.cpp
 *
 *  Created on: 09/04/2013
 *      Author: Leandro
 */

#include "MatchWithPMLRenderer.h"
#include "emstudio/util/converters/Converter.h"

MatchWithPMLRenderer::MatchWithPMLRenderer() {
	wxGridCellBoolEditor::UseStringValues(Converter::GetTrueString(), Converter::GetFalseString());
}

MatchWithPMLRenderer::~MatchWithPMLRenderer() {
}

wxGridCellRenderer* MatchWithPMLRenderer::Clone() const {
	return new MatchWithPMLRenderer;
}
