/*
 * Source.h
 *
 *  Created on: 24/08/2011
 *      Author: Leandro
 */

#ifndef SOURCETYPE_H_
#define SOURCETYPE_H_

#include "../ElementType.h"

class SourceType : public ElementType {
public:
	SourceType();
	virtual ~SourceType();

	virtual wxString GetName();
	virtual wxIcon GetIcon();
	virtual ElementTypeSmartPointer NewElementType();
	virtual int GetSortIndex();
};

#endif /* SOURCETYPE_H_ */
