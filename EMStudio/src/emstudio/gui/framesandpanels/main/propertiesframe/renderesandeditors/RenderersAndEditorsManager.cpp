/*
 * RenderersAndEditorsManager.cpp
 *
 *  Created on: 07/09/2011
 *      Author: Leandro
 */

#include "RenderersAndEditorsManager.h"

#include "emstudio/gui/basetypes/DoubleWrapper.h"
#include "editors/DoubleWrapperEditor.h"
#include "renderers/DoubleWrapperRenderer.h"

#include "emstudio/gui/basetypes/FloatWrapper.h"
#include "editors/FloatWrapperEditor.h"
#include "renderers/FloatWrapperRenderer.h"

#include "emstudio/gui/basetypes/IntWrapper.h"
#include "editors/IntWrapperEditor.h"
#include "renderers/IntWrapperRenderer.h"

#include "emstudio/gui/basetypes/LongWrapper.h"
#include "editors/LongWrapperEditor.h"
#include "renderers/LongWrapperRenderer.h"

#include "emstudio/gui/basetypes/ColourWrapper.h"
#include "editors/ColourWrapperEditor.h"
#include "renderers/ColourWrapperRenderer.h"

#include "emstudio/gui/basetypes/BoolWrapper.h"
#include "editors/BoolWrapperEditor.h"
#include "renderers/BoolWrapperRenderer.h"

#include "emstudio/gui/basetypes/StringWrapper.h"
#include "editors/StringWrapperEditor.h"
#include "renderers/StringWrapperRenderer.h"

#include "emstudio/gui/basetypes/Priority.h"
#include "editors/PriorityEditor.h"
#include "renderers/PriorityRenderer.h"

#include "emstudio/gui/basetypes/Point3D.h"
#include "editors/Point3DEditor.h"
#include "renderers/Point3DRenderer.h"

#include "emstudio/gui/basetypes/Point3DME.h"
#include "editors/Point3DMEEditor.h"
#include "renderers/Point3DMERenderer.h"

#include "emstudio/gui/basetypes/Sheet.h"
#include "editors/SheetEditor.h"
#include "renderers/SheetRenderer.h"

#include "emstudio/gui/basetypes/SheetME.h"
#include "editors/SheetMEEditor.h"
#include "renderers/SheetMERenderer.h"

#include "emstudio/gui/basetypes/GenericSheet.h"
#include "editors/GenericSheetEditor.h"
#include "renderers/GenericSheetRenderer.h"

#include "emstudio/gui/basetypes/GenericSheetME.h"
#include "editors/GenericSheetMEEditor.h"
#include "renderers/GenericSheetMERenderer.h"

#include "emstudio/gui/basetypes/DXFFile.h"
#include "editors/DXFFileEditor.h"

#include "emstudio/gui/basetypes/File.h"
#include "editors/FileEditor.h"
#include "renderers/FileRenderer.h"

#include "emstudio/gui/basetypes/MathExpressionParser.h"
#include "editors/MathExpressionParserEditor.h"
#include "renderers/MathExpressionParserRenderer.h"

#include "emstudio/gui/basetypes/IntMathExpressionParser.h"
#include "editors/IntMathExpressionParserEditor.h"
#include "renderers/IntMathExpressionParserRenderer.h"

#include "emstudio/gui/basetypes/RectangularTubeGeometryME.h"
#include "editors/RectangularTubeGeometryMEEditor.h"
#include "renderers/RectangularTubeGeometryMERenderer.h"

#include "renderers/SelectFieldRenderer.h"
#include "editors/SelectFieldEditor.h"
#include "emstudio/gui/basetypes/SelectField.h"

#include "renderers/MaterialRenderer.h"
#include "editors/MaterialEditor.h"
#include "emstudio/gui/basetypes/Material.h"

#include "renderers/DirectionPlaneWaveRenderer.h"
#include "editors/DirectionPlaneWaveEditor.h"
#include "emstudio/gui/basetypes/DirectionPlaneWave.h"

#include "renderers/DirectionPlaneWaveMERenderer.h"
#include "editors/DirectionPlaneWaveMEEditor.h"
#include "emstudio/gui/basetypes/DirectionPlaneWaveME.h"

#include "renderers/OrientationRenderer.h"
#include "editors/OrientationEditor.h"
#include "emstudio/gui/basetypes/Orientation.h"

#include "renderers/PlaneRenderer.h"
#include "editors/PlaneEditor.h"
#include "emstudio/gui/basetypes/Plane.h"

#include "renderers/ExcitationMERenderer.h"
#include "editors/ExcitationMEEditor.h"
#include "emstudio/gui/basetypes/ExcitationME.h"

#include "renderers/ABCRenderer.h"
#include "editors/ABCEditor.h"
#include "emstudio/gui/basetypes/AbsorvingBoundaryCondition.h"

#include "renderers/MatchWithPMLRenderer.h"
#include "editors/MatchWithPMLEditor.h"
#include "emstudio/gui/basetypes/MatchWithPML.h"

#include "renderers/MicrostripXYPortsMERenderer.h"
#include "editors/MicrostripXYPortsMEEditor.h"
#include "emstudio/gui/basetypes/MicrostripXYPortsME.h"

#include "emstudio/gui/basetypes/GroundParameters.h"
#include "editors/GroundParametersEditor.h"

RenderersAndEditorsManager::RenderersAndEditorsManager() {
	editorMap = EditorMap();
	rendererMap = RendererMap();

	Register((DoubleWrapper()).GetBaseTypeClassName(), wxGridCellEditorSmartPointer(new DoubleWrapperEditor), wxGridCellRendererSmartPointer(new DoubleWrapperRenderer));
	Register((FloatWrapper()).GetBaseTypeClassName(), wxGridCellEditorSmartPointer(new FloatWrapperEditor), wxGridCellRendererSmartPointer(new FloatWrapperRenderer));
	Register((IntWrapper()).GetBaseTypeClassName(), wxGridCellEditorSmartPointer(new IntWrapperEditor), wxGridCellRendererSmartPointer(new IntWrapperRenderer));
	Register((LongWrapper()).GetBaseTypeClassName(), wxGridCellEditorSmartPointer(new LongWrapperEditor), wxGridCellRendererSmartPointer(new LongWrapperRenderer));
	Register((ColourWrapper()).GetBaseTypeClassName(), wxGridCellEditorSmartPointer(new ColourWrapperEditor), wxGridCellRendererSmartPointer(new ColourWrapperRenderer));
	Register((BoolWrapper()).GetBaseTypeClassName(), wxGridCellEditorSmartPointer(new BoolWrapperEditor), wxGridCellRendererSmartPointer(new BoolWrapperRenderer));
	Register((StringWrapper()).GetBaseTypeClassName(), wxGridCellEditorSmartPointer(new StringWrapperEditor), wxGridCellRendererSmartPointer(new StringWrapperRenderer));
	Register((Priority()).GetBaseTypeClassName(), wxGridCellEditorSmartPointer(new PriorityEditor), wxGridCellRendererSmartPointer(new PriorityRenderer));
	Register((Point3D()).GetBaseTypeClassName(), wxGridCellEditorSmartPointer(new Point3DEditor), wxGridCellRendererSmartPointer(new Point3DRenderer));
	Register((Point3DME()).GetBaseTypeClassName(), wxGridCellEditorSmartPointer(new Point3DMEEditor), wxGridCellRendererSmartPointer(new Point3DMERenderer));
	Register((Sheet()).GetBaseTypeClassName(), wxGridCellEditorSmartPointer(new SheetEditor), wxGridCellRendererSmartPointer(new SheetRenderer));
	Register((SheetME()).GetBaseTypeClassName(), wxGridCellEditorSmartPointer(new SheetMEEditor), wxGridCellRendererSmartPointer(new SheetMERenderer));
	Register((RectangularTubeGeometryME()).GetBaseTypeClassName(), wxGridCellEditorSmartPointer(new RectangularTubeGeometryMEEditor), wxGridCellRendererSmartPointer(new RectangularTubeGeometryMERenderer));
	Register((GenericSheet()).GetBaseTypeClassName(), wxGridCellEditorSmartPointer(new GenericSheetEditor), wxGridCellRendererSmartPointer(new GenericSheetRenderer));
	Register((GenericSheetME()).GetBaseTypeClassName(), wxGridCellEditorSmartPointer(new GenericSheetMEEditor), wxGridCellRendererSmartPointer(new GenericSheetMERenderer));
	Register((File()).GetBaseTypeClassName(), wxGridCellEditorSmartPointer(new FileEditor), wxGridCellRendererSmartPointer(new FileRenderer));
	Register((DXFFile()).GetBaseTypeClassName(), wxGridCellEditorSmartPointer(new DXFFileEditor), wxGridCellRendererSmartPointer(new FileRenderer));
	Register((MathExpressionParser()).GetBaseTypeClassName(), wxGridCellEditorSmartPointer(new MathExpressionParserEditor), wxGridCellRendererSmartPointer(new MathExpressionParserRenderer));
	Register((IntMathExpressionParser()).GetBaseTypeClassName(), wxGridCellEditorSmartPointer(new IntMathExpressionParserEditor), wxGridCellRendererSmartPointer(new IntMathExpressionParserRenderer));
	Register((Material()).GetBaseTypeClassName(), wxGridCellEditorSmartPointer(new MaterialEditor(Material::GetMaterialLibrary())), wxGridCellRendererSmartPointer(new MaterialRenderer));
	Register((Orientation()).GetBaseTypeClassName(), wxGridCellEditorSmartPointer(new OrientationEditor), wxGridCellRendererSmartPointer(new OrientationRenderer));
	Register((Plane()).GetBaseTypeClassName(), wxGridCellEditorSmartPointer(new PlaneEditor), wxGridCellRendererSmartPointer(new PlaneRenderer));
	Register((ExcitationME()).GetBaseTypeClassName(), wxGridCellEditorSmartPointer(new ExcitationMEEditor), wxGridCellRendererSmartPointer(new ExcitationMERenderer));
	Register((AbsorvingBoundaryCondition()).GetBaseTypeClassName(), wxGridCellEditorSmartPointer(new ABCEditor), wxGridCellRendererSmartPointer(new ABCRenderer));
	Register((DirectionPlaneWave()).GetBaseTypeClassName(), wxGridCellEditorSmartPointer(new DirectionPlaneWaveEditor), wxGridCellRendererSmartPointer(new DirectionPlaneWaveRenderer));
	Register((DirectionPlaneWaveME()).GetBaseTypeClassName(), wxGridCellEditorSmartPointer(new DirectionPlaneWaveMEEditor), wxGridCellRendererSmartPointer(new DirectionPlaneWaveMERenderer));
	Register((MatchWithPML()).GetBaseTypeClassName(), wxGridCellEditorSmartPointer(new MatchWithPMLEditor), wxGridCellRendererSmartPointer(new MatchWithPMLRenderer));
	Register((SelectField()).GetBaseTypeClassName(), wxGridCellEditorSmartPointer(new SelectFieldEditor), wxGridCellRendererSmartPointer(new SelectFieldRenderer));
	Register((MicrostripXYPortsME()).GetBaseTypeClassName(), wxGridCellEditorSmartPointer(new MicrostripXYPortsMEEditor), wxGridCellRendererSmartPointer(new MicrostripXYPortsMERenderer));
	Register((mom::GroundParameters()).GetBaseTypeClassName(), wxGridCellEditorSmartPointer(new mom::GroundParametersEditor), wxGridCellRendererSmartPointer(new StringWrapperRenderer));
}

RenderersAndEditorsManager::~RenderersAndEditorsManager() {
	/*
	 * Esse era o código antes do uso de Smart Pointers.
	 * Achei que ele não funcionaria com wxGridCellEditor, pois seu destrutor é privado (deveria ser destruído usando DecRef().
	 * No entanto, o código com shared_ptr está funcionando
	 * */
//	RenderersAndEditorsManager::RendererMap::iterator rendererIterator = rendererMap.begin();
//	RenderersAndEditorsManager::EditorMap::iterator   editorIterator   = editorMap.begin();
//
//	while(rendererIterator != rendererMap.end()) {
//		wxString propertyType = rendererIterator->first;
//		wxGridCellRenderer* renderer = rendererIterator->second;
//		wxGridCellEditor* editor = editorIterator->second;
//
//		delete renderer;
//		editor->DecRef();
//		renderer = 0;
//		editor = 0;
//
//		rendererIterator++;
//		editorIterator++;
//	}

	rendererMap.clear();
	editorMap.clear();
}

void RenderersAndEditorsManager::Register(wxString baseTypeName, wxGridCellEditorSmartPointer editor, wxGridCellRendererSmartPointer renderer) {
	editorMap[baseTypeName] = editor;
	rendererMap[baseTypeName] = renderer;
}

RenderersAndEditorsManager::EditorMap& RenderersAndEditorsManager::GetEditorMap() {
	return editorMap;
}

RenderersAndEditorsManager::RendererMap& RenderersAndEditorsManager::GetRendererMap() {
	return rendererMap;
}
