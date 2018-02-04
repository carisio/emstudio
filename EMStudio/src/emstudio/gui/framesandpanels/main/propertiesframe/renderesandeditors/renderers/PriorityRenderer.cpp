/*
 * PriorityRenderer.cpp
 *
 *  Created on: 13/02/2012
 *      Author: Leandro
 */

#include "PriorityRenderer.h"

PriorityRenderer::PriorityRenderer() {

}

PriorityRenderer::~PriorityRenderer() {
}

wxGridCellRenderer* PriorityRenderer::Clone() const {
	PriorityRenderer* clone = new PriorityRenderer;

	return clone;
}
