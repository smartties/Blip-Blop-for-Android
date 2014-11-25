#pragma once

#include "graphics.h"
///MODIF SDL
#include "../SDL/include/SDL.h"

#include "sdl_pixelformat.h"
#include "sdl_surfaceinfo.h"

#ifndef DDLOCK_WAIT // not used by SDL
#define DDLOCK_SURFACEMEMORYPTR 0x1
#define DDLOCK_WAIT 0x2
#define DDLOCK_WRITEONLY 0x4
#endif

namespace SDL
{

	class Surface
	{
		private:
		SDL_Surface *surface;
		Surface *backBuffer;

		public:
		//Surface();

		Surface(SDL_Surface* surf) {
			//SDL_SetSurfaceBlendMode(surf, SDL_BLENDMODE_NONE);
			SDL_SetSurfaceAlphaMod(surf, 0xff);
			surface = surf;
			backBuffer = 0;
		}

		Surface(SDL_Surface* surf, Surface* bb) {
			//SDL_SetSurfaceBlendMode(surf, SDL_BLENDMODE_NONE);
			SDL_SetSurfaceAlphaMod(surf, 0xff);
			surface = surf;
			backBuffer = bb;
		}

		inline void SetBackBuffer(Surface* b)
		{
			backBuffer = b;
		}

		inline SDL_Surface *Get(){ return surface; };
		inline void BltFast(int x, int y, SDL::Surface *surf /*This is the Source Surface! Damn, DD!*/, RECT *r, int flags=0)
		{

			/*static int test_i = 1;
			char buf[128];
			sprintf(buf, "test/%d.bmp", test_i);
			SDL_SaveBMP(surf->Get(), buf);
			test_i++;*/

			SDL_Rect rect,position;
			position.x = x;
			position.y = y;
			if (r == 0)
			{
				SDL_BlitSurface(surf->Get(), 0, surface, &position);
			}
			else
			{
				rect.x = r->left;
				rect.y = r->top;
				rect.w = r->right - r->left;
				rect.h = r->bottom - r->top;
				/*SDL_BlitSurface(SDL_Surface*    src,
				const SDL_Rect* srcrect,
				SDL_Surface*    dst,
				SDL_Rect*       dstrect)*/
				int ret=SDL_BlitSurface(surf->Get(), &rect, surface, &position);
				unsigned long* px = (unsigned long*)surf->Get()->pixels;
				if (ret != 0)
				{
					debug <<"Errore SDL_BlitSurface in sdl_surface.h - "<< SDL_GetError() << "\n";
					exit(0);
				}

				/*static int test_i = 1;
				char buf[128];
				sprintf(buf, "test/%d.bmp", test_i);
				SDL_SaveBMP(surf->Get(), buf);
				test_i++;*/
			}

		}

		inline void Blt(RECT *src, SDL::Surface *surf, RECT *dest, int flags = 0, DDBLTFX *pad = 0)
		{
			/*
			TODO: IF flags contains DDBLT_COLORFILL then i must fill the surface with the color of
			*/
			SDL_Rect *rect=0, *position=0;
			if (src)
			{
				rect = new SDL_Rect;
				rect->x = src->left;
				rect->y = src->top;
				rect->w = src->right - src->left;
				rect->h = src->bottom - src->top;
			}
			if (dest)
			{
				position = new SDL_Rect;
				position->x = dest->left;
				position->y = dest->top;
				position->w = dest->right - dest->left;
				position->h = dest->bottom - dest->top;
			}
			if (surf)
			{
				SDL_BlitSurface(surf->Get(), rect, surface, position);
			}
			else
			{
				if (pad)
					SDL_FillRect(surface, rect, pad->dwFillColor);
				else
					SDL_FillRect(surface, rect, 0x000000);
			}
			if (rect)
				delete rect;
			if (position)
				delete position;

			/*else
			{
				SDL_BlitSurface(0, rect, surface, position);
			}*/

			/*if (src!=0&&dest!=0)
			{
				SDL_Rect rect, position;
				rect.x = src->left;
				rect.y = src->top;
				rect.w = src->right - src->left;
				rect.h = src->bottom - src->top;
				position.x = dest->left;
				position.y = dest->top;
				position.w = dest->right - dest->left;
				position.h = dest->bottom - dest->top;
				SDL_BlitSurface(surface, &rect, surf->Get(), &position);
			}
			else if (src!=0)
			{
				SDL_Rect rect, position;
				position.x = dest->left;
				position.y = dest->top;
				position.w = dest->right - dest->left;
				position.h = dest->bottom - dest->top;
				SDL_BlitSurface(surface, 0, surf->Get(), &position);
			}
			else if (dest != 0)
			{
				SDL_Rect rect, position;
				rect.x = src->left;
				rect.y = src->top;
				rect.w = src->right - src->left;
				rect.h = src->bottom - src->top;
				SDL_BlitSurface(surf->Get(), &rect, surface, 0);
			}
			else
			{
				SDL_BlitSurface(surf->Get(), 0, surface, 0);
			}*/
		}

		/*inline void Blt(RECT *src, SDL::Surface *surf, RECT *dest, DDBLTFX *pad = 0, int flags = 0)
		{
			//Call the original function with the last 2 arguments swapped
			Blt(src, surf, dest, flags,pad);
		}*/

		inline void Release()
		{
			SDL_FreeSurface(surface);
			delete this;
		}
		inline bool Restore()
		{
			return true;
		}

		inline void FillRect(RECT *r,unsigned int color)
		{
			if (!r)
			{
				SDL_FillRect(surface, 0, color);
			}
			else
			{
				SDL_Rect rect;
				rect.x = r->left;
				rect.y = r->top;
				rect.w = r->right - r->left;
				rect.h = r->bottom - r->top;
				SDL_FillRect(surface, &rect, color);
			}

		}

		bool GetPixelFormat(SDL::PixelFormat* format)
		{
			*format = SDL::PixelFormat(surface->format);
			return true;
		}

		bool Lock(RECT* r, SDL::SurfaceInfo* info, int flags, void* unused)
		{
			if (SDL_LockSurface(surface) != 0) {
				return false;
			}
			info->lpSurface = surface->pixels;
			info->lPitch = surface->pitch;
			return true;
		}

		void Unlock(RECT* r)
		{
			SDL_UnlockSurface(surface);
		}

		bool IsLost() {
			return false;
		}
	};

};
