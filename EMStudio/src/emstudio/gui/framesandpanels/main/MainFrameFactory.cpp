/*
 * MainFrameFactory.cpp
 *
 *  Created on: 02/05/2014
 *      Author: leandrocarisio
 */

#include "MainFrameFactory.h"
#include "emstudio/moderator/ConfigApp.h"

MainFrameFactory::MainFrameFactory() {
}

MainFrameFactory::~MainFrameFactory() {
}

MainFrame* MainFrameFactory::NewMainFrame(Moderator* moderator) {
	MainFrame* frame = 0;
	if (AppType == "FDTD")
		frame = new FDTDMainFrame(wxT("EM Studio"), moderator);
	else if (AppType == "MoM")
		frame = new NECMainFrame(wxT("EM Studio"), moderator);
	return frame;
}
