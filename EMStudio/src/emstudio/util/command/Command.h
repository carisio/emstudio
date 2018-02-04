/*
 * Command.h
 *
 *  Created on: 27/06/2012
 *      Author: Leandro
 */

#ifndef COMMAND_H_
#define COMMAND_H_

class Command {
public:
	Command();
	virtual ~Command();
	virtual void Execute() = 0;
};

#endif /* COMMAND_H_ */
