/*
 * FileRenderer.cpp
 *
 *  Created on: 20/06/2013
 *      Author: leandrocarisio
 */

#include "FileRenderer.h"

FileRenderer::FileRenderer() {

}

FileRenderer::~FileRenderer() {
}

wxGridCellRenderer* FileRenderer::Clone() const {
	return new FileRenderer;
}
