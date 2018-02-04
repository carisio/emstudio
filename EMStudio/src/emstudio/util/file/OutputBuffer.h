/*
 * OutputBuffer.h
 *
 *  Created on: 06/05/2013
 *      Author: leandrocarisio
 */

#ifndef OUTPUTBUFFER_H_
#define OUTPUTBUFFER_H_

#include "wx/wx.h"
#include <vector>
#include "emstudio/util/tnt/tnt.h"

using namespace::std;
using namespace::TNT;

class OutputBuffer {
public:
	OutputBuffer();
	virtual ~OutputBuffer();

	virtual void WriteChar(char& c) = 0;
	virtual void WriteBool(bool& b) = 0;
	virtual void WriteInt(int& i) = 0;
	virtual void WriteLong(long& l) = 0;
	virtual void WriteFloat(float& f) = 0;
	virtual void WriteDouble(double& d) = 0;
	virtual void WriteString(wxString& s) = 0;
	virtual void WriteArray1D(Array1D<double>& a) = 0;
	virtual void WriteArray2D(Array2D<double>& a) = 0;
	virtual void WriteArray3D(Array3D<double>& a) = 0;

	virtual void WriteVectorString(vector<wxString>& v) = 0;
	virtual void WriteVectorDouble(vector<double>& v) = 0;
};

#endif /* OUTPUTBUFFER_H_ */
