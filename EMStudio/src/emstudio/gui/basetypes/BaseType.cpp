/*
 * BaseType.cpp
 *
 *  Created on: 01/09/2011
 *      Author: Leandro
 */

#include "BaseType.h"

BaseType::BaseType() : writeVersion(0), readVersion(0) {

}

BaseType::~BaseType() {

}

void BaseType::SetWriteVersion(int v) {
	writeVersion = v;
}
int BaseType::GetReadVersion() {
	return readVersion;
}

void BaseType::Write(OutputBuffer& buffer) {
	buffer.WriteInt(writeVersion);
	DoWrite(buffer);
}
void BaseType::Read(InputBuffer& buffer) throw(BaseTypeIncompatibleException) {
	readVersion = buffer.ReadInt();
	DoRead(buffer);
}
