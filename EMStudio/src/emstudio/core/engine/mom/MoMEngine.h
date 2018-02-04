/*
 * MoMEngine.h
 *
 *  Created on: 03/06/2014
 *      Author: leandrocarisio
 */

#ifndef MOMENGINE_H_
#define MOMENGINE_H_

#include "emstudio/core/Engine.h"
#include "emstudio/dto/momapp/MoMDTO.h"
#include <emstudio/util/nec/code/nec_context.h>
#include "emstudio/util/nec/code/c_geometry.h"
#include "elementcore/MoMElementCore.h"
#include <tr1/memory>
#include <list>

namespace mom {

typedef std::tr1::shared_ptr<nec_context> NECContextSmartPointer;

class MoMEngine : public Engine {
private:
	NECContextSmartPointer necContextSmartPointer;
	MoMDTO dto;
	wxString necCommand;
	/*
	 * This structure represents the geometry of the problem.
	 * index is a unique of the ElementCoreSmartPointer
	 */
	std::vector<std::pair<int, ElementCoreSmartPointer> > indexGeometry;
	std::vector<ElementCoreSmartPointer> sources;
	std::vector<ElementCoreSmartPointer> connections;
	std::vector<ElementCoreSmartPointer> probes;
	std::vector<ElementCoreSmartPointer> executionCards;
public:
	MoMEngine(ElementDTOSmartPointer dto, InformSimulationStatusSmartPointer status);
	virtual ~MoMEngine();

	MoMDTO& GetMoMDTO();
	NECContextSmartPointer GetNecContext();

	std::pair<std::vector<int>, Segments> GetAllSegmentsSortedBySequentialSegmentIndex();
	bool FindClosestSegment(double x, double y, double z, int& tagNumber, int& mthSegment, int& sequentialSegmentNumber);
	virtual bool DoIsProjectConsistentBegin();

	virtual void DoCreateProject();
	virtual void DoStartSimulation();
	int GetNumberOfExecutionCards();

	virtual std::list<ResultSmartPointer> GetMyOwnResults();
};

} /* namespace mom */
#endif /* MOMENGINE_H_ */
