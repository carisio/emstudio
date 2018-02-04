/*
 * PlaneRenderer.cpp
 *
 *  Created on: 30/09/2011
 *      Author: leandrocarisio
 */

#include "PlaneRenderer.h"

PlaneRenderer::PlaneRenderer() {

}

PlaneRenderer::~PlaneRenderer() {

}

wxGridCellRenderer* PlaneRenderer::Clone() const {
	PlaneRenderer* clone = new PlaneRenderer;

	return clone;
}
