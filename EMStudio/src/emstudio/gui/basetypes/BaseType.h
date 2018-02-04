/*
 * BaseType.h
 *
 *  Created on: 01/09/2011
 *      Author: Leandro
 */

#ifndef BASETYPE_H_
#define BASETYPE_H_

#include "wx/wx.h"
#include "emstudio/util/file/InputBuffer.h"
#include "emstudio/util/file/OutputBuffer.h"
#include "emstudio/exception/BaseTypeIncompatibleException.h"

class BaseType {
private:
	/**
	 * Representa a versão da interface de um BaseType. Suponha que determinado tipo base tenha uma interface com 2 inteiros.
	 * Em seguida, a interface é alterada para considerar 2 inteiros e 1 string.
	 * Um basetype salvo no formato novo não pode travar uma cópia antiga do programa. Por isso, os método DoRead devem primeiro verificar
	 * se a versão é compatível, ou seja, se ele sabe ler aquele tipo de programa.
	 */
	int writeVersion;
	int readVersion;
public:
	BaseType();
	virtual ~BaseType();
	virtual void Copy(BaseType* b) = 0;
	virtual wxString GetBaseTypeClassName() = 0;

	virtual void SetUserFriendlyStringRepresentation(wxString str) = 0;
	virtual wxString GetUserFriendlyStringRepresentation() = 0;

	void SetWriteVersion(int v);
	int GetReadVersion();
	void Write(OutputBuffer& buffer);
	void Read(InputBuffer& buffer) throw(BaseTypeIncompatibleException);
	virtual void DoWrite(OutputBuffer& buffer) = 0;
	virtual void DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException) = 0;
};

#endif /* BASETYPE_H_ */
