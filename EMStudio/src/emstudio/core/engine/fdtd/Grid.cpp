/*
 * Grid.cpp
 *
 *  Created on: 01/08/2011
 *      Author: Martins
 */

#include "Grid.h"

#include <iostream>
using namespace::std;

Grid::Grid(FDTDDTO dto)
	: dto(dto),
	xMin(dto.GetXmin()),
	yMin(dto.GetYmin()),
	zMin(dto.GetZmin()),
	xMax(dto.GetXmax()),
	yMax(dto.GetYmax()),
	zMax(dto.GetZmax()),
	Nx(dto.GetXcells()),
	Ny(dto.GetYcells()),
	Nz(dto.GetZcells()),
	Npml(dto.GetNpml()) {

	GenerateUniformGrid();
}
/*
 * Configura a extensão do grid devido a condição de contorno.
 *
 * Exemplo
 * -------
 *
 * 1) Suponha que o usuário definiu, no eixo x, as seguintes dimensões para o grid: xMin, xMax
 *
 * 1.1) Se o usuário tiver escolhido PEC:
 * 1.1.1) Em xNeg não é adicionada nenhuma célula, portanto não há extensão do grid.
 * 1.1.1) Em xPos, deve ser adicionada uma célula. Considerando grid uniforme, essa célula tem tamanho igual a xPositve = (xMax-xMin)/Nx.
 *
 * 1.2) Se o usuário tiver escolhido PML em xNeg e xPos:
 * 1.2.1) Nesse caso, são adicionadas Npml células de cada lado do eixo x. Cada célula tem tamanho igual a deltaX = (xMax-xMin/Nx).
 *        Como são Npml células, xNegative = xPositve = deltaX*Npml.
 *
 * 1.3) Se o usuário tiver escolhido PBC:
 * 1.3.1) Nesse caso, nenhuma célula é adicionada. xNegative = xPositive = 0
 *
 * Em todos os casos, NxTOTAL, NyTOTAL e NzTOTAL guarda o número total de células em cada direção.
 */
void Grid::ConfigureExtendedGridDimensions() {
	double deltaX = ((xMax-xMin)/Nx);
	double deltaY = ((yMax-yMin)/Ny);
	double deltaZ = ((zMax-zMin)/Nz);

	NxTOTAL = Nx;
	NyTOTAL = Ny;
	NzTOTAL = Nz;

	/* Verifica eixo x Negativo */
	if (dto.GetABC().IsPML(xNeg)) {
		xNegative = deltaX*Npml;
		NxTOTAL += Npml;
	} else if (dto.GetABC().IsPEC(xNeg)) {
		xNegative = 0;
	} else if (dto.GetABC().IsPeriodic(xNeg)) {
		xNegative = 0;
	}
	/* Verifica eixo x Positivo */
	if (dto.GetABC().IsPML(xPos)) {
		xPositive = deltaX*Npml;
		NxTOTAL += Npml;
	} else if (dto.GetABC().IsPEC(xPos)) {
		xPositive = deltaX*1;
		NxTOTAL += 1;
	} else if (dto.GetABC().IsPeriodic(xPos)) {
		xPositive = deltaX*1;
		NxTOTAL += 1;
	}
	/* Verifica eiyo y Negativo */
	if (dto.GetABC().IsPML(yNeg)) {
		yNegative = deltaY*Npml;
		NyTOTAL += Npml;
	} else if (dto.GetABC().IsPEC(yNeg)) {
		yNegative = 0;
	} else if (dto.GetABC().IsPeriodic(yNeg)) {
		yNegative = 0;
	}
	/* Verifica eiyo y Positivo */
	if (dto.GetABC().IsPML(yPos)) {
		yPositive = deltaY*Npml;
		NyTOTAL += Npml;
	} else if (dto.GetABC().IsPEC(yPos)) {
		yPositive = deltaY*1;
		NyTOTAL += 1;
	} else if (dto.GetABC().IsPeriodic(yPos)) {
		yPositive = deltaY*1;
		NyTOTAL += 1;
	}
	/* Verifica eizo z Negativo */
	if (dto.GetABC().IsPML(zNeg)) {
		zNegative = deltaZ*Npml;
		NzTOTAL += Npml;
	} else if (dto.GetABC().IsPEC(zNeg)) {
		zNegative = 0;
	} else if (dto.GetABC().IsPeriodic(zNeg)) {
		zNegative = 0;
	}
	/* Verifica eizo z Positivo */
	if (dto.GetABC().IsPML(zPos)) {
		zPositive = deltaZ*Npml;
		NzTOTAL += Npml;
	} else if (dto.GetABC().IsPEC(zPos)) {
		zPositive = deltaZ*1;
		NzTOTAL += 1;
	} else if (dto.GetABC().IsPeriodic(zPos)) {
		zPositive = deltaZ*1;
		NzTOTAL += 1;
	}
}

/*
 * Gera um eixo uniforme de tamanho N, começando em min e terminando em max.
 */
void Grid::GenerateUniformAxis(vector<double>& array, vector<double>& accumulated_array, int N, double min, double max) {
	/* somatorioAteI guarda o somatário até, mas não incluindo, i */
	double somatorioAteI = min;
	for (int i = 0; i < N; i++) {
		double delta_cell = (max-min)/(N);

		array.push_back(delta_cell);
		accumulated_array.push_back(somatorioAteI);

		somatorioAteI += delta_cell;
	}
	/* Adiciona uma "última célula" virtual para considerar o somatório até ela */
	accumulated_array.push_back(somatorioAteI);
}
/*
 * Gera um grid uniforme. Na verdade, ele verifica se tem PML ou PEC nos eixos e chama a função GenerateUniformAxis para
 * criar um grid uniforme.
 */
void Grid::GenerateUniformGrid() {
	/* Calcula (x,y,z)Negative, (x,y,z)Positive e NxTOTAL, NyTOTAL, NzTOTAL */
	ConfigureExtendedGridDimensions();

	GenerateUniformAxis(dx, accumulated_dx, NxTOTAL, xMin-xNegative, xMax+xPositive);
	GenerateUniformAxis(dy, accumulated_dy, NyTOTAL, yMin-yNegative, yMax+yPositive);
	GenerateUniformAxis(dz, accumulated_dz, NzTOTAL, zMin-zNegative, zMax+zPositive);
}
/*
 * Retorna o valor mínimo em um vetor
 */
double Grid::Min(vector<double> array) {
	int N = array.size();
	double min = 1e30;
	for (int i = 0; i < N; i++)
		if (array[i] < min)
			min = array[i];
   return min;
}
/*
 * Retorna o valor máximo em um vetor
 */
double Grid::Max(vector<double> array) {
	int N = array.size();
	double max = 0;
	for (int i = 0; i < N; i++)
		if (array[i] > max)
			max = array[i];
	return max;
}
/*
 * Retorna o deltax para um determinado índice
 */
double Grid::GetDx(int index) {
	return dx[index];
}
/*
 * Retorna o deltay para um determinado índice
 */
double Grid::GetDy(int index) {
	return dy[index];
}
/*
 * Retorna o deltaz para um determinado índice
 */
double Grid::GetDz(int index) {
	return dz[index];
}
/*
 * Retorna o deltax acumulado para um determinado índice
 */
double Grid::GetAccumulatedDx(int index) {
	return accumulated_dx[index];
}
/*
 * Retorna o deltay acumulado para um determinado índice
 */
double Grid::GetAccumulatedDy(int index) {
	return accumulated_dy[index];
}
/*
 * Retorna o deltaz acumulado para um determinado índice
 */
double Grid::GetAccumulatedDz(int index) {
	return accumulated_dz[index];
}
/*
 * Retorna o índice em um vetor que contém o valor value.
 * Para isso, considera que o vetor passado como parâmetro, arraySpacing, começa em min e termina em max
 */
int Grid::GetCell(vector<double>& arraySpacing, double min, double max, double value) {
	int N = arraySpacing.size();
	int index = 0;
	//  O código abaixo retorna a célula mais próxima.
	double lValue = min;
	double rValue = lValue + arraySpacing[index]/2;

	/*
	 * Estrutura:
	 *
	 * min    delta_i              max
	 * ^       ^                    ^
	 * |       |                    |
	 * |----|----|----|----|...|----|
	 *    |----|
	 *    ^    ^
	 *    |    |
	 * lvalue rvalue
	 *
	 * Esse loop verifica se o índice está entre lvalue e rvalue.
	 * Inicialmente, lvalue é igual a min e rvalue é igual a delta_0/2
	 * A partir do próximo passo, o valor de lvalue é atualizado com rvalue, e rvalue é calculado considerando delta_i / 2 + delta_i_plus_1 / 2
	 *
	 * O primeiro índice é verificado apenas dentro de um limite de delta_0/2.
	 * Os demais, com exceção do último, são verificados em delta_i/2 + delta_i_plus_1/2.
	 * O último índice é verificado dentro de um limite de delta_penultimo/2 + delta_ultimo.
	 *
	 * Nesse último caso, é considerado que qualquer valor maior ou igual a (max - delta_ultimo) > 2 retorne o índice de max,
	 * mesmo que o valor pesquisado seja > max.
	 *
	 */
	while ( !((lValue <= value) && (value <= rValue))
			&& (index < N-1) ) {
		lValue = rValue;
		rValue += (arraySpacing[index]/2 + arraySpacing[index+1]/2);

		index++;
	}
//	if (index == N) { Não precisa desse if se a comparação no while anterior for (index < N-1) no lugar de (index < N)
//		index = N-1;
//	}

	return index;

}

int Grid::GetNxTOTAL() {
	return NxTOTAL;
}
int Grid::GetNyTOTAL() {
	return NyTOTAL;
}
int Grid::GetNzTOTAL() {
	return NzTOTAL;
}
int Grid::GetXCell(double x) {
	return GetCell(dx, xMin-xNegative, xMax+xPositive, x);
}

int Grid::GetYCell(double y) {
	return GetCell(dy, yMin-yNegative, yMax+yPositive, y);
}

int Grid::GetZCell(double z) {
	return GetCell(dz, zMin-zNegative, zMax+zPositive, z);
}

double Grid::GetXMin() {
	return xMin;
}
double Grid::GetYMin() {
	return yMin;
}
double Grid::GetZMin() {
	return zMin;
}
double Grid::GetXMax() {
	return xMax;
}
double Grid::GetYMax() {
	return yMax;
}
double Grid::GetZMax() {
	return zMax;
}

Grid::~Grid() {

}
