#!/bin/sh
# Build, boot an emulator (window + host GPU), install and launch the game.
# Usage: tools/play.sh [avd]   (default: bb_tv; e.g. bb_phone)
set -e
AVD=${1:-bb_tv}
cd "$(dirname "$0")/.."
export JAVA_HOME=${JAVA_HOME:-/opt/homebrew/opt/openjdk@17}
export ANDROID_HOME=${ANDROID_HOME:-$HOME/Library/Android/sdk}
export PATH="$ANDROID_HOME/platform-tools:$ANDROID_HOME/emulator:$PATH"

[ -d assets/data ] || tools/fetch_game_data.sh
./gradlew -q assembleDebug

# Without hw.keyboard=yes the emulator drops the Mac's keyboard input.
CFG="$HOME/.android/avd/$AVD.avd/config.ini"
[ -f "$CFG" ] && sed -i '' 's/^hw.keyboard=no/hw.keyboard=yes/' "$CFG"

emu() { adb devices | awk '/^emulator-/{print $1; exit}'; }
if [ -z "$(emu)" ]; then
    emulator -avd "$AVD" -gpu host >/dev/null 2>&1 &
    until [ -n "$(emu)" ]; do sleep 2; done
fi
export ANDROID_SERIAL=$(emu)   # target the emulator even if a phone is plugged in
adb wait-for-device
until [ "$(adb shell getprop sys.boot_completed 2>/dev/null | tr -d '\r')" = 1 ]; do sleep 2; done

adb install -r build/outputs/apk/debug/BlipBlop-debug.apk
adb shell am start -n com.blip.blop/.Smartblip
