/*
 * GenericSheetRenderer.cpp
 *
 *  Created on: 16/04/2013
 *      Author: leandrocarisio
 */

#include "GenericSheetRenderer.h"

GenericSheetRenderer::GenericSheetRenderer() {

}

GenericSheetRenderer::~GenericSheetRenderer() {
}

wxGridCellRenderer* GenericSheetRenderer::Clone() const {
	return new GenericSheetRenderer;
}
