/*
 * Mesh.cpp
 *
 *  Created on: 01/08/2011
 *      Author: Martins
 */

#include "Mesh.h"
#include "wx/wx.h"
#include "emstudio/util/file/FileManager.h"
#include "emstudio/util/converters/Converter.h"
#include "emstudio/core/Engine.h"
#include "FDTDEngine.h"
#include "emstudio/util/time/TicTac.h"
#include "wx/log.h"

//Mesh::Mesh() {
//
//}

Mesh::Mesh(std::vector<ElementsWithFacetsDTO*> objectsWithFacets, Grid& g, double deltaT)
		: objectsWithFacets(objectsWithFacets), grid(g), dt(deltaT) {
	cout << "Mesh: " << endl;
	Nx = g.GetNxTOTAL();
	Ny = g.GetNyTOTAL();
	Nz = g.GetNzTOTAL();
	cout << "Nx: " << Nx << endl;
	cout << "Ny: " << Ny << endl;
	cout << "Nz: " << Nz << endl;
	/* Insere espaço livre na posição 0 da lookuptable. */
	Material ar;
	int index = GetMaterialIndexInLookupTable(ar);
//	cout << "Criou matriz de materiais" << endl;
	/* Inicializa a matriz de índices com espaço livre (0) */
	indexMatrix = Array3D<int>(Nx,Ny,Nz,index);
//	cout << "Conseguiu iniciarlizar array com índices. Saindo do construtor de Mesh" << endl;
	/* Para gerar a malha é necessário chamar o Generate() */
}

Mesh::~Mesh() {

}

int Mesh::GetMaterialIndexInLookupTable(Material& m) {
	int index = -1;

//	cout << "Procurando " << m.GetDescription() << " em lookupTable " << endl;
	for (size_t i = 0; i < lookupTable.size(); i++) {
//		cout << "\tlookupTable[" << i << "].GetName() == " << lookupTable[i].GetName() << endl;
//		if (lookupTable[i].GetName() == m.GetDescription()) {
		if (lookupTable[i].GetMaterial().Equals(m)) {
			index = i;
//			cout << "\tEncontrou o material. Retornando o índice " << index << endl;
			break;
		}
	}
//	cout << "\tMaterial não existe. Inserindo na lookupTable..." << endl;
	if (index == -1) {
		index = lookupTable.size();
		lookupTable.push_back(MaterialCoefficients(m, dt));
	}
//	cout << "\tMaterial inserido na posição " << index << " => " << lookupTable[index].GetName() << lookupTable[index].GetMaterial().GetEx() << endl;

	return index;
}
// Recebe a engine como parâmetro apenas para informar status da geração da malha
void Mesh::Generate(Engine* engine, bool smoothMesh) {
//	TicTac medeTempoGerarMalha;
//	medeTempoGerarMalha.Tic("Mesh::Generate");
//	cout << "Gerando a malha" << endl;
	Facet facet;
	Rvector3 v1,v2;
	Line line;
	Line ray;

	indexMatrix = Array3D<int>(Nx,Ny,Nz,0);

	double X,Y,Z;
	int i,j,k;

	cout << "Grid.GetAccumulatedDx() e GetDx()  " << endl;
	for (int i = 0; i < grid.GetNxTOTAL(); i++) {
		cout << "\t" << grid.GetAccumulatedDx(i) << "\t" << grid.GetDx(i) << endl;
	}
	cout << "FIM Grid.GetAccumulatedDx()" << endl;

	std::vector<Line> polygon;
	// Faz a varredura dos objetos em fatias ao longo do plano Z
	wxString status = "Generating mesh (";
	size_t ob = 0;
	size_t facetNum = 0;
	for (k = 0; k < Nz; k++) {
	   double stepPercentage = ((double)k)/((double)Nz) * 100;
	   bool continuar = engine->InformStatus(status + Converter::DoubleToFormattedString(stepPercentage, 0) + "%)");
	   if (!continuar) return;

		Z = grid.GetAccumulatedDz(k) + grid.GetDz(k)/2;
//		cout << "Observando z = " << Z << endl;

//		cout << "objectsWithFacets.size() = " << objectsWithFacets.size() << endl;
		for(ob = 0; ob < objectsWithFacets.size(); ob++) {
//			cout << "Verificando as faces do objeto " << objectsWithFacets[ob]->GetName() << endl;
			std::vector<Facet> facetsOfAnObject = objectsWithFacets[ob]->GetFacets();
//			cout << "No total sao " << objectsWithFacets[ob]->GetFacets().size() << " faces" << endl;

			polygon.clear();
			for(facetNum = 0; facetNum < facetsOfAnObject.size(); facetNum++) {
//				cout << "Verificando face #" << facetNum << endl;
				facet = facetsOfAnObject[facetNum];

				std::vector<Rvector3> vertices = facet.GetVertex();

//				cout << "\tDados da face: " << endl;
//				for (size_t t = 0; t < vertices.size(); t++)
//					cout << "\t\tVértices: (x, y, z) = (" << vertices[t].X << ", " <<  vertices[t].Y << ", " << vertices[t].Z << ")" << endl;
//
//				cout << "Verificando plano de corte em Z = " << Z << endl;
				if (facet.IsFaceCrossXYPlaneAt(Z)) {
//					cout << "\t\tEm Z = " << Z << " ha cruzamento com a face " << endl;
					facet.GetCrossLineXYPlane(Z, v1, v2);
//					cout << "\t\tLinha de cruzamento: " << endl;
//					cout << "\t\t\tDe (x, y, z) = ( " << v1.X << ", " <<  v1.Y << ", " << v1.Z << ") ate (" << v2.X << ", " <<  v2.Y << ", " << v2.Z << ")" << endl;
					line = Line(v1, v2);
					polygon.push_back(line);
				}
			}

//			if (polygon.size() != 0) {
//				cout << "\t\t\tTamanho do polígono é diferente de 0. Coordenadas do polígono para Z = " << Z << ": " << endl;
//				for (size_t lixo = 0; lixo < polygon.size(); lixo++) {
//					Rvector3 v1 = polygon[lixo].P1;
//					Rvector3 v2 = polygon[lixo].P2;
//					cout << "\t\t\t\tDe (x, y, z) = ( " << v1.X << ", " <<  v1.Y << ", " << v1.Z << ") ate (" << v2.X << ", " <<  v2.Y << ", " << v2.Z << ")" << endl;
//				}
//			}

			// Agora determina quem esta dentro e quem está fora do objeto
			for(i = 0; i < Nx; i++){
				X = grid.GetAccumulatedDx(i) + grid.GetDx(i)/2;

				for(j = 0; j < Ny; j++){
					Y = grid.GetAccumulatedDy(j) + grid.GetDy(j)/2;

					// Original:
					// ray.P1.X = grid.GetAccumulatedDx(0) - 1e-10;
					ray.P1.X = grid.GetAccumulatedDx(0) - 1e-10;
					ray.P1.Y = Y;
					ray.P1.Z = Z;
					ray.P2.X = X;
					ray.P2.Y = Y;
					ray.P2.Z = Z;

					/*Esse código é somente para fazer um teste olhando em Y = 0.225 */
//					double YMin = 0.225*0.9999; double YMax = 0.225*1.0001;
//					if (YMin < Y && Y < YMax){
//						cout << "**************" << endl;
//						cout << "X, Y = "<< X << ", " << Y << endl;
//						cout << "ray.P1.X " << ray.P1.X << endl;
//						cout << "ray.P1.Y " << ray.P1.Y << endl;
//						cout << "ray.P1.Z " << ray.P1.Z << endl;
//						cout << "ray.P2.X " << ray.P2.X << endl;
//						cout << "ray.P2.Y " << ray.P2.Y << endl;
//						cout << "ray.P2.Z " << ray.P2.Z << endl;
//
//						for (size_t lixo = 0; lixo < polygon.size(); lixo++) {
//							Rvector3 v1 = polygon[lixo].P1;
//							Rvector3 v2 = polygon[lixo].P2;
//							cout << "\t\t\t\tDe (x, y, z) = ( " << v1.X << ", " <<  v1.Y << ", " << v1.Z << ") ate (" << v2.X << ", " <<  v2.Y << ", " << v2.Z << ")" << endl;
//						}
//						cout << "**************" << endl;
//					}

					if (IsInside(ray, polygon)) {
//						cout << "IsInside(ray, polygon) = true para (X,Y) = " << X << ", " << Y << endl;
						SetMaterial(i, j, k, objectsWithFacets[ob]->GetMaterial());
					}
//					else {
//						cout << "IsInside(ray, polygon) = false para (X,Y) = " << X << ", " << Y << endl;
//					}
				}
			}
		}
	}

	//------------------------------------------------------------------------
	// Inserido este código
	FDTDEngine* fdtdEngine = static_cast<FDTDEngine*>(engine);
	if (fdtdEngine->GetFDTDDTO().GetABC().IsPeriodic(zPos)) {
		for(i = 0; i < Nx; i++)
			for(j = 0; j < Ny; j++)
				indexMatrix[i][j][Nz-1] = indexMatrix[i][j][Nz-2];
	}

	/*
	for(i = 0; i < Nx; i++)
		for(k = 0; k < Nz; k++)
			indexMatrix[i][Ny-1][k] = indexMatrix[i][Ny-2][k];
	*/
	if (fdtdEngine->GetFDTDDTO().GetABC().IsPeriodic(xPos)) {
		for(j = 0; j < Ny; j++)
			for(k = 0; k < Nz; k++)
				indexMatrix[Nx-1][j][k] = indexMatrix[Nx-2][j][k];
	}
//---------------------------------------------------------------
	engine->InformStatus("");
	cout << "SmoothMesh: " << smoothMesh << endl;
	if (smoothMesh) {
		SmoothMesh(engine);
	}

//	SaveMeshXYToFile(0);
//	SaveMeshXYToFile(Nz-1);

	SaveMeshXYToFile(10);

//
//	SaveMeshYZToFile(0);
//	SaveMeshYZToFile(Nx-1);
//
//	SaveMeshXZToFile(0);
//	SaveMeshXZToFile(Ny-1);
//	medeTempoGerarMalha.Tac();
//	cout << "Malha gerada" << endl;
}

void Mesh::SmoothMesh(Engine* engine) {
	Array3D<int> newIndexMatrix = Array3D<int>(Nx,Ny,Nz);

   double epsx, epsy, epsz;
   double mix, miy, miz;
   double sigx, sigy, sigz;

   Material M;
   Material Mi1;
   Material Mj1;
   Material Mk1;
   Material Mij1;
   Material Mik1;
   Material Mjk1;

//   cout << "Mesh::SmoothMesh()" << endl;
   wxString status = "Smoothing mesh (";
   for (int i = 0; i < Nx; i++) {
	   double stepPercentage = ((double)i)/((double)Nx) * 100;
	   bool continuar = engine->InformStatus(status + Converter::DoubleToFormattedString(stepPercentage, 0) + "%)");
	   if (!continuar) return;

	   for (int j = 0; j < Ny; j++) {
		   for (int k = 0; k < Nz; k++) {
			   // No início, todos são ar.
			   M = Mi1 = Mj1 = Mk1 = Mij1 = Mik1 = Mjk1 = Material();

			   if ((i < Nx) && (j < Ny) && (k < Nz))
				   M = GetCoefficients(i, j, k).GetMaterial();

			   if ((i > 0) && (j < Ny) && (k < Nz))
				   Mi1 = GetCoefficients(i-1, j, k).GetMaterial();

			   if ((j > 0) && (i < Nx) && (k < Nz))
				   Mj1 = GetCoefficients(i, j-1, k).GetMaterial();

			   if ((k > 0) && (i < Nx) && (j < Ny))
				   Mk1 = GetCoefficients(i, j, k-1).GetMaterial();

			   if ((i > 0) && (j > 0) && (k < Nz))
				   Mij1 = GetCoefficients(i-1, j-1, k).GetMaterial();

			   if ((i > 0) && (k > 0) && (j < Ny))
				   Mik1 = GetCoefficients(i-1, j, k-1).GetMaterial();

			   if ((j > 0) && (k > 0) && (i < Nx))
				   Mjk1 = GetCoefficients(i, j-1, k-1).GetMaterial();
//			   cout << "OK i, j, k = "<< i << ", " << j << ", " << k << endl;
//			   cout << "M " << &M << endl;
//			   cout << "M.GetDescription() = " << M.GetDescription() << endl;
//			   cout << "Mi1 " << &Mi1 << endl;
//			   cout << "Mi1.GetDescription() = " << Mi1.GetDescription() << endl;
//			   cout << "Mj1 " << &Mj1 << endl;
//			   cout << "Mj1.GetDescription() = " << Mj1.GetDescription() << endl;
//			   cout << "Mk1 " << &Mk1 << endl;
//			   cout << "Mk1.GetDescription() = " << Mk1.GetDescription() << endl;
//			   cout << "Mij1 " << &Mij1 << endl;
//			   cout << "Mij1.GetDescription() = " << Mij1.GetDescription() << endl;
//			   cout << "Mik1 " << &Mik1 << endl;
//			   cout << "Mik1.GetDescription() = " << Mik1.GetDescription() << endl;
//			   cout << "Mjk1 " << &Mjk1 << endl;
//			   cout << "Mjk1.GetDescription() = " << Mjk1.GetDescription() << endl;

			   epsx = (M.GetEx() + Mj1.GetEx() + Mjk1.GetEx() + Mk1.GetEx())/4;
			   epsy = (M.GetEy() + Mi1.GetEy() + Mik1.GetEy() + Mk1.GetEy())/4;
			   epsz = (M.GetEz() + Mi1.GetEz() + Mij1.GetEz() + Mj1.GetEz())/4;
			   sigx = (M.GetSx() + Mj1.GetSx() + Mjk1.GetSx() + Mk1.GetSx())/4;
			   sigy = (M.GetSy() + Mi1.GetSy() + Mik1.GetSy() + Mk1.GetSy())/4;
			   sigz = (M.GetSz() + Mi1.GetSz() + Mij1.GetSz() + Mj1.GetSz())/4;

			   /*
			   // TODO: VERIFICAR COM O MARTINS. NO CASO DE U, A MÉDIA É SÓ COM 2 CÉLULAS?
			   paramID = M->GetParameterID("PermeabilityX");
			   mix = (M->GetRealParameter(paramID) + Mk1->GetRealParameter(paramID))/2;
			   paramID=M->GetParameterID("PermeabilityY");
			   miy = (M->GetRealParameter(paramID) + Mi1->GetRealParameter(paramID))/2;
			   paramID=M->GetParameterID("PermeabilityZ");
			   miz = (M->GetRealParameter(paramID) + Mj1->GetRealParameter(paramID))/2;
			   */
			   mix = M.GetUx();
			   miy = M.GetUy();
			   miz = M.GetUz();
			   wxString smoothMaterialName = M.GetDescription().Append(Mi1.GetDescription()).Append(Mj1.GetDescription()).Append(Mk1.GetDescription())
					   .Append(Mij1.GetDescription()).Append(Mik1.GetDescription()).Append(Mjk1.GetDescription());

			   Material smoothMaterial;
			   smoothMaterial.SetEx(epsx);
			   smoothMaterial.SetEy(epsy);
			   smoothMaterial.SetEz(epsz);
			   smoothMaterial.SetSx(sigx);
			   smoothMaterial.SetSy(sigy);
			   smoothMaterial.SetSz(sigz);
			   smoothMaterial.SetUx(mix);
			   smoothMaterial.SetUy(miy);
			   smoothMaterial.SetUz(miz);
			   smoothMaterial.SetDescription(smoothMaterialName);

			   int index = GetMaterialIndexInLookupTable(smoothMaterial);
			   newIndexMatrix[i][j][k] = index;
		   }
	   }
   }

   engine->InformStatus("");
   indexMatrix = newIndexMatrix;
}
bool Mesh::IsInside(Line& ray, std::vector<Line>& polygon) {
//	cout << "Mesh::IsInside" << endl;
	Line line;
	int crosses = 0;

	for (size_t i = 0; i < polygon.size(); i++) {
		line = polygon[i];

		if (line.Cross(Line::XY_PLANE, ray)) {
		  crosses++;
//		  cout << "line.Cross == true" << endl;
		}
	}
//	cout << "crosses = " << crosses << endl;
	return crosses % 2 != 0;
}
void Mesh::SaveMeshXZToFile(int yCell) {
	wxString conteudo;

	std::vector<MaterialCoefficients>::iterator it = lookupTable.begin();
	std::vector<MaterialCoefficients>::iterator end = lookupTable.end();
	int indice = 0;
	while (it != end) {
		MaterialCoefficients mc = *it;
		conteudo.Append(Converter::IntToFormattedString(indice)).Append(" - ").Append(mc.GetMaterial().GetDescription()).Append(" - ex, ey, ez = ").Append(Converter::DoubleToFormattedString(mc.GetGax())).Append(" ").Append(Converter::DoubleToFormattedString(mc.GetGay())).Append(" ").Append(Converter::DoubleToFormattedString(mc.GetGaz())).Append("\n");
		indice++;
		it++;
	}

	for (int i = 0; i < Nx; i++) {
		for (int k = 0; k < Nz; k++) {
			conteudo.Append(Converter::IntToFormattedString(indexMatrix[i][yCell][k])).Append(" ");
		}
		conteudo.Append("\n");
	}
	wxString file = "c:/meshXZ";
	file.Append(Converter::IntToFormattedString(yCell));
	file.Append(".txt");
	FileManager::SaveFile(file, conteudo);
	wxLogDebug(conteudo);
}
void Mesh::SaveMeshXYToFile(int zCell) {
	wxString conteudo;

	std::vector<MaterialCoefficients>::iterator it = lookupTable.begin();
	std::vector<MaterialCoefficients>::iterator end = lookupTable.end();
	int indice = 0;
	while (it != end) {
		MaterialCoefficients mc = *it;
		conteudo.Append(Converter::IntToFormattedString(indice)).Append(" - ").Append(mc.GetMaterial().GetDescription()).Append(" - ex, ey, ez = ").Append(Converter::DoubleToFormattedString(mc.GetGax())).Append(" ").Append(Converter::DoubleToFormattedString(mc.GetGay())).Append(" ").Append(Converter::DoubleToFormattedString(mc.GetGaz())).Append("\n");
		indice++;
		it++;
	}

	for (int i = 0; i < Nx; i++) {
		for (int j = 0; j < Ny; j++) {
			conteudo.Append(Converter::IntToFormattedString(indexMatrix[i][j][zCell])).Append(" ");
		}
		conteudo.Append("\n");
	}
	wxString file = "c:/meshXY";
	file.Append(Converter::IntToFormattedString(zCell));
	file.Append(".txt");
	FileManager::SaveFile(file, conteudo);
	wxLogDebug(conteudo);
	cout << conteudo << endl;
}
void Mesh::SaveMeshYZToFile(int xCell) {
	wxString conteudo;

	std::vector<MaterialCoefficients>::iterator it = lookupTable.begin();
	std::vector<MaterialCoefficients>::iterator end = lookupTable.end();
	int indice = 0;
	while (it != end) {
		MaterialCoefficients mc = *it;
		conteudo.Append(Converter::IntToFormattedString(indice)).Append(" - ").Append(mc.GetMaterial().GetDescription()).Append(" - ex, ey, ez = ").Append(Converter::DoubleToFormattedString(mc.GetGax())).Append(" ").Append(Converter::DoubleToFormattedString(mc.GetGay())).Append(" ").Append(Converter::DoubleToFormattedString(mc.GetGaz())).Append("\n");
		indice++;
		it++;
	}

	for (int j = 0; j < Ny; j++) {
		for (int k = 0; k < Nz; k++) {
			conteudo.Append(Converter::IntToFormattedString(indexMatrix[xCell][j][k])).Append(" ");
		}
		conteudo.Append("\n");
	}
	wxString file = "c:/meshYZ";
	file.Append(Converter::IntToFormattedString(xCell));
	file.Append(".txt");
	FileManager::SaveFile(file, conteudo);
	wxLogDebug(conteudo);
}
const MaterialCoefficients& Mesh::GetCoefficients(int i, int j, int k) const {
	int index = indexMatrix[i][j][k];
	return lookupTable[index];
}

void Mesh::SetMaterial(int i, int j, int k, Material m) {
//	cout << "Chamando Mesh::SetMaterial(" << i << ", " << j << ", " << k << ", " << m.GetDescription() << ")";
	int index = GetMaterialIndexInLookupTable(m);
//	cout << "\tIndice: " << index << endl;
	indexMatrix[i][j][k] = index;
}
