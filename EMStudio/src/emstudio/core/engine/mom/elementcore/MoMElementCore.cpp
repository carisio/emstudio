/*
 * MoMElementCore.cpp
 *
 *  Created on: 03/06/2014
 *      Author: leandrocarisio
 */

#include "MoMElementCore.h"
#include "emstudio/dto/momapp/MoMDTO.h"

namespace mom {

MoMElementCore::MoMElementCore() {
}

MoMElementCore::~MoMElementCore() {
}
Segments MoMElementCore::GetSegments() {
	MoMDTO* momDTO = static_cast<MoMDTO*>(GetDTO().get());
	return momDTO->GetSegments();
}
void MoMElementCore::SetGeometry(int tag_id) {
}
void MoMElementCore::SetSource() {
}
void MoMElementCore::SetConnection() {
}
void MoMElementCore::SetProbe() {
}
void MoMElementCore::SetExecutionCard() {

}
} /* namespace mom */
