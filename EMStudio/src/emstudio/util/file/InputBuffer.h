/*
 * InputBuffer.h
 *
 *  Created on: 06/05/2013
 *      Author: leandrocarisio
 */

#ifndef INPUTBUFFER_H_
#define INPUTBUFFER_H_

#include "wx/wx.h"
#include <vector>
#include "emstudio/util/tnt/tnt.h"

using namespace::TNT;

class InputBuffer {
public:
	InputBuffer();
	virtual ~InputBuffer();

	virtual char ReadChar() = 0;
	virtual bool ReadBool() = 0;
	virtual int ReadInt() = 0;
	virtual long ReadLong() = 0;
	virtual float ReadFloat() = 0;
	virtual double ReadDouble() = 0;
	virtual wxString ReadString() = 0;
	virtual Array1D<double> ReadArray1D() = 0;
	virtual Array2D<double> ReadArray2D() = 0;
	virtual Array3D<double> ReadArray3D() = 0;

	virtual std::vector<wxString> ReadVectorString() = 0;
	virtual std::vector<double> ReadVectorDouble() = 0;
};

#endif /* INPUTBUFFER_H_ */
