/******************************************************************
*
*
*		----------------
*		    TxtData.h
*		----------------
*
*		Permet de charger les textes
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/


#ifndef _TxtData_
#define _TxtData_

#ifndef TXT_DATA_CPP
extern char **	txt_data;
#endif

#include "asset.h"

bool loadTxtData(const char * file);
void freeTxtData();

#endif
