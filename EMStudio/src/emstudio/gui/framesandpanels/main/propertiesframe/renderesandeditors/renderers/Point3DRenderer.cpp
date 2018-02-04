/*
 * Point3DRenderer.cpp
 *
 *  Created on: 13/02/2012
 *      Author: Leandro
 */

#include "Point3DRenderer.h"

Point3DRenderer::Point3DRenderer() {

}

Point3DRenderer::~Point3DRenderer() {
}

wxGridCellRenderer* Point3DRenderer::Clone() const {
	return new Point3DRenderer;
}
