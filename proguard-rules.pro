# R8 / ProGuard rules for the release build (build.gradle).
#
# The native code (SDL2, SDL2_mixer, the game) finds the Java side by name
# through JNI: org.libsdl.app classes, their native methods and the methods C
# calls back (SDLActivity, SDLAudioManager, SDLControllerManager,
# HIDDeviceManager...). None of them may be renamed or removed.
-keep,includedescriptorclasses,allowoptimization class org.libsdl.app.** { *; }
-keepclasseswithmembernames,includedescriptorclasses class * {
    native <methods>;
}

# The activity is started by name from the manifest.
-keep class com.blip.blop.Smartblip { *; }
