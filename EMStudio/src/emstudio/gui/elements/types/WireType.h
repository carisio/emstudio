/*
 * WireType.h
 *
 *  Created on: 15/07/2014
 *      Author: leandrocarisio
 */

#ifndef WIRETYPE_H_
#define WIRETYPE_H_

#include "../ElementType.h"

namespace mom {

class WireType : public ElementType {
public:
	WireType();
	virtual ~WireType();

	virtual wxString GetName();
    virtual wxIcon GetIcon();
    virtual ElementTypeSmartPointer NewElementType();
    virtual int GetSortIndex();
};

} /* namespace mom */
#endif /* WIRETYPE_H_ */
