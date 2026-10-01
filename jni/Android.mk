# SDL_mixer codecs: the game's music (.zik) is Ogg Vorbis (stb_vorbis) plus two MP3
# files (minimp3); sound effects are WAV. Everything else is turned off.
SUPPORT_WAV := true
SUPPORT_OGG_STB := true
SUPPORT_MP3_MINIMP3 := true
SUPPORT_FLAC_DRFLAC := false
SUPPORT_FLAC_LIBFLAC := false
SUPPORT_OGG := false
SUPPORT_MP3_MPG123 := false
SUPPORT_WAVPACK := false
SUPPORT_GME := false
SUPPORT_MOD_XMP := false
SUPPORT_MID_TIMIDITY := false

include $(call all-subdir-makefiles)
