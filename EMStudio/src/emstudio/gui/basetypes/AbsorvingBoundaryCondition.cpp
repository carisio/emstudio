/*
 * AbsorvingBoundaryCondition.cpp
 *
 *  Created on: 16/10/2011
 *      Author: Leandro
 */

#include "AbsorvingBoundaryCondition.h"

AbsorvingBoundaryCondition::AbsorvingBoundaryCondition()
	: abcTypesYDirection(), pec(0), pml(0), periodic(0), Npml(8) {

	SetWriteVersion(1);

	pml = xNeg | xPos | yNeg | yPos | zNeg | zPos;

	abcTypesXDirection.Add("PEC");
	abcTypesXDirection.Add("PML");
	abcTypesXDirection.Add("Periodic");

	abcTypesYDirection.Add("PEC");
	abcTypesYDirection.Add("PML");

	abcTypesZDirection.Add("PEC");
	abcTypesZDirection.Add("PML");
	abcTypesZDirection.Add("Periodic");
}

void AbsorvingBoundaryCondition::SetUserFriendlyStringRepresentation(wxString s) {

}
wxString AbsorvingBoundaryCondition::GetUserFriendlyStringRepresentation() {
	return "ABC";
}
void AbsorvingBoundaryCondition::DoWrite(OutputBuffer& buffer) {
	buffer.WriteChar(pml);
	buffer.WriteChar(pec);
	buffer.WriteChar(periodic);
	buffer.WriteInt(Npml);
}
void AbsorvingBoundaryCondition::DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException) {
	if (GetReadVersion() != 1)
		throw BaseTypeIncompatibleException(GetBaseTypeClassName());

	pml = buffer.ReadChar();
	pec = buffer.ReadChar();
	periodic = buffer.ReadChar();
	Npml = buffer.ReadInt();
}

void AbsorvingBoundaryCondition::Copy(BaseType* b) {
	AbsorvingBoundaryCondition* abc = (static_cast<AbsorvingBoundaryCondition*>(b));

	pml = abc->pml;
	pec = abc->pec;
	periodic = abc->periodic;
	Npml = abc->Npml;
}

wxString AbsorvingBoundaryCondition::GetBaseTypeClassName() {
	return "AbsorvingBoundaryCondition";
}

AbsorvingBoundaryCondition::~AbsorvingBoundaryCondition() {

}

void AbsorvingBoundaryCondition::SetBit(char& c, char bit) {
	c = c | bit;
}
void AbsorvingBoundaryCondition::UnsetBit(char& c, char bit) {
	c = c & (~bit);
}

void AbsorvingBoundaryCondition::SetBit(wxString abcType, char bit) {
	if (abcType == "PML") {
		SetBit(pml, bit);
		UnsetBit(pec, bit);
		UnsetBit(periodic, bit);
	} else if (abcType == "PEC") {
		UnsetBit(pml, bit);
		SetBit(pec, bit);
		UnsetBit(periodic, bit);
	} else if (abcType == "Periodic") {
		UnsetBit(pml, bit);
		UnsetBit(pec, bit);
		SetBit(periodic, bit);
	}
}

wxArrayString AbsorvingBoundaryCondition::GetAvailableABCsXDirection() {
	return abcTypesXDirection;
}
wxArrayString AbsorvingBoundaryCondition::GetAvailableABCsYDirection() {
	return abcTypesYDirection;
}
wxArrayString AbsorvingBoundaryCondition::GetAvailableABCsZDirection() {
	return abcTypesZDirection;
}
void AbsorvingBoundaryCondition::SetABCXNeg(wxString abcType) {
	SetBit(abcType, xNeg);
}

void AbsorvingBoundaryCondition::SetABCYNeg(wxString abcType) {
	SetBit(abcType, yNeg);
}

void AbsorvingBoundaryCondition::SetABCZNeg(wxString abcType) {
	SetBit(abcType, zNeg);
}

void AbsorvingBoundaryCondition::SetABCXPos(wxString abcType) {
	SetBit(abcType, xPos);
}

void AbsorvingBoundaryCondition::SetABCYPos(wxString abcType) {
	SetBit(abcType, yPos);
}

void AbsorvingBoundaryCondition::SetABCZPos(wxString abcType) {
	SetBit(abcType, zPos);
}
void AbsorvingBoundaryCondition::SetNpml(int npml) {
	Npml = npml;
}
wxString AbsorvingBoundaryCondition::GetABC(char bit) {
	wxString result;
	if (pml & bit) {
		result = "PML";
	} else if (pec & bit) {
		result = "PEC";
	} else if (periodic & bit) {
		result = "Periodic";
	}
	return result;
}
wxString AbsorvingBoundaryCondition::GetABCXNeg() {
	return GetABC(xNeg);
}
wxString AbsorvingBoundaryCondition::GetABCXPos() {
	return GetABC(xPos);
}
wxString AbsorvingBoundaryCondition::GetABCYNeg() {
	return GetABC(yNeg);
}
wxString AbsorvingBoundaryCondition::GetABCYPos() {
	return GetABC(yPos);
}
wxString AbsorvingBoundaryCondition::GetABCZNeg() {
	return GetABC(zNeg);
}
wxString AbsorvingBoundaryCondition::GetABCZPos() {
	return GetABC(zPos);
}

bool AbsorvingBoundaryCondition::IsPML(char wall) {
	return (pml & wall);
}
bool AbsorvingBoundaryCondition::IsPeriodic(char wall) {
	return (periodic & wall);
}
bool AbsorvingBoundaryCondition::IsPEC(char wall) {
	return (pec & wall);
}
int AbsorvingBoundaryCondition::GetNpml() {
	return Npml;
}
