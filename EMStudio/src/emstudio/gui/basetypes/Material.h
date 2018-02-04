/*
 * Material.h
 *
 *  Created on: 26/09/2011
 *      Author: leandrocarisio
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "BaseType.h"
#include "emstudio/util/converters/Converter.h"
#include "MaterialLibrary.h"

#include "wx/wx.h"

#include "wx/tokenzr.h"
#include <tr1/memory>

class MaterialLibrary;

enum MaterialType{PEC, ANISOTROPIC, ISOTROPIC};

class Material : public BaseType {
private:
	static std::tr1::shared_ptr<MaterialLibrary> library;
//public:
//	static std::tr1::shared_ptr<MaterialLibrary> GetMaterialLibrary();
//	static void SetMaterialLibrary(std::tr1::shared_ptr<MaterialLibrary> library);

private:

	int type;
	double ex; double ey; double ez;
	double ux; double uy; double uz;
	double sx; double sy; double sz;
	double rho;
	wxString description;
	wxColour color;
public:
	Material();
	Material(std::tr1::shared_ptr<MaterialLibrary> library);
	static void SetMaterialLibrary(std::tr1::shared_ptr<MaterialLibrary> library);
	static std::tr1::shared_ptr<MaterialLibrary> GetMaterialLibrary();
	virtual ~Material();

	virtual void Copy(BaseType* b);
	virtual wxString GetBaseTypeClassName();

	/* Converte para string e popula o objeto com uma string */
	virtual wxString GetUserFriendlyStringRepresentation();
	virtual void SetUserFriendlyStringRepresentation(wxString str);

	virtual void DoWrite(OutputBuffer& buffer);
	virtual void DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException);

	/* Sincroniza com a biblioteca de materiais */
	void Sync(bool updateLibrary);

    wxString GetDescription() const;
    double GetEx() const;
    double GetEy() const;
    double GetEz() const;
    double GetRho() const;
    double GetSx() const;
    double GetSy() const;
    double GetSz() const;
    double GetUx() const;
    double GetUy() const;
    double GetUz() const;
    wxColour GetColor() const;
    int GetType();
    bool IsPec();
    bool IsFreeSpace();
    void SetDescription(wxString description);
    void SetEx(double ex);
    void SetEy(double ey);
    void SetEz(double ez);
    void SetRho(double rho);
    void SetSx(double sx);
    void SetSy(double sy);
    void SetSz(double sz);
    void SetUx(double ux);
    void SetUy(double uy);
    void SetUz(double uz);
    void SetType(int type);
    void SetColor(wxColour c);

    bool Equals(Material& m) const;
};

#endif /* MATERIAL_H_ */
