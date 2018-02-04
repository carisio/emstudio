/*
 * ConnectionType.h
 *
 *  Created on: 15/07/2014
 *      Author: leandrocarisio
 */

#ifndef CONNECTIONTYPE_H_
#define CONNECTIONTYPE_H_

#include "../ElementType.h"

namespace mom {

class ConnectionType : public ElementType {
public:
	ConnectionType();
	virtual ~ConnectionType();

	virtual wxString GetName();
    virtual wxIcon GetIcon();
    virtual ElementTypeSmartPointer NewElementType();
    virtual int GetSortIndex();
};

} /* namespace mom */
#endif /* CONNECTIONTYPE_H_ */
