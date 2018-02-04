/*
 * Object2DType.h
 *
 *  Created on: 20/11/2013
 *      Author: leandrocarisio
 */

#ifndef OBJECT2DTYPE_H_
#define OBJECT2DTYPE_H_

#include "../ElementType.h"

class Object2DType : public ElementType {
public:
	Object2DType();
	virtual ~Object2DType();

	virtual wxString GetName();
    virtual wxIcon GetIcon();
    virtual ElementTypeSmartPointer NewElementType();
    virtual int GetSortIndex();
};

#endif /* OBJECT2DTYPE_H_ */
