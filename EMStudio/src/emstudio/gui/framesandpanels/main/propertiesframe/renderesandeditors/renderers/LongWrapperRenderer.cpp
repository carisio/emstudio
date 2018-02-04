/*
 * LongWrapperRenderer.cpp
 *
 *  Created on: 10/09/2011
 *      Author: Leandro
 */

#include "LongWrapperRenderer.h"

LongWrapperRenderer::LongWrapperRenderer() {

}

LongWrapperRenderer::~LongWrapperRenderer() {

}

wxGridCellRenderer* LongWrapperRenderer::Clone() const {
	LongWrapperRenderer* clone = new LongWrapperRenderer;

	return clone;
}
