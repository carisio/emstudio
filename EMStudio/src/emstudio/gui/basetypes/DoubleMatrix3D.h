/*
 * DoubleMatrix3D.h
 *
 *  Created on: 28/04/2013
 *      Author: Leandro
 */

#ifndef DOUBLEMATRIX3D_H_
#define DOUBLEMATRIX3D_H_

#include "wx/wx.h"
#include "BaseType.h"
#include "emstudio/util/tnt/tnt.h"

using namespace::TNT;

/**
 * Classe representa uma matrix 3D de double
 */
class DoubleMatrix3D : public BaseType {
private:
	Array3D<double> data;

public:
	DoubleMatrix3D();
	virtual ~DoubleMatrix3D();

	virtual void Copy(BaseType* b);
    virtual wxString GetBaseTypeClassName();

    virtual void SetUserFriendlyStringRepresentation(wxString str);
    virtual wxString GetUserFriendlyStringRepresentation();

	virtual void DoWrite(OutputBuffer& buffer);
	virtual void DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException);

	Array3D<double>& GetData();
    void SetData(Array3D<double> v);
};

#endif /* DOUBLEMATRIX3D_H_ */
