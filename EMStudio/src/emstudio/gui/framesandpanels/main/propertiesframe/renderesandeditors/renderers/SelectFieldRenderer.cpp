/*
 * SelectFieldRenderer.cpp
 *
 *  Created on: 25/04/2013
 *      Author: Leandro
 */

#include "SelectFieldRenderer.h"

SelectFieldRenderer::SelectFieldRenderer() {

}

SelectFieldRenderer::~SelectFieldRenderer() {
}

wxGridCellRenderer* SelectFieldRenderer::Clone() const {
	SelectFieldRenderer* clone = new SelectFieldRenderer;

	return clone;
}
