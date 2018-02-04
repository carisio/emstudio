/*
 * GenericPECSheetsDTO.h
 *
 *  Created on: 16/12/2013
 *      Author: leandrocarisio
 */

#ifndef GENERICPECSHEETSDTO_H_
#define GENERICPECSHEETSDTO_H_

#include "ElementsWithFacetsDTO.h"
#include "emstudio/gui/basetypes/MatchWithPML.h"
#include "emstudio/gui/basetypes/GenericSheet.h"
#include <vector>

class GenericPECSheetsDTO : public ElementsWithFacetsDTO {
private:
	std::vector<GenericSheet> sheets;

public:
	GenericPECSheetsDTO();
	virtual ~GenericPECSheetsDTO();

	void SetGenericSheets(std::vector<GenericSheet> s);
	std::vector<GenericSheet> GetGenericSheets();

	virtual void DoUnnormalize(Units units);
	virtual wxString GetDTOClassName();
	virtual Priority GetPriority();
};

#endif /* GENERICPECSHEETSDTO_H_ */
