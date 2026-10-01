#include "main.h"
#include "SDL.h"


int main(int argc, char **argv)
{
    // Must be set before SDL_Init (graphics.cpp).
    // - BACK (TV remote, phone) is delivered to the game as SDLK_AC_BACK
    //   instead of finishing the activity: it opens the pause menu / goes back.
    // - The accelerometer is not a joystick, TV remotes are plain keys
    //   (arrows / SELECT / BACK) and real gamepads are SDL game controllers.
    SDL_SetHint(SDL_HINT_ANDROID_TRAP_BACK_BUTTON, "1");
    SDL_SetHint(SDL_HINT_ACCELEROMETER_AS_JOYSTICK, "0");
    SDL_SetHint(SDL_HINT_TV_REMOTE_AS_JOYSTICK, "0");
    SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "0");

    if (!InitApp(0, 0)) {
        // Usually the game data is missing from the APK (assets/data, see
        // tools/fetch_game_data.sh). Say so instead of closing silently.
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Blip & Blop",
            "The game could not start: its data files are missing or damaged.\n"
            "Reinstall the app.", NULL);
        return 1;
    }

    game.go();

    // "EXIT" in the main menu: returning ends the activity (Smartblip
    // then ends the process so a relaunch starts from a clean state).
    return 0;
}
