package com.blip.blop;

import android.view.InputDevice;
import android.view.KeyEvent;
import android.view.MotionEvent;

import org.libsdl.app.SDLActivity;

public class Smartblip extends SDLActivity
{
    @Override
    protected String[] getLibraries() {
        return new String[] {
            "SDL2",
            "SDL2_mixer",
            "main"
        };
    }

    // Gamepad button key events from a device that SDL does not open as a
    // joystick (TV remotes, remote apps, "adb shell input gamepad keyevent")
    // go down SDL's keyboard path, where most BUTTON_* keys are dropped or
    // turned into the wrong key. Hand them over as F1..F6 instead;
    // jni/src/input.cpp gives those the same meaning as on a controller.
    // Real controllers are left alone: SDL reads them as game controllers.
    private static int gamepadButtonToKey(int keyCode) {
        switch (keyCode) {
            case KeyEvent.KEYCODE_BUTTON_A:      return KeyEvent.KEYCODE_F1;
            case KeyEvent.KEYCODE_BUTTON_B:      return KeyEvent.KEYCODE_F2;
            case KeyEvent.KEYCODE_BUTTON_X:
            case KeyEvent.KEYCODE_BUTTON_R1:
            case KeyEvent.KEYCODE_BUTTON_R2:     return KeyEvent.KEYCODE_F3;
            case KeyEvent.KEYCODE_BUTTON_Y:
            case KeyEvent.KEYCODE_BUTTON_L1:
            case KeyEvent.KEYCODE_BUTTON_L2:     return KeyEvent.KEYCODE_F4;
            case KeyEvent.KEYCODE_BUTTON_START:  return KeyEvent.KEYCODE_F5;
            case KeyEvent.KEYCODE_BUTTON_SELECT: return KeyEvent.KEYCODE_F6;
            default:                             return -1;
        }
    }

    // Same rule as SDL: with SDL_TV_REMOTE_AS_JOYSTICK=0, Android_AddJoystick
    // skips devices with fewer than two joystick axes and no hat.
    private static boolean opensAsJoystick(int deviceId) {
        InputDevice device = InputDevice.getDevice(deviceId);
        if (device == null)
            return false;
        int axes = 0, hats = 0;
        for (InputDevice.MotionRange range : device.getMotionRanges()) {
            if ((range.getSource() & InputDevice.SOURCE_CLASS_JOYSTICK) == 0)
                continue;
            if (range.getAxis() == MotionEvent.AXIS_HAT_X || range.getAxis() == MotionEvent.AXIS_HAT_Y)
                hats++;
            else
                axes++;
        }
        return axes >= 2 || hats >= 2;   // a hat is an X and a Y range
    }

    @Override
    public boolean dispatchKeyEvent(KeyEvent event) {
        int key = gamepadButtonToKey(event.getKeyCode());
        if (key >= 0 && !opensAsJoystick(event.getDeviceId())) {
            event = new KeyEvent(event.getDownTime(), event.getEventTime(), event.getAction(),
                    key, event.getRepeatCount(), event.getMetaState(), event.getDeviceId(),
                    event.getScanCode(), event.getFlags(), event.getSource());
        }
        return super.dispatchKeyEvent(event);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        // The C++ game keeps all of its state in globals and cannot be
        // started twice in the same process. When the activity really goes
        // away (EXIT in the menu, swiped from recents), end the process so the
        // next launch starts clean.
        if (isFinishing()) {
            System.exit(0);
        }
    }
}
