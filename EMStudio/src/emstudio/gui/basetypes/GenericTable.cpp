/*
 * GenericTable.cpp
 *
 *  Created on: 13/03/2012
 *      Author: leandrocarisio
 */

#include "GenericTable.h"
#include "emstudio/util/converters/Converter.h"
#include "wx/tokenzr.h"

/**
 * Esta classe representa uma tabela genérica. É considerado que todos os dados da tabela são numéricos (double).
 * Toda a tabela é representada por dois atributos. O primeiro, data, representa as colunas da tabela.
 * data é do tipo vector<ColumnDataRepresentation>, sendo que ColumnDataRepresentation é um apelido para vector<double>.
 * O segundo atributo, dataLabel, representa o label das colunas.
 *
 * -------------------------------------------------------------------
 * | dataLabel[0] | dataLabel[1] | dataLabel[2] | ... | dataLabel[C] |
 * -------------------------------------------------------------------
 * |    data[0]   |    data[1]   |    data[2]   | ... |    data[C]   |
 * -------------------------------------------------------------------
 *
 * Obs: data[X] é do tipo vector<double>. Logo, a tabela é, na verdade:
 * -------------------------------------------------------------------
 * | dataLabel[0] | dataLabel[1] | dataLabel[2] | ... | dataLabel[C] |
 * -------------------------------------------------------------------
 * | data[0][0]   | data[1][0]   | data[2][0]   | ... |  data[C][0]  |
 * -------------------------------------------------------------------
 * | data[0][1]   | data[1][1]   | data[2][1]   | ... |  data[C][1]  |
 * -------------------------------------------------------------------
 * |                     ..............                              |
 * -------------------------------------------------------------------
 * | data[0][L]   | data[1][L]   | data[2][L]   | ... |  data[C][L]  |
 * -------------------------------------------------------------------
 */

/*
 * Inicia a tabela como vazio
 */
GenericTable::GenericTable()
	: dataLabel(std::vector<wxString>()),
	  data(std::vector<ColumnDataRepresentation>()) {

	SetWriteVersion(1);
}

GenericTable::~GenericTable() {
}

/*
 * Copia de um GenericTable. Basta copiar os dados e os labels dos dados
 */
void GenericTable::Copy(BaseType* b) {
	data = ((static_cast<GenericTable*>(b))->GetColumns());
	dataLabel = ((static_cast<GenericTable*>(b))->GetColumnsLabel());
}

wxString GenericTable::GetBaseTypeClassName() {
	return "GenericTable";
}
/**
 * Retorna uma descrição dos dados. Provavél que esse método não seja utilizado em lugar nenhum.
 * Por isso, coloquei uma string qualquer que fica fácil de procurar caso seja necessário utilizar essas
 * informações.
 */
wxString GenericTable::GetUserFriendlyStringRepresentation() {
	return "VEJA ARQUIVO GenericTable.cpp";
}

void GenericTable::SetUserFriendlyStringRepresentation(wxString str) {
	// Não faz nada, pois não tem como fazer essa atribuição
}


/*
 * Salva a tabela em buffer. Formato:
 */
void GenericTable::DoWrite(OutputBuffer& buffer) {
	/* Rótulo das colunas */
	buffer.WriteVectorString(dataLabel);
	/* Número de colunas */
	int nCol = data.size();
	buffer.WriteInt(nCol);
	/* Colunas */
	for (int i = 0; i < nCol; i++) {
		buffer.WriteVectorDouble(data[i]);
	}
}
void GenericTable::DoRead(InputBuffer& buffer) throw(BaseTypeIncompatibleException) {
	if (GetReadVersion() != 1)
		throw BaseTypeIncompatibleException(GetBaseTypeClassName());

	dataLabel = buffer.ReadVectorString();
	int nCol = buffer.ReadInt();
	/* Colunas */
	data.clear();
	for (int i = 0; i < nCol; i++) {
		data.push_back(buffer.ReadVectorDouble());
	}
}

std::vector<GenericTable::ColumnDataRepresentation>& GenericTable::GetColumns() {
	return data;
}
std::vector<wxString>& GenericTable::GetColumnsLabel() {
	return dataLabel;
}
GenericTable::ColumnDataRepresentation& GenericTable::GetColumn(int col) {
	return GetColumns()[col];
}
void GenericTable::AppendInColumn(int col, double val) {
	GetColumn(col).push_back(val);
}
void GenericTable::AddColumn(ColumnDataRepresentation column) {
	data.push_back(column);
}
void GenericTable::SetTableData(std::vector<ColumnDataRepresentation> v) {
	data = v;
}
void GenericTable::SetColumnsLabel(std::vector<wxString> colLabels) {
	dataLabel = colLabels;
}
