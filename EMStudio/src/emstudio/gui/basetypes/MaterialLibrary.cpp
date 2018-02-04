/*
 * MaterialLibrary.cpp
 *
 *  Created on: 28/09/2011
 *      Author: leandrocarisio
 */

#include "MaterialLibrary.h"
MaterialLibrary::MaterialLibrary() {
	library = std::list<Material>();
}

MaterialLibrary::~MaterialLibrary() {
}
/**
 * Sincroniza��o da biblioteca.
 *
 * Passo 1) Verifica se o material m est� na biblioteca (checa o nome do material).
 * 			Se n�o estiver, adiciona.
 *
 * 		 2) Se o material j� existir na biblioteca, verifica se o nome e as propriedades s�o iguais.
 * 		    Se for, n�o faz nada.
 *
 * 		    2.1) Se o material for diferente, h� duas possibilidades:
 *
 * 		    	 2.1.1) Se updateLibrary == true, atualiza o material na biblioteca com os dados de m.
 * 		    	 2.1.2) Se updateLibrary == false, atualiza m com os dados do material dispon�vel na biblioteca.
 */
void MaterialLibrary::Sync(Material* m, bool updateLibrary) {
	/* Passo 1 */
	if (!Contains(m->GetDescription())) {
//		Register(*m); CORRE��O DO ERRO E002
		library.push_back(*m);
		return;
	}
	/* Passo 2.1 */
	Material materialFromLibraryToBeUpdated = GetMaterial(m->GetDescription());
	if (! (m->Equals(materialFromLibraryToBeUpdated) && m->GetColor() == materialFromLibraryToBeUpdated.GetColor())) {
		/* Passo 2.1.1. */
		if (updateLibrary) {
			ChangeMaterial(m->GetDescription(), *m);
		} else { /* Passo 2.1.2 */
			m->Copy(&materialFromLibraryToBeUpdated);
		}
	}
}
// Register � equivalente a chamar Sync passando true, ou seja, se o novo material ainda n�o estiver na biblioteca, ele adiciona � ela. Caso contr�rio, apenas
// atualiza a biblioteca com os novos dados.
void MaterialLibrary::Register(Material m) {
//	library.push_back(*m); CORRE��O DO ERRO E002
	Sync(&m, true);
}
void MaterialLibrary::ChangeMaterial(wxString description, Material m) {
	std::list<Material>::iterator it = library.begin();
	std::list<Material>::iterator end = library.end();

	while (it != end) {
		if (it->GetDescription() == description) {
			it->Copy(&m);
			break;
		}
		it++;
	}
}
void MaterialLibrary::DeleteMaterial(wxString description) {
	std::list<Material>::iterator it = library.begin();
	std::list<Material>::iterator end = library.end();

	while (it != end) {
		if (it->GetDescription() == description) {
			library.erase(it);
			break;
		}
		it++;
	}
}
/* Dada uma descri��o, retorna um material. Caso ele n�o seja encontrado, retorna um material padr�o (ar) */
Material MaterialLibrary::GetMaterial(wxString description) {
	std::list<Material>::iterator it = library.begin();
	std::list<Material>::iterator end = library.end();

	Material m;
	while (it != end) {
		if (it->GetDescription() == description)
			return *it;
		it++;
	}
	return m;
}
bool MaterialLibrary::Contains(wxString description) {
	std::list<Material>::iterator it = library.begin();
	std::list<Material>::iterator end = library.end();

	while (it != end) {
		if (it->GetDescription() == description)
			return true;
		it++;
	}
	return false;
}
std::list<Material> MaterialLibrary::GetList() {
	return library;
}

wxArrayString MaterialLibrary::GetMaterialDescriptionList() {
	wxArrayString result = wxArrayString();

	std::list<Material>::iterator it = library.begin();
	std::list<Material>::iterator end = library.end();

	while (it != end) {
		result.Add(it->GetDescription());
		it++;
	}
	result.Sort(false);
	return result;

}
