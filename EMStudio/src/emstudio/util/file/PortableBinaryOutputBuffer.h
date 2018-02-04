/*
 * PortableBinaryOutputBuffer.h
 *
 *  Created on: 06/05/2013
 *      Author: leandrocarisio
 */

#ifndef PORTABLEBINARYOUTPUTBUFFER_H_
#define PORTABLEBINARYOUTPUTBUFFER_H_

#include "wx/wx.h"
#include "emstudio/util/file/OutputBuffer.h"
#include <string>
#include "msgpack/msgpack.hpp"

using namespace::std;

class PortableBinaryOutputBuffer : public OutputBuffer {
private:
	msgpack::sbuffer buffer;
	msgpack::packer<msgpack::sbuffer> pk;
public:
	PortableBinaryOutputBuffer();
	virtual ~PortableBinaryOutputBuffer();

	virtual void WriteChar(char& c);
	virtual void WriteBool(bool& b);
	virtual void WriteInt(int& i);
	virtual void WriteLong(long& l);
	virtual void WriteFloat(float& f);
	virtual void WriteDouble(double& d);
	virtual void WriteString(wxString& s);
	virtual void WriteArray1D(Array1D<double>& a);
	virtual void WriteArray2D(Array2D<double>& a);
	virtual void WriteArray3D(Array3D<double>& a);

	virtual void WriteVectorString(vector<wxString>& v);
	virtual void WriteVectorDouble(vector<double>& v);

	string GetStringRepresentation(); // Representação do buffer em string
	bool SaveToFile(wxString fileName);
};

#endif /* PORTABLEBINARYOUTPUTBUFFER_H_ */
