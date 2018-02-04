/*
 * ElementsWithSegments.cpp
 *
 *  Created on: 28/05/2014
 *      Author: leandrocarisio
 */

#include "ElementsWithSegments.h"
#include "emstudio/gui/basetypes/Material.h"
#include "emstudio/dto/momapp/ElementsWithSegmentsDTO.h"

#include <iostream>
using namespace::std;

namespace mom {

ElementsWithSegments::ElementsWithSegments(ElementTypeSmartPointer type)
	: ElementGUI(type) {
}

ElementsWithSegments::~ElementsWithSegments() {
}

Segments& ElementsWithSegments::GetSegments() {
	if (IsChanged()) {
		SetSegments(BuildSegments());
		SetChanged(false);
	}
	return segments;
}
Segments ElementsWithSegments::BuildSegments() {
	return Segments();
}
void ElementsWithSegments::SetSegments(Segments s) {
	segments = s;
}
bool ElementsWithSegments::HasSegments() {
	if (IsChanged()) {
		SetSegments(BuildSegments());
		SetChanged(false);
	}
	return segments.size() > 0;
}
bool ElementsWithSegments::FindClosestSegmentInAllElements(double x, double y, double z, Segment& s, double& d) {
	double dTemp;
	d = dTemp = 1e30;

	if (GetElementsInProject() == 0) return false;

	ElementManagerSmartPointer elements = GetElementsInProject();
	ElementManager::ElementMap projectMap = elements->GetElementMap();

	ElementManager::ElementMap::iterator it = projectMap.begin();
	ElementManager::ElementMap::iterator end = projectMap.end();
	while(it != end) {
		ElementTypeSmartPointer type = it->first;

		ElementManager::ElementList eList = it->second;

		ElementManager::ElementList::iterator itList = eList.begin();
		ElementManager::ElementList::iterator itListEnd = eList.end();

		while (itList != itListEnd) {
			ElementGUISmartPointer element = *itList;
			ElementsWithSegments* es = static_cast<ElementsWithSegments*>(element.get());

			if (es->HasSegments()) {
				Segment sTemp = es->FindClosestSegment(x, y, z, dTemp);
				if (dTemp < d) {
					s = sTemp;
					d = dTemp;
				}
			}
			itList++;
		}
		it++;
	}
	return true;
}
Segment ElementsWithSegments::FindClosestSegment(double x, double y, double z, double& d2center) {
	/* Essa rotina considera que o DTO veio preenchido com segmentos */
	d2center = 1e30;

	Segments::iterator it = segments.begin();
	Segments::iterator itEnd = segments.end();
	Segment s;
	while (it != itEnd) {
		double distance = it->GetDistanceToCenter(x, y, z);
		if (distance < d2center) {
			d2center = distance;
			s = *it;
		}
		it++;
	}
	return s;
}
void ElementsWithSegments::AddVisibleProperty(wxString propertyName, bool visible) {
	this->visible.SetValue(visible);
	AddProperty(Property(propertyName, &(this->visible)));
}
bool ElementsWithSegments::IsVisible() {
	return visible.IsValue();
}
void ElementsWithSegments::AddSolidProperty(wxString propertyName, bool solid) {
	this->solid.SetValue(solid);
	AddProperty(Property(propertyName, &(this->solid)));
}
bool ElementsWithSegments::IsSolid() {
	return solid.IsValue();
}
void ElementsWithSegments::Draw(OpenGLStateMachine* opengl) {
	if (IsVisible()) {
		SetColor(GetSegmentsColor());
		DrawSegments(GetSegments(), IsSolid());
	}
}
bool ElementsWithSegments::FillApproximateDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	if (IsVisible() && GetSegments().size() > 0) {
		FillApproximateDimensionsWithSegments(xmin, ymin, zmin, xmax, ymax, zmax);
		return true;
	} else {
		return false;
	}
}
bool ElementsWithSegments::GetProjectBoundary(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	xmin = 1e30; ymin = 1e30; zmin = 1e30;
	xmax = -1e30; ymax = -1e30; zmax = -1e30;
	bool hasDimensions = false;


	if (GetElementsInProject() == 0) return false;

	ElementManagerSmartPointer elements = GetElementsInProject();
	ElementManager::ElementMap projectMap = elements->GetElementMap();

	ElementManager::ElementMap::iterator it = projectMap.begin();
	ElementManager::ElementMap::iterator end = projectMap.end();
	while(it != end) {
		ElementTypeSmartPointer type = it->first;

		ElementManager::ElementList eList = it->second;

		ElementManager::ElementList::iterator itList = eList.begin();
		ElementManager::ElementList::iterator itListEnd = eList.end();

		while (itList != itListEnd) {
			ElementGUISmartPointer element = *itList;
			ElementsWithSegments* es = static_cast<ElementsWithSegments*>(element.get());

			double xminTemp, yminTemp, zminTemp, xmaxTemp, ymaxTemp, zmaxTemp;
			bool hasDimensionsTemp = es->FillApproximateDimensions(xminTemp, yminTemp, zminTemp, xmaxTemp, ymaxTemp, zmaxTemp);
			hasDimensions = hasDimensions || hasDimensionsTemp;

			if (hasDimensionsTemp) {
				xmin = xminTemp < xmin ? xminTemp : xmin;
				ymin = yminTemp < ymin ? yminTemp : ymin;
				zmin = zminTemp < zmin ? zminTemp : zmin;
				xmax = xmaxTemp > xmax ? xmaxTemp : xmax;
				ymax = ymaxTemp > ymax ? ymaxTemp : ymax;
				zmax = zmaxTemp > zmax ? zmaxTemp : zmax;
			}
			itList++;
		}
		it++;
	}
	return hasDimensions;
}
void ElementsWithSegments::FillApproximateDimensionsWithSegments(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	Rvector3 maxBoundary(-1e30, -1e30, -1e30);
	Rvector3 minBoundary(+1e30, +1e30, +1e30);

	Segments s = GetSegments();
	for (size_t i = 0; i < s.size(); i++) {
	   Rvector3 p1 = s[i].GetP1();
	   Rvector3 p2 = s[i].GetP2();
	   double radius = s[i].GetRadius();

	   if (p1.X + radius > maxBoundary.X) {
		   maxBoundary.X = p1.X + radius;
	   }
	   if (p1.Y + radius > maxBoundary.Y) {
		   maxBoundary.Y = p1.Y + radius;
	   }
	   if (p1.Z + radius > maxBoundary.Z) {
		   maxBoundary.Z = p1.Z + radius;
	   }
	   if (p2.X + radius > maxBoundary.X) {
		   maxBoundary.X = p2.X + radius;
	   }
	   if (p2.Y + radius > maxBoundary.Y) {
		   maxBoundary.Y = p2.Y + radius;
	   }
	   if (p2.Z + radius > maxBoundary.Z) {
		   maxBoundary.Z = p2.Z + radius;
	   }
	   if (p1.X - radius < minBoundary.X) {
		   minBoundary.X = p1.X - radius;
	   }
	   if (p1.Y - radius < minBoundary.Y) {
		   minBoundary.Y = p1.Y - radius;
	   }
	   if (p1.Z - radius < minBoundary.Z) {
		   minBoundary.Z = p1.Z - radius;
	   }
	   if (p2.X - radius < minBoundary.X) {
		   minBoundary.X = p2.X - radius;
	   }
	   if (p2.Y - radius < minBoundary.Y) {
		   minBoundary.Y = p2.Y - radius;
	   }
	   if (p2.Z - radius < minBoundary.Z) {
		   minBoundary.Z = p2.Z - radius;
	   }
	}
	xmin = minBoundary.X;
	ymin = minBoundary.Y;
	zmin = minBoundary.Z;
	xmax = maxBoundary.X;
	ymax = maxBoundary.Y;
	zmax = maxBoundary.Z;
}
wxColour ElementsWithSegments::GetSegmentsColor() {
	return GetPECColor();
}
wxColour ElementsWithSegments::GetPECColor() {
	Material pec;
	pec.SetDescription("PEC");
	pec.SetType(PEC);
	pec.Sync(false);

	return pec.GetColor();
}

void ElementsWithSegments::DoPopulateDTO(ElementDTOSmartPointer p) {
	ElementGUI::DoPopulateDTO(p);

	ElementsWithSegmentsDTOSmartPointer emStudioDTO = std::tr1::static_pointer_cast<ElementsWithSegmentsDTO>(p);

	if (HasSegments()) {
		emStudioDTO->SetSegments(GetSegments());
	}
}
}
