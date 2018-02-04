/*
 * NECMainFrame.h
 *
 *  Created on: 02/05/2014
 *      Author: leandrocarisio
 */

#ifndef NECMAINFRAME_H_
#define NECMAINFRAME_H_

#include "MainFrame.h"

#include "emstudio/moderator/Moderator.h"

#include "wx/wx.h"

class NECMainFrame : public MainFrame {
private:
	virtual void RegisterAvailableElements();
	virtual void RegisterDefaultElementsInProject();


public:
	virtual wxString GetAppType();
	NECMainFrame(const wxString& title, Moderator* moderator);
	virtual ~NECMainFrame();
};

#endif /* NECMAINFRAME_H_ */
