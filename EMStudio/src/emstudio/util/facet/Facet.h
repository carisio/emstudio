/*
 * Facet.h
 *
 *  Created on: 23/04/2012
 *      Author: leandrocarisio
 */

#ifndef FACET_H_
#define FACET_H_

#include "emstudio/util/vector/Rvector3.h"
#include <vector>

using std::vector;

class Facet {
private:
	vector<Rvector3> face;
	Rvector3 BoundMax;
	Rvector3 BoundMin;
	Rvector3 Normal;

	void BuildNormal();
public:
	Facet();

	Rvector3 GetBoundMax();
	Rvector3 GetBoundMin();

	/* Adiciona um v�rtice a uma face.
	 * Nota: H� duas suposi��es impl�citas no programa:
	 * 1 - Os v�rtices de uma face devem ser adicionados no sentido anti-hor�rio:
	 * 2 - Todos os v�rtices devem pertencer a um mesmo plano (isso n�o � verificado pela classe, mas deve ser inserido dessa forma).
	 */
	void Add(Rvector3 vertex);
	/*
	 * Verifica se a face cruza o plano XY na posi��o z
	 */
	bool IsFaceCrossXYPlaneAt(double z);
	/*
	 * Multiplica todos os v�rtices por scale. Usado para desnormalizar uma face (alterar as unidades para MKS).
	 */
	void MultiplyVertex(double scale);
	/*
	 * Verifica a linha de cruzamento da face no plano z e preenche os dados nos pontos v1 e v2.
	 */
	void GetCrossLineXYPlane(double z, Rvector3& v1, Rvector3& v2);

	/*
	 * Retorna os v�rtices da face
	 */
	vector<Rvector3> GetVertex();

	Rvector3 GetNormal();

	void Rotate(Rvector3 Orig, double Rx, double Ry, double Rz);
	void Translate(double Tx, double Ty, double Tz);
	virtual ~Facet();
};
void RotateFacets(vector<Facet>& v, double RxDegree, double RyDegree, double RzDegree);
void RotateFacets(vector<Facet>& v, Rvector3 Orig, double RxDegree, double RyDegree, double RzDegree);
void TranslateFacets(vector<Facet>& v, double Tx, double Ty, double Tz);
void FillBoundaries(vector<Facet>& v, Rvector3& min, Rvector3& max);
#endif /* FACET_H_ */
