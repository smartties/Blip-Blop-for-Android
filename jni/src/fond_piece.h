/******************************************************************
*
*
*		---------------------------
*		    FondPiece.h
*		---------------------------
*
*
*
*		Mephisto / LOADED -   V 0.2 - 12 Janvier 2001
*
*
*
******************************************************************/

#ifndef _FondPiece_
#define _FondPiece_



class FondPiece : public Sprite
{
private:
	static int etape_synchro;
	static int ss_etape_synchro;
	static bool synchro;

public:
	virtual void update();

};

#endif