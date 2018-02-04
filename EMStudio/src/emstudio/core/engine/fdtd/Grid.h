/*
 * Grid.hpp
 *
 *  Created on: 01/08/2011
 *      Author: Martins
 */

#ifndef GRID_H_
#define GRID_H_

#include "emstudio/dto/fdtdapp/FDTDDTO.h"
#include <vector>

using namespace std;

class Grid {
private:
	FDTDDTO dto;

	/* Pontos extremos do grid */
    double xMin;
    double yMin;
    double zMin;
    double xMax;
    double yMax;
    double zMax;

    /* Essas variáveis são as dimensões em x, y e z que devem ser estendidas para acomodar a condição de contorno. */
    /* Por exemplo, se existir PML em X(-) e em X(+), as dimensões do GRID serão de:
     * xMin-xNegative até xMax+xPositve, sendo que de xMin até xMax é área útil e o resto é a área onde fica a PML
     */
	double xNegative;
	double xPositive;
	double yNegative;
	double yPositive;
	double zNegative;
	double zPositive;


    /* Quantidade de células em cada eixo, conforme definido pelo usuário */
    int Nx;
    int Ny;
    int Nz;
    int Npml;
    /* Quantidade de células em cada eixo. Nesse caso o acumulado já é considerado.
     * Por exemplo, se o usuário definiu Nx = 50, Npml = 8, PML em +X e PEC em -X, NxTOTAL será 58
     */
    int NxTOTAL;
    int NyTOTAL;
    int NzTOTAL;


    /* Vetor contendo o espaçamento */
    vector<double> dx;
    vector<double> dy;
    vector<double> dz;
    /* Esse vetor contém os dados acumulados de dx, dy, dz.
     * Ou seja, para uma determinada posição i, accumulated_dx[i] retorna
     * dx[0] + dx[1] + ... + dx[i-1] */
    vector<double> accumulated_dx;
    vector<double> accumulated_dy;
    vector<double> accumulated_dz;

    double Min(vector<double> array);
    double Max(vector<double> array);

    void GenerateUniformAxis(vector<double>& array, vector<double>& accumulated_array, int N, double min, double max);

    int GetCell(vector<double>& array, double min, double max, double value);
    void ConfigureExtendedGridDimensions();
public:
	Grid(FDTDDTO dto);

	/* Gera um grid uniforme */
	void GenerateUniformGrid();

	/* Para uma dada célula, retorna o delta_x, delta_y ou delta_z */
	double GetDx(int index);
	double GetDy(int index);
	double GetDz(int index);

	/* Para uma dada célula, retorna o acumulado de dx, dy e dz */
	double GetAccumulatedDx(int index);
	double GetAccumulatedDy(int index);
	double GetAccumulatedDz(int index);

	/* Dado um valor de x, y ou z retorna o número da célula a que o valor pertence */
	int GetXCell(double x);
	int GetYCell(double y);
	int GetZCell(double z);

	/* Retorna NxTOTAL, NyTOTAL, NzTOTAL */
	int GetNxTOTAL();
	int GetNyTOTAL();
	int GetNzTOTAL();

	/* Retorna os pontos extremos do grid */
	double GetXMin();
	double GetYMin();
	double GetZMin();
	double GetXMax();
	double GetYMax();
	double GetZMax();

	virtual ~Grid();
};

#endif /* GRID_HPP_ */
