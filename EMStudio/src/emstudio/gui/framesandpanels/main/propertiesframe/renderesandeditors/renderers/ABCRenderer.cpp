/*
 * ABCRenderer.cpp
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#include "ABCRenderer.h"

ABCRenderer::ABCRenderer() {

}

ABCRenderer::~ABCRenderer() {

}

wxGridCellRenderer* ABCRenderer::Clone() const {
	return new ABCRenderer;
}
