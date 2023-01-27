/*
 * Resource.h
 *
 *  Created on: 11/04/2012
 *      Author: Leandro
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include "wx/wx.h"

class UtilResource {
public:
	UtilResource();

	static wxIcon GetIcon(wxString resourceIcoName);
	static wxBitmap GetBitmapFromIcon(wxString resourceIcoName);
	static wxBitmap GetBitmapFromIcon(wxIcon icon);
	static wxBitmap GetBitmap(wxString resourceBitmapName);

	virtual ~UtilResource();
};

#endif /* RESOURCE_H_ */
