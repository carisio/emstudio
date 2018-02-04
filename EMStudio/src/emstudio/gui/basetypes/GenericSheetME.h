/*
 * GenericSheetME.h
 *
 *  Created on: 18/11/2013
 *      Author: leandrocarisio
 */

#ifndef GENERICSHEETME_H_
#define GENERICSHEETME_H_

#include "emstudio/util/muparser/MathParser.h" /* OBS.: Esse include tem que aparecer sempre antes do include do wx/wx.h !!!! */
#include "BaseType.h"
#include "GenericSheet.h"

#include "wx/wx.h"

#include <vector>
#include <map>

class GenericSheetME : public BaseType {
private:
	GenericSheet gs;

	MathParser parser;

	enum SheetCutAtPlane{XY, YZ, ZX};
	/* Representa o plano em que a placa está */
	int plane;
	/* Representa as coordenadas da placa.
	 *
	 * As coordenadas são representadas da seguinte forma:
	 * Se o corte é em x, as coordenadas são dadas em (y, z);
	 * Se o corte é em y, as coordenadas são dadas em (x, z);
	 * Se o corte é em z, as coordenadas são dadas em (x, y);
	 */
	std::vector<std::pair<wxString, wxString> > coordinates;

	wxString cutAt;

	void BuildGS();
public:
	GenericSheetME();
	virtual ~GenericSheetME();

	/* Métodos acessores para as coordenadas da placa */
	std::vector<std::pair<wxString, wxString> > GetCoordinates();
	void SetCoordinates(std::vector<std::pair<wxString, wxString> >);

	bool IsCutAtX();
	bool IsCutAtY();
	bool IsCutAtZ();
	void SetCutAtX(wxString x);
	void SetCutAtY(wxString y);
	void SetCutAtZ(wxString z);
	wxString GetCutAtExpression();
	double GetCutAt();

	bool IsGenericSheetValid();
	GenericSheet ConvertToGenericSheet(bool forceRebuildGenericSheet);

	virtual void Copy(BaseType* b);
	virtual wxString GetBaseTypeClassName();

	virtual void SetUserFriendlyStringRepresentation(wxString str);
	virtual wxString GetUserFriendlyStringRepresentation();

	virtual void DoWrite(OutputBuffer& buffer);
	virtual void DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException);
};

#endif /* GENERICSHEETME_H_ */
