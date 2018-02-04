/*
 * GenericPECSheetDTO.h
 *
 *  Created on: 16/04/2013
 *      Author: Leandro
 */

#ifndef GENERICPECSHEETDTO_H_
#define GENERICPECSHEETDTO_H_

#include "ElementsWithFacetsDTO.h"
#include "emstudio/gui/basetypes/MatchWithPML.h"
#include "emstudio/gui/basetypes/GenericSheet.h"

class GenericPECSheetDTO : public ElementsWithFacetsDTO {
private:
	GenericSheet sheet;
//	MatchWithPML matchWithPML;
public:
	GenericPECSheetDTO();
	virtual ~GenericPECSheetDTO();

	void SetGenericSheet(GenericSheet g);
//	void SetMatchWithPML(MatchWithPML m);

	GenericSheet GetGenericSheet();
//	MatchWithPML GetMatchWithPML();

	virtual void DoUnnormalize(Units units);
	virtual wxString GetDTOClassName();
	virtual Priority GetPriority();
};

#endif /* GENERICPECSHEETDTO_H_ */
