/******************************************************************
*
*
*		-----------------
*		   TexteCool.h
*		-----------------
*
*		Pour les textes "tetra tuerie"
*
*
*		Prosper / LOADED -   V 0.1 - 17 Aout 2000
*
*
*
******************************************************************/

#define TEXTE_COOL_CPP

#include "globals.h"
#include "texte_cool.h"
#include "txt_data.h"

bool text_cool_free[10];

TexteCool::TexteCool() : x(960), t(0)
{
	nn = 0;

	while (nn < 10 && !text_cool_free[nn])
		nn++;

	if (nn >= 10)
		nn = 0;

	y = 150 + nn * 30;

	text_cool_free[nn] = false;
}



void TexteCool::update()
{
	if (x == 320) {
		t += 1;

		if (t >= 350) {
			x -= 16;
			text_cool_free[nn] = true;
		}
	} else
		x -= 16;

}

void TexteCool::affiche()
{
	fnt_cool.printC(backSurface, x, y, txt_data[ntxt]);
}

void clearTexteCool()
{
	for (int i = 0; i < 10; i++)
		text_cool_free[i] = true;
}