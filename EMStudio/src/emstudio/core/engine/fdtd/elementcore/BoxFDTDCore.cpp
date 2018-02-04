/*
 * BoxCore.cpp
 *
 *  Created on: 07/02/2012
 *      Author: Leandro
 */

#include "BoxFDTDCore.h"
#include "emstudio/util/constants/Constants.h"

BoxFDTDCore::BoxFDTDCore() {

}

BoxFDTDCore::~BoxFDTDCore() {
}

ElementCoreSmartPointer BoxFDTDCore::NewElementCore() {
	return ElementCoreSmartPointer(new BoxFDTDCore);
}
/*
 * Observação: O método DoConfigure pode alterar a face do objeto para entrar na PML. Isso faz com que o projeto dê erro, pois o método FillDimensions implementado
 * em FDTDElementCore irá pesquisar as faces do objeto e retornar os pontos de máximos e mínimos de acordo com elas. Assim, a FDTDEngine irá verificar o retorno e
 * verá que, sempre que o box for casado com a PML, seu tamanho será estendido para dentro dela, gerando erro, pois a face sairá do grid.
 * Entretanto, o erro deve ser gerado apenas se o usuário digitar o box fora do grid. Por isso, é necessário alterar a implementação padrão do FillDimensions do Box
 * para retornar apenas o que o usuário digitou, e não a alteração feita do DoConfigure.
 */
bool BoxFDTDCore::FillDimensions(double& xmin, double& ymin, double& zmin, double& xmax, double& ymax, double& zmax) {
	xmin = dto.GetX1();
	ymin = dto.GetY1();
	zmin = dto.GetZ1();
	xmax = dto.GetX2();
	ymax = dto.GetY2();
	zmax = dto.GetZ2();

	return true;
}
void BoxFDTDCore::DoConfigure(ElementDTOSmartPointer elementDTOSmartPtr) {
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());
	BoxDTO* boxDTO = static_cast<BoxDTO*>(elementDTOSmartPtr.get());

	/*
	 * Dimensões do box, caso seja necessário alterá-lo em caso de estar casado com a PML
	 */
	double xmin = boxDTO->GetX1();
	double ymin = boxDTO->GetY1();
	double zmin = boxDTO->GetZ1();
	double xmax = boxDTO->GetX2();
	double ymax = boxDTO->GetY2();
	double zmax = boxDTO->GetZ2();
	bool matched = false;

	// Se o elemento estiver casado, altera ele
	if (boxDTO->GetMatchWithPML().IsMatchedWithPML(xNeg)) {
		matched = true;
		xmin = engine->GetGrid().GetAccumulatedDx(0);
	}
	if (boxDTO->GetMatchWithPML().IsMatchedWithPML(yNeg)) {
		matched = true;
		ymin = engine->GetGrid().GetAccumulatedDy(0);
	}
	if (boxDTO->GetMatchWithPML().IsMatchedWithPML(zNeg)) {
		matched = true;
		zmin = engine->GetGrid().GetAccumulatedDz(0);
	}
	if (boxDTO->GetMatchWithPML().IsMatchedWithPML(xPos)) {
		matched = true;
		xmax = engine->GetGrid().GetAccumulatedDx(engine->GetGrid().GetNxTOTAL()-1);
	}
	if (boxDTO->GetMatchWithPML().IsMatchedWithPML(yPos)) {
		matched = true;
		ymax = engine->GetGrid().GetAccumulatedDy(engine->GetGrid().GetNyTOTAL()-1);
	}
	if (boxDTO->GetMatchWithPML().IsMatchedWithPML(zPos)) {
		matched = true;
		zmax = engine->GetGrid().GetAccumulatedDz(engine->GetGrid().GetNzTOTAL()-1);
	}

	if (matched) {
		vector<Facet> facets;

		Facet f1;
		f1.Add(Rvector3(xmin, ymin, zmin));
		f1.Add(Rvector3(xmax,ymin,zmin));
		f1.Add(Rvector3(xmax,ymax,zmin));
		f1.Add(Rvector3(xmin,ymax,zmin));
		facets.push_back(f1);

		Facet f2;
		f2.Add(Rvector3(xmin, ymin, zmin));
		f2.Add(Rvector3(xmin,ymax,zmin));
		f2.Add(Rvector3(xmin,ymax,zmax));
		f2.Add(Rvector3(xmin,ymin,zmax));
		facets.push_back(f2);

		Facet f3;
		f3.Add(Rvector3(xmin, ymin, zmin));
		f3.Add(Rvector3(xmax,ymin,zmin));
		f3.Add(Rvector3(xmax,ymin,zmax));
		f3.Add(Rvector3(xmin,ymin,zmax));
		facets.push_back(f3);

		Facet f4;
		f4.Add(Rvector3(xmax, ymax, zmax));
		f4.Add(Rvector3(xmin,ymax,zmax));
		f4.Add(Rvector3(xmin,ymin,zmax));
		f4.Add(Rvector3(xmax,ymin,zmax));
		facets.push_back(f4);

		Facet f5;
		f5.Add(Rvector3(xmax, ymax, zmax));
		f5.Add(Rvector3(xmax,ymin,zmax));
		f5.Add(Rvector3(xmax,ymin,zmin));
		f5.Add(Rvector3(xmax,ymax,zmin));
		facets.push_back(f5);

		Facet f6;
		f6.Add(Rvector3(xmax, ymax, zmax));
		f6.Add(Rvector3(xmin,ymax,zmax));
		f6.Add(Rvector3(xmin,ymax,zmin));
		f6.Add(Rvector3(xmax,ymax,zmin));
		facets.push_back(f6);

		/*
		 * A partir de agora as faces contém o box até o último elemento do grid.
		 * Os elementos x1, y1, z1 e x2, y2 e z2 do DTO continuam com o que o usuário digitou.
		 */
		boxDTO->SetFacets(facets);
	}

	dto = *boxDTO;
}

bool BoxFDTDCore::IsElementConsistent() {
	bool elementOK = true;
	FDTDEngine* engine = static_cast<FDTDEngine*>(GetEngine());

	/****************************************************************************/
	/* Se o box for casado com a PML, tem q verificar se tem PML no grid e se o */
	/* box foi posicionado tal que a posição que o usuário digitou coincide com */
	/* a posição do grid.                                                       */
	/****************************************************************************/
	if (dto.GetMatchWithPML().IsMatchedWithPML(xNeg)) {
		if (engine->GetFDTDDTO().GetXmin() != dto.GetX1()) {
			wxString errorMessage = "Lower boundary (X) of " + GetName() + " should be equal the lower boundary of the grid (X)";
			AppendErrorMessage(errorMessage);
			elementOK = false;
		}
		if (!(engine->GetFDTDDTO().GetABC().IsPML(xNeg))) {
			wxString errorMessage = GetName() + " cannot match with PML. Grid (-X) is ";
			errorMessage.Append(engine->GetFDTDDTO().GetABC().GetABCXNeg());
			AppendErrorMessage(errorMessage);
			elementOK = false;
		}
	}
	if (dto.GetMatchWithPML().IsMatchedWithPML(yNeg)) {
		if (engine->GetFDTDDTO().GetYmin() != dto.GetY1()) {
			wxString errorMessage = "Lower boundary (Y) of " + GetName() + " should be equal the lower boundary of the grid (Y)";
			AppendErrorMessage(errorMessage);
			elementOK = false;
		}
		if (!(engine->GetFDTDDTO().GetABC().IsPML(yNeg))) {
			wxString errorMessage = GetName() + " cannot match with PML. Grid (-Y) is ";
			errorMessage.Append(engine->GetFDTDDTO().GetABC().GetABCYNeg());
			AppendErrorMessage(errorMessage);
			elementOK = false;
		}
	}
	if (dto.GetMatchWithPML().IsMatchedWithPML(zNeg)) {
		if (engine->GetFDTDDTO().GetZmin() != dto.GetZ1()) {
			wxString errorMessage = "Lower boundary (Z) of " + GetName() + " should be equal the lower boundary of the grid (Z)";
			AppendErrorMessage(errorMessage);
			elementOK = false;
		}
		if (!(engine->GetFDTDDTO().GetABC().IsPML(zNeg))) {
			wxString errorMessage = GetName() + " cannot match with PML. Grid (-Z) is ";
			errorMessage.Append(engine->GetFDTDDTO().GetABC().GetABCZNeg());
			AppendErrorMessage(errorMessage);
			elementOK = false;
		}
	}
	if (dto.GetMatchWithPML().IsMatchedWithPML(xPos)) {
		if (engine->GetFDTDDTO().GetXmax() != dto.GetX2()) {
			wxString errorMessage = "Upper boundary (X) of " + GetName() + " should be equal the upper boundary of the grid (X)";
			AppendErrorMessage(errorMessage);
			elementOK = false;
		}
		if (!(engine->GetFDTDDTO().GetABC().IsPML(xPos))) {
			wxString errorMessage = GetName() + " cannot match with PML. Grid (+X) is ";
			errorMessage.Append(engine->GetFDTDDTO().GetABC().GetABCXPos());
			AppendErrorMessage(errorMessage);
			elementOK = false;
		}
	}
	if (dto.GetMatchWithPML().IsMatchedWithPML(yPos)) {
		if (engine->GetFDTDDTO().GetYmax() != dto.GetY2()) {
			wxString errorMessage = "Upper boundary (Y) of " + GetName() + " should be equal the upper boundary of the grid (Y)";
			AppendErrorMessage(errorMessage);
			elementOK = false;
		}
		if (!(engine->GetFDTDDTO().GetABC().IsPML(yPos))) {
			wxString errorMessage = GetName() + " cannot match with PML. Grid (+Y) is ";
			errorMessage.Append(engine->GetFDTDDTO().GetABC().GetABCYPos());
			AppendErrorMessage(errorMessage);
			elementOK = false;
		}
	}
	if (dto.GetMatchWithPML().IsMatchedWithPML(zPos)) {
		if (engine->GetFDTDDTO().GetZmax() != dto.GetZ2()) {
			wxString errorMessage = "Upper boundary (Z) of " + GetName() + " should be equal the upper boundary of the grid (Z)";
			AppendErrorMessage(errorMessage);
			elementOK = false;
		}
		if (!(engine->GetFDTDDTO().GetABC().IsPML(zPos))) {
			wxString errorMessage = GetName() + " cannot match with PML. Grid (+Z) is ";
			errorMessage.Append(engine->GetFDTDDTO().GetABC().GetABCZPos());
			AppendErrorMessage(errorMessage);
			elementOK = false;
		}
	}

	return elementOK;
}
