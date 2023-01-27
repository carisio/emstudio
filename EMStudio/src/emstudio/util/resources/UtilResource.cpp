/*
 * Resource.cpp
 *
 *  Created on: 11/04/2012
 *      Author: Leandro
 */

#include "UtilResource.h"

UtilResource::UtilResource() {


}

UtilResource::~UtilResource() {
}

wxIcon UtilResource::GetIcon(wxString resourceIcoName) {
	return wxIcon(resourceIcoName, wxBITMAP_TYPE_ICO_RESOURCE);
}
wxBitmap UtilResource::GetBitmapFromIcon(wxString resourceIcoName) {
	return UtilResource::GetBitmapFromIcon(UtilResource::GetIcon(resourceIcoName));
}
wxBitmap UtilResource::GetBitmapFromIcon(wxIcon icon) {
	wxBitmap r;
	r.CopyFromIcon(icon);
	return r;
}
wxBitmap UtilResource::GetBitmap(wxString resourceBitmapName) {
	return wxBitmap(resourceBitmapName, wxBITMAP_TYPE_RESOURCE);
}
