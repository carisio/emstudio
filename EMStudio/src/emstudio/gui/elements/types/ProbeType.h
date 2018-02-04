/*
 * ProbeType.h
 *
 *  Created on: 05/02/2012
 *      Author: Leandro
 */

#ifndef PROBETYPE_H_
#define PROBETYPE_H_

#include "../ElementType.h"

class ProbeType : public ElementType {
public:
	ProbeType();
	virtual ~ProbeType();

	virtual wxString GetName();
    virtual wxIcon GetIcon();
    virtual ElementTypeSmartPointer NewElementType();
    virtual int GetSortIndex();
};

#endif /* PROBETYPE_H_ */
