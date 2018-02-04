/*
 * BaseTypeIncompatibleExcepation.h
 *
 *  Created on: 06/05/2013
 *      Author: leandrocarisio
 */

#ifndef BASETYPEINCOMPATIBLEEXCEPATION_H_
#define BASETYPEINCOMPATIBLEEXCEPATION_H_

#include "wx/wx.h"

class BaseTypeIncompatibleException {
private:
	wxString baseTypeName;
public:
	BaseTypeIncompatibleException(wxString propertyName);
	virtual ~BaseTypeIncompatibleException();

	wxString GetBaseTypeName();
};

#endif /* BASETYPEINCOMPATIBLEEXCEPATION_H_ */
