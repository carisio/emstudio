/*
 * MaterialLibrary.h
 *
 *  Created on: 28/09/2011
 *      Author: leandrocarisio
 */

#ifndef MATERIALLIBRARY_H_
#define MATERIALLIBRARY_H_

#include "Material.h"

#include "wx/wx.h"
#include "wx/arrstr.h"

#include <list>
#include <tr1/memory>

class Material;
class MaterialLibrary;

typedef std::tr1::shared_ptr<MaterialLibrary> MaterialLibrarySmartPointer;

using namespace::std;

class MaterialLibrary {
private:
	std::list<Material> library;
public:
	MaterialLibrary();
	virtual ~MaterialLibrary();

	void Sync(Material* m, bool updateLibrary);
	void Register(Material m);
	void ChangeMaterial(wxString description, Material m);
	void DeleteMaterial(wxString description);
	Material GetMaterial(wxString description);
	bool Contains(wxString description);
	std::list<Material> GetList();
	wxArrayString GetMaterialDescriptionList();
};

#endif /* MATERIALLIBRARY_H_ */
