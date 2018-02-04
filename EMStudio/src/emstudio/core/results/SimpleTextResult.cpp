/*
 * SimpleTextResult.cpp
 *
 *  Created on: 30/09/2015
 *      Author: Leandro
 */

#include <emstudio/core/results/SimpleTextResult.h>

#include "emstudio/util/resources/UtilResource.h"
#include "emstudio/util/file/FileManager.h"

SimpleTextResult::SimpleTextResult(wxString resultName, wxString contents) {
	SetName(resultName);
	this->contents.SetValue(contents);
	AddProperty(Property("contents", &this->contents));
}

SimpleTextResult::~SimpleTextResult() {
}

ResultSmartPointer SimpleTextResult::NewResult() {
	return ResultSmartPointer(new SimpleTextResult);
}
wxIcon SimpleTextResult::GetIcon() {
	return UtilResource::GetIcon("table");
}
wxString SimpleTextResult::GetResultClassName() {
	return "SimpleTextResult";
}
wxString SimpleTextResult::GetContents() {
	return contents.GetValue();
}
void SimpleTextResult::SetContents(wxString contents) {
	this->contents.SetValue(contents);
}
bool SimpleTextResult::ExportData(wxString fileName) {
	bool saveOk = true;

	wxString path = FileManager::GetFolder(fileName);
	wxString baseFileName = FileManager::GetFileNameWithoutExtension(fileName);

	/* Salva o conteúdo do arquivo */
	wxString dataFileName = path; dataFileName.Append(baseFileName).Append(".txt");
	saveOk &= FileManager::SaveFile(dataFileName, contents.GetValue());

	return saveOk;
}
