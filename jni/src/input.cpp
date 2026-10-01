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
#include <unistd.h>



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
	for (int p = 0; p < NB_PAD_PLAYERS; p++) {
		pads[p].gc = NULL;
		pads[p].id = -1;
		pads[p].stick_dir = -1;
		for (int t = 0; t < 2; t++) {
			pads[p].trig_rest[t] = 0;
			pads[p].trig_on[t] = false;
		}
		super_pending[p] = 0;
		aim[p] = 0.0f;
		last_hdir[p] = 1;
		for (int i = 0; i < NB_ACT; i++)
			act_held[p][i] = false;
	}
	pause_pending = false;
	disconnect_pending = false;
	pad_any_held = false;
	two_players = false;
	ZeroMemory(buffer, 256);
	ZeroMemory(specialsbuffer, sizeof(specialsbuffer));
	gauche = false;
    haut = false;
    droit = false;
    bas = false;
    tirer = false;
    sauter = false;
    ulti = false;
    ulti2 = false;
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

	// Controllers are opened when SDL reports them (SDL_CONTROLLERDEVICEADDED
	// is sent for every pad already connected at SDL_Init and on hot-plug),
	// see Input::update().
	n_joy = 0;

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

// Keyboard / TV remote keys -> game actions and menu navigation.
// A TV remote (NVIDIA Shield remote, Android TV remotes, "adb shell input
// keyevent") arrives as keyboard keys: DPAD -> arrows, DPAD_CENTER -> SELECT,
// BACK -> AC_BACK.
struct KeyMap {
	SDL_Keycode	key;
	int			act;	// -1 = none
	int			nav;	// -1 = none
};

static const KeyMap key_map[] = {
	{ SDLK_UP,				ACT_UP,		NAV_UP },
	{ SDLK_DOWN,			ACT_DOWN,	NAV_DOWN },
	{ SDLK_LEFT,			ACT_LEFT,	NAV_LEFT },
	{ SDLK_RIGHT,			ACT_RIGHT,	NAV_RIGHT },
	{ SDLK_SELECT,			ACT_FIRE,	NAV_OK },		// remote OK / DPAD center
	{ SDLK_RETURN,			ACT_FIRE,	NAV_OK },
	{ SDLK_KP_ENTER,		ACT_FIRE,	NAV_OK },
	{ SDLK_LCTRL,			ACT_FIRE,	-1 },
	{ SDLK_RCTRL,			ACT_FIRE,	-1 },
	{ SDLK_z,				ACT_FIRE,	NAV_OK },
	{ SDLK_x,				ACT_JUMP,	-1 },
	{ SDLK_LALT,			ACT_JUMP,	-1 },
	{ SDLK_MENU,			ACT_JUMP,	-1 },		// remote menu key
	{ SDLK_AUDIOPLAY,		ACT_JUMP,	-1 },		// remote play/pause
	{ SDLK_c,				ACT_SUPER,	-1 },
	{ SDLK_SPACE,			ACT_SUPER,	-1 },
	{ SDLK_AUDIOFASTFORWARD,ACT_SUPER,	-1 },
	{ SDLK_AC_BACK,			ACT_PAUSE,	NAV_BACK },	// Android BACK (trapped, see main.cpp)
	{ SDLK_ESCAPE,			ACT_PAUSE,	NAV_BACK },
	{ SDLK_BACKSPACE,		-1,			NAV_BACK },
	{ SDLK_p,				ACT_PAUSE,	-1 },
	{ SDLK_PAUSE,			ACT_PAUSE,	-1 },
	// Gamepad buttons sent by a device Android does not report as a game
	// controller (some TV remotes and remote apps, "adb shell input gamepad
	// keyevent"). Smartblip.java turns them into F1..F6, with the same
	// meaning as on a controller (button_map below).
	{ SDLK_F1,				ACT_JUMP,	NAV_OK },		// A
	{ SDLK_F2,				ACT_SUPER,	NAV_BACK },		// B
	{ SDLK_F3,				ACT_FIRE,	NAV_OK },		// X, R1, R2
	{ SDLK_F4,				ACT_SUPER,	-1 },			// Y, L1, L2
	{ SDLK_F5,				ACT_PAUSE,	NAV_OK },		// START
	{ SDLK_F6,				ACT_PAUSE,	NAV_BACK },		// SELECT
};
static const int NB_KEY_MAP = sizeof(key_map) / sizeof(key_map[0]);

// Game controller buttons -> game actions and menu navigation.
struct ButtonMap {
	SDL_GameControllerButton	button;
	int							act;
	int							nav;
};

static const ButtonMap button_map[] = {
	{ SDL_CONTROLLER_BUTTON_DPAD_UP,		ACT_UP,		NAV_UP },
	{ SDL_CONTROLLER_BUTTON_DPAD_DOWN,		ACT_DOWN,	NAV_DOWN },
	{ SDL_CONTROLLER_BUTTON_DPAD_LEFT,		ACT_LEFT,	NAV_LEFT },
	{ SDL_CONTROLLER_BUTTON_DPAD_RIGHT,		ACT_RIGHT,	NAV_RIGHT },
	{ SDL_CONTROLLER_BUTTON_A,				ACT_JUMP,	NAV_OK },
	{ SDL_CONTROLLER_BUTTON_X,				ACT_FIRE,	NAV_OK },
	{ SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,	ACT_FIRE,	-1 },
	{ SDL_CONTROLLER_BUTTON_B,				ACT_SUPER,	NAV_BACK },
	{ SDL_CONTROLLER_BUTTON_Y,				ACT_SUPER,	-1 },
	{ SDL_CONTROLLER_BUTTON_LEFTSHOULDER,	ACT_SUPER,	-1 },
	{ SDL_CONTROLLER_BUTTON_START,			ACT_PAUSE,	NAV_OK },
	{ SDL_CONTROLLER_BUTTON_BACK,			ACT_PAUSE,	NAV_BACK },
};
static const int NB_BUTTON_MAP = sizeof(button_map) / sizeof(button_map[0]);

#define STICK_THRESHOLD		14000	// ~0.43 of full deflection
#define TRIGGER_THRESHOLD	12000

// Triggers are compared with their rest position rather than with 0. When a
// centred axis (a stick axis, -1..1 on Android) ends up mapped on a trigger,
// SDL reads it at rest as exactly half pressed (16383), and the game would
// fire / drop cow bombs on its own. That value is taken as the rest position;
// any lower value brings the rest position back down. A full press still
// clears the threshold from a half-travel rest.
#define TRIGGER_CENTRED		16383	// SDL value of a centred axis on a trigger

bool Input::triggerHeld(int slot, int t, int value)
{
	PadSlot &pd = pads[slot];
	if (value == TRIGGER_CENTRED)
		pd.trig_rest[t] = value;
	else if (value < pd.trig_rest[t])
		pd.trig_rest[t] = value;
	return value - pd.trig_rest[t] > TRIGGER_THRESHOLD;
}

// Stick / DPAD directions -> aiming angle used by the shots (same convention
// as the touch pad in Game::updateTouch: 0 = right, 90 = up, 180 = left...).
static float dir_angle(bool l, bool r, bool u, bool d, int last_hdir)
{
	if (u && r) return 45;
	if (u && l) return 135;
	if (d && l) return 225;
	if (d && r) return 315;
	if (u) return 90;
	if (d) return 270;
	if (l) return 180;
	if (r) return 0;
	return last_hdir == 2 ? 180 : 0;
}

void Input::padAdded(int device_index)
{
	if (!SDL_IsGameController(device_index))
		return;

	SDL_JoystickID id = SDL_JoystickGetDeviceInstanceID(device_index);
	if (padSlot(id) >= 0)
		return;		// already open

	for (int p = 0; p < NB_PAD_PLAYERS; p++) {
		if (pads[p].gc == NULL) {
			pads[p].gc = SDL_GameControllerOpen(device_index);
			if (pads[p].gc == NULL)
				return;
			pads[p].id = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(pads[p].gc));
			pads[p].stick_dir = -1;
			pads[p].trig_rest[0] = pads[p].trig_rest[1] = 0;
			pads[p].trig_on[0] = pads[p].trig_on[1] = false;
			const char *nm = SDL_GameControllerName(pads[p].gc);
			LOGI("Controller connected: '%s' -> player %d", nm ? nm : "?", p + 1);
			char *map = SDL_GameControllerMapping(pads[p].gc);
			LOGI("  mapping: %s", map ? map : "?");
			SDL_free(map);
			n_joy = nbPads();
			return;
		}
	}
	LOGI("Controller ignored (already %d connected)", NB_PAD_PLAYERS);
}

void Input::padRemoved(SDL_JoystickID id)
{
	int p = padSlot(id);
	if (p < 0)
		return;

	SDL_GameControllerClose(pads[p].gc);
	pads[p].gc = NULL;
	pads[p].id = -1;
	pads[p].stick_dir = -1;
	for (int i = 0; i < NB_ACT; i++)
		act_held[p][i] = false;
	LOGI("Controller of player %d disconnected", p + 1);
	n_joy = nbPads();

	// In a 2-player game the slots stay put, so replugging gives the
	// player back their own character. Otherwise the controller that is
	// left becomes player 1.
	if (!two_players && compactPads())
		p = 1;

	// A controller vanished (unplugged, asleep, flat battery): the level
	// pauses (Game::updateMenu). Kept apart from pause_pending, which the
	// pause menu reads as "resume".
	disconnect_pending = true;

	// A controller ignored while both slots were taken takes the free one.
	for (int i = 0; i < SDL_NumJoysticks() && pads[p].gc == NULL; i++)
		if (SDL_JoystickGetDeviceInstanceID(i) != id)
			padAdded(i);
}

// Player 1's slot is free but player 2's is not: move player 2's
// controller to player 1, so the next one plugged in is player 2.
bool Input::compactPads()
{
	if (pads[0].gc != NULL || pads[1].gc == NULL)
		return false;
	pads[0] = pads[1];
	pads[1].gc = NULL;
	pads[1].id = -1;
	pads[1].stick_dir = -1;
	for (int i = 0; i < NB_ACT; i++) {
		act_held[0][i] = act_held[1][i];
		act_held[1][i] = false;
	}
	LOGI("Controller of player 2 is now player 1");
	return true;
}

void Input::setTwoPlayers(bool on)
{
	two_players = on;
	if (!on)
		compactPads();
}

int Input::padSlot(SDL_JoystickID id) const
{
	for (int p = 0; p < NB_PAD_PLAYERS; p++)
		if (pads[p].gc != NULL && pads[p].id == id)
			return p;
	return -1;
}

int Input::nbPads() const
{
	int n = 0;
	for (int p = 0; p < NB_PAD_PLAYERS; p++)
		if (pads[p].gc != NULL)
			n++;
	return n;
}

void Input::pressAction(int player, int act)
{
	if (act < 0)
		return;
	// In a one-player game every controller plays player 1.
	if (!two_players)
		player = 0;

	act_pressed[player][act] = true;

	if (act == ACT_SUPER)
		super_pending[player]++;
	if (act == ACT_PAUSE)
		pause_pending = true;
	if (act == ACT_FIRE || act == ACT_JUMP || act == ACT_SUPER || act == ACT_PAUSE)
		pad_tap = true;
}

void Input::pressNav(int n)
{
	if (n < 0)
		return;
	nav[n] = true;
	if (n == NAV_OK || n == NAV_BACK)
		pad_tap = true;
}

// Recomputes the "held" state of every action from the keyboard buffer and
// the current controller state (so a lost button-up event never sticks).
void Input::updateHeld()
{
	for (int p = 0; p < NB_PAD_PLAYERS; p++)
		for (int i = 0; i < NB_ACT; i++)
			act_held[p][i] = false;

	for (int k = 0; k < NB_KEY_MAP; k++)
		if (key_map[k].act >= 0 && scanKey(key_map[k].key))
			act_held[0][key_map[k].act] = true;

	pad_any_held = false;
	for (int p = 0; p < NB_PAD_PLAYERS; p++) {
		SDL_GameController *gc = pads[p].gc;
		if (gc == NULL)
			continue;

		int pl = two_players ? p : 0;
		bool h[NB_ACT] = { false };

		for (int b = 0; b < NB_BUTTON_MAP; b++)
			if (SDL_GameControllerGetButton(gc, button_map[b].button))
				h[button_map[b].act] = true;

		int ax = SDL_GameControllerGetAxis(gc, SDL_CONTROLLER_AXIS_LEFTX);
		int ay = SDL_GameControllerGetAxis(gc, SDL_CONTROLLER_AXIS_LEFTY);
		bool sl = ax < -STICK_THRESHOLD, sr = ax > STICK_THRESHOLD;
		bool su = ay < -STICK_THRESHOLD, sd = ay > STICK_THRESHOLD;
		if (sl) h[ACT_LEFT] = true;
		if (sr) h[ACT_RIGHT] = true;
		if (su) h[ACT_UP] = true;
		if (sd) h[ACT_DOWN] = true;

		if (triggerHeld(p, 0, SDL_GameControllerGetAxis(gc, SDL_CONTROLLER_AXIS_TRIGGERRIGHT)))
			h[ACT_FIRE] = true;
		if (triggerHeld(p, 1, SDL_GameControllerGetAxis(gc, SDL_CONTROLLER_AXIS_TRIGGERLEFT)))
			h[ACT_SUPER] = true;

		for (int i = 0; i < NB_ACT; i++) {
			if (h[i]) {
				act_held[pl][i] = true;
				pad_any_held = true;
			}
		}

		// Menu navigation with the stick: one step per push.
		int dir = -1;
		if (su) dir = NAV_UP;
		else if (sd) dir = NAV_DOWN;
		else if (sl) dir = NAV_LEFT;
		else if (sr) dir = NAV_RIGHT;
		if (dir != pads[p].stick_dir && dir >= 0)
			pressNav(dir);
		pads[p].stick_dir = dir;
	}

	for (int p = 0; p < NB_PAD_PLAYERS; p++) {
		bool l = padHeld(p, ACT_LEFT), r = padHeld(p, ACT_RIGHT);
		bool u = padHeld(p, ACT_UP), d = padHeld(p, ACT_DOWN);
		if (r) last_hdir[p] = 1;
		if (l) last_hdir[p] = 2;
		aim[p] = dir_angle(l, r, u, d, last_hdir[p]);
	}
}

bool Input::padHeld(int player, int act) const
{
	return act_held[player][act] || act_pressed[player][act];
}

bool Input::padHasDir(int player) const
{
	return padHeld(player, ACT_LEFT) || padHeld(player, ACT_RIGHT) ||
	       padHeld(player, ACT_UP) || padHeld(player, ACT_DOWN);
}

bool Input::takeSuper(int player)
{
	if (super_pending[player] <= 0)
		return false;
	super_pending[player] = 0;
	return true;
}

bool Input::takePause()
{
	bool r = pause_pending;
	pause_pending = false;
	return r;
}

bool Input::takeDisconnect()
{
	bool r = disconnect_pending;
	disconnect_pending = false;
	return r;
}

void Input::clearPadInput(bool keep_disconnect)
{
	clear_pad_edges();
	for (int p = 0; p < NB_PAD_PLAYERS; p++)
		super_pending[p] = 0;
	pause_pending = false;
	if (!keep_disconnect)
		disconnect_pending = false;
	nb_taps = 0;
}

//-----------------------------------------------------------------------------
// Nom: Input::update()
// Desc: Met à jour les entrées
//-----------------------------------------------------------------------------

extern void Graphics_RenderReset();
extern void Graphics_MapTouch(float &x, float &y);

void Input::update()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)){

		switch (e.type) {

		// Android lifecycle, handled here on the game thread (SDL blocks this
		// thread while the activity is paused).
		case SDL_APP_WILLENTERBACKGROUND:
			app_pause();
			break;
		case SDL_APP_DIDENTERFOREGROUND:
			app_resume();
			break;

		case SDL_QUIT:
			// The activity is being destroyed and the game cannot restart
			// in this process. _exit, not exit: exit() runs the C++ static
			// destructors while Android's render threads still use them,
			// which aborts (FORTIFY: pthread_mutex_lock on a destroyed mutex).
			app_killed = true;
			_exit(0);
			break;

		case SDL_RENDER_TARGETS_RESET:
		case SDL_RENDER_DEVICE_RESET:
			Graphics_RenderReset();
			break;

		case SDL_KEYDOWN:
		case SDL_KEYUP:
		{
			SDL_Keycode sym = e.key.keysym.sym;
			char v = (e.type == SDL_KEYDOWN) ? 1 : 0;

			// Keys SDL has no keycode for (Android KEYCODE_HENKAN and the
			// like) all arrive as SDLK_UNKNOWN (0): never record them.
			if (sym == SDLK_UNKNOWN)
				break;

			if (sym >= 0 && sym < 255)
				buffer[sym] = v;
			else
				specialsbuffer[sym & 0xFFF] = v;

			if (e.type == SDL_KEYDOWN && !e.key.repeat) {
				for (int k = 0; k < NB_KEY_MAP; k++) {
					if (key_map[k].key == sym) {
						pressAction(0, key_map[k].act);
						pressNav(key_map[k].nav);
					}
				}
			}
			break;
		}

		case SDL_CONTROLLERDEVICEADDED:
			padAdded(e.cdevice.which);
			break;
		case SDL_CONTROLLERDEVICEREMOVED:
			padRemoved(e.cdevice.which);
			break;

		case SDL_CONTROLLERBUTTONDOWN:
		{
			int p = padSlot(e.cbutton.which);
			if (p < 0)
				break;
			for (int b = 0; b < NB_BUTTON_MAP; b++) {
				if (button_map[b].button == e.cbutton.button) {
					pressAction(p, button_map[b].act);
					pressNav(button_map[b].nav);
				}
			}
			break;
		}

		case SDL_CONTROLLERAXISMOTION:
		{
			// Triggers: RT = fire, LT = cow bomb (edges only, held state is
			// polled in updateHeld()).
			int p = padSlot(e.caxis.which);
			if (p < 0)
				break;
			int t = -1, act = -1;
			if (e.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT) { t = 0; act = ACT_FIRE; }
			if (e.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT)  { t = 1; act = ACT_SUPER; }
			if (t < 0)
				break;
			bool on = triggerHeld(p, t, e.caxis.value);
			if (on && !pads[p].trig_on[t])
				pressAction(p, act);
			pads[p].trig_on[t] = on;
			break;
		}

		case SDL_FINGERUP:
		case SDL_FINGERDOWN:
		case SDL_FINGERMOTION:
		{
			int state = (e.type == SDL_FINGERUP) ? TOUCH_NOTHING : TOUCH_PRESSING;
			float fx = e.tfinger.x, fy = e.tfinger.y;
			// The 640x480 picture is letterboxed: map to picture coordinates.
			Graphics_MapTouch(fx, fy);
			set(e.tfinger.fingerId, state, fx, fy);
			if (e.type == SDL_FINGERDOWN)
				add_tap(fx, fy);
			break;
		}
		}
	}

	updateHeld();
}

//-----------------------------------------------------------------------------
// Nom: Input::waitKey()
// Desc: Attends que l'utilisateur tape une touche et renvoie sa valeur
//-----------------------------------------------------------------------------

unsigned int Input::waitKey()
{
	unsigned int	key = 0;

	while (!app_killed)
	{
		update();
		if (pad_tap)
		{
			pad_tap = false;
			return DIK_RETURN;
		}
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
		SDL_Delay(10);
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
	Uint32 start = SDL_GetTicks();
	while (1)
	{
		bool j = false;
		bool keys = false;
		update();
		for (int i = 0; i < 256; i++)
		{
			if (buffer[i] != 0)
			{
				keys = true;
			}
		}
		for (int i = 0; i < 0xFFF; i++)
		{
			if (specialsbuffer[i] != 0)
			{
				keys = true;
			}
		}
		// Wait for keys and controller buttons to be released, but never
		// more than a second: a drifting stick, a noisy trigger or a remote
		// key whose release got lost must not freeze the game here.
		bool waited = SDL_GetTicks() - start >= 1000;
		if ((keys || pad_any_held) && !waited)
			j = true;
		if (!j || app_killed)
		{
			if (keys) {
				// Still "held" after a second: most likely the release was
				// lost (e.g. across a background / foreground switch).
				// Forget it, or the key would stay stuck in the game too.
				LOGI("waitClean: key still held after 1 s, releasing it");
				ZeroMemory(buffer, sizeof(buffer));
				ZeroMemory(specialsbuffer, sizeof(specialsbuffer));
			}
			if (pad_any_held) {
				int mask = 0;
				for (int p = 0; p < NB_PAD_PLAYERS; p++)
					for (int a = 0; a < NB_ACT; a++)
						if (act_held[p][a])
							mask |= 1 << (p * NB_ACT + a);
				LOGI("waitClean: controller still held (actions 0x%x), continuing anyway", mask);
			}
			// Whatever was pressed to get here must not also trigger the
			// next screen.
			clearPadInput();
			return;
		}
		SDL_Delay(10);
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
	if (pad_tap)
		return true;
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
