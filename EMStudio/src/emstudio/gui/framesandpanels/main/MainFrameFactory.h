/*
 * MainFrameFactory.h
 *
 *  Created on: 02/05/2014
 *      Author: leandrocarisio
 */

#ifndef MAINFRAMEFACTORY_H_
#define MAINFRAMEFACTORY_H_

#include "MainFrame.h"
#include "FDTDMainFrame.h"
#include "NECMainFrame.h"
#include "emstudio/moderator/Moderator.h"
#include "wx/wx.h"

class MainFrameFactory {
public:
	MainFrameFactory();
	virtual ~MainFrameFactory();

	static MainFrame* NewMainFrame(Moderator* moderator);
};

#endif /* MAINFRAMEFACTORY_H_ */
