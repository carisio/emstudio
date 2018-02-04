/*
 * FieldAtPlaneDTO.h
 *
 *  Created on: 13/03/2013
 *      Author: leandrocarisio
 */

#ifndef FIELDATPLANEDTO_H_
#define FIELDATPLANEDTO_H_

#include "RectangularPECSheetDTO.h"
#include "emstudio/gui/basetypes/SelectField.h"

class FieldAtPlaneDTO : public RectangularPECSheetDTO {
private:
	int numberOfSamples;
	SelectField field;

public:
	FieldAtPlaneDTO();
	virtual ~FieldAtPlaneDTO();

	int GetNumberOfSamples();
	void SetNumberOfSamples(int samples);

	SelectField GetField();
	void SetField(SelectField f);

	virtual Priority GetPriority();

	virtual wxString GetDTOClassName();
};

#endif /* FIELDATPLANEDTO_H_ */
