/*
 * ObjectType.h
 *
 *  Created on: 24/08/2011
 *      Author: Leandro
 */

#ifndef OBJECT3DTYPE_H_
#define OBJECT3DTYPE_H_

#include "../ElementType.h"

class Object3DType : public ElementType {
public:
	Object3DType();
	virtual ~Object3DType();

	virtual wxString GetName();
    virtual wxIcon GetIcon();
    virtual ElementTypeSmartPointer NewElementType();
    virtual int GetSortIndex();
};

#endif /* OBJECT3DTYPE_H_ */
