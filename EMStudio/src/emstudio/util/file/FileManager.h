/*
 * FileManager.h
 *
 *  Created on: 26/09/2011
 *      Author: leandrocarisio
 */

#ifndef FILEMANAGER_H_
#define FILEMANAGER_H_

#include <list>
#include <fstream>
#include <string>
#include "wx/tokenzr.h"
#include "wx/wx.h"
#include "emstudio/gui/elements/ElementGUI.h"
#include "emstudio/gui/elements/Propertyable.h"
#include "emstudio/util/converters/Converter.h"
#include "emstudio/gui/elements/ElementManager.h"
#include "emstudio/units/Units.h"
#include "emstudio/gui/basetypes/MaterialLibrary.h"
#include "emstudio/exception/PropertyNotFoundException.h"
#include "emstudio/util/dialogs/UtilDialog.h"
#include "emstudio/core/results/Result.h"
#include "emstudio/core/results/ResultManager.h"
#include "PortableBinaryInputBuffer.h"
#include "PortableBinaryOutputBuffer.h"
#include "emstudio/util/dialogs/StatusDialog.h"
#include "emstudio/util/muparser/MathParser.h"

using namespace::std;
class FileManager {
public:
	static wxString FILE_NOT_CHOOSEN;
	static wxString LAST_DIR;
	static wxString currentFileDescription;
	static int currentFileV1;
	static int currentFileV2;
	static int currentFileV3;

	FileManager();

	static bool SaveProject(wxString fileName, UnitsSmartPointer units, SymbolsMapSmartPointer symbolsMap, ElementManagerSmartPointer em, ResultTree& resultTree);
	static void AppendVersionToBuffer(OutputBuffer& buff);
	static void AppendUnitsToBuffer(OutputBuffer& buff, UnitsSmartPointer units);
	static void AppendSymbolsToBuffer(OutputBuffer& buff, SymbolsMapSmartPointer symbols);
	static void AppendElementManagerToBuffer(OutputBuffer& buff, ElementManagerSmartPointer em);
	static void AppendProjectResults(OutputBuffer& buff, ResultTree& resultTree, StatusDialog& dialog);

	static bool LoadProject(wxString fileName, UnitsSmartPointer units, SymbolsMapSmartPointer symbolsMap, ElementManagerSmartPointer availableElements, ElementManagerSmartPointer project, ResultTree& resultTree, ResultManager& resultManager, wxString& errorMessage);
	static bool RetrieveVersionFromBuffer(InputBuffer& buff);
	static void RetrieveUnitsFromBuffer(InputBuffer& buff, UnitsSmartPointer units);
	static void RetrieveSymbolsFromBuffer(InputBuffer& input, SymbolsMapSmartPointer symbols);
	static void RetrieveElementManagerFromBuffer(InputBuffer& buff, ElementManagerSmartPointer availableElements, ElementManagerSmartPointer project);
	static void RetrieveResultTreeFromBuffer(InputBuffer& input, ResultTree& resultTree, ResultManager& resultManager, StatusDialog& dialog);

	static wxString GetProjectCode(UnitsSmartPointer units, SymbolsMapSmartPointer symbolsMap, ElementManagerSmartPointer em);

	static bool SaveBinaryFile(wxString fileName, Array3D<double>& array);
	static bool SaveFile(wxString fileName, wxString contents);
	static bool OpenFile(wxString fileName, wxString& contents);

	static bool SaveMaterialLibrary(wxString fileName, MaterialLibrary library);
	static bool OpenMaterialLibrary(wxString fileName, MaterialLibrarySmartPointer library);

	static wxString GetAppPath();
	static wxString GetMaterialLibraryFileName();

	static wxString ShowFileDialog(wxWindow *parent, wxString title, wxString wildcard, long style, wxString defaultDir = LAST_DIR);

	static bool FileExists(wxString fileName);

	static wxString GetFolder(wxString fileNameWithFolder);
	static wxString GetFileName(wxString fileNameWithFolder);
	static wxString GetFileNameWithoutExtension(wxString fileNameWithFolder);

	virtual ~FileManager();
};

#endif /* FILEMANAGER_H_ */
