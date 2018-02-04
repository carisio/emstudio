/*
 * DoubleMatrix2D.h
 *
 *  Created on: 28/04/2013
 *      Author: Leandro
 */

#ifndef DOUBLEMATRIX2D_H_
#define DOUBLEMATRIX2D_H_

#include "wx/wx.h"
#include "BaseType.h"
#include "emstudio/util/tnt/tnt.h"

using namespace::TNT;

/**
 * Classe representa uma matrix 2D de double
 */
class DoubleMatrix2D : public BaseType {
private:
	Array2D<double> data;

public:
	DoubleMatrix2D();
	virtual ~DoubleMatrix2D();

	virtual void Copy(BaseType* b);
    virtual wxString GetBaseTypeClassName();

    virtual void SetUserFriendlyStringRepresentation(wxString str);
    virtual wxString GetUserFriendlyStringRepresentation();

	virtual void DoWrite(OutputBuffer& buffer);
	virtual void DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException);

    Array2D<double>& GetData();
    void SetData(Array2D<double> v);
};

#endif /* DOUBLEMATRIX2D_H_ */
