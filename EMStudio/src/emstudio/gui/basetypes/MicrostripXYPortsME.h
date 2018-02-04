/*
 * MicrostripXYPortsME.h
 *
 *  Created on: 05/12/2013
 *      Author: leandrocarisio
 */

#ifndef MICROSTRIPXYPORTSME_H_
#define MICROSTRIPXYPORTSME_H_

#include "emstudio/util/muparser/MathParser.h" /* OBS.: Esse include tem que aparecer sempre antes do include do wx/wx.h !!!! */
#include "BaseType.h"
#include "MicrostripXYPorts.h"
#include "wx/wx.h"
#include <vector>

class MicrostripXYPortsME : public BaseType {
private:
	MathParser parser;

	std::vector<std::pair<wxString, wxString> > coordinates;
public:
	MicrostripXYPortsME();
	virtual ~MicrostripXYPortsME();

	/* Métodos acessores para as coordenadas da placa */
	std::vector<std::pair<wxString, wxString> > GetCoordinates();
	void SetCoordinates(std::vector<std::pair<wxString, wxString> >);

	bool IsPortsValid();
	MicrostripXYPorts ConvertToMicrostripXYPorts();

	virtual void Copy(BaseType* b);
	virtual wxString GetBaseTypeClassName();

	virtual void SetUserFriendlyStringRepresentation(wxString str);
	virtual wxString GetUserFriendlyStringRepresentation();

	virtual void DoWrite(OutputBuffer& buffer);
	virtual void DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException);
};

#endif /* MICROSTRIPXYPORTSME_H_ */
