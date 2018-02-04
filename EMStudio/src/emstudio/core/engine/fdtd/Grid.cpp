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
 * Configura a extens�o do grid devido a condi��o de contorno.
 *
 * Exemplo
 * -------
 *
 * 1) Suponha que o usu�rio definiu, no eixo x, as seguintes dimens�es para o grid: xMin, xMax
 *
 * 1.1) Se o usu�rio tiver escolhido PEC:
 * 1.1.1) Em xNeg n�o � adicionada nenhuma c�lula, portanto n�o h� extens�o do grid.
 * 1.1.1) Em xPos, deve ser adicionada uma c�lula. Considerando grid uniforme, essa c�lula tem tamanho igual a xPositve = (xMax-xMin)/Nx.
 *
 * 1.2) Se o usu�rio tiver escolhido PML em xNeg e xPos:
 * 1.2.1) Nesse caso, s�o adicionadas Npml c�lulas de cada lado do eixo x. Cada c�lula tem tamanho igual a deltaX = (xMax-xMin/Nx).
 *        Como s�o Npml c�lulas, xNegative = xPositve = deltaX*Npml.
 *
 * 1.3) Se o usu�rio tiver escolhido PBC:
 * 1.3.1) Nesse caso, nenhuma c�lula � adicionada. xNegative = xPositive = 0
 *
 * Em todos os casos, NxTOTAL, NyTOTAL e NzTOTAL guarda o n�mero total de c�lulas em cada dire��o.
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
 * Gera um eixo uniforme de tamanho N, come�ando em min e terminando em max.
 */
void Grid::GenerateUniformAxis(vector<double>& array, vector<double>& accumulated_array, int N, double min, double max) {
	/* somatorioAteI guarda o somat�rio at�, mas n�o incluindo, i */
	double somatorioAteI = min;
	for (int i = 0; i < N; i++) {
		double delta_cell = (max-min)/(N);

		array.push_back(delta_cell);
		accumulated_array.push_back(somatorioAteI);

		somatorioAteI += delta_cell;
	}
	/* Adiciona uma "�ltima c�lula" virtual para considerar o somat�rio at� ela */
	accumulated_array.push_back(somatorioAteI);
}
/*
 * Gera um grid uniforme. Na verdade, ele verifica se tem PML ou PEC nos eixos e chama a fun��o GenerateUniformAxis para
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
 * Retorna o valor m�nimo em um vetor
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
 * Retorna o valor m�ximo em um vetor
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
 * Retorna o deltax para um determinado �ndice
 */
double Grid::GetDx(int index) {
	return dx[index];
}
/*
 * Retorna o deltay para um determinado �ndice
 */
double Grid::GetDy(int index) {
	return dy[index];
}
/*
 * Retorna o deltaz para um determinado �ndice
 */
double Grid::GetDz(int index) {
	return dz[index];
}
/*
 * Retorna o deltax acumulado para um determinado �ndice
 */
double Grid::GetAccumulatedDx(int index) {
	return accumulated_dx[index];
}
/*
 * Retorna o deltay acumulado para um determinado �ndice
 */
double Grid::GetAccumulatedDy(int index) {
	return accumulated_dy[index];
}
/*
 * Retorna o deltaz acumulado para um determinado �ndice
 */
double Grid::GetAccumulatedDz(int index) {
	return accumulated_dz[index];
}
/*
 * Retorna o �ndice em um vetor que cont�m o valor value.
 * Para isso, considera que o vetor passado como par�metro, arraySpacing, come�a em min e termina em max
 */
int Grid::GetCell(vector<double>& arraySpacing, double min, double max, double value) {
	int N = arraySpacing.size();
	int index = 0;
	//  O c�digo abaixo retorna a c�lula mais pr�xima.
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
	 * Esse loop verifica se o �ndice est� entre lvalue e rvalue.
	 * Inicialmente, lvalue � igual a min e rvalue � igual a delta_0/2
	 * A partir do pr�ximo passo, o valor de lvalue � atualizado com rvalue, e rvalue � calculado considerando delta_i / 2 + delta_i_plus_1 / 2
	 *
	 * O primeiro �ndice � verificado apenas dentro de um limite de delta_0/2.
	 * Os demais, com exce��o do �ltimo, s�o verificados em delta_i/2 + delta_i_plus_1/2.
	 * O �ltimo �ndice � verificado dentro de um limite de delta_penultimo/2 + delta_ultimo.
	 *
	 * Nesse �ltimo caso, � considerado que qualquer valor maior ou igual a (max - delta_ultimo) > 2 retorne o �ndice de max,
	 * mesmo que o valor pesquisado seja > max.
	 *
	 */
	while ( !((lValue <= value) && (value <= rValue))
			&& (index < N-1) ) {
		lValue = rValue;
		rValue += (arraySpacing[index]/2 + arraySpacing[index+1]/2);

		index++;
	}
//	if (index == N) { N�o precisa desse if se a compara��o no while anterior for (index < N-1) no lugar de (index < N)
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
