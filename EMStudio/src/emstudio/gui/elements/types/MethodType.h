/*
 * MethodType.h
 *
 *  Created on: 29/08/2011
 *      Author: Leandro
 */

#ifndef METHODTYPE_H_
#define METHODTYPE_H_

#include "../ElementType.h"

class MethodType : public ElementType {
public:
	MethodType();
	virtual ~MethodType();

	virtual wxString GetName();
    virtual wxIcon GetIcon();
    virtual ElementTypeSmartPointer NewElementType();
    virtual int GetSortIndex();
};

#endif /* METHODTYPE_H_ */
