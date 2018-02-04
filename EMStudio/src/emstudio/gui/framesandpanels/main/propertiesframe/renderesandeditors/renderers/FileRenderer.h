/*
 * FileRenderer.h
 *
 *  Created on: 20/06/2013
 *      Author: leandrocarisio
 */

#ifndef FILERENDERER_H_
#define FILERENDERER_H_

#include "wx/grid.h"

class FileRenderer : public wxGridCellAutoWrapStringRenderer {
public:
	FileRenderer();
	virtual wxGridCellRenderer* Clone() const;
	virtual ~FileRenderer();
};

#endif /* FILERENDERER_H_ */
