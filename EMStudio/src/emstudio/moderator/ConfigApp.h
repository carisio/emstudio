/*
 * Config.h
 *
 *  Created on: 26/05/2014
 *      Author: leandrocarisio
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include "wx/wx.h"

/* Tipo de aplicação */
static const wxString AppType = "FDTD";
//static const wxString AppType = "MoM";


/* Versão da aplicação.
 * O versionamento segue a seguinte nomenclatura:
 * x.y.z
 * Uma alteração em z é apenas uma alteração de tela. Dessa forma, se x e y forem iguais, um arquivo salvo em uma versão z diferente pode ser aberto.
 * Uma alteração em y é uma alteração maior.
 * Uma alteração em x representa uma nova versão do programa.
 * */
static const int AppV1 = 0;
static const int AppV2 = 1;
static const int AppV3 = 1;

#endif /* CONFIG_H_ */
