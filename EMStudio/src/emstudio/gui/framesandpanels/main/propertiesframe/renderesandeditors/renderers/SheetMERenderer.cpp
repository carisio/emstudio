/*
 * SheetMERenderer.cpp
 *
 *  Created on: 18/11/2013
 *      Author: leandrocarisio
 */

#include "SheetMERenderer.h"

SheetMERenderer::SheetMERenderer() {

}

SheetMERenderer::~SheetMERenderer() {
}


wxGridCellRenderer* SheetMERenderer::Clone() const {
	return new SheetMERenderer;
}
