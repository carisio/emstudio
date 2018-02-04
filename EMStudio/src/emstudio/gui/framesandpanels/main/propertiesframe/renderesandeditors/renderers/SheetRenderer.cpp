/*
 * SheetRenderer.cpp
 *
 *  Created on: 14/11/2012
 *      Author: leandrocarisio
 */

#include "SheetRenderer.h"

SheetRenderer::SheetRenderer() {

}

SheetRenderer::~SheetRenderer() {
}

wxGridCellRenderer* SheetRenderer::Clone() const {
	return new SheetRenderer;
}
