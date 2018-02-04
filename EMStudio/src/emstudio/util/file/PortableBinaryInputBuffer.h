/*
 * PortableBinaryInputBuffer.h
 *
 *  Created on: 06/05/2013
 *      Author: leandrocarisio
 */

#ifndef PORTABLEBINARYINPUTBUFFER_H_
#define PORTABLEBINARYINPUTBUFFER_H_

#include "wx/wx.h"
#include "emstudio/util/file/InputBuffer.h"
#include <string>
#include <sys/stat.h>
#include "msgpack/msgpack.hpp"

using namespace::std;

class PortableBinaryInputBuffer : public InputBuffer {
private:
	bool b;
	int i;
	long l;
	float f;
	double d;
	string s;

	msgpack::unpacker pac;
	msgpack::unpacked result;

public:
	PortableBinaryInputBuffer();
	virtual ~PortableBinaryInputBuffer();

	bool LoadFile(wxString fileName);

	virtual char ReadChar();
	virtual bool ReadBool();
	virtual int ReadInt();
	virtual long ReadLong();
	virtual float ReadFloat();
	virtual double ReadDouble();
	virtual wxString ReadString();
	virtual Array1D<double> ReadArray1D();
	virtual Array2D<double> ReadArray2D();
	virtual Array3D<double> ReadArray3D();

	virtual vector<wxString> ReadVectorString();
	virtual vector<double> ReadVectorDouble();
};

#endif /* PORTABLEBINARYINPUTBUFFER_H_ */
