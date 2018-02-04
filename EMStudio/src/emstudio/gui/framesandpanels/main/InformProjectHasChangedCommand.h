/*
 * InformProjectHasChangedCommand.h
 *
 *  Created on: 27/06/2012
 *      Author: Leandro
 */

#ifndef INFORMPROJECTHASCHANGEDCOMMAND_H_
#define INFORMPROJECTHASCHANGEDCOMMAND_H_

#include "emstudio/util/command/Command.h"
#include "MainFrame.h"

class MainFrame;

class InformProjectHasChangedCommand : public Command {
private:
	MainFrame* frame;
public:
	InformProjectHasChangedCommand(MainFrame* frame);
	virtual ~InformProjectHasChangedCommand();
	virtual void Execute();
};

#endif /* INFORMPROJECTHASCHANGEDCOMMAND_H_ */
