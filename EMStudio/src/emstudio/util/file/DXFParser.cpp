/////////////////////////////////////////////////////////////////////////////
// Name:        DXFParser.cpp
// Purpose:     DXF reader and renderer
// Author:      Sandro Sigala
// Modified by:
// Created:     2005-11-10
// RCS-ID:      $Id: DXFParser.cpp 51630 2008-02-10 13:26:01Z VZ $
// Copyright:   (c) Sandro Sigala
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"
#include "wx/tokenzr.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/wfstream.h"
#include "wx/txtstrm.h"

#if !wxUSE_GLCANVAS
    #error "OpenGL required: set wxUSE_GLCANVAS to 1 and rebuild the library"
#endif

#ifdef __DARWIN__
    #include "OpenGL/glu.h"
#else
    #include <GL/glu.h>
#endif

#include "wx/glcanvas.h"

#include <sstream>

#include "DXFParser.h"

#include "wx/listimpl.cpp"
WX_DEFINE_LIST(DXFEntityList)
WX_DEFINE_LIST(DXFLayerList)

#include "emstudio/util/file/FileManager.h"
#include "emstudio/util/constants/Constants.h"
#include "emstudio/util/time/TicTac.h"
#include <iostream>
using namespace::std;

void DXFFace::CalculateNormal()
{
    Rvector3 v01, v02;
    v01.X = v0.X - v1.X;
    v01.Y = v0.Y - v1.Y;
    v01.Z = v0.Z - v1.Z;
    v02.X = v0.X - v2.X;
    v02.Y = v0.Y - v2.Y;
    v02.Z = v0.Z - v2.Z;
    n = CrossProduct(v01, v02);
    float mod = sqrt(n.X*n.X + n.Y*n.Y + n.Z*n.Z);
    n.X /= mod;
    n.Y /= mod;
    n.Z /= mod;
}


// DXFReader constructor
DXFParser::DXFParser()
{
    m_loaded = false;
}

// DXFReader destructor
DXFParser::~DXFParser()
{
    Clear();
}

// deallocate all the dynamic data
void DXFParser::ClearLayerList() {
    for (DXFLayerList::compatibility_iterator node = m_layers.GetFirst(); node; node = node->GetNext())
    {
        DXFLayer *current = node->GetData();
        delete current;
    }
    m_layers.Clear();
}
void DXFParser::ClearEntityList() {
	for (DXFEntityList::compatibility_iterator node = m_entities.GetFirst(); node; node = node->GetNext())
	{
		DXFEntity *current = node->GetData();
		delete current;
	}
	m_entities.Clear();
}
void DXFParser::Clear()
{
    m_loaded = false;
    ClearLayerList();
    ClearEntityList();
}

int DXFParser::GetLayerColour(const wxString& layer) const
{
    for (DXFLayerList::compatibility_iterator node = m_layers.GetFirst(); node; node = node->GetNext())
    {
        DXFLayer *current = node->GetData();
        if (current->name == layer)
            return current->colour;
    }
    return 7;   // white
}

// read two sequential lines
inline void GetLines(wxStringTokenizer& tokens, wxString& line1, wxString& line2)
{
    line1 = tokens.NextToken().Trim().Trim(false);
    line2 = tokens.NextToken().Trim().Trim(false);
}


// parse header section: just skip everything
bool DXFParser::ParseHeader(wxStringTokenizer& tokens)
{
    wxString line1, line2;
    while (tokens.HasMoreTokens())
    {
        GetLines(tokens, line1, line2);
        if (line1 == wxT("0") && line2 == wxT("ENDSEC"))
            return true;
    }
    return false;
}

// parse tables section: save layers name and colour
bool DXFParser::ParseTables(wxStringTokenizer& tokens)
{
    wxString line1, line2;
    bool inlayer=false;
    DXFLayer layer;
    while (tokens.HasMoreTokens())
    {
        GetLines(tokens, line1, line2);
        if (line1 == wxT("0") && inlayer)
        {
            // flush layer
            if (!layer.name.IsEmpty() && layer.colour != -1)
            {
                DXFLayer *p = new DXFLayer;
                p->name = layer.name;
                p->colour = layer.colour;
                m_layers.Append(p);
            }
            layer = DXFLayer();
            inlayer = false;
        }
        if (line1 == wxT("0") && line2 == wxT("ENDSEC"))
            return true;
        else if (line1 == wxT("0") && line2 == wxT("LAYER"))
            inlayer = true;
        else if (inlayer)
        {
            if (line1 == wxT("2")) // layer name
                layer.name = line2;
            else if (line1 == wxT("62")) // ACI colour
            {
                long l;
                line2.ToLong(&l);
                layer.colour = l;
            }
        }
    }
    return false;
}

// This method is used instead of numStr.ToDouble(d) because the latter
// (wxString::ToDouble()) takes the systems proper locale into account,
// whereas the implementation below works with the default locale.
// (Converting numbers that are formatted in the default locale can fail
//  with system locales that use e.g. the comma as the decimal separator.)
static double ToDouble(const wxString& numStr)
{
	double d;
	numStr.ToCDouble(&d);
	return d;
//    double             d;
//    std::string        numStr_(numStr.c_str());
//    std::istringstream iss(numStr_);
//
//    iss >> d;
//
//    return d;
}

// parse entities section: save 3DFACE and LINE entities
bool DXFParser::ParseEntities(wxStringTokenizer& tokens)
{
    wxString line1, line2;
    int state = 0;  // 0: none, 1: 3DFACE, 2: LINE
    Rvector3 v[4];
    int colour = -1;
    wxString layer;
    while (tokens.HasMoreTokens())
    {
        GetLines(tokens, line1, line2);
        if (line1 == wxT("0") && state > 0)
        {
            // flush entity
            if (state == 1) // 3DFACE
            {
                DXFFace *p = new DXFFace;
                p->v0 = v[0];
                p->v1 = v[1];
                p->v2 = v[2];
                p->v3 = v[3];
                p->CalculateNormal();
                if (colour != -1)
                    p->colour = colour;
                else
                    p->colour = GetLayerColour(layer);
                m_entities.Append(p);
                colour = -1; layer = wxEmptyString;
                v[0] = v[1] = v[2] = v[3] = Rvector3();
                state = 0;
            }
            /*else if (state == 2) // LINE
            {
                DXFLine *p = new DXFLine;
                p->v0 = v[0];
                p->v1 = v[1];
                if (colour != -1)
                    p->colour = colour;
                else
                    p->colour = GetLayerColour(layer);
                m_entities.Append(p);
                colour = -1; layer = wxEmptyString;
                v[0] = v[1] = v[2] = v[3] = Rvector3();
                state = 0;
            }*/
        }
        if (line1 == wxT("0") && line2 == wxT("ENDSEC"))
            return true;
        else if (line1 == wxT("0") && line2 == wxT("3DFACE"))
            state = 1;
        else if (line1 == wxT("0") && line2 == wxT("LINE"))
            state = 2;
        else if (state > 0)
        {
            const double d=ToDouble(line2);

            if (line1 == wxT("10"))
                v[0].X = d;
            else if (line1 == wxT("20"))
                v[0].Y = d;
            else if (line1 == wxT("30"))
                v[0].Z = d;
            else if (line1 == wxT("11"))
                v[1].X = d;
            else if (line1 == wxT("21"))
                v[1].Y = d;
            else if (line1 == wxT("31"))
                v[1].Z = d;
            else if (line1 == wxT("12"))
                v[2].X = d;
            else if (line1 == wxT("22"))
                v[2].Y = d;
            else if (line1 == wxT("32"))
                v[2].Z = d;
            else if (line1 == wxT("13"))
                v[3].X = d;
            else if (line1 == wxT("23"))
                v[3].Y = d;
            else if (line1 == wxT("33"))
                v[3].Z = d;
            else if (line1 == wxT("8"))  // layer
                layer = line2;
            else if (line1 == wxT("62")) // colour
            {
                long l;
                line2.ToLong(&l);
                colour = l;
            }
        }
    }
    return false;
}

// parse and load a DXF file
// currently pretty limited, but knows enought do handle 3DFACEs and LINEs
bool DXFParser::Load(wxString fileName)
{
	TicTac t;
	t.Tic("DXFParser::Load");

	wxString contents;
	bool openOK = FileManager::OpenFile(fileName, contents);
	if (!openOK) return false;

	Clear();
	wxStringTokenizer tokens(contents, "\n");

	wxString line1, line2;
	while (tokens.HasMoreTokens())
	{
		GetLines(tokens, line1, line2);
		if (line1 == wxT("999")) // comment
			continue;
		else if (line1 == wxT("0") && line2 == wxT("SECTION"))
		{
			GetLines(tokens, line1, line2);
			if (line1 == wxT("2"))
			{
				if (line2 == wxT("HEADER"))
				{
					ParseHeader(tokens);
//                    if (!ParseHeader(tokens))
//                        return false;
				}
				else if (line2 == wxT("TABLES"))
				{
					ParseTables(tokens);
//                    if (!ParseTables(tokens))
//                        return false;
				}
				else if (line2 == wxT("ENTITIES"))
				{
					ParseEntities(tokens);
//                    if (!ParseEntities(tokens))
//                        return false;
				}
			}
		}
	}

//    NormalizeEntities();
    m_loaded = true;

    ConvertToFacets();
    t.Tac();
    return true;
}

inline float mymin(float x, float y) { return x < y ? x : y; }
inline float mymax(float x, float y) { return x > y ? x : y; }

/* Rotate aqui é passado em graus */
void DXFParser::Transform(bool normalize, double rotX, double rotY, double rotZ, double transX, double transY, double transZ, double scale) {
	TicTac t;
	t.Tic("Transform");
    // calculate current min and max boundings of object
    Rvector3 minv(10e20f, 10e20f, 10e20f);
    Rvector3 maxv(-10e20f, -10e20f, -10e20f);
    for (DXFEntityList::compatibility_iterator node = m_entities.GetFirst(); node; node = node->GetNext())
    {
        DXFEntity *p = node->GetData();
        /*
        if (p->type == DXFEntity::Line)
        {
            DXFLine *line = (DXFLine *)p;
            const Rvector3 *v[2] = { &line->v0, &line->v1 };
            for (int i = 0; i < 2; ++i)
            {
                minv.X = mymin(v[i]->X, minv.X);
                minv.Y = mymin(v[i]->Y, minv.Y);
                minv.Z = mymin(v[i]->Z, minv.Z);
                maxv.X = mymax(v[i]->X, maxv.X);
                maxv.Y = mymax(v[i]->Y, maxv.Y);
                maxv.Z = mymax(v[i]->Z, maxv.Z);
            }
        } else */if (p->type == DXFEntity::Face)
        {
            DXFFace *face = (DXFFace *)p;
            const Rvector3 *v[4] = { &face->v0, &face->v1, &face->v2, &face->v3 };
            for (int i = 0; i < 4; ++i)
            {
                minv.X = mymin(v[i]->X, minv.X);
                minv.Y = mymin(v[i]->Y, minv.Y);
                minv.Z = mymin(v[i]->Z, minv.Z);
                maxv.X = mymax(v[i]->X, maxv.X);
                maxv.Y = mymax(v[i]->Y, maxv.Y);
                maxv.Z = mymax(v[i]->Z, maxv.Z);
            }
       }
    }

    /* Fator de normalização */
    Rvector3 span(maxv.X - minv.X, maxv.Y - minv.Y, maxv.Z - minv.Z);
    bool rotate = (rotX != 0 || rotY != 0 || rotZ != 0);

    float normalizeFactor = mymin(mymin(1.0f / span.X, 1.0f / span.Y), 1.0f / span.Z);
    if (!normalize) normalizeFactor = 1.0f;

    /* Calcula novo span, considerando a normalização */
    Rvector3 newspan(span.X*normalizeFactor, span.Y*normalizeFactor, span.Z*normalizeFactor);

    /* Faz a normalização e a translação */
    for (DXFEntityList::compatibility_iterator node2 = m_entities.GetFirst(); node2; node2 = node2->GetNext())
    {
        DXFEntity *p = node2->GetData();
        /*if (p->type == DXFEntity::Line)
        {
            DXFLine *line = (DXFLine *)p;
            Rvector3 *v[2] = { &line->v0, &line->v1 };
            for (int i = 0; i < 2; ++i)
            {
            	// Joga o centro para o ponto (0,0,0) e rotaciona
				if (rotate) {
					v[i]->X -= minv.X + span.X/2;
					v[i]->Y -= minv.Y + span.Y/2;
					v[i]->Z -= minv.Z + span.Z/2;
					v[i]->Rotate(Rvector3(0,0,0), rotX*PI/180, rotY*PI/180, rotZ*PI/180);
					// Volta para o ponto que estava
					v[i]->X += minv.X + span.X/2;
					v[i]->Y += minv.Y + span.Y/2;
					v[i]->Z += minv.Z + span.Z/2;
				}

				// Normalize
				if (normalize) {
					v[i]->X -= minv.X; v[i]->X *= normalizeFactor;
					v[i]->Y -= minv.Y; v[i]->Y *= normalizeFactor;
					v[i]->Z -= minv.Z; v[i]->Z *= normalizeFactor;
				}

				// Scale
				if (normalize) {
					v[i]->X -= newspan.X/2; v[i]->X *= scale;
					v[i]->Y -= newspan.Y/2; v[i]->Y *= scale;
					v[i]->Z -= newspan.Z/2; v[i]->Z *= scale;
					v[i]->X += scale*newspan.X/2;
					v[i]->Y += scale*newspan.Y/2;
					v[i]->Z += scale*newspan.Z/2;
				} else {
					v[i]->X -= minv.X + span.X/2; v[i]->X *= scale;
					v[i]->Y -= minv.Y + span.Y/2; v[i]->Y *= scale;
					v[i]->Z -= minv.Z + span.Z/2; v[i]->Z *= scale;
					v[i]->X += scale*newspan.X/2;
					v[i]->Y += scale*newspan.Y/2;
					v[i]->Z += scale*newspan.Z/2;
				}

				v[i]->X += transX;
				v[i]->Y += transY;
				v[i]->Z += transZ;
            }
        } else */if (p->type == DXFEntity::Face)
        {
            DXFFace *face = (DXFFace *)p;
            Rvector3 *v[4] = { &face->v0, &face->v1, &face->v2, &face->v3 };
            for (int i = 0; i < 4; ++i)
            {
            	/* Joga o centro para o ponto (0,0,0) e rotaciona */
            	if (rotate) {
					v[i]->X -= minv.X + span.X/2;
					v[i]->Y -= minv.Y + span.Y/2;
					v[i]->Z -= minv.Z + span.Z/2;
					v[i]->Rotate(Rvector3(0,0,0), rotX*PI/180, rotY*PI/180, rotZ*PI/180);
//				   if (rotX != 0)
//					   v[i]->Rotate(Rvector3(0,0,0), rotX*PI/180,0,0);
//				   if (rotY != 0)
//					   v[i]->Rotate(Rvector3(0,0,0), 0,rotY*PI/180,0);
//				   if (rotZ != 0)
//					   v[i]->Rotate(Rvector3(0,0,0), 0,0,rotZ*PI/180);
					/* Volta para o ponto que estava*/
					v[i]->X += minv.X + span.X/2;
					v[i]->Y += minv.Y + span.Y/2;
					v[i]->Z += minv.Z + span.Z/2;
            	}

            	/* Normalize */
            	if (normalize) {
            		v[i]->X -= minv.X; v[i]->X *= normalizeFactor;
					v[i]->Y -= minv.Y; v[i]->Y *= normalizeFactor;
					v[i]->Z -= minv.Z; v[i]->Z *= normalizeFactor;
            	}

            	/* Scale */
            	if (normalize) {
					v[i]->X -= newspan.X/2; v[i]->X *= scale;
					v[i]->Y -= newspan.Y/2; v[i]->Y *= scale;
					v[i]->Z -= newspan.Z/2; v[i]->Z *= scale;
					v[i]->X += scale*newspan.X/2;
					v[i]->Y += scale*newspan.Y/2;
					v[i]->Z += scale*newspan.Z/2;
            	} else {
					v[i]->X -= minv.X + span.X/2; v[i]->X *= scale;
					v[i]->Y -= minv.Y + span.Y/2; v[i]->Y *= scale;
					v[i]->Z -= minv.Z + span.Z/2; v[i]->Z *= scale;
					v[i]->X += scale*newspan.X/2;
					v[i]->Y += scale*newspan.Y/2;
					v[i]->Z += scale*newspan.Z/2;
            	}

                v[i]->X += transX;
                v[i]->Y += transY;
                v[i]->Z += transZ;

//                if (rotate) {
//                	v[i]->X -= center.X;
//                	v[i]->Y -= center.Y;
//                	v[i]->Z -= center.Z;
//
//                	v[i]->X += center.X;
//					v[i]->Y += center.Y;
//					v[i]->Z += center.Z;
//				}
            }
       }
    }

//    /* Faz a rotação */
//    bool rotate = (rotX != 0 || rotY != 0 || rotZ != 0);
//    if (rotate) {
//    	for (DXFEntityList::compatibility_iterator node2 = m_entities.GetFirst(); node2; node2 = node2->GetNext())
//    	    {
//    	        DXFEntity *p = node2->GetData();
//    	        if (p->type == DXFEntity::Line)
//    	        {
//    	            DXFLine *line = (DXFLine *)p;
//    	            Rvector3 *v[2] = { &line->v0, &line->v1 };
//    	            for (int i = 0; i < 2; ++i)
//    	            {
//    	            	/* Normalize */
//    	            	if (normalize) {
//    	            		v[i]->X -= minv.X; v[i]->X *= normalizeFactor;
//    						v[i]->Y -= minv.Y; v[i]->Y *= normalizeFactor;
//    						v[i]->Z -= minv.Z; v[i]->Z *= normalizeFactor;
//    	            	}
//    	            	// Translate
//    	                v[i]->X += transX;
//    	                v[i]->Y += transY;
//    	                v[i]->Z += transZ;
//
//    	                // Scale
//    	                v[i]->X *= scale;
//    	                v[i]->Y *= scale;
//    	                v[i]->Z *= scale;
//    	            }
//    	        } else if (p->type == DXFEntity::Face)
//    	        {
//    	            DXFFace *face = (DXFFace *)p;
//    	            Rvector3 *v[4] = { &face->v0, &face->v1, &face->v2, &face->v3 };
//    	            for (int i = 0; i < 4; ++i)
//    	            {
//    	            	/* Normalize */
//    	            	if (normalize) {
//    	            		v[i]->X -= minv.X; v[i]->X *= normalizeFactor;
//    						v[i]->Y -= minv.Y; v[i]->Y *= normalizeFactor;
//    						v[i]->Z -= minv.Z; v[i]->Z *= normalizeFactor;
//    	            	}
//    	                v[i]->X += transX;
//    	                v[i]->Y += transY;
//    	                v[i]->Z += transZ;
//
//    	                v[i]->X *= scale;
//    	                v[i]->Y *= scale;
//    	                v[i]->Z *= scale;
//    	            }
//    	       }
//    	    }
//    }
    ConvertToFacets();
    t.Tac();
}

void DXFParser::SetEntityList(DXFEntityList& list) {
	ClearEntityList();
	m_entities = list;
}
void DXFParser::SetLayerList(DXFLayerList& list) {
	ClearLayerList();
	m_layers = list;
}
DXFEntityList& DXFParser::GetDXFEntityList() {
	return m_entities;
}
DXFLayerList& DXFParser::GetLayerList() {
	return m_layers;
}
void DXFParser::ConvertToFacets() {
	facets.clear();
    // Copia para os objetos do tipo facet
    for (DXFEntityList::compatibility_iterator node = m_entities.GetFirst(); node; node = node->GetNext())
    {
        DXFEntity *p = node->GetData();
        if (p->type == DXFEntity::Face)
        {
            DXFFace *face = (DXFFace *)p;

            Facet f;
            f.Add(Rvector3(face->v0.X, face->v0.Y, face->v0.Z));
            f.Add(Rvector3(face->v1.X, face->v1.Y, face->v1.Z));
            f.Add(Rvector3(face->v2.X, face->v2.Y, face->v2.Z));

            facets.push_back(f);
        }
    }
}

DXFParser& DXFParser::operator=(DXFParser& other) {
	if (this == &other)
		return *this;

	// Copia a lista de layers
	DXFLayerList originalLyerList = other.GetLayerList();
	DXFLayerList layerList;
	for (DXFLayerList::compatibility_iterator node = originalLyerList.GetFirst(); node; node = node->GetNext()) {
		DXFLayer *p = node->GetData();
		DXFLayer *copiedNode = new DXFLayer;

		*copiedNode = *p;
		layerList.Append(copiedNode);
	}

	DXFEntityList originalEntityList = other.GetDXFEntityList();
	DXFEntityList entityList;
	for (DXFEntityList::compatibility_iterator node = originalEntityList.GetFirst(); node; node = node->GetNext())
	{
		DXFEntity *p = node->GetData();
		/*if (p->type == DXFEntity::Line) {
			DXFLine *line = (DXFLine *)p;
			DXFLine *newLine = new DXFLine;

			*newLine = *line;
			entityList.Append(newLine);
		} else */if (p->type == DXFEntity::Face) {
			DXFFace *face = (DXFFace *)p;
			DXFFace *newFace = new DXFFace;

			*newFace = *face;
			entityList.Append(newFace);
		}
	}

	SetEntityList(entityList);
	SetLayerList(layerList);

	return *this;
}
