/*
 * OrientationRenderer.cpp
 *
 *  Created on: 29/09/2011
 *      Author: leandrocarisio
 */

#include "OrientationRenderer.h"

OrientationRenderer::OrientationRenderer() {

}

OrientationRenderer::~OrientationRenderer() {

}

wxGridCellRenderer* OrientationRenderer::Clone() const {
	OrientationRenderer* clone = new OrientationRenderer;

	return clone;
}
