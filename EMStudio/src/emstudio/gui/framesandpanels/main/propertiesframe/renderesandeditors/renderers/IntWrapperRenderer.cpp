/*
 * IntWrapperRenderer.cpp
 *
 *  Created on: 10/09/2011
 *      Author: Leandro
 */

#include "IntWrapperRenderer.h"

IntWrapperRenderer::IntWrapperRenderer() {

}

IntWrapperRenderer::~IntWrapperRenderer() {

}

wxGridCellRenderer* IntWrapperRenderer::Clone() const {
	IntWrapperRenderer* clone = new IntWrapperRenderer;

	return clone;
}
