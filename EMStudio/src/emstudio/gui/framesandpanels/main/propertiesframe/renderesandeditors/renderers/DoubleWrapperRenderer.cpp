/*
 * DoubleWrapperRenderer.cpp
 *
 *  Created on: 07/09/2011
 *      Author: Leandro
 */

#include "DoubleWrapperRenderer.h"

DoubleWrapperRenderer::DoubleWrapperRenderer() {
}

DoubleWrapperRenderer::~DoubleWrapperRenderer() {
}

wxGridCellRenderer* DoubleWrapperRenderer::Clone() const {
	DoubleWrapperRenderer* clone = new DoubleWrapperRenderer;

	return clone;
}
