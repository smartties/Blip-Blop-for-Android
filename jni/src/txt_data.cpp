/******************************************************************
*
*
*		-----------------
*		   TxtData.cpp
*		-----------------
*
*		Permet de charger les textes
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/

#define TXT_DATA_CPP
#define NB_TXT_DATA		1000

#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "txt_data.h"
#include "ben_debug.h"

char **	txt_data = NULL;


bool loadTxtData(const char * file)
{
	txt_data = new char * [NB_TXT_DATA];

	if (txt_data == NULL)
		return false;

	for (int i = 0; i < NB_TXT_DATA; i++)
		txt_data[i] = NULL;
    ///MODIF ifstream
	//ifstream	f;
	istringstream f;

	int			num;
	char		buffer[400];

	///MODIF open
	//f.open(file);

	///MODIF is_open
	//if (!f.is_open())
	if(AAsset_istringstream(file, f) == false)
    return false;

	while (!f.eof()) {
		f.getline(buffer, 400, '^');
		num = atoi(buffer);
		f.getline(buffer, 400);

		txt_data[num] = new char[strlen(buffer) + 1];
		strcpy(txt_data[num], buffer);
	}

    ///MODIF close
    //f.close();
    f.str("");
    f.clear();

	return true;
}


void freeTxtData()
{
	if (txt_data != NULL) {
		for (int i = 0; i < NB_TXT_DATA; i++)
			if (txt_data[i] != NULL)
				delete [] txt_data[i];

		delete [] txt_data;
		txt_data = NULL;
	}
}

