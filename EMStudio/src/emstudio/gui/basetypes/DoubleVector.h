/*
 * DoubleVector.h
 *
 *  Created on: 28/04/2013
 *      Author: Leandro
 */

#ifndef DOUBLEVECTOR_H_
#define DOUBLEVECTOR_H_

#include "wx/wx.h"
#include "BaseType.h"
#include "emstudio/util/tnt/tnt.h"

using namespace::TNT;
/**
 * Classe representa um vetor de double
 */
class DoubleVector : public BaseType {
private:
	Array1D<double> data;

public:
	DoubleVector();
	virtual ~DoubleVector();

	virtual void Copy(BaseType* b);
    virtual wxString GetBaseTypeClassName();

    virtual void SetUserFriendlyStringRepresentation(wxString str);
    virtual wxString GetUserFriendlyStringRepresentation();

	virtual void DoWrite(OutputBuffer& buffer);
	virtual void DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException);

	Array1D<double>& GetData();
    void SetData(Array1D<double> v);
};

#endif /* DOUBLEVECTOR_H_ */
