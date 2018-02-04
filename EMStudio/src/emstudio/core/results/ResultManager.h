/*
 * ResultManager.h
 *
 *  Created on: 26/03/2012
 *      Author: leandrocarisio
 */

#ifndef RESULTMANAGER_H_
#define RESULTMANAGER_H_

#include "wx/wx.h"
#include "Result.h"
#include <list>

class ResultManager {
private:
	std::list<ResultSmartPointer> resultList;

public:
	ResultManager();

	void AddResult(ResultSmartPointer r);
	ResultSmartPointer NewResult(wxString resultClassName);

	virtual ~ResultManager();
};

#endif /* RESULTMANAGER_H_ */
