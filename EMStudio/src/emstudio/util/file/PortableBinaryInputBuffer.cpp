/*
 * PortableBinaryInputBuffer.cpp
 *
 *  Created on: 06/05/2013
 *      Author: leandrocarisio
 */

#include "PortableBinaryInputBuffer.h"
#include "emstudio/util/time/TicTac.h"
#include <iostream>
using namespace::std;
PortableBinaryInputBuffer::PortableBinaryInputBuffer() : pac(), result() {

}

PortableBinaryInputBuffer::~PortableBinaryInputBuffer() {
}

bool PortableBinaryInputBuffer::LoadFile(wxString fileName) {
	TicTac t;
	t.Tic("LoadFile - Carregando arquivo para o buffer");
	// TODO: Verificar se tem que apagar dataFile ou não
	struct stat fileInfo;
	stat(fileName, &fileInfo);
	char* dataFile = new char[fileInfo.st_size];
	cout << "Abrir arquivo" << endl;
	cout << "Arquivo: " << fileName << endl;
	cout << "Tamanho: " << fileInfo.st_size << endl;

	ifstream file(fileName, ios::binary);
	if (file.is_open()) {
		file.read(dataFile, fileInfo.st_size);
		file.close();

		pac.reserve_buffer(fileInfo.st_size);
		memcpy(pac.buffer(), dataFile, fileInfo.st_size);
		pac.buffer_consumed(fileInfo.st_size);

		delete[] dataFile;
		t.Tac();
		return true;
	} else {
		return false;
	}
}
char PortableBinaryInputBuffer::ReadChar() {
//	cout << "ReadChar() = ";
	// Char é gravado como um int
	pac.next(&result);
	msgpack::object obj = result.get();
	obj.convert(&i);
//	cout << i << endl;
	return (char)i;
}
bool PortableBinaryInputBuffer::ReadBool() {
//	cout << "ReadBool() = ";
	pac.next(&result);
	msgpack::object obj = result.get();
	obj.convert(&b);
//	cout << b << endl;
	return b;
}
int PortableBinaryInputBuffer::ReadInt() {
//	cout << "ReadInt() = ";
	pac.next(&result);
	msgpack::object obj = result.get();
	obj.convert(&i);
//	cout << i << endl;
	return i;
}
long PortableBinaryInputBuffer::ReadLong() {
//	cout << "ReadLong() = ";
	pac.next(&result);
	msgpack::object obj = result.get();
	obj.convert(&l);
//	cout << l << endl;
	return l;
}
float PortableBinaryInputBuffer::ReadFloat() {
//	cout << "ReadFloat() = ";
	pac.next(&result);
	msgpack::object obj = result.get();
	obj.convert(&f);
//	cout << f << endl;
	return f;
}
double PortableBinaryInputBuffer::ReadDouble() {
//	cout << "ReadDouble() = ";
	pac.next(&result);
	msgpack::object obj = result.get();
	obj.convert(&d);
//	cout << d << endl;
	return d;
}
wxString PortableBinaryInputBuffer::ReadString() {
////	cout << "ReadString() = ";
	pac.next(&result);
	msgpack::object obj = result.get();
	obj.convert(&s);
////	cout << s << endl;
	return s;
}
Array1D<double> PortableBinaryInputBuffer::ReadArray1D() {
	int dim1;

	pac.next(&result);
	msgpack::object obj = result.get();
	obj.convert(&dim1);

	Array1D<double> array(dim1);

	for (int i = 0; i < dim1; i++) {
		pac.next(&result);
		obj = result.get();
		obj.convert(&d);
		array[i] = d;
	}

	return array;
}
Array2D<double> PortableBinaryInputBuffer::ReadArray2D() {
	int dim1;
	int dim2;

	pac.next(&result);
	msgpack::object obj = result.get();
	obj.convert(&dim1);

	pac.next(&result);
	obj = result.get();
	obj.convert(&dim2);


	Array2D<double> array(dim1, dim2);

	for (int i = 0; i < dim1; i++) {
		for (int j = 0; j < dim2; j++) {
			pac.next(&result);
			obj = result.get();
			obj.convert(&d);
			array[i][j] = d;
		}
	}

	return array;
}
Array3D<double> PortableBinaryInputBuffer::ReadArray3D() {
	TicTac t;
	t.Tic("PortableBinaryInputBuffer::ReadArray3D");

	int dim1;
	int dim2;
	int dim3;

	pac.next(&result);
	msgpack::object obj = result.get();
	obj.convert(&dim1);

	pac.next(&result);
	obj = result.get();
	obj.convert(&dim2);

	pac.next(&result);
	obj = result.get();
	obj.convert(&dim3);

	Array3D<double> array(dim1, dim2, dim3);

	for (int i = 0; i < dim1; i++) {
		for (int j = 0; j < dim2; j++) {
			for (int k = 0; k < dim3; k++) {
				pac.next(&result);
				obj = result.get();
				obj.convert(&(array[i][j][k]));
//				array[i][j][k] = d;
			}
		}
	}
	t.Tac();
	return array;
}

vector<wxString> PortableBinaryInputBuffer::ReadVectorString() {
	int size;

	pac.next(&result);
	msgpack::object obj = result.get();
	obj.convert(&size);

	vector<wxString> vec;
	for (int i = 0; i < size; i++) {
		pac.next(&result);
		obj = result.get();
		obj.convert(&s);
		vec.push_back(s);

	}

	return vec;
}
vector<double> PortableBinaryInputBuffer::ReadVectorDouble() {
	int size;

	pac.next(&result);
	msgpack::object obj = result.get();
	obj.convert(&size);

	vector<double> vec;
	for (int i = 0; i < size; i++) {
		pac.next(&result);
		obj = result.get();
		obj.convert(&d);
		vec.push_back(d);

	}

	return vec;
}
