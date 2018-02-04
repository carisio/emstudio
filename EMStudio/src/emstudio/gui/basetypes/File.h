/*
 * File.h
 *
 *  Created on: 20/06/2013
 *      Author: leandrocarisio
 */

#ifndef FILE_H_
#define FILE_H_

#include "BaseType.h"
#include "wx/wx.h"

class File : public BaseType {
private:
	wxString fileName;
	wxString wildcard; // File type. Ex: "Material files (*.mat)|*.mat"

public:
	File();
	virtual ~File();

	void SetFileName(wxString fileName);
	void SetWildcard(wxString wildcard);
	wxString GetFileName();
	wxString GetWildcard();

	virtual bool ProcessFile(wxString fileName);

	virtual void Copy(BaseType* b);
	virtual wxString GetBaseTypeClassName();

	virtual void SetUserFriendlyStringRepresentation(wxString str);
	virtual wxString GetUserFriendlyStringRepresentation();

	virtual void DoWrite(OutputBuffer& buffer);
	virtual void DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException);
};

#endif /* FILE_H_ */
