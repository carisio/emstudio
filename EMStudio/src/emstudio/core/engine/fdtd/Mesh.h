#ifndef MESH_H_
#define MESH_H_

#include "Grid.h"

#include "emstudio/util/tnt/tnt.h"
#include "emstudio/util/facet/Facet.h"
#include "emstudio/util/vector/Rvector3.h"
#include "emstudio/util/line/Line.h"

#include "emstudio/gui/basetypes/Material.h"

#include "MaterialCoefficients.h"
#include <vector>

using namespace TNT;

class Engine;

class Mesh {
private:
	std::vector<ElementsWithFacetsDTO*> objectsWithFacets;
	Grid grid;

	Array1D<Material> materialLookUpTable;

	int Nx, Ny, Nz;
	double dt;

	Array3D<int> indexMatrix;
	std::vector<MaterialCoefficients> lookupTable;

	/* Pesquisa pelo Material m na variável lookuptable.
	 * Se não existir, cria um novo material na lista.
	 * A pesquisa é feita pelo nome do material.
	 *
	 * Retorna o índice que o material ocupa em lookuptable
	 */
	int GetMaterialIndexInLookupTable(Material& m);
	bool IsInside(Line& ray, std::vector<Line>& polygon);
	void SmoothMesh(Engine* engine);
public:
//	Mesh();
	Mesh(std::vector<ElementsWithFacetsDTO*> objectsWithFacets, Grid& g, double dt);
	virtual ~Mesh();

    void Generate(Engine* engine, bool smoothMesh = true);

    void SaveMeshXZToFile(int yCell);
    void SaveMeshXYToFile(int zCell);
    void SaveMeshYZToFile(int xCell);
    const MaterialCoefficients& GetCoefficients(int i, int j, int k) const;
    void SetMaterial(int i, int j, int k, Material m);
};

#endif /* MESH_H_ */
