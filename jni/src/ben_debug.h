/******************************************************************
*
*
*		----------------
*		   BenDebug.h
*		----------------
*
*
*		Classe "debug" pour afficher les
*		messages d'erreur dans un fichier
*
*
*		Prosper / LOADED -   V 0.6 - 13 Juillet 2000
*
*
*
******************************************************************/

#ifndef _DEBUG_
#define _DEBUG_

//-----------------------------------------------------------------------------
//		Constantes pour le débugage
//-----------------------------------------------------------------------------

#define FILE_LOG	"BlipBlop.log"			// Nom du fichier utilisé
#define MSG_MAX		50000					// Nombre de messages maximum

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include <fstream>

using namespace std;

//-----------------------------------------------------------------------------
//		Définition de la classe Debug
//-----------------------------------------------------------------------------

class Debug
{
private:
	ofstream	f;					// Le fichier .log
	int			nbmsg;				// Nombre de messages transmis
	char 		nomfic[256];				// Le nom du fichier

	Debug();
	void Msg(const char * msg);

public:
	Debug(const char * nf);

	Debug & operator << (const char * msg);
	Debug & operator << (int nb);
	Debug & operator << (void * ptr);
	~Debug();

};

//-----------------------------------------------------------------------------
//		Déclaration d'un objet 'debug' global
//-----------------------------------------------------------------------------

#ifndef DEBUG_CPP_FILE
extern Debug debug;
#endif

#endif