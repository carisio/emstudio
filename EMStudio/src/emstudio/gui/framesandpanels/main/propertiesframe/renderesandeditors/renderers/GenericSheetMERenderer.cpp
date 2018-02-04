/*
 * GenericSheetMERenderer.cpp
 *
 *  Created on: 18/11/2013
 *      Author: leandrocarisio
 */

#include "GenericSheetMERenderer.h"

GenericSheetMERenderer::GenericSheetMERenderer() {

}

GenericSheetMERenderer::~GenericSheetMERenderer() {
}


wxGridCellRenderer* GenericSheetMERenderer::Clone() const {
	return new GenericSheetMERenderer;
}
