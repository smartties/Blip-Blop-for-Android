/******************************************************************
*
*
*		----------------
*		  Input.h
*		----------------
*
*		Classe Input
*
*
*		La Classe Input représente toutes les entrées :
*
*		 - Clavier
*
*
*
*
*		Prosper / LOADED -   V 0.2
update
anyKeyPressed
waitClean
waitKey

scanKey
*
*
*
******************************************************************/

#ifndef _BENINPUT_
#define _BENINPUT_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "graphics.h"
#include "log.h"

//-----------------------------------------------------------------------------
//		Constantes pour les entrées
//-----------------------------------------------------------------------------

/*SDL KEYS*/
#define DIK_ESCAPE SDLK_ESCAPE
#define DIK_UP SDLK_UP
#define DIK_DOWN SDLK_DOWN
#define DIK_LEFT SDLK_LEFT
#define DIK_RIGHT SDLK_RIGHT
#define DIK_LCONTROL SDLK_LCTRL
#define DIK_LMENU SDLK_MENU
#define DIK_SPACE SDLK_SPACE
#define DIK_Q 	SDLK_q
#define DIK_W	SDLK_w
#define DIK_E	SDLK_e
#define DIK_R	SDLK_r
#define DIK_T	SDLK_t
#define DIK_Y	SDLK_y
#define DIK_U	SDLK_u
#define DIK_I	SDLK_i
#define DIK_O	SDLK_o
#define DIK_P	SDLK_p
#define DIK_L	SDLK_l
#define DIK_K	SDLK_k
#define DIK_J	SDLK_j
#define DIK_H	SDLK_h
#define DIK_G	SDLK_g
#define DIK_F	SDLK_f
#define DIK_D	SDLK_d
#define DIK_S	SDLK_s
#define DIK_A	SDLK_a
#define DIK_Z	SDLK_z
#define DIK_X	SDLK_x
#define DIK_C	SDLK_c
#define DIK_V	SDLK_v
#define DIK_B	SDLK_b
#define DIK_N	SDLK_n
#define DIK_M	SDLK_m

#define DIK_TAB SDLK_TAB
#define DIK_F1 SDLK_F1
#define DIK_F2 SDLK_F2
#define DIK_F3 SDLK_F3
#define DIK_F4 SDLK_F4
#define DIK_F5 SDLK_F5
#define DIK_F6 SDLK_F6
#define DIK_F7 SDLK_F7
#define DIK_F8 SDLK_F8
#define DIK_F9 SDLK_F9
#define DIK_F10 SDLK_F10
#define DIK_F11 SDLK_F11
#define DIK_F12 SDLK_F12
#define DIK_F13 SDLK_F13
#define DIK_F14 SDLK_F14
#define DIK_F15 SDLK_F15

#define DIK_COMMA SDLK_COMMA
#define DIK_PERIOD SDLK_PERIOD
#define DIK_SLASH SDLK_SLASH
#define DIK_RSHIFT SDLK_RSHIFT
#define DIK_MULTIPLY SDLK_KP_MULTIPLY
#define DIK_CAPITAL SDLK_CAPSLOCK
#define DIK_NUMLOCK SDLK_NUMLOCKCLEAR

#define DIK_RETURN SDLK_RETURN

#define DIK_0 SDLK_0
#define DIK_1 SDLK_1
#define DIK_2 SDLK_2
#define DIK_3 SDLK_3
#define DIK_4 SDLK_4
#define DIK_5 SDLK_5
#define DIK_6 SDLK_6
#define DIK_7 SDLK_7
#define DIK_8 SDLK_8
#define DIK_9 SDLK_9

#define DIK_MINUS SDLK_MINUS
#define DIK_EQUALS SDLK_EQUALS
#define DIK_BACK SDLK_BACKSPACE

#define DIK_LBRACKET SDLK_LEFTBRACKET
#define DIK_RBRACKET SDLK_RIGHTBRACKET

#define DIK_SEMICOLON SDLK_SEMICOLON
#define DIK_APOSTROPHE SDLK_QUOTE
/*#define DIK_GRAVE SDLK_EXCLAIM*/
#define DIK_LSHIFT SDLK_LSHIFT
#define DIK_BACKSLASH SDLK_BACKSLASH
#define DIK_SCROLL SDLK_SCROLLLOCK
#define DIK_BACKSPACE SDLK_BACKSPACE
#define DIK_LALT SDLK_LALT
//#define DIK_OEM_102 SDLK_EXCLAIM

#define DIK_NUMPAD1 SDLK_KP_1
#define DIK_NUMPAD2 SDLK_KP_2
#define DIK_NUMPAD3 SDLK_KP_3
#define DIK_NUMPAD4 SDLK_KP_4
#define DIK_NUMPAD5 SDLK_KP_5
#define DIK_NUMPAD6 SDLK_KP_6
#define DIK_NUMPAD7 SDLK_KP_7
#define DIK_NUMPAD8 SDLK_KP_8
#define DIK_NUMPAD9 SDLK_KP_9
#define DIK_NUMPAD0 SDLK_KP_0
#define DIK_ADD SDLK_KP_PLUS
#define DIK_SUBTRACT SDLK_MINUS
#define DIK_DECIMAL SDLK_KP_DECIMAL
#define DIK_NUMPADENTER SDLK_KP_ENTER
#define DIK_DIVIDE SDLK_KP_DIVIDE
#define DIK_RMENU SDLK_RALT
#define DIK_PRIOR SDLK_PAGEUP
#define DIK_NEXT SDLK_PAGEDOWN
#define DIK_DELETE SDLK_DELETE
#define DIK_INSERT SDLK_INSERT
#define DIK_HOME SDLK_HOME
#define DIK_END SDLK_END
#define DIK_RCONTROL SDLK_RCTRL

/**/

#define	BINPUT_KEYB		1		// On peut utiliser le clavier
#define BINPUT_JOY		2		// On peut utiliser un joystick

#define MAX_JOY			5		// Nombre maximal de joystick pouvant être gérés

#define	JOY_UP			10
#define	JOY_DOWN		11
#define	JOY_LEFT		12
#define	JOY_RIGHT		13

struct DIJOYSTATE
{
	char name[64];
	SDL_Joystick *handle;
};

extern bool app_killed;


float calcul_angle(float x1, float y1, float x2, float y2);
void update_tir(int &x, int &y, int xd, int yd, float angle);
//-----------------------------------------------------------------------------
//		Définition de la classe Input
//-----------------------------------------------------------------------------

#define TOUCH_NOTHING  0
#define TOUCH_PRESSING 1
#define TOUCH_DOWN     2
#define TOUCH_UP       3

class Finger
{
    public :
    Finger()
    {
        state = TOUCH_NOTHING;
        x = 0;
        y = 0;
    }

    int state;

    float x;
    float y;
    void *ptr;
};
class Touch_manager
{
    public :

    bool set(int f_id, int state, float x, float y)
    {
        if(f_id < 0 || f_id > 1)
        return false;

        finger[f_id].x = x;
        finger[f_id].y = y;

        if(state == TOUCH_PRESSING && finger[f_id].state == TOUCH_DOWN)
        finger[f_id].state = TOUCH_DOWN;
        else if( (finger[f_id].state == TOUCH_DOWN || finger[f_id].state == TOUCH_PRESSING ) && state == TOUCH_NOTHING)
        finger[f_id].state = TOUCH_UP;
        else
        finger[f_id].state = state;

        if(finger[f_id].state == TOUCH_UP)
        LOGI("UP");


        if(finger[f_id].state == TOUCH_NOTHING)
        finger[f_id].ptr = NULL;

        return true;
    }

    void refresh()
    {
        int i;

        for(i = 0; i < 2; i++)
        {
            if(finger[i].state == TOUCH_PRESSING)
            finger[i].state = TOUCH_DOWN;
            if(finger[i].state == TOUCH_UP)
            {
                finger[i].state = TOUCH_NOTHING;
                finger[i].ptr = NULL;
            }

        }
        gauche = false;
        haut = false;
        droit = false;
        bas = false;
        tirer = false;
        sauter = false;
        ulti = false;
    }

    void reset()
    {
        int i;
        for(i = 0; i < 2; i++)
        {
            finger[i].x = 0;
            finger[i].y = 0;
            finger[i].state = TOUCH_NOTHING;
            finger[i].ptr = NULL;
        }

        gauche = false;
        haut = false;
        droit = false;
        bas = false;
        tirer = false;
        sauter = false;
        ulti = false;
        angle = 0;
        dist = 0;
    }

    int search_up()
    {
        int i;

        for(i = 0; i < 2; i++)
        {
            if(finger[i].state == TOUCH_UP)
            return i;
        }

        return -1;
    }
    bool so_up()
    {
        return search_up() >= 0;
    }
    int search_down()
    {
        int i;

        for(i = 0; i < 2; i++)
        {
            if(finger[i].state == TOUCH_PRESSING || finger[i].state == TOUCH_DOWN)
            return i;
        }

        return -1;
    }
    bool so_down()
    {
        return search_down() >= 0;
    }

    int search_ptr(void *ptr)
    {
        int i;

        for(i = 0; i < 2; i++)
        {
            if(finger[i].ptr == ptr)
            return i;
        }

        return -1;
    }

    int search_pressing()
    {
        int i;

        for(i = 0; i < 2; i++)
        {
            if(finger[i].state == TOUCH_PRESSING)
            return i;
        }

        return -1;
    }
    bool so_pressing()
    {
        return search_pressing() >= 0;
    }
    bool nothing()
    {
        int i;

        for(i = 0; i < 2; i++)
        {
            if(finger[i].state != TOUCH_NOTHING)
            return false;
        }

        return true;
    }

    Finger finger[2];
    bool gauche;
    bool haut;
    bool droit;
    bool bas;
    bool tirer;
    bool sauter;
    bool ulti;

    bool padded;
    double pad_x;
    double pad_y;
    float angle;
    float dist;
};



class Input : public Touch_manager
{
private:
	int				n_joy;
	DIJOYSTATE		js[MAX_JOY];
	char 			buffer[256];
	char			specialsbuffer[0xFFF];
	unsigned int	aliastab[256];

public:
	Input();
	~Input();

	int scanKey(unsigned int k) const;

	inline int scanAlias(int a) const
	{
		return (scanKey(aliastab[a]));
	};
	inline unsigned int getAlias(int n) const
	{
		return aliastab[n];
	};

	int		nbJoy() const
	{
		return n_joy;
	};
	bool	open(HWND wh, HINSTANCE inst, int flags = BINPUT_KEYB | BINPUT_JOY);
	void	setAlias(int a, unsigned int val);

	unsigned int		waitKey();

	void	waitClean();
	void	update();
	void	close();
	bool	anyKeyPressed();
	bool	reAcquire();
};

//-----------------------------------------------------------------------------
//		Déclaration d'un objet 'in' global
//-----------------------------------------------------------------------------

#ifndef BENINPUT_CPP_FILE
extern Input		in;
#endif

#endif
