/*
 * MicrostripXYPortsMERenderer.cpp
 *
 *  Created on: 05/12/2013
 *      Author: leandrocarisio
 */

#include "MicrostripXYPortsMERenderer.h"

MicrostripXYPortsMERenderer::MicrostripXYPortsMERenderer() {

}

MicrostripXYPortsMERenderer::~MicrostripXYPortsMERenderer() {
}


wxGridCellRenderer* MicrostripXYPortsMERenderer::Clone() const {
	return new MicrostripXYPortsMERenderer;
}
