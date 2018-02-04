/*
 * InformProjectHasChangedCommand.cpp
 *
 *  Created on: 27/06/2012
 *      Author: Leandro
 */

#include "InformProjectHasChangedCommand.h"

InformProjectHasChangedCommand::InformProjectHasChangedCommand(MainFrame* frame)
	: frame(frame) {

}

InformProjectHasChangedCommand::~InformProjectHasChangedCommand() {
}

void InformProjectHasChangedCommand::Execute() {
	frame->InformProjectHasChanged();
}
