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
	wxBitmap r;
	r.CopyFromIcon(wxIcon(resourceIcoName, wxBITMAP_TYPE_ICO_RESOURCE));
	return r;
}
wxBitmap UtilResource::GetBitmap(wxString resourceBitmapName) {
	return wxBitmap(resourceBitmapName, wxBITMAP_TYPE_RESOURCE);
}
