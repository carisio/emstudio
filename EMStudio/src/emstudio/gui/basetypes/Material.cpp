/*
 * Material.cpp
 *
 *  Created on: 26/09/2011
 *      Author: leandrocarisio
 */

#include "Material.h"

// Inicializa o pointeiro para a biblioteca de materiais.
// Cria um temporário qualquer, apenas para começar.
std::tr1::shared_ptr<MaterialLibrary> Material::library = std::tr1::shared_ptr<MaterialLibrary>();

Material::Material()
	: type(ISOTROPIC), ex(1), ey(1), ez(1), ux(1), uy(1), uz(1), sx(0), sy(0), sz(0), rho(1), description("Air"), color(255,0,0) {
	SetWriteVersion(2);
}

Material::Material(std::tr1::shared_ptr<MaterialLibrary> library)
	: type(ISOTROPIC), ex(1), ey(1), ez(1), ux(1), uy(1), uz(1), sx(0), sy(0), sz(0), rho(1), description("Air"), color(255,0,0) {
	SetWriteVersion(2);
	Material::library = library;
}
void Material::SetMaterialLibrary(std::tr1::shared_ptr<MaterialLibrary> library) {
	Material::library = library;
}
std::tr1::shared_ptr<MaterialLibrary> Material::GetMaterialLibrary() {
	return library;
}
//std::tr1::shared_ptr<MaterialLibrary> Material::GetMaterialLibrary() {
//	return Material::library;
//}
//void Material::SetMaterialLibrary(std::tr1::shared_ptr<MaterialLibrary> library) {
//	Material::library = library;
//}

Material::~Material() {

}

void Material::Sync(bool updateLibrary) {
//	if (GetMaterialLibrary()) {
//		GetMaterialLibrary()->Sync(this, updateLibrary);
//	}
	if (Material::library) {
		Material::library->Sync(this, updateLibrary);
	}

}

void Material::Copy(BaseType* b) {
	Material* m = static_cast<Material*>(b);
	SetEx(m->GetEx());
	SetEy(m->GetEy());
	SetEz(m->GetEz());
	SetUx(m->GetUx());
	SetUy(m->GetUy());
	SetUz(m->GetUz());
	SetSx(m->GetSx());
	SetSy(m->GetSy());
	SetSz(m->GetSz());
	SetRho(m->GetRho());
	SetDescription(m->GetDescription());
	SetType(m->GetType());
//	cout << "Copiando material. Cor antiga: " << m->GetDescription() << "\t" << (int)GetColor().Red() << " , " << (int)GetColor().Green() << ", " << (int)GetColor().Blue() << endl;
	SetColor(m->GetColor());
//	cout << "Copiando material. Cor nova: " << m->GetDescription() << "\t" << (int)GetColor().Red() << " , " << (int)GetColor().Green() << ", " << (int)GetColor().Blue() << endl;
}

wxString Material::GetBaseTypeClassName() {
	return "Material";
}

void Material::SetUserFriendlyStringRepresentation(wxString str) {
	SetDescription(str);
}
wxString Material::GetUserFriendlyStringRepresentation() {
	return GetDescription();
}
void Material::DoWrite(OutputBuffer& buffer) {
	/**
	 * Existem dois lugares em que ConvertFromString é chamado:
	 * GetXMLPropertiesString e GetMaterialLibraryString.
	 * Em ambos os casos, isso é feito quando o arquivo de projeto está sendo salvo ou quando a biblioteca de materiais está sendo exportada.
	 * Nesses casos, é necessário fazer a sincronização com a biblioteca, atualizando os dados do material com os dados da bilioteca,
	 * caso algum material tiver sido editado.
	 */
	Sync(false);

	buffer.WriteInt(type);
	buffer.WriteDouble(ex);
	buffer.WriteDouble(ey);
	buffer.WriteDouble(ez);
	buffer.WriteDouble(ux);
	buffer.WriteDouble(uy);
	buffer.WriteDouble(uz);
	buffer.WriteDouble(sx);
	buffer.WriteDouble(sy);
	buffer.WriteDouble(sz);
	buffer.WriteDouble(rho);
	buffer.WriteString(description);
	char c = color.Red();
	buffer.WriteChar(c);
	c = color.Green();
	buffer.WriteChar(c);
	c = color.Blue();
	buffer.WriteChar(c);
}
void Material::DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException) {
	if (GetReadVersion() != 1 && GetReadVersion() != 2)
		throw BaseTypeIncompatibleException(GetBaseTypeClassName());

	/* Versão 1 salva com esses campos: */
	type = buffer.ReadInt();
	ex = buffer.ReadDouble();
	ey = buffer.ReadDouble();
	ez = buffer.ReadDouble();
	ux = buffer.ReadDouble();
	uy = buffer.ReadDouble();
	uz = buffer.ReadDouble();
	sx = buffer.ReadDouble();
	sy = buffer.ReadDouble();
	sz = buffer.ReadDouble();
	rho = buffer.ReadDouble();
	description = buffer.ReadString();

	/* Versão 2 salva também uma cor */
	if (GetReadVersion() == 2) {
		char r = buffer.ReadChar();
		char g = buffer.ReadChar();
		char b = buffer.ReadChar();
		color.Set(r, g, b);
	}

	/**
	 * Existem dois lugares em que ConvertFromString é chamado:
	 * FillProperties e OpenMaterialLibrary.
	 * Em ambos os casos, isso é feito quando o arquivo de projeto está sendo lido ou quando uma biblioteca de materiais está sendo importada.
	 * Nesses casos, é necessário fazer a sincronização com a biblioteca mantendo as propriedades que acabaram de ser lidas a partir de um arquivo.
	 */
	Sync(true);
}

wxString Material::GetDescription() const {
    return description;
}

double Material::GetEx() const {
    return ex;
}

double Material::GetEy() const {
    return ey;
}

double Material::GetEz() const {
    return ez;
}

double Material::GetRho() const {
    return rho;
}

double Material::GetSx() const {
    return sx;
}

double Material::GetSy() const {
    return sy;
}

double Material::GetSz() const {
    return sz;
}

double Material::GetUx() const {
    return ux;
}

double Material::GetUy() const {
    return uy;
}

double Material::GetUz() const {
    return uz;
}

bool Material::IsPec() {
    return PEC == GetType();
}
bool Material::IsFreeSpace() {
	return ex == 1 && ey == 1 && ez == 1 &&
		   ux == 1 && uy == 1 && uz == 1 &&
		   sx == 0 && sy == 0 && sz == 0;
}
int Material::GetType() {
	return type;
}

void Material::SetDescription(wxString description) {
    this->description = description;
}

void Material::SetEx(double ex) {
    this->ex = ex;
}

void Material::SetEy(double ey) {
    this->ey = ey;
}

void Material::SetEz(double ez) {
    this->ez = ez;
}

void Material::SetRho(double rho) {
    this->rho = rho;
}

void Material::SetSx(double sx) {
    this->sx = sx;
}

void Material::SetSy(double sy) {
    this->sy = sy;
}

void Material::SetSz(double sz) {
    this->sz = sz;
}

void Material::SetUx(double ux) {
    this->ux = ux;
}

void Material::SetUy(double uy) {
    this->uy = uy;
}

void Material::SetUz(double uz) {
    this->uz = uz;
}

void Material::SetType(int type) {
	this->type = type;
	if (PEC == GetType()) {
		SetEx(1.0);
		SetEy(1.0);
		SetEz(1.0);
		SetUx(0.0);
		SetUy(0.0);
		SetUz(0.0);
		SetSx(1e30);
		SetSy(1e30);
		SetSz(1e30);
	}
}

bool Material::Equals(Material& m) const {
	return (this->ex == m.GetEx()) &&
			(this->ey == m.GetEy()) &&
			(this->ez == m.GetEz()) &&
			(this->ux == m.GetUx()) &&
			(this->uy == m.GetUy()) &&
			(this->uz == m.GetUz()) &&
			(this->sx == m.GetSx()) &&
			(this->sy == m.GetSy()) &&
			(this->sz == m.GetSz());
}
void Material::SetColor(wxColour c) {
	color = c;
}
wxColour Material::GetColor() const {
	return color;
}
