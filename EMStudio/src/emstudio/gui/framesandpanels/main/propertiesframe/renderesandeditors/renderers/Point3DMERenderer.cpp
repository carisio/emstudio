/*
 * Point3DMERenderer.cpp
 *
 *  Created on: 17/10/2013
 *      Author: leandrocarisio
 */

#include "Point3DMERenderer.h"

Point3DMERenderer::Point3DMERenderer() {

}

Point3DMERenderer::~Point3DMERenderer() {
}

wxGridCellRenderer* Point3DMERenderer::Clone() const {
	return new Point3DMERenderer;
}
