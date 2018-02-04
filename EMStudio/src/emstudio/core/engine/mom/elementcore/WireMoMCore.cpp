/*
 * WireMoMCore.cpp
 *
 *  Created on: 03/06/2014
 *      Author: leandrocarisio
 */

#include "WireMoMCore.h"
#include "emstudio/core/engine/mom/MoMEngine.h"
#include "emstudio/util/converters/Converter.h"
#include <iostream>
using namespace::std;

namespace mom {

WireMoMCore::WireMoMCore() {
}

WireMoMCore::~WireMoMCore() {
}
ElementCoreSmartPointer WireMoMCore::NewElementCore() {
	return ElementCoreSmartPointer(new WireMoMCore);
}

void WireMoMCore::DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr) {
	WireDTO* wireDTO = static_cast<WireDTO*>(elementDTOSmartPtr.get());

	dto = *wireDTO;
}

void WireMoMCore::SetGeometry(int tag_id) {
	MoMEngine* engine = static_cast<MoMEngine*>(GetEngine());

	c_geometry* geo = engine->GetNecContext()->get_geometry();
	geo->wire(tag_id, dto.GetNumberOfSegments(), dto.GetP1().X, dto.GetP1().Y, dto.GetP1().Z, dto.GetP2().X, dto.GetP2().Y, dto.GetP2().Z, dto.GetRadius(), 1, 1);
	necCommand = "GW ";
	necCommand.Append(Converter::IntToFormattedString(tag_id)).Append(" ").
			Append(Converter::IntToFormattedString(dto.GetNumberOfSegments())).Append(" ").
			Append(Converter::DoubleToFormattedString(dto.GetP1().X)).Append(" ").
			Append(Converter::DoubleToFormattedString(dto.GetP1().Y)).Append(" ").
			Append(Converter::DoubleToFormattedString(dto.GetP1().Z)).Append(" ").
			Append(Converter::DoubleToFormattedString(dto.GetP2().X)).Append(" ").
			Append(Converter::DoubleToFormattedString(dto.GetP2().Y)).Append(" ").
			Append(Converter::DoubleToFormattedString(dto.GetP2().Z)).Append(" ").
			Append(Converter::DoubleToFormattedString(dto.GetRadius())).Append(" 1 1\n");

	cout << "geo->wire(" << tag_id << "," << dto.GetNumberOfSegments() << "," << dto.GetP1().X << "," << dto.GetP1().Y << "," << dto.GetP1().Z << "," << dto.GetP2().X << "," << dto.GetP2().Y << "," << dto.GetP2().Z << "," << dto.GetRadius() << "," << 1 << "," << 1 << ");" << endl;
}

MoMElementCoreType WireMoMCore::GetType() {
	return GEOMETRY;
}
wxString WireMoMCore::GetNECCommand() {
	return necCommand;
}
} /* namespace mom */
