/*
 * DXFFile.h
 *
 *  Created on: 20/06/2013
 *      Author: leandrocarisio
 */

#ifndef DXFFILE_H_
#define DXFFILE_H_

#include "File.h"
#include "emstudio/util/file/DXFParser.h"

class DXFFile : public File {
private:
	DXFParser parser;

public:
	DXFFile();
	virtual ~DXFFile();

	virtual bool ProcessFile(wxString fileName);

	virtual void Copy(BaseType* b);
	virtual wxString GetBaseTypeClassName();

	DXFEntityList& GetEntityList();
	DXFParser& GetParser();

	virtual void DoWrite(OutputBuffer& buffer);
	virtual void DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException);
};

#endif /* DXFFILE_H_ */
