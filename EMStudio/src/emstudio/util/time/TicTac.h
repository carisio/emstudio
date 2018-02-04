/*
 * TicTac.h
 *
 *  Created on: 10/11/2012
 *      Author: Leandro
 */

#ifndef TICTAC_H_
#define TICTAC_H_

#include "wx\wx.h"
#include <ctime>
#include "wx\log.h"

class TicTac {
private:
	wxString message;
	double tstart;
	double tend;
public:
	TicTac();
	virtual ~TicTac();
	void Tic(wxString msg);
	void Tac();
};

#endif /* TICTAC_H_ */
