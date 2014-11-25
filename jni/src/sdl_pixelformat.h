#pragma once
///MODIF SDL
#include "../SDL/include/SDL.h"

namespace SDL
{

	// DDPIXELFORMAT
	struct PixelFormat
	{
		unsigned int dwRBitMask;
		unsigned int dwGBitMask;
		unsigned int dwBBitMask;
		unsigned int dwABitMask;

		PixelFormat() {}

		PixelFormat(SDL_PixelFormat* format) {
			dwRBitMask = format->Rmask;
			dwGBitMask = format->Gmask;
			dwBBitMask = format->Bmask;
			dwABitMask = format->Amask;
		}
	};

};

