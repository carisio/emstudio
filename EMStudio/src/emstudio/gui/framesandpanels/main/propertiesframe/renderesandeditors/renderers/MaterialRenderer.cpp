/*
 * MaterialRenderer.cpp
 *
 *  Created on: 29/09/2011
 *      Author: leandrocarisio
 */

#include "MaterialRenderer.h"

MaterialRenderer::MaterialRenderer() {

}

MaterialRenderer::~MaterialRenderer() {

}

wxGridCellRenderer* MaterialRenderer::Clone() const {
	MaterialRenderer* clone = new MaterialRenderer;

	return clone;
}
