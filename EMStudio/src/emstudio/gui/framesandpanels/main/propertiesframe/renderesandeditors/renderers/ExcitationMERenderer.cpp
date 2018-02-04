/*
 * ExcitationMERenderer.cpp
 *
 *  Created on: 06/11/2013
 *      Author: leandrocarisio
 */

#include "ExcitationMERenderer.h"

ExcitationMERenderer::ExcitationMERenderer() {

}

ExcitationMERenderer::~ExcitationMERenderer() {
}

wxGridCellRenderer* ExcitationMERenderer::Clone() const {
	return new ExcitationMERenderer;
}
