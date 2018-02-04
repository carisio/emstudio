/*
 * ElementDTO.h
 *
 *  Created on: 29/08/2011
 *      Author: Leandro
 */

#ifndef ELEMENTDTO_H_
#define ELEMENTDTO_H_

#include "wx/wx.h"
#include <tr1/memory>
#include "emstudio/units/Units.h"

class ElementDTO;

typedef std::tr1::shared_ptr<ElementDTO> ElementDTOSmartPointer;

class ElementDTO {
private:
	wxString name;
public:
	ElementDTO();
	virtual wxString GetDTOClassName() = 0;
	virtual ~ElementDTO();

    wxString GetName() const;
    void SetName(wxString name);

	virtual void Unnormalize(Units units);
	virtual void DoUnnormalize(Units units);
};

#endif /* ELEMENTDTO_H_ */
