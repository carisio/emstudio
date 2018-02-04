/*
 * BoolWrapperRenderer.cpp
 *
 *  Created on: 10/09/2011
 *      Author: Leandro
 */

#include "BoolWrapperRenderer.h"
#include "wx/renderer.h"
#include "emstudio/gui/basetypes/BoolWrapper.h"
#include "../../PropertiesGridTable.h"
#include "emstudio/util/converters/Converter.h"

BoolWrapperRenderer::BoolWrapperRenderer() {
	wxGridCellBoolEditor::UseStringValues(Converter::GetTrueString(), Converter::GetFalseString());
}

BoolWrapperRenderer::~BoolWrapperRenderer() {

}
wxGridCellRenderer* BoolWrapperRenderer::Clone() const {
	BoolWrapperRenderer* clone = new BoolWrapperRenderer;

	return clone;
}
