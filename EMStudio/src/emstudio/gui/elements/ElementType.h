/*
 * ElementType.h
 *
 *  Created on: 24/08/2011
 *      Author: Leandro
 */

#ifndef ELEMENTTYPE_H_
#define ELEMENTTYPE_H_

#include "wx/wx.h"
#include <tr1/memory>
class ElementType;

typedef std::tr1::shared_ptr<ElementType> ElementTypeSmartPointer;

class ElementType {
public:
	ElementType();
	virtual ~ElementType();
	virtual wxString GetName() = 0;
    virtual wxIcon GetIcon() = 0;
    virtual ElementTypeSmartPointer NewElementType() = 0;
    virtual int GetSortIndex() = 0;
};

#endif /* ELEMENTTYPE_H_ */
