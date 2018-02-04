/*
 * DXFFile.cpp
 *
 *  Created on: 20/06/2013
 *      Author: leandrocarisio
 */

#include "DXFFile.h"
#include <iostream>
using namespace::std;

DXFFile::DXFFile() {
	SetWriteVersion(1);
	SetWildcard("DXF files (*.dxf)|*.dxf");
}

DXFFile::~DXFFile() {

}

void DXFFile::Copy(BaseType* b) {
	// Copia arquivos comuns
	File::Copy(b);
	parser = ((static_cast<DXFFile*>(b))->parser);
}
wxString DXFFile::GetBaseTypeClassName() {
	return "DXFFile";
}
bool DXFFile::ProcessFile(wxString fileName) {
	bool ret = parser.Load(fileName);

	return ret;
}
DXFParser& DXFFile::GetParser() {
	return parser;
}
DXFEntityList& DXFFile::GetEntityList() {
	return parser.GetDXFEntityList();
}
void DXFFile::DoWrite(OutputBuffer& buffer) {
	wxString s = GetFileName();
	buffer.WriteString(s);
	s = GetWildcard();
	buffer.WriteString(s);

	// Grava a lista de layers
	DXFLayerList layerList = parser.GetLayerList();
	int sizeLayerList = layerList.size();
	buffer.WriteInt(sizeLayerList);
	for (DXFLayerList::compatibility_iterator node = layerList.GetFirst(); node; node = node->GetNext()) {
		DXFLayer *p = node->GetData();
		buffer.WriteString(p->name);
		buffer.WriteInt(p->colour);
	}

	// Grava a lista de entidades
	DXFEntityList entityList = parser.GetDXFEntityList();
	int sizeEntityList = entityList.size();
	buffer.WriteInt(sizeEntityList);
	for (DXFEntityList::compatibility_iterator node = entityList.GetFirst(); node; node = node->GetNext())
	{
		DXFEntity *p = node->GetData();
		int type = p->type;
		buffer.WriteInt(type);
		buffer.WriteInt(p->colour);
		if (p->type == DXFEntity::Line) {
			DXFLine *line = (DXFLine *)p;
			buffer.WriteDouble(line->v0.X);buffer.WriteDouble(line->v0.Y);buffer.WriteDouble(line->v0.Z);
			buffer.WriteDouble(line->v1.X);buffer.WriteDouble(line->v1.Y);buffer.WriteDouble(line->v1.Z);

		} else if (p->type == DXFEntity::Face) {
			DXFFace *face = (DXFFace *)p;
			buffer.WriteDouble(face->v0.X);buffer.WriteDouble(face->v0.Y);buffer.WriteDouble(face->v0.Z);
			buffer.WriteDouble(face->v1.X);buffer.WriteDouble(face->v1.Y);buffer.WriteDouble(face->v1.Z);
			buffer.WriteDouble(face->v2.X);buffer.WriteDouble(face->v2.Y);buffer.WriteDouble(face->v2.Z);
			buffer.WriteDouble(face->v3.X);buffer.WriteDouble(face->v3.Y);buffer.WriteDouble(face->v3.Z);
			buffer.WriteDouble(face->n.X);buffer.WriteDouble(face->n.Y);buffer.WriteDouble(face->n.Z);
		}
	}
}
void DXFFile::DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException) {
	if (GetReadVersion() != 1)
		throw BaseTypeIncompatibleException(GetBaseTypeClassName());
	SetFileName(buffer.ReadString());
	SetWildcard(buffer.ReadString());

	// Recuera a lista de layers
	DXFLayerList layerList;
	int sizeLayerList = buffer.ReadInt();

	for (int i = 0; i < sizeLayerList; i++) {
		DXFLayer *p = new DXFLayer;
		p->name = buffer.ReadString();
		p->colour = buffer.ReadInt();
		layerList.Append(p);
	}

	// Recupera a lista de entidades
	DXFEntityList entityList;
	int sizeEntityList = buffer.ReadInt();
	for (int i = 0; i < sizeEntityList; i++) {
		int type = buffer.ReadInt();
		int color = buffer.ReadInt();

		if (type == DXFEntity::Line) {
			DXFLine* p = new DXFLine;
			p->type = (DXFEntity::Type)type;
			p->colour = color;
			p->v0.X = buffer.ReadDouble(); p->v0.Y = buffer.ReadDouble(); p->v0.Z = buffer.ReadDouble();
			p->v1.X = buffer.ReadDouble(); p->v1.Y = buffer.ReadDouble(); p->v1.Z = buffer.ReadDouble();
			entityList.Append(p);
		} else if (type == DXFEntity::Face) {
			DXFFace* p = new DXFFace;
			p->type = (DXFEntity::Type)type;
			p->colour = color;
			p->v0.X = buffer.ReadDouble(); p->v0.Y = buffer.ReadDouble(); p->v0.Z = buffer.ReadDouble();
			p->v1.X = buffer.ReadDouble(); p->v1.Y = buffer.ReadDouble(); p->v1.Z = buffer.ReadDouble();
			p->v2.X = buffer.ReadDouble(); p->v2.Y = buffer.ReadDouble(); p->v2.Z = buffer.ReadDouble();
			p->v3.X = buffer.ReadDouble(); p->v3.Y = buffer.ReadDouble(); p->v3.Z = buffer.ReadDouble();
			p->n.X = buffer.ReadDouble(); p->n.Y = buffer.ReadDouble(); p->n.Z = buffer.ReadDouble();
			entityList.Append(p);
		}
	}

	parser.SetEntityList(entityList);
	parser.SetLayerList(layerList);
}
