/*
 * FileManager.cpp
 *
 *  Created on: 26/09/2011
 *      Author: leandrocarisio
 */

#include "FileManager.h"
#include "emstudio/moderator/ConfigApp.h"
#include "emstudio/util/time/TicTac.h"
#include "emstudio/util/md5/MD5.h"
#include <sys/stat.h>

using namespace std;

wxString FileManager::FILE_NOT_CHOOSEN = "\"'!@#$%^&*()";
wxString FileManager::LAST_DIR = ".";
wxString FileManager::currentFileDescription = "";
int FileManager::currentFileV1 = 0;
int FileManager::currentFileV2 = 0;
int FileManager::currentFileV3 = 0;

FileManager::FileManager() {

}

FileManager::~FileManager() {

}

wxString FileManager::GetAppPath() {
	wxString out = wxString(".");
	return out;
}
wxString FileManager::GetMaterialLibraryFileName() {
	wxString out = "materiallibrary.mat";
	return out;
}
wxString FileManager::GetProjectCode(UnitsSmartPointer units, SymbolsMapSmartPointer symbolsMap, ElementManagerSmartPointer em) {
	cout << "FileManager::GetProjectCode" << endl;
	PortableBinaryOutputBuffer output;

	AppendUnitsToBuffer(output, units);
	AppendSymbolsToBuffer(output, symbolsMap);
	AppendElementManagerToBuffer(output, em);

	cout << "Fez todos os apends" << endl;
	string str = output.GetStringRepresentation();
	cout << "Pegou a string" << endl;
	wxString code = md5(str);
	cout << "md5 ok" << endl;
	cout << str << endl;
	cout << "Código do projeto = " << code << endl;
	return code;

}
bool FileManager::SaveProject(wxString fileName, UnitsSmartPointer units, SymbolsMapSmartPointer symbolsMap, ElementManagerSmartPointer em, ResultTree& resultTree) {
	TicTac t;
	t.Tic("Método SaveProject" );
	StatusDialog status("Saving project...");

	PortableBinaryOutputBuffer output;

	AppendVersionToBuffer(output);
	status.SetStatus("Saving units...");
	AppendUnitsToBuffer(output, units);
	status.SetStatus("Saving symbols...");
	AppendSymbolsToBuffer(output, symbolsMap);
	status.SetStatus("Saving elements...");
	AppendElementManagerToBuffer(output, em);
	status.SetStatus("Saving results...");
	AppendProjectResults(output, resultTree, status);
	status.SetStatus("Exporting to file...");
	TicTac t2;
	t2.Tic("Chamando output.SaveToFile");
	bool ok = output.SaveToFile(fileName);
	t2.Tac();
	t.Tac();

	status.Hide();
	return ok;
}

void FileManager::AppendVersionToBuffer(OutputBuffer& buff) {
	// Versão atual: EM Studio [FDTD] v. 0.0.1
	wxString description = "EM Studio [" + AppType + "]";
	int v1 = AppV1;
	int v2 = AppV2;
	int v3 = AppV3;
	buff.WriteString(description);
	buff.WriteInt(v1);
	buff.WriteInt(v2);
	buff.WriteInt(v3);
}
/**
 * Apenas concatena 3 strings representando as unidades escolhidas pelo usuário
 */
void FileManager::AppendUnitsToBuffer(OutputBuffer& buff, UnitsSmartPointer units) {
	wxString s = units->GetUserDefinedSpaceUnit().first;
	buff.WriteString(s);
	s = units->GetUserDefinedTimeUnit().first;
	buff.WriteString(s);
	s = units->GetUserDefinedFrequencyUnit().first;
	buff.WriteString(s);
}
void FileManager::AppendSymbolsToBuffer(OutputBuffer& buff, SymbolsMapSmartPointer symbols) {
	std::list<wxString> symbolsName = symbols->GetSymbolsName();
	int nSymbols = symbolsName.size();
	std::list<wxString>::iterator it = symbolsName.begin();
	std::list<wxString>::iterator end = symbolsName.end();

	buff.WriteInt(nSymbols);
	while (it != end) {
		wxString symbolName = *it;
		double symbolValue = symbols->GetSymbol(symbolName);

		buff.WriteString(symbolName);
		buff.WriteDouble(symbolValue);

		it++;
	}
}
/**
 * Concatena todos os elementos ao buffer
 */
void FileManager::AppendElementManagerToBuffer(OutputBuffer& buff, ElementManagerSmartPointer em) {
	// Guarda inicialmente o número de elementos
	int size = em->GetNumberOfElements();
	buff.WriteInt(size);

	// Itera pelos elementos e salva cada um deles
	ElementManager::ElementTypeList typeList = em->GetElementTypeList();
	ElementManager::ElementTypeList::iterator it = typeList.begin();
	ElementManager::ElementTypeList::iterator endTypes = typeList.end();

	while (it != endTypes) {
		ElementManager::ElementList& elementsList = em->GetElementList(*it);
		ElementManager::ElementList::iterator itElements = elementsList.begin();
		ElementManager::ElementList::iterator endElements = elementsList.end();

		while (itElements != endElements) {
			wxString registeredElementName = (*itElements)->GetRegisteredName();
			buff.WriteString(registeredElementName);
			(*itElements)->WriteProperties(buff);

			itElements++;
		}
		it++;
	}
}
void FileManager::AppendProjectResults(OutputBuffer& buff, ResultTree& resultTree, StatusDialog& dialog) {
	TicTac t;
	t.Tic("Adicionando resultados ao buffer");

	// Salva o código do projeto
	wxString projectCode = resultTree.GetProjectCode();
	buff.WriteString(projectCode);

	// Salva o número de engines
	list<EngineResults> listOfEngineResults = resultTree.GetEngineResults();
	list<EngineResults>::iterator engineResultsIt = listOfEngineResults.begin();
	list<EngineResults>::iterator engineResultsEnd = listOfEngineResults.end();

	int size = listOfEngineResults.size();
	buff.WriteInt(size);

	while(engineResultsIt != engineResultsEnd) {
		EngineResults engineResults = *engineResultsIt;

		// Para cada engine, salva o nome da classe do DTO ...
		wxString dtoClassName = engineResults.GetDTOClassName();
		buff.WriteString(dtoClassName);
		// ... e salva também o nome do método, conforme definido pelo usuário
		wxString engineName = engineResults.GetName();
		buff.WriteString(engineName);

		// Salva os resultados da própria engine
		list<ResultSmartPointer> myOwnResults = engineResults.GetMyResults();
		list<ResultSmartPointer>::iterator myOwnResultsBegin = myOwnResults.begin();
		list<ResultSmartPointer>::iterator myOwnResultsEnd = myOwnResults.end();
		int nElements = myOwnResults.size();
		buff.WriteInt(nElements);
		while (myOwnResultsBegin!=myOwnResultsEnd) {
			// Cada resultado é salvo com o nome, o nome de sua classe e, em seguida, suas propriedades
			ResultSmartPointer result = (*myOwnResultsBegin);
			wxString resultName = result->GetName();
			wxString resultClassName = result->GetResultClassName();

			wxString status = "Saving ";
			status.Append(resultName).Append(" of ").Append(engineName).Append("...");
			dialog.SetStatus(status);

			buff.WriteString(resultName);
			buff.WriteString(resultClassName);
			// Agora salva as propriedades
			result->WriteProperties(buff);

			myOwnResultsBegin++;
		}

		// Agora começa a iterar os resultados dos elementos da engine em si.
		list<ElementResults> listaDeElementosDaEngine = engineResults.GetElementsResults();
		list<ElementResults>::iterator listaDeElementosDaEngineIt = listaDeElementosDaEngine.begin();
		list<ElementResults>::iterator listaDeElementosDaEngineEnd = listaDeElementosDaEngine.end();
		nElements = listaDeElementosDaEngine.size();
		// Salva a quantidade de elementos que a engine tem
		buff.WriteInt(nElements);

		while (listaDeElementosDaEngineIt != listaDeElementosDaEngineEnd) {
			ElementResults elementResults = *listaDeElementosDaEngineIt;
			// Para cada resultado, grava também o nome do DTO correspondente à classe que chamou e o nome conforme definido pelo usuário
			dtoClassName = elementResults.GetDTOClassName();
			wxString elementName = elementResults.GetName();
			buff.WriteString(dtoClassName);
			buff.WriteString(elementName);

			// Cada elemento pode ter vários resultados
			list<ResultSmartPointer> listaDeResultados = elementResults.GetResults();
			list<ResultSmartPointer>::iterator listaDeResultadosIt = listaDeResultados.begin();
			list<ResultSmartPointer>::iterator listaDeResultadosEnd = listaDeResultados.end();
			int nResults = listaDeResultados.size();
			// Salva a quantidade de resultados que o elemento tem
			buff.WriteInt(nResults);

			while (listaDeResultadosIt != listaDeResultadosEnd) {
				// Cada resultado é salvo com o nome, o nome de sua classe e, em seguida, suas propriedades
				ResultSmartPointer result = (*listaDeResultadosIt);
				wxString resultName = result->GetName();
				wxString resultClassName = result->GetResultClassName();

				wxString status = "Saving ";
				status.Append(resultName).Append(" of ").Append(elementName).Append(" (").Append(engineName).Append(") ...");
				dialog.SetStatus(status);

				buff.WriteString(resultName);
				buff.WriteString(resultClassName);
				// Agora salva as propriedades
				result->WriteProperties(buff);

				listaDeResultadosIt++;
			}

			listaDeElementosDaEngineIt++;
		}
		engineResultsIt++;
	}
	t.Tac();
}


bool FileManager::LoadProject(wxString fileName, UnitsSmartPointer units, SymbolsMapSmartPointer symbolsMap, ElementManagerSmartPointer availableElements, ElementManagerSmartPointer project, ResultTree& resultTree, ResultManager& resultManager, wxString& errorMessage) {
	TicTac t;
	t.Tic("LoadProject");
	try{

		StatusDialog status("Loading project...");

		status.SetStatus("Opening file...");
		PortableBinaryInputBuffer input;
		bool ok = input.LoadFile(fileName);

		if (!ok) {
			return false;
		}
		symbolsMap->ClearMap();
		project->Clear();
		resultTree.ClearResults();

		TicTac t2;
		if (!RetrieveVersionFromBuffer(input)) {
			errorMessage = "It was created with a future version of ";
			errorMessage.Append(currentFileDescription).Append(" (v. ").
					Append(Converter::IntToFormattedString(currentFileV1)).Append(".").
					Append(Converter::IntToFormattedString(currentFileV2)).Append(".").
					Append(Converter::IntToFormattedString(currentFileV3)).Append(")");
		}
		status.SetStatus("Loading units...");
		t2.Tic("RetrieveUnitsFromBuffer");
		RetrieveUnitsFromBuffer(input, units);
		t2.Tac();
		status.SetStatus("Loading symbols...");
		t2.Tic("RetrieveSymbolsFromBuffer");
		RetrieveSymbolsFromBuffer(input, symbolsMap);
		t2.Tac();
		t2.Tic("RetrieveElementManagerFromBuffer");
		status.SetStatus("Loading elements...");
		RetrieveElementManagerFromBuffer(input, availableElements, project);
		t2.Tac();
		t2.Tic("RetrieveResultTreeFromBuffer");
		status.SetStatus("Loading results...");
		RetrieveResultTreeFromBuffer(input, resultTree, resultManager, status);
		t2.Tac();

		status.Hide();
	} catch (PropertyNotFoundException& exception) {
		errorMessage = "File format unknown";
		return false;
	} catch (BaseTypeIncompatibleException& e) {
		errorMessage = "File format unknown";
		return false;
	} catch (exception& e) {
		errorMessage = "File format unknown";
		cout << "Ocorreu uma exceção: " << e.what() << endl;
		return false;
	}

	t.Tac();
	return true;
}
bool FileManager::RetrieveVersionFromBuffer(InputBuffer& buff) {
	currentFileDescription = buff.ReadString();
	currentFileV1 = buff.ReadInt();
	currentFileV2 = buff.ReadInt();
	currentFileV3 = buff.ReadInt();

	/* Essa versão permite apenas a leitura de "EM Studio [APPTYPE] v. 0.0.X ou v. 0.1.X
	 * v3 pode ser maior do que 1, pois ele apenas representa melhorias de tela,
	 * e não alterações nos formatos dos arquivos */
	cout << "Abrindo. VERSÃO: " << currentFileDescription << currentFileV1 << currentFileV2 << currentFileV3 << endl;
	return (currentFileDescription == ("EM Studio [" + AppType + "]") && currentFileV1 == 0 && currentFileV2 == 0) ||
			(currentFileDescription == ("EM Studio [" + AppType + "]") && currentFileV1 == 0 && currentFileV2 == 1);
}
void FileManager::RetrieveUnitsFromBuffer(InputBuffer& buff, UnitsSmartPointer units) {
	wxString s = units->GetUserDefinedSpaceUnit().first;
	s = buff.ReadString();
	units->SetUserDefinedSpaceUnit(s);
	s = buff.ReadString();
	units->SetUserDefinedTimeUnit(s);
	s = buff.ReadString();
	units->SetUserDefinedFrequencyUnit(s);
}
void FileManager::RetrieveSymbolsFromBuffer(InputBuffer& input, SymbolsMapSmartPointer symbols) {
	int nSymbols = input.ReadInt();
	cout << "Existem " << nSymbols << " simbolos guardados no arquivo: " << endl;
	for (int i = 0; i < nSymbols; i++) {
		wxString symbolName = input.ReadString();
		double symbolValue = input.ReadDouble();
		symbols->AddSymbol(symbolName, symbolValue);
		cout << "\t" << symbolName << " = " << symbolValue << endl;
	}
}
void FileManager::RetrieveElementManagerFromBuffer(InputBuffer& buff, ElementManagerSmartPointer availableElements, ElementManagerSmartPointer project) {
	cout << "Qtd de elementos salvos = " << endl;
	int nElements = buff.ReadInt();
	cout << nElements << endl;

	for (int i = 0; i < nElements; i++) {
		cout << "Carregando elemento. Nome = ";
		wxString registeredName = buff.ReadString();
		cout << registeredName << endl;
		ElementGUISmartPointer e = availableElements->NewElementGUI(registeredName);
		if (e) {
			e->ReadProperties(buff);
			project->RegisterElement(e);
		} else {
			cout << "Elemento não encontrado!" << endl;
		}
	}
}

void FileManager::RetrieveResultTreeFromBuffer(InputBuffer& buff, ResultTree& resultTree, ResultManager& resultManager, StatusDialog& dialog) {
	// Recupera o código do projeto
	wxString projectCode = buff.ReadString();
	resultTree.SetProjectCode(projectCode);

	// Recupera o número de engines
	int nEngines = buff.ReadInt();

	for (int i = 0; i < nEngines; i++) {
		// Para cada engine, recupera o seu nome e o nome do arquivo DTO
		wxString dtoClassName = buff.ReadString();
		wxString engineName = buff.ReadString();
		EngineResults engineResults(dtoClassName, engineName);

		// Recupera a quantidade de resultados que a própria Engine tem.
		// NOTA. ISSO FOI IMPLEMENTADO APENAS APÓS A VERSÃO 0.1.1
		// Antes dessa versão foi implementado apenas a versão 0.0.1
		if (!(currentFileV1 == 0 && currentFileV2 == 0 && currentFileV3 == 1)) {
			cout << "Esse elemento tem resultados próprios" << endl;
			// Le a quantidade de resultados que este elemento possui
			int nResults = buff.ReadInt();
			for (int k = 0; k < nResults; k++) {
				// Para cada resultado, recupera o seu nome e o nome de sua classe
				wxString resultName = buff.ReadString();
				wxString resultClassName = buff.ReadString();

				wxString status = "Loading ";
				status.Append(resultName).Append(" of ").Append(engineName).Append("...");
				dialog.SetStatus(status);
				// Obtém o resultado
				ResultSmartPointer result = resultManager.NewResult(resultClassName);
				if (result != 0) {
					result->ReadProperties(buff);
					engineResults.GetMyResults().push_back(result);
				} else {
					cout << "DEU PAU pesquisando o resultado " << resultClassName << endl;
				}
			}

		}

		// Recupera a quantidade de elementos que a Engine tem:
		int nElements = buff.ReadInt();

		for (int j = 0; j < nElements; j++) {
			// Para cada elemento, recupera o seu nome e o nome do arquivo DTO
			wxString dtoClassName = buff.ReadString();
			wxString elementName = buff.ReadString();
			ElementResults elementResult(dtoClassName, elementName);

			// Le a quantidade de resultados que este elemento possui
			int nResults = buff.ReadInt();
			for (int k = 0; k < nResults; k++) {
				// Para cada resultado, recupera o seu nome e o nome de sua classe
				wxString resultName = buff.ReadString();
				wxString resultClassName = buff.ReadString();

				wxString status = "Loading ";
				status.Append(resultName).Append(" of ").Append(elementName).Append(" (").Append(engineName).Append(") ...");
				dialog.SetStatus(status);
				// Obtém o resultado
				ResultSmartPointer result = resultManager.NewResult(resultClassName);
				if (result != 0) {
					result->ReadProperties(buff);
					elementResult.GetResults().push_back(result);
				} else {
					cout << "DEU PAU pesquisando o resultado " << resultClassName << endl;
				}
			}
			engineResults.GetElementsResults().push_back(elementResult);
		}
		resultTree.GetEngineResults().push_back(engineResults);
	}
}

bool FileManager::OpenMaterialLibrary(wxString fileName, MaterialLibrarySmartPointer library) {
	try{

	PortableBinaryInputBuffer input;
	bool ok = input.LoadFile(fileName);

	if (!ok) {
		return false;
	}
		int size = input.ReadInt();
		for (int i = 0; i < size; i++) {
			Material m;
			m.Read(input);
			library->Register(m);
		}
	} catch (PropertyNotFoundException& exception) {
		return false;
	} catch (BaseTypeIncompatibleException& e) {
		return false;
	} catch (exception& e) {
		cout << "Ocorreu uma exceção: " << e.what() << endl;
	}

	return true;
}
bool FileManager::SaveMaterialLibrary(wxString fileName, MaterialLibrary library) {
	TicTac t2;
	t2.Tic("FileManager::SaveMaterialLibrary");

	PortableBinaryOutputBuffer output;

	list<Material> materialList = library.GetList();
	list<Material>::iterator it = materialList.begin();
	list<Material>::iterator end = materialList.end();

	int size = materialList.size();
	output.WriteInt(size);
	while (it != end) {
		it->Write(output);
		it++;
	}

	bool ok = output.SaveToFile(fileName);
	t2.Tac();
	return ok;
}

bool FileManager::SaveBinaryFile(wxString fileName, Array3D<double>& array) {
	ofstream file(fileName, ios::out | ios::binary);
	if (file.is_open()) {
		for (int i = 0; i < array.dim1(); i++) {
			for (int j = 0; j < array.dim2(); j++) {
				for (int k = 0; k < array.dim3(); k++) {
					file.write(reinterpret_cast<char *>(&array[i][j][k]), sizeof(double));
				}
			}
		}
		file.close();
		return true;
	} else {
		return false;
	}
}

bool FileManager::SaveFile(wxString fileName, wxString contents) {
	ofstream file(fileName, ios::out);
	if (file.is_open()) {
		file << contents;
		file.close();
		return true;
	} else {
		return false;
	}
}
bool FileManager::OpenFile(wxString fileName, wxString& contents) {
	TicTac tictac;
	tictac.Tic("FileManager::OpenFile");

	string line = string();
	ifstream file(fileName, ios::in);
	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);
			contents.Append(line).Append("\n");
		}
		file.close();

		tictac.Tac();
		return true;
	} else {
		return false;
	}
}

wxString FileManager::ShowFileDialog(wxWindow *parent, wxString title, wxString wildcard, long style, wxString defaultDir) {
	wxFileDialog dialog(parent, title, defaultDir, "", wildcard, style);
	wxString file = FILE_NOT_CHOOSEN;
	if (dialog.ShowModal() == wxID_OK) {
		file = dialog.GetPath();
		LAST_DIR = GetFolder(file);
	}
	return file;
}

bool FileManager::FileExists(wxString fileName) {
	struct stat info;
	int ret = -1;

	ret = stat(fileName.c_str(), &info);

	// 0 = conseguir retornar os atributos do arquivo (arquivo existe)
	return (ret == 0);
}
wxString FileManager::GetFolder(wxString fileNameWithFolder) {
	return fileNameWithFolder.BeforeLast('\\').Append('\\');
}
wxString FileManager::GetFileName(wxString fileNameWithFolder) {
	return fileNameWithFolder.AfterLast('\\');
}
wxString FileManager::GetFileNameWithoutExtension(wxString fileNameWithFolder) {
	return GetFileName(fileNameWithFolder).BeforeLast('.');
}
