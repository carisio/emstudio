///////////////////////////////////////////////////////////////////////////////
//// Name:        dxfrenderer.h
//// Purpose:     DXF reader and renderer
//// Author:      Sandro Sigala
//// Modified by:
//// Created:     2005-11-10
//// RCS-ID:      $Id: dxfrenderer.h 36174 2005-11-14 17:38:24Z JS $
//// Copyright:   (c) Sandro Sigala
//// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////
//
//#ifndef _DXFRENDERER_H_
//#define _DXFRENDERER_H_
//
//#include "util/vector/Rvector3.h"
//#include "util/facet/Facet.h"
//#include "util/line/Line.h"
//#include <vector>
//using namespace::std;
//
//struct DXFEntity
//{
//    enum Type { Line, Face } type;
//    int colour;
//};
//
//struct DXFLine: public DXFEntity
//{
//    DXFLine() { type = Line; }
//    Rvector3 v0;
//    Rvector3 v1;
//};
//
//struct DXFFace: public DXFEntity
//{
//    DXFFace() { type = Face; }
//    void CalculateNormal();
//    Rvector3 v0;
//    Rvector3 v1;
//    Rvector3 v2;
//    Rvector3 v3;
//    Rvector3 n;       // normal
//};
//
//struct DXFLayer
//{
//    DXFLayer() { colour = -1; }
//    wxString name;
//    int colour;
//};
//
//WX_DECLARE_LIST(DXFEntity, DXFEntityList);
//WX_DECLARE_LIST(DXFLayer, DXFLayerList);
//
//class DXFRenderer
//{
//public:
//    DXFRenderer();
//    ~DXFRenderer();
//
//    void Clear();
//    bool Load(wxString contents);
//    bool IsOk() const { return m_loaded; }
//    void Render(bool fill) const;
//    wxString GetContents() {return contents; }
//    vector<Facet> GetFacets() {return facets; }
//    void Translate(double x, double y, double z) {tx = x; ty = y; tz = z;}
//    void Rotate(double x, double y, double z) {rx = x; ry = y; rz = z;}
//private:
//    bool ParseHeader(wxStringTokenizer& tokens);
//    bool ParseTables(wxStringTokenizer& tokens);
//    bool ParseEntities(wxStringTokenizer& tokens);
//    int GetLayerColour(const wxString& layer) const;
//    void NormalizeEntities();
//
//    bool m_loaded;
//    DXFLayerList m_layers;
//    DXFEntityList m_entities;
//
//    // Guarda o conteúdo do arquivo DXF que foi lido
//    wxString contents;
//    // Guarda os mesmos objetos mas do tipo Facet
//    vector<Facet> facets;
//    // Dados para translação
//    double tx, ty, tz;
//    // Dados para rotação
//    double rx, ry, rz;
//};
//
//#endif // !_DXFRENDERER_H_
//
//
