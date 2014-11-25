
#include <string.h>
#include <stdio.h>
#include "config.h"
#include "input.h"
#include "key_translator.h"

#define KMAP( _num, _val) case _num: strcpy( str, _val); break;

void DIK_to_string(int n, char * str)
{
	if (lang_type == LANG_FR)
		DIK_to_string_fr(n, str);
	else
		DIK_to_string_uk(n, str);
}

void DIK_to_string_uk(int n, char * str)
{
	/*int	j = n >> 10;*/

	if (/*j == 0*/true) {
		switch (n) {
				KMAP(DIK_ESCAPE, "ESCAPE");
				KMAP(DIK_1, "1");
				KMAP(DIK_2, "2");
				KMAP(DIK_3, "3");
				KMAP(DIK_4, "4");
				KMAP(DIK_5, "5");
				KMAP(DIK_6, "6");
				KMAP(DIK_7, "7");
				KMAP(DIK_8, "8");
				KMAP(DIK_9, "9");
				KMAP(DIK_0, "0");
				KMAP(DIK_MINUS, "-");
				KMAP(DIK_EQUALS, "=");
				KMAP(DIK_BACK, "BACKSPACE");
				KMAP(DIK_TAB, "TAB");
				KMAP(DIK_Q, "Q");
				KMAP(DIK_W, "W");
				KMAP(DIK_E, "E");
				KMAP(DIK_R, "R");
				KMAP(DIK_T, "T");
				KMAP(DIK_Y, "Y");
				KMAP(DIK_U, "U");
				KMAP(DIK_I, "I");
				KMAP(DIK_O, "O");
				KMAP(DIK_P, "P");
				KMAP(DIK_LBRACKET, "[");
				KMAP(DIK_RBRACKET, "]");
				KMAP(DIK_RETURN, "RETURN");
				KMAP(DIK_LCONTROL, "LEFT CONTROL");
				KMAP(DIK_LALT, "LEFT ALT");
				KMAP(DIK_A, "A");
				KMAP(DIK_S, "S");
				KMAP(DIK_D, "D");
				KMAP(DIK_F, "F");
				KMAP(DIK_G, "G");
				KMAP(DIK_H, "H");
				KMAP(DIK_J, "J");
				KMAP(DIK_K, "K");
				KMAP(DIK_L, "L");
				KMAP(DIK_SEMICOLON, ";");
				KMAP(DIK_APOSTROPHE, "'");
				//KMAP(DIK_GRAVE, "`");
				KMAP(DIK_LSHIFT, "LEFT SHIFT");
				KMAP(DIK_BACKSLASH, "\\");
				//KMAP(DIK_OEM_102, "\\");
				KMAP(DIK_Z, "Z");
				KMAP(DIK_X, "X");
				KMAP(DIK_C, "C");
				KMAP(DIK_V, "V");
				KMAP(DIK_B, "B");
				KMAP(DIK_N, "N");
				KMAP(DIK_M, "M");
				KMAP(DIK_COMMA, ",");
				KMAP(DIK_PERIOD, ".");
				KMAP(DIK_SLASH, "/");
				KMAP(DIK_RSHIFT, "RIGHT SHIFT");
				KMAP(DIK_MULTIPLY, "NUM *");
				KMAP(DIK_LMENU, "LEFT ALT");
				KMAP(DIK_SPACE, "SPACE");
				KMAP(DIK_CAPITAL, "CAPS LOCK");
				KMAP(DIK_F1, "F1");
				KMAP(DIK_F2, "F2");
				KMAP(DIK_F3, "F3");
				KMAP(DIK_F4, "F4");
				KMAP(DIK_F5, "F5");
				KMAP(DIK_F6, "F6");
				KMAP(DIK_F7, "F7");
				KMAP(DIK_F8, "F8");
				KMAP(DIK_F9, "F9");
				KMAP(DIK_F10, "F10");
				KMAP(DIK_F11, "F11");
				KMAP(DIK_F12, "F12");
				KMAP(DIK_F13, "F13");
				KMAP(DIK_F14, "F14");
				KMAP(DIK_F15, "F15");
				KMAP(DIK_NUMLOCK, "NUM LOCK");
				KMAP(DIK_SCROLL, "SCROLL LOCK");
				KMAP(DIK_NUMPAD1, "NUM 1");
				KMAP(DIK_NUMPAD2, "NUM 2");
				KMAP(DIK_NUMPAD3, "NUM 3");
				KMAP(DIK_NUMPAD4, "NUM 4");
				KMAP(DIK_NUMPAD5, "NUM 5");
				KMAP(DIK_NUMPAD6, "NUM 6");
				KMAP(DIK_NUMPAD7, "NUM 7");
				KMAP(DIK_NUMPAD8, "NUM 8");
				KMAP(DIK_NUMPAD9, "NUM 9");
				KMAP(DIK_NUMPAD0, "NUM 0");
				KMAP(DIK_ADD, "NUM +");
				//KMAP(DIK_SUBTRACT, "NUM -");
				KMAP(DIK_DECIMAL, "NUM .");
				KMAP(DIK_NUMPADENTER, "NUM ENTER");
				KMAP(DIK_DIVIDE, "NUM /");
				KMAP(DIK_RMENU, "RIGHT ALT");
				KMAP(DIK_PRIOR, "PAGE UP");
				KMAP(DIK_NEXT, "PAGE DOWN");
				KMAP(DIK_DELETE, "DELETE");
				KMAP(DIK_INSERT, "INSERT");
				KMAP(DIK_HOME, "HOME");
				KMAP(DIK_END, "END");
				KMAP(DIK_UP, "UP ARROW");
				KMAP(DIK_DOWN, "DOWN ARROW");
				KMAP(DIK_LEFT, "LEFT ARROW");
				KMAP(DIK_RIGHT, "RIGHT ARROW");
				KMAP(DIK_RCONTROL, "RIGHT CONTROL");
				/*KMAP(DIK_LWIN, "LEFT WIN");
				KMAP(DIK_RWIN, "RIGHT WIN");
				KMAP(DIK_APPS, "APPS KEY");*/

			default:
				strcpy(str, "UNDEFINED");
				break;
		}
	} /*else {
		int	d = n & 0x3FF;

		switch (d) {
			case JOY_UP:
				sprintf(str, "JOY%d UP", j);
				break;
			case JOY_DOWN:
				sprintf(str, "JOY%d DOWN", j);
				break;
			case JOY_LEFT:
				sprintf(str, "JOY%d LEFT", j);
				break;
			case JOY_RIGHT:
				sprintf(str, "JOY%d RIGHT", j);
				break;
			default:
				sprintf(str, "JOY%d BUTTON%d", j, d + 1);
				break;
		}
	}*/
}


void DIK_to_string_fr(int n, char * str)
{
	int		j = n >> 10;

	if (j == 0) {
		switch (n) {
				KMAP(DIK_ESCAPE, "ESCAPE");
				KMAP(DIK_1, "1");
				KMAP(DIK_2, "2");
				KMAP(DIK_3, "3");
				KMAP(DIK_4, "4");
				KMAP(DIK_5, "5");
				KMAP(DIK_6, "6");
				KMAP(DIK_7, "7");
				KMAP(DIK_8, "8");
				KMAP(DIK_9, "9");
				KMAP(DIK_0, "0");
				//KMAP(DIK_MINUS, ")");
				KMAP(DIK_EQUALS, "=");
				KMAP(DIK_BACK, "BACKSPACE");
				KMAP(DIK_TAB, "TAB");
				KMAP(DIK_Q, "A");
				KMAP(DIK_W, "Z");
				KMAP(DIK_E, "E");
				KMAP(DIK_R, "R");
				KMAP(DIK_T, "T");
				KMAP(DIK_Y, "Y");
				KMAP(DIK_U, "U");
				KMAP(DIK_I, "I");
				KMAP(DIK_O, "O");
				KMAP(DIK_P, "P");
				KMAP(DIK_LBRACKET, "^");
				KMAP(DIK_RBRACKET, "$");
				KMAP(DIK_RETURN, "RETOUR");
				KMAP(DIK_LCONTROL, "CONTROLE GAUCHE");
				KMAP(DIK_A, "Q");
				KMAP(DIK_S, "S");
				KMAP(DIK_D, "D");
				KMAP(DIK_F, "F");
				KMAP(DIK_G, "G");
				KMAP(DIK_H, "H");
				KMAP(DIK_J, "J");
				KMAP(DIK_K, "K");
				KMAP(DIK_L, "L");
				KMAP(DIK_SEMICOLON, "M");
				KMAP(DIK_APOSTROPHE, "ù");
				//KMAP(DIK_GRAVE, "²");
				KMAP(DIK_LSHIFT, "SHIFT GAUCHE");
				KMAP(DIK_BACKSLASH, "*");
				//KMAP(DIK_OEM_102, "<");
				KMAP(DIK_Z, "W");
				KMAP(DIK_X, "X");
				KMAP(DIK_C, "C");
				KMAP(DIK_V, "V");
				KMAP(DIK_B, "B");
				KMAP(DIK_N, "N");
				KMAP(DIK_M, ",");
				KMAP(DIK_COMMA, ";");
				KMAP(DIK_PERIOD, ":");
				KMAP(DIK_SLASH, "!");
				KMAP(DIK_RSHIFT, "SHIFT DROITE");
				KMAP(DIK_MULTIPLY, "NUM *");
				KMAP(DIK_LMENU, "ALT GAUCHE");
				KMAP(DIK_SPACE, "ESPACE");
				KMAP(DIK_CAPITAL, "CAPS LOCK");
				KMAP(DIK_F1, "F1");
				KMAP(DIK_F2, "F2");
				KMAP(DIK_F3, "F3");
				KMAP(DIK_F4, "F4");
				KMAP(DIK_F5, "F5");
				KMAP(DIK_F6, "F6");
				KMAP(DIK_F7, "F7");
				KMAP(DIK_F8, "F8");
				KMAP(DIK_F9, "F9");
				KMAP(DIK_F10, "F10");
				KMAP(DIK_F11, "F11");
				KMAP(DIK_F12, "F12");
				KMAP(DIK_F13, "F13");
				KMAP(DIK_F14, "F14");
				KMAP(DIK_F15, "F15");
				KMAP(DIK_NUMLOCK, "NUM LOCK");
				KMAP(DIK_SCROLL, "SCROLL LOCK");
				KMAP(DIK_NUMPAD1, "NUM 1");
				KMAP(DIK_NUMPAD2, "NUM 2");
				KMAP(DIK_NUMPAD3, "NUM 3");
				KMAP(DIK_NUMPAD4, "NUM 4");
				KMAP(DIK_NUMPAD5, "NUM 5");
				KMAP(DIK_NUMPAD6, "NUM 6");
				KMAP(DIK_NUMPAD7, "NUM 7");
				KMAP(DIK_NUMPAD8, "NUM 8");
				KMAP(DIK_NUMPAD9, "NUM 9");
				KMAP(DIK_NUMPAD0, "NUM 0");
				KMAP(DIK_ADD, "NUM +");
				KMAP(DIK_SUBTRACT, "NUM -");
				KMAP(DIK_DECIMAL, "NUM .");
				KMAP(DIK_NUMPADENTER, "NUM ENTREE");
				KMAP(DIK_DIVIDE, "NUM /");
				KMAP(DIK_RMENU, "ALT DROITE");
				KMAP(DIK_PRIOR, "PAGE PRECEDENTE");
				KMAP(DIK_NEXT, "PAGE SUIVANTE");
				KMAP(DIK_DELETE, "SUPPR.");
				KMAP(DIK_INSERT, "INSERE");
				KMAP(DIK_HOME, "DEBUT");
				KMAP(DIK_END, "FIN");
				KMAP(DIK_UP, "FLECHE HAUT");
				KMAP(DIK_DOWN, "FLECHE BAS");
				KMAP(DIK_LEFT, "FLECHE GAUCHE");
				KMAP(DIK_RIGHT, "FLECHE DROITE");
				KMAP(DIK_RCONTROL, "CONTROL DROITE");
				/*KMAP(DIK_LWIN, "WIN GAUCHE");
				KMAP(DIK_RWIN, "WIN DROITE");
				KMAP(DIK_APPS, "APPS");*/

			default:
				strcpy(str, "INDEFINIE");
				break;
		}
	} else {
		int	d = n & 0x3FF;

		switch (d) {
			case JOY_UP:
				sprintf(str, "JOY%d HAUT", j);
				break;
			case JOY_DOWN:
				sprintf(str, "JOY%d BAS", j);
				break;
			case JOY_LEFT:
				sprintf(str, "JOY%d GAUCHE", j);
				break;
			case JOY_RIGHT:
				sprintf(str, "JOY%d DROITE", j);
				break;
			default:
				sprintf(str, "JOY%d BOUTON%d", j, d + 1);
				break;
		}
	}
}