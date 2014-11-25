/******************************************************************
*
*
*		----------------
*		  Input.cpp
*		----------------
*
*		Classe Input
*
*
*		La Classe Input représente toutes les entrées :
*
*		 - Clavier
*		 - Joystick
*
*
*
*		Prosper / LOADED -   V 0.2
*
*
*
******************************************************************/

#define BENINPUT_CPP_FILE

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "graphics.h"
#include "input.h"
#include "ben_debug.h"



float calcul_angle(float x1, float y1, float x2, float y2)
{
            float angle_rad = 0, angle = 0;
            float horizontale = 0, verticale = 0;

            if(x1 == x2 && y1 == y2)
            return 4000;

            if(x2 - x1 > 0)
            horizontale = x2 - x1;
            else
            horizontale = x1 - x2;

            if(y2 - y1 > 0)
            verticale = y2 - y1;
            else
            verticale = y1 - y2;

            if(x2 >= x1 && y2 <= y1)
            {
            angle_rad = (float)atan(verticale/horizontale);
            angle = (float)(180.0 * angle_rad / M_PI);
            }
            if(x2 <= x1 && y2 <= y1)
            {
            angle_rad = (float)atanf(horizontale/verticale);
            angle = (float)(180.0 * angle_rad / M_PI) + 90.0;
            }
            else if(x2 <= x1 && y2 >= y1)
            {
            angle_rad = (float)atanf(verticale/horizontale);
            angle = (float)(180.0 * angle_rad / M_PI) + 180.0;
            }
            else if(x2 >= x1 && y2 >= y1)
            {
            angle_rad = (float)atanf(horizontale/verticale);
            angle = (float)(180.0 * angle_rad / M_PI) + 270.0;
            }

            return angle;
}

void update_tir(int &_x, int &_y, int xd, int yd, float angle)
{
    float dist = sqrt(xd*xd+yd*yd);
    float x, y, ang = angle;

    if(angle > 350)
    angle = 360;
    if(angle > 180 && angle < 190)
    angle = 180;

    angle = (M_PI*angle)/180.f;
    x = cos(angle)*dist;
    y = sin(angle)*dist;

    _x += x;
    _y -= y;
}

//-----------------------------------------------------------------------------
//		Déclaration REELLE de l'objet 'in' global
//-----------------------------------------------------------------------------

Input		in;

//-----------------------------------------------------------------------------
// Nom: Input::Input() - CONSTRUCTEUR -
// Desc: Met à NULL les valeurs susceptibles de foirer
//-----------------------------------------------------------------------------

Input::Input() : n_joy(0)
{
	ZeroMemory(buffer, 256);
	ZeroMemory(specialsbuffer, 0xFFF);
	gauche = false;
    haut = false;
    droit = false;
    bas = false;
    tirer = false;
    sauter = false;
    ulti = false;
    padded = false;
    angle = 0;
}

Input::~Input()
{

}



//-----------------------------------------------------------------------------
// Nom: Input::open(HWND, HINSTANCE, int, int)
// Desc: Ouvre BINPUT
//-----------------------------------------------------------------------------

bool Input::open(HWND wh, HINSTANCE inst, int flags)
{

	SDL_JoystickEventState(SDL_TRUE);

	this->n_joy = SDL_NumJoysticks();

	for (int i = 0; i < n_joy; i++)
	{
		js[i].handle = SDL_JoystickOpen(i);
		strcpy(this->js[i].name, SDL_JoystickName(js[i].handle));
	}

	/*if (dinput != NULL) {
		debug << "Input::open->DINPUT déjà initialisé!\n";
		return false;
	}

	if (DirectInput8Create(inst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, NULL) != DI_OK) {
		debug << "Input::open->Ne peut pas ouvrir DINPUT\n";
		dinput = NULL;
		return false;
	}


	if (flags & BINPUT_KEYB) {
		if (dinput->CreateDevice(GUID_SysKeyboard, (LPDIRECTINPUTDEVICE8A *)&dikeyb, NULL) != DI_OK) {
			debug << "Input::open->Ne peut pas créer le clavier!\n";
			dikeyb = NULL;
			return false;
		} else {
			if (dikeyb->SetDataFormat(&c_dfDIKeyboard) != DI_OK) {
				debug << "Input::open->Ne peut pas initialiser le clavier (set data)\n";
				dikeyb->Release();
				dikeyb = NULL;
				return false;
			} else {
				if (dikeyb->SetCooperativeLevel(wh, cl) != DI_OK) {
					debug << "Input::open->Ne peut pas règler le coop du clavier\n";
					dikeyb->Release();
					dikeyb = NULL;
					return false;
				} else
					dikeyb->Acquire();
			}
		}
	}

	// Associe le joystick
	//
	if (flags & BINPUT_JOY) {
		if (dinput->EnumDevices(DI8DEVTYPE_GAMEPAD, EnumJoysticksCallback, this, DIEDFL_ATTACHEDONLY) != DI_OK) {
			debug << "Cannot enumerate joysticks\n";
		} else {
			debug << n_joy << " joystick(s) found\n";

			for (int i = 0; i < n_joy; i++) {
				if (dijoy[i] != NULL) {
					if (dijoy[i]->SetDataFormat(&c_dfDIJoystick) != DI_OK) {
						debug << "Cannot initialise joystick " << i << "\n";
						dijoy[i]->Release();
						dijoy[i] = NULL;
					} else {
						if (dijoy[i]->SetCooperativeLevel(wh, DISCL_EXCLUSIVE | DISCL_FOREGROUND) != DI_OK) {
							debug << "Cannot set priority level of joystick " << i << "\n";
							dijoy[i]->Release();
							dijoy[i] = NULL;
						} else {
							DIPROPRANGE diprg;

							diprg.diph.dwSize       = sizeof(diprg);
							diprg.diph.dwHeaderSize = sizeof(diprg.diph);
							diprg.diph.dwObj        = DIJOFS_X;
							diprg.diph.dwHow        = DIPH_BYOFFSET;
							diprg.lMin              = -1000;
							diprg.lMax              = +1000;

							dijoy[i]->SetProperty(DIPROP_RANGE, &diprg.diph);

							diprg.diph.dwObj        = DIJOFS_Y;
							dijoy[i]->SetProperty(DIPROP_RANGE, &diprg.diph);

							DIPROPDWORD dipdw;

							dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
							dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
							dipdw.diph.dwHow        = DIPH_BYOFFSET;
							dipdw.dwData            = 5000;

							dipdw.diph.dwObj         = DIJOFS_X;
							dijoy[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);

							dipdw.diph.dwObj = DIJOFS_Y;
							dijoy[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);


							if (dijoy[i]->Acquire() != DI_OK) {
								debug << "Cannot get joystick " << i << "\n";
							}
						}
					}
				}
			}
		}
	}*/

	return true;
}

//-----------------------------------------------------------------------------
// Nom: Input::update()
// Desc: Met à jour les entrées
//-----------------------------------------------------------------------------

void Input::update()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)){

		if (e.type == SDL_QUIT)
		{
			app_killed = true;
			exit(0);
		}

		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym < 255)
			{
				buffer[e.key.keysym.sym] = 1;
			}
			else
				specialsbuffer[e.key.keysym.sym & 0xFFF] = 1;
		}
		if (e.type == SDL_KEYUP)
		{
			if (e.key.keysym.sym < 255)
			{
				buffer[e.key.keysym.sym] = 0;
			}
			else
				specialsbuffer[e.key.keysym.sym & 0xFFF] = 0;
		}

		if(e.type == SDL_FINGERUP || e.type == SDL_FINGERDOWN || e.type == SDL_FINGERMOTION)
		{
		    int state;

		    if(e.type == SDL_FINGERDOWN || e.type == SDL_FINGERMOTION)
		    state = TOUCH_PRESSING;
		    if(e.type == SDL_FINGERUP)
		    state = TOUCH_NOTHING;

		    set(e.tfinger.fingerId, state, e.tfinger.x, e.tfinger.y);
		}
	}
	/*if (dikeyb != NULL)
		dikeyb->GetDeviceState(sizeof(buffer), (void *)&buffer);

	for (int i = 0; i < n_joy; i++) {
		if (dijoy[i] != NULL) {
			dijoy[i]->Poll();
			dijoy[i]->GetDeviceState(sizeof(DIJOYSTATE), (void*) &js[i]);
		}
	}*/
}

//-----------------------------------------------------------------------------
// Nom: Input::waitKey()
// Desc: Attends que l'utilisateur tape une touche et renvoie sa valeur
//-----------------------------------------------------------------------------

unsigned int Input::waitKey()
{
	unsigned int	key = 0;

	while (1)
	{
		update();
		for (int i = 0; i < 256; i++)
		{
			if (buffer[i] != 0)
			{
				return i;
			}
		}
		for (int i = 0; i < 0xFFF; i++)
		{
			if (specialsbuffer[i] != 0)
			{
				return i | 0x40000000;
			}
		}
	}
	/*unsigned int	i = 0;
	int				j;
	int				k;

	while (key == 0) {
		update();

		for (i = 0; i < 256; i++)
			if (scanKey(i))
				key = i;

		for (i = 0; i < (unsigned int)n_joy; i++) {
			k = (i + 1) * (1 << 10);

			for (j = 0; j < 14; j++)
				if (scanKey(k + j))
					key = k + j;
		}
	}*/

	return key;
}

//-----------------------------------------------------------------------------
// Nom: Input::waitClean()
// Desc: Attends qu'aucune touche ne soit enfoncée
//-----------------------------------------------------------------------------

void Input::waitClean()
{
	//Waits for all keys to be released?
	while (1)
	{
		bool j = false;
		update();
		for (int i = 0; i < 256; i++)
		{
			if (buffer[i] != 0)
			{
				j = true;
			}
		}
		for (int i = 0; i < 0xFFF; i++)
		{
			if (specialsbuffer[i] != 0)
			{
				j = true;
			}
		}
		if (!j)
			return;
	}
	/*unsigned int		i, j = 1;		// Bcoz si j = 0 alors on sort tout de suite!

	while (j) {
		update();
		j = 0;
		for (i = 0; i < 256; i++)
			j |= scanKey(i);

		for (i = 0; i < (unsigned int)n_joy; i++) {
			unsigned int k = (i + 1) * (1 << 10);

			for (int l = 0; l < 14; l++)
				j |= scanKey(k + l);
		}
	}*/

}

//-----------------------------------------------------------------------------
// Nom: Input::setAlias()
// Desc: Règle la valeur d'un alias
//-----------------------------------------------------------------------------
void Input::setAlias(int a, unsigned int val)
{
	aliastab[a] = val;
}

//-----------------------------------------------------------------------------
// Nom: Input::close()
// Desc: Ferme toutes les entrées
//-----------------------------------------------------------------------------

void Input::close()
{
	/*if (dikeyb != NULL) {
		dikeyb->Unacquire();
		dikeyb->Release();
		dikeyb = NULL;
	}

	if (dinput != NULL) {
		dinput->Release();
		dinput = NULL;
	}

	for (int i = 0; i < n_joy; i++) {
		if (dijoy[i] != NULL) {
			dijoy[i]->Release();
			dijoy[i] = NULL;
		}
	}

	n_joy = 0;*/
}


//-----------------------------------------------------------------------------

bool Input::anyKeyPressed()
{
	unsigned int	i;
	unsigned int	k;
	int key = 0;

	update();
	for (int i = 0; i < 256; i++)
	{
		if (buffer[i] != 0)
		{
			return true;
		}
	}
	for (int i = 0; i < 0xFFF; i++)
	{
		if (specialsbuffer[i] != 0)
		{
			return true;
		}
	}
	return false;


	/*int j;

	update();

	for (i = 0; i < 256; i++)
		if (scanKey(i))
			key = i;

	for (i = 0; i < (unsigned int)n_joy; i++) {
		k = (i + 1) * (1 << 10);

		for (j = 0; j < 14; j++)
			if (scanKey(k + j))
				key = k + j;
	}*/
}

int Input::scanKey(unsigned int k) const
{
	/*int j = (k >> 10);

	if (j == 0)
		return buffer[k] & 0x80;

	j -= 1;

	if (j < 0 || j >= n_joy)
		return 0;
	else {
		int		z = 0;
		int		k2 = k & 0x3FF;

		switch (k2) {
			case JOY_UP:
				if (js[j].lY < -200) z = 1;
				break;

			case JOY_DOWN:
				if (js[j].lY > 200) z = 1;
				break;

			case JOY_LEFT:
				if (js[j].lX < -200) z = 1;
				break;

			case JOY_RIGHT:
				if (js[j].lX > 200) z = 1;
				break;

			default:
				z = (js[j].rgbButtons[k2] & 0x80);
				break;
		}

		return z;
	}*/
	if (k<255)
		return buffer[k];
	else
		return specialsbuffer[k & 0xFFF];

	return 0;
}

//-----------------------------------------------------------------------------
// Nom: Input::waitKey()
// Desc: Attends que l'utilisateur tape une touche et renvoie sa valeur
//-----------------------------------------------------------------------------

bool Input::reAcquire()
{
	/*if (dinput == NULL)
		return false;

	if (dikeyb != NULL)
		dikeyb->Acquire();

	for (int i = 0; i < MAX_JOY; i++)
		if (dijoy[i] != NULL)
			dijoy[i]->Acquire();*/

	return true;
}
