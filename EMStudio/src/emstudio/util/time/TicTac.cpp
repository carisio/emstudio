/*
 * TicTac.cpp
 *
 *  Created on: 10/11/2012
 *      Author: Leandro
 */

#include "TicTac.h"
#include <iostream>
using namespace::std;

TicTac::TicTac() {
}

TicTac::~TicTac() {
}

void TicTac::Tic(wxString msg) {
	message = msg;
	tstart = (double)clock()/CLOCKS_PER_SEC;
}

void TicTac::Tac() {
	tend = (double)clock()/CLOCKS_PER_SEC;
	cout << message << endl;
	cout << "\tDuracao = " << (tend-tstart) << " segundos" << endl;
}
