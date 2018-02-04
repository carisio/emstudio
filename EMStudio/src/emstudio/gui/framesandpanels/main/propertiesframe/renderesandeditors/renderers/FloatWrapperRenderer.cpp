/*
 * FloatWrapperRenderer.cpp
 *
 *  Created on: 10/09/2011
 *      Author: Leandro
 */

#include "FloatWrapperRenderer.h"

FloatWrapperRenderer::FloatWrapperRenderer() {

}

FloatWrapperRenderer::~FloatWrapperRenderer() {

}

wxGridCellRenderer* FloatWrapperRenderer::Clone() const {
	FloatWrapperRenderer* clone = new FloatWrapperRenderer;

	return clone;
}
