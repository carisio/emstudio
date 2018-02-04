/*
 * MoMEngine.cpp
 *
 *  Created on: 03/06/2014
 *      Author: leandrocarisio
 */

#include <emstudio/core/engine/mom/elementcore/ChargeDensitiesMoMCore.h>
#include <emstudio/core/engine/mom/elementcore/CurrentsMoMCore.h>
#include <emstudio/core/engine/mom/elementcore/RadiationPatternMoMCore.h>
#include <emstudio/core/engine/mom/elementcore/TransmissionLineMoMCore.h>
#include <emstudio/core/engine/mom/elementcore/VoltageSourceMoMCore.h>
#include <emstudio/core/engine/mom/elementcore/WireMoMCore.h>
#include <emstudio/core/engine/mom/MoMEngine.h>
#include <emstudio/core/InformSimulationStatus.h>
#include <emstudio/core/results/Result.h>
#include <emstudio/core/results/SimpleTextResult.h>
#include <emstudio/dto/ElementDTO.h>
#include <emstudio/dto/momapp/ChargeDensitiesDTO.h>
#include <emstudio/dto/momapp/CurrentsDTO.h>
#include <emstudio/dto/momapp/RadiationPatternDTO.h>
#include <emstudio/dto/momapp/TransmissionLineDTO.h>
#include <emstudio/dto/momapp/VoltageSourceDTO.h>
#include <emstudio/dto/momapp/WireDTO.h>
#include <emstudio/util/converters/Converter.h>
#include <emstudio/util/nec/code/nec_exception.h>
#include <emstudio/util/nec/Segment.h>
#include <wx/string.h>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

using namespace::std;

namespace mom {

MoMEngine::MoMEngine(ElementDTOSmartPointer dtosmartptr, InformSimulationStatusSmartPointer status) :
		Engine(dtosmartptr, status),
		dto(*(static_cast<MoMDTO*>(dtosmartptr.get()))) {
	cout << "MoMEngine::ctor" << endl;
	/*
	 * REGISTRA TODOS OS PARES DE ELEMENTOS DTO E CORE
	 */
	Register(ElementDTOSmartPointer(new WireDTO), ElementCoreSmartPointer(new WireMoMCore));
	Register(ElementDTOSmartPointer(new VoltageSourceDTO), ElementCoreSmartPointer(new VoltageSourceMoMCore));
	Register(ElementDTOSmartPointer(new TransmissionLineDTO), ElementCoreSmartPointer(new TransmissionLineMoMCore));
	Register(ElementDTOSmartPointer(new CurrentsDTO), ElementCoreSmartPointer(new CurrentsMoMCore));
	Register(ElementDTOSmartPointer(new ChargeDensitiesDTO), ElementCoreSmartPointer(new ChargeDensitiesMoMCore));
	Register(ElementDTOSmartPointer(new RadiationPatternDTO), ElementCoreSmartPointer(new RadiationPatternMoMCore));
}

MoMEngine::~MoMEngine() {
	indexGeometry.clear();
	sources.clear();
	necContextSmartPointer.reset();
}

MoMDTO& MoMEngine::GetMoMDTO() {
	return dto;
}
NECContextSmartPointer MoMEngine::GetNecContext() {
	return necContextSmartPointer;
}
void MoMEngine::DoStartSimulation() {
	try {
		necContextSmartPointer = NECContextSmartPointer(new nec_context);
		necContextSmartPointer->initialize();

		if (SimulationWasCanceled())
			return;
		/* Create geometry */
		InformStatus("Setting geometry");
		std::vector<std::pair<int, ElementCoreSmartPointer> >::iterator itGeometry = indexGeometry.begin();
		std::vector<std::pair<int, ElementCoreSmartPointer> >::iterator itGeometryEnd = indexGeometry.end();

		necCommand = "CM Generated with EM Studio [NEC]\nCE\n";
		while (itGeometry != itGeometryEnd) {
			MoMElementCore* momElementCorePtr = static_cast<MoMElementCore*>(itGeometry->second.get());
			momElementCorePtr->SetGeometry(itGeometry->first);
			necCommand.Append(momElementCorePtr->GetNECCommand());
			itGeometry++;
		}
		if (SimulationWasCanceled())
			return;
		if (!dto.HasMedium1()) {
			cout << "necContextSmartPointer->geometry_complete(0,0);" << endl;
			necContextSmartPointer->geometry_complete(0,0);
			necCommand.Append("GE 0\n");
		} else {
			cout << "necContextSmartPointer->geometry_complete(1,0);" << endl;
			necContextSmartPointer->geometry_complete(1,0);
			necCommand.Append("GE 1\n");
		}
		/* Geometry created */
		if (SimulationWasCanceled())
			return;
		/* Define extended thin-wire kernel */
		necContextSmartPointer->set_extended_thin_wire_kernel(dto.IsUseExtendedThinWireKernel());
		necCommand.Append("EK ").Append(Converter::IntToFormattedString((dto.IsUseExtendedThinWireKernel() ? 0 : -1))).Append("\n");
		cout << "necContextSmartPointer->set_extended_thin_wire_kernel(" << dto.IsUseExtendedThinWireKernel() << ");" << endl;
		/* Extended thin-wire kernel defined */

		/* Define connections */
		std::vector<ElementCoreSmartPointer>::iterator itConnections = connections.begin();
		std::vector<ElementCoreSmartPointer>::iterator itConnectionsEnd = connections.end();
		if (itConnections != itConnectionsEnd)
			InformStatus("Setting connections");
		while (itConnections != itConnectionsEnd) {
			MoMElementCore* momElementCorePtr = static_cast<MoMElementCore*>(itConnections->get());
			momElementCorePtr->SetConnection();
			necCommand.Append(momElementCorePtr->GetNECCommand());
			itConnections++;
		}
		/* Connections defined */
		if (SimulationWasCanceled())
			return;
		/* Set up sources */
		std::vector<ElementCoreSmartPointer>::iterator itSources = sources.begin();
		std::vector<ElementCoreSmartPointer>::iterator itSourcesEnd = sources.end();
		if (itSources != itSourcesEnd)
			InformStatus("Setting sources");
		while (itSources != itSourcesEnd) {
			MoMElementCore* momElementCorePtr = static_cast<MoMElementCore*>(itSources->get());
			momElementCorePtr->SetSource();
			necCommand.Append(momElementCorePtr->GetNECCommand());
			itSources++;
		}
		/* All sources setted */
		if (SimulationWasCanceled())
			return;
		/* Define Ground, if any */
		if (dto.HasMedium1() || dto.GetNumberOfRadials() > 0) {
			InformStatus("Setting ground");
			if (dto.GetMedium1().IsPec()) {
				cout << "necContextSmartPointer->gn_card(1, 0, 0, 0, 0, 0, 0, 0)" << endl;
				necContextSmartPointer->gn_card(1, 0, 0, 0, 0, 0, 0, 0);
				necCommand.Append("GN 1 0 0 0 0 0 0 0\n");
			} else {
				cout << "necContextSmartPointer->gn_card(0, " << dto.GetNumberOfRadials() << "," << dto.GetMedium1().GetEx() << "," << dto.GetMedium1().GetSx() << "," << dto.GetWireLength() << "," << dto.GetWireRadius() << ",0, 0);" << endl;
				necContextSmartPointer->gn_card(0, dto.GetNumberOfRadials(), dto.GetMedium1().GetEx(), dto.GetMedium1().GetSx(), dto.GetWireLength(), dto.GetWireRadius(), 0, 0);
				necCommand.Append("GN 0 ").Append(Converter::IntToFormattedString(dto.GetNumberOfRadials())).Append(" ").
						Append(Converter::DoubleToFormattedString(dto.GetMedium1().GetEx())).Append(" ").
						Append(Converter::DoubleToFormattedString_MaxPrecision(dto.GetMedium1().GetSx())).Append(" ").
						Append(Converter::DoubleToFormattedString(dto.GetWireLength())).Append(" ").
						Append(Converter::DoubleToFormattedString(dto.GetWireRadius())).Append(" 0 0\n");
			}
		}
		if (dto.HasMedium2()) {
			cout << "necContextSmartPointer->gd_card(" << dto.GetMedium2().GetEx() << "," << dto.GetMedium2().GetSx() << "," << dto.GetDistFromOrigin() << "," << dto.GetDistBelowGround() << ");" << endl;
			necContextSmartPointer->gd_card(dto.GetMedium2().GetEx(), dto.GetMedium2().GetSx(), dto.GetDistFromOrigin(), dto.GetDistBelowGround());
			necCommand.Append("GD ").Append(Converter::DoubleToFormattedString(dto.GetMedium2().GetEx())).Append(" ").
					Append(Converter::DoubleToFormattedString_MaxPrecision(dto.GetMedium2().GetSx())).Append(" ").
					Append(Converter::DoubleToFormattedString(dto.GetDistFromOrigin())).Append(" ").
					Append(Converter::DoubleToFormattedString(dto.GetDistBelowGround())).Append("\n");
		}
		/* Ground defined*/
		if (SimulationWasCanceled())
			return;
		/* Define probes */
		std::vector<ElementCoreSmartPointer>::iterator itProbes = probes.begin();
		std::vector<ElementCoreSmartPointer>::iterator itProbesEnd = probes.end();
		if (itProbes != itProbesEnd)
			InformStatus("Setting probes");
		while (itProbes != itProbesEnd) {
			MoMElementCore* momElementCorePtr = static_cast<MoMElementCore*>(itProbes->get());
			momElementCorePtr->SetProbe();
			necCommand.Append(momElementCorePtr->GetNECCommand());
			itProbes++;
		}
		/* Probes defined */
		if (SimulationWasCanceled())
			return;
		/* Define frequencies */
		cout << "necContextSmartPointer->fr_card(0, " << dto.GetNFrequency() << "," << dto.GetInitialFrequency() << "," << dto.GetFrequencyStep() << ");" << endl;
		InformStatus("Setting frequencies");
		necContextSmartPointer->fr_card(0, dto.GetNFrequency(), dto.GetInitialFrequency(), dto.GetFrequencyStep());
		necCommand.Append("FR 0 ").Append(Converter::IntToFormattedString(dto.GetNFrequency())).Append(" ").
				Append(Converter::DoubleToFormattedString(dto.GetInitialFrequency())).Append(" ").
				Append(Converter::DoubleToFormattedString(dto.GetFrequencyStep())).Append("\n");
		/* Frequencies defined */
		necContextSmartPointer->xq_card(0, GetInformSimulationStatusSmartPointer(), 0, 100/(executionCards.size()+1));
		necCommand.Append("XQ 0\n");

		/* Execute */
		std::vector<ElementCoreSmartPointer>::iterator itExecutionCards = executionCards.begin();
		std::vector<ElementCoreSmartPointer>::iterator itExecutionCardsEnd = executionCards.end();
		while (itExecutionCards != itExecutionCardsEnd) {
			MoMElementCore* momElementCorePtr = static_cast<MoMElementCore*>(itExecutionCards->get());
			momElementCorePtr->SetExecutionCard();
			necCommand.Append(momElementCorePtr->GetNECCommand());
			itExecutionCards++;
			if (SimulationWasCanceled())
				return;
		}

		if (SimulationWasCanceled())
			return;
		UpdateProgress(100);

	} catch (nec_exception* e) {
		cout << e->get_message() << endl;
	}
}

void MoMEngine::DoCreateProject() {
	cout << "MoMEngine::DoCreateProject" << endl;
	ProjectList& prj = GetProjectList();
	ProjectList::iterator itPrj = prj.begin();
	ProjectList::iterator itPrjEnd = prj.end();

	indexGeometry = std::vector<std::pair<int, ElementCoreSmartPointer> >();
	int currentIndexGeometry = 1;
	sources = std::vector<ElementCoreSmartPointer>();

	while (itPrj != itPrjEnd) {
		MoMElementCore* momElementCorePtr = static_cast<MoMElementCore*>(itPrj->get());

		/* Monta a geometria */
		if (momElementCorePtr->GetType() == GEOMETRY) {
			cout << "Adicionando geometria. Indice = " << currentIndexGeometry << endl;
			indexGeometry.push_back(std::pair<int, ElementCoreSmartPointer>(currentIndexGeometry, *itPrj));
			currentIndexGeometry++;
		}

		/* Monta a fonte */
		if (momElementCorePtr->GetType() == SOURCE) {
			sources.push_back(*itPrj);
		}

		/* Monta as conexões */
		if (momElementCorePtr->GetType() == CONNECTIONS) {
			connections.push_back(*itPrj);
		}
		/* Monta os probes */
		if (momElementCorePtr->GetType() == PROBES) {
			probes.push_back(*itPrj);
		}
		/* Monta os execution cards (RP, NE, NH) */
		if (momElementCorePtr->GetType() == EXECUTION_CARDS) {
			executionCards.push_back(*itPrj);
		}
		itPrj++;
	}
}

bool MoMEngine::DoIsProjectConsistentBegin() {
	cout << "MoMEngine::DoIsProjectConsistentBegin" << endl;
	bool prjOk = true;
	if (indexGeometry.size() == 0) {
		wxString errorMessage = "There is no geometry to simulate.";
		AppendErrorMessage(errorMessage);
		prjOk = false;
	}
	return prjOk;
}
std::pair<std::vector<int>, Segments> MoMEngine::GetAllSegmentsSortedBySequentialSegmentIndex() {
	/* Essa rotina considera que o DTO veio preenchido com segmentos */
	std::vector<std::pair<int, ElementCoreSmartPointer> >::iterator itGeometry = indexGeometry.begin();
	std::vector<std::pair<int, ElementCoreSmartPointer> >::iterator itGeometryEnd = indexGeometry.end();

	Segments allSegments;
	std::vector<int> tags;
	std::vector<int> segmentIndexsSequential;
	std::vector<int> segmentIndexsMth;

	int segmentIndexSequential = 1;
	while (itGeometry != itGeometryEnd) {
		int tag = itGeometry->first;
		MoMElementCore* momElementCorePtr = static_cast<MoMElementCore*>(itGeometry->second.get());
		Segments segments = momElementCorePtr->GetSegments();
		Segments::iterator itSegments = segments.begin();
		Segments::iterator itSegmentsEnd = segments.end();

		int segmentIndexMth = 1;
		while (itSegments != itSegmentsEnd) {
			allSegments.push_back(*itSegments);
			tags.push_back(tag);
			segmentIndexsSequential.push_back(segmentIndexSequential);
			segmentIndexsMth.push_back(segmentIndexMth);

			segmentIndexMth++;
			segmentIndexSequential++;
			itSegments++;
		}
		itGeometry++;
	}
	return std::pair<std::vector<int>, Segments>(segmentIndexsSequential, allSegments);
}
bool MoMEngine::FindClosestSegment(double x, double y, double z, int& tagNumber, int& mthSegment, int& sequentialSegmentNumber) {
	/* Essa rotina considera que o DTO veio preenchido com segmentos */
	double d2center = 1e30;

	std::vector<std::pair<int, ElementCoreSmartPointer> >::iterator itGeometry = indexGeometry.begin();
	std::vector<std::pair<int, ElementCoreSmartPointer> >::iterator itGeometryEnd = indexGeometry.end();

	int segmentIndexSequential = 1;
	while (itGeometry != itGeometryEnd) {
		MoMElementCore* momElementCorePtr = static_cast<MoMElementCore*>(itGeometry->second.get());
		Segments segments = momElementCorePtr->GetSegments();
		Segments::iterator itSegments = segments.begin();
		Segments::iterator itSegmentsEnd = segments.end();

		int segmentIndexMth = 1;
		while (itSegments != itSegmentsEnd) {
			double distance = itSegments->GetDistanceToCenter(x, y, z);
			if (distance < d2center) {
				d2center = distance;
				tagNumber = itGeometry->first;
				mthSegment = segmentIndexMth;
				sequentialSegmentNumber = segmentIndexSequential;
			}

			segmentIndexMth++;
			segmentIndexSequential++;
			itSegments++;
		}
		itGeometry++;
	}
	return d2center != 1e30;
}
int MoMEngine::GetNumberOfExecutionCards() {
	cout << "executionCards.size() = " << executionCards.size() << endl;
	return executionCards.size();
}

std::list<ResultSmartPointer> MoMEngine::GetMyOwnResults() {
	list<ResultSmartPointer> results;

	results.push_back(ResultSmartPointer(new SimpleTextResult("NEC input file", necCommand)));

	return results;
}
} /* namespace mom */
