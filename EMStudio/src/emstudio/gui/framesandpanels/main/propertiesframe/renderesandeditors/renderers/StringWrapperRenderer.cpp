/*
 * StringWrapperRenderer.cpp
 *
 *  Created on: 10/09/2011
 *      Author: Leandro
 */

#include "StringWrapperRenderer.h"

StringWrapperRenderer::StringWrapperRenderer() {
}

StringWrapperRenderer::~StringWrapperRenderer() {
}

wxGridCellRenderer* StringWrapperRenderer::Clone() const {
	StringWrapperRenderer* clone = new StringWrapperRenderer;
	return clone;
}
