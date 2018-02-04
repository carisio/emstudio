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

    /* Essas vari�veis s�o as dimens�es em x, y e z que devem ser estendidas para acomodar a condi��o de contorno. */
    /* Por exemplo, se existir PML em X(-) e em X(+), as dimens�es do GRID ser�o de:
     * xMin-xNegative at� xMax+xPositve, sendo que de xMin at� xMax � �rea �til e o resto � a �rea onde fica a PML
     */
	double xNegative;
	double xPositive;
	double yNegative;
	double yPositive;
	double zNegative;
	double zPositive;


    /* Quantidade de c�lulas em cada eixo, conforme definido pelo usu�rio */
    int Nx;
    int Ny;
    int Nz;
    int Npml;
    /* Quantidade de c�lulas em cada eixo. Nesse caso o acumulado j� � considerado.
     * Por exemplo, se o usu�rio definiu Nx = 50, Npml = 8, PML em +X e PEC em -X, NxTOTAL ser� 58
     */
    int NxTOTAL;
    int NyTOTAL;
    int NzTOTAL;


    /* Vetor contendo o espa�amento */
    vector<double> dx;
    vector<double> dy;
    vector<double> dz;
    /* Esse vetor cont�m os dados acumulados de dx, dy, dz.
     * Ou seja, para uma determinada posi��o i, accumulated_dx[i] retorna
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

	/* Para uma dada c�lula, retorna o delta_x, delta_y ou delta_z */
	double GetDx(int index);
	double GetDy(int index);
	double GetDz(int index);

	/* Para uma dada c�lula, retorna o acumulado de dx, dy e dz */
	double GetAccumulatedDx(int index);
	double GetAccumulatedDy(int index);
	double GetAccumulatedDz(int index);

	/* Dado um valor de x, y ou z retorna o n�mero da c�lula a que o valor pertence */
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
