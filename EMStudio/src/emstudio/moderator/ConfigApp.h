/*
 * Config.h
 *
 *  Created on: 26/05/2014
 *      Author: leandrocarisio
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include "wx/wx.h"

/* Tipo de aplica��o */
static const wxString AppType = "FDTD";
//static const wxString AppType = "MoM";


/* Vers�o da aplica��o.
 * O versionamento segue a seguinte nomenclatura:
 * x.y.z
 * Uma altera��o em z � apenas uma altera��o de tela. Dessa forma, se x e y forem iguais, um arquivo salvo em uma vers�o z diferente pode ser aberto.
 * Uma altera��o em y � uma altera��o maior.
 * Uma altera��o em x representa uma nova vers�o do programa.
 * */
static const int AppV1 = 0;
static const int AppV2 = 1;
static const int AppV3 = 1;

#endif /* CONFIG_H_ */
