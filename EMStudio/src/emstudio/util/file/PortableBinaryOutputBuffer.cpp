/*
 * PortableBinaryOutputBuffer.cpp
 *
 *  Created on: 06/05/2013
 *      Author: leandrocarisio
 */

#include "PortableBinaryOutputBuffer.h"
#include <iostream>
using namespace::std;

PortableBinaryOutputBuffer::PortableBinaryOutputBuffer() : OutputBuffer() , buffer(), pk(&buffer) {
}

PortableBinaryOutputBuffer::~PortableBinaryOutputBuffer() {
}

void PortableBinaryOutputBuffer::WriteChar(char& c) {
	pk.pack(((int)c));
}
void PortableBinaryOutputBuffer::WriteBool(bool& b) {
	pk.pack(b);
}
void PortableBinaryOutputBuffer::WriteInt(int& i) {
	pk.pack(i);
}
void PortableBinaryOutputBuffer::WriteLong(long& l) {
	pk.pack(l);
}
void PortableBinaryOutputBuffer::WriteFloat(float& f) {
	pk.pack(f);
}
void PortableBinaryOutputBuffer::WriteDouble(double& d) {
	pk.pack(d);
}
void PortableBinaryOutputBuffer::WriteString(wxString& s) {
	std::string str = s.ToStdString();
	pk.pack(str);
//	cout << "WriteString: " << str << endl;
}
void PortableBinaryOutputBuffer::WriteArray1D(Array1D<double>& a) {
	int dim1 = a.dim1();
	pk.pack(dim1);
	for (int i = 0; i < dim1; i++) {
		pk.pack(a[i]);
	}
}
void PortableBinaryOutputBuffer::WriteArray2D(Array2D<double>& a) {
	int dim1 = a.dim1();
	int dim2 = a.dim2();
	pk.pack(dim1);
	pk.pack(dim2);
	for (int i = 0; i < dim1; i++) {
		for (int j = 0; j < dim2; j++) {
			pk.pack(a[i][j]);
		}
	}
}
void PortableBinaryOutputBuffer::WriteArray3D(Array3D<double>& a) {
	int dim1 = a.dim1();
	int dim2 = a.dim2();
	int dim3 = a.dim3();
	pk.pack(dim1);
	pk.pack(dim2);
	pk.pack(dim3);
	for (int i = 0; i < dim1; i++) {
		for (int j = 0; j < dim2; j++) {
			for (int k = 0; k < dim3; k++) {
				pk.pack(a[i][j][k]);
			}
		}
	}
}

void PortableBinaryOutputBuffer::WriteVectorString(vector<wxString>& v) {
	int size = v.size();
	pk.pack(size);
	for (int i = 0; i < size; i++) {
		WriteString(v[i]);
	}
}
void PortableBinaryOutputBuffer::WriteVectorDouble(vector<double>& v) {
	int size = v.size();
	pk.pack(size);
	for (int i = 0; i < size; i++) {
		WriteDouble(v[i]);
	}
}

string PortableBinaryOutputBuffer::GetStringRepresentation() {
//	cout << "PortableBinaryOutputBuffer::GetStringRepresentation()" << endl;
//	string s;
//	s.reserve(buffer.size());
//	char* data = buffer.data();
//	cout << "\0 = " << (int)('\0') << endl;
//	for (int i = 0; i < buffer.size(); i++) {
//		if (data[i] == '\0') {
//			s.append(1, '0');
//		} else {
//			s.append(1, data[i]);
//		}
//	}
//	cout << "s = " << s << endl;

	cout << "PortableBinaryOutputBuffer::GetStringRepresentation()" << endl;
	string s(buffer.data(), buffer.size());
	cout << "s = " << s << endl;
	return s;
}

bool PortableBinaryOutputBuffer::SaveToFile(wxString fileName) {
	try{
		ofstream outFile(fileName, ios::binary);

		if (outFile.is_open()) {
			char* dados = buffer.data();
			outFile.write(dados, buffer.size());
			outFile.close();
			return true;
		} else {
			return false;
		}
	} catch (const std::exception& ex) {
		cout << ex.what() << endl;
		return false;
	}

	return true;
}
