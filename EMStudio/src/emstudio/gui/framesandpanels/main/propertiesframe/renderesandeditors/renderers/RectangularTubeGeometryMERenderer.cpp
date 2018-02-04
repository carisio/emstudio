/*
 * RectangularTubeGeometryMERenderer.cpp
 *
 *  Created on: 28/12/2013
 *      Author: Leandro
 */

#include "RectangularTubeGeometryMERenderer.h"

RectangularTubeGeometryMERenderer::RectangularTubeGeometryMERenderer() {

}

RectangularTubeGeometryMERenderer::~RectangularTubeGeometryMERenderer() {
}

wxGridCellRenderer* RectangularTubeGeometryMERenderer::Clone() const {
	return new RectangularTubeGeometryMERenderer;
}
