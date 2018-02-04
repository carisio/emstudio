/*
 * renderesandeditors.h
 *
 *  Created on: 26/04/2014
 *      Author: Leandro
 */

#ifndef RENDERESANDEDITORS_H_
#define RENDERESANDEDITORS_H_

#include "emstudio/gui/framesandpanels/main/propertiesframe/BasicCopyPasteGrid.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/PropertiesGridTable.h"

#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/RenderersAndEditorsManager.h"

#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/ABCEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/BoolWrapperEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/ColourWrapperEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/DirectionPlaneWaveEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/DirectionPlaneWaveMEEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/DoubleWrapperEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/DXFFileEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/ExcitationMEEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/FileEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/FixedComboBoxEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/FloatWrapperEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/GenericSheetEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/GenericSheetMEEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/IntMathExpressionParserEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/IntWrapperEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/LongWrapperEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/MatchWithPMLEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/MaterialEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/MathExpressionParserEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/MicrostripXYPortsMEEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/OrientationEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/PlaneEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/Point3DEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/Point3DMEEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/PriorityEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/RectangularTubeGeometryMEEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/SelectFieldEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/SheetEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/SheetMEEditor.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/StringWrapperEditor.h"

#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/editorsframes/ABCFrame.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/editorsframes/DirectionPlaneWaveFrame.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/editorsframes/DirectionPlaneWaveMEFrame.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/editorsframes/ExcitationMEFrame.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/editorsframes/GenericSheetFrame.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/editorsframes/GenericSheetMEFrame.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/editorsframes/MatchWithPMLFrame.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/editorsframes/MicrostripXYPortsMEFrame.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/editorsframes/Point3DFrame.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/editorsframes/Point3DMEFrame.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/editorsframes/RectangularTubeGeometryMEFrame.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/editorsframes/SheetFrame.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/editors/editorsframes/SheetMEFrame.h"

#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/ABCRenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/BoolWrapperRenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/ColourWrapperRenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/DirectionPlaneWaveMERenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/DirectionPlaneWaveRenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/DoubleWrapperRenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/ExcitationMERenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/FileRenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/FloatWrapperRenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/GenericSheetMERenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/GenericSheetRenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/IntMathExpressionParserRenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/IntWrapperRenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/LongWrapperRenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/MatchWithPMLRenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/MaterialRenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/MathExpressionParserRenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/MicrostripXYPortsMERenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/OrientationRenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/PlaneRenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/Point3DMERenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/Point3DRenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/PriorityRenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/RectangularTubeGeometryMERenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/SelectFieldRenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/SheetMERenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/SheetRenderer.h"
#include "emstudio/gui/framesandpanels/main/propertiesframe/renderesandeditors/renderers/StringWrapperRenderer.h"



#endif /* RENDERESANDEDITORS_H_ */
