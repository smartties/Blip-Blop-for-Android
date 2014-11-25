#include "graphics.h"

extern SDL::Surface	*	backSurface;

#define WIDTH  640
#define HEIGHT 480

Graphics::Graphics()
{
	window = NULL;
	renderer = NULL;
}

bool Graphics::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
		debug << SDL_GetError() << "\n";
		return false;
	}
	return true;
}


bool Graphics::SetCooperativeLevel(HWND wh)
{
	return true;
}

bool Graphics::SetCooperativeLevel(HWND wh, int flags)
{
	return true;
}

bool Graphics::SetGfxMode(int x, int y, int d)
{
	if(renderer!=0)
	{
		SDL_DestroyRenderer(renderer);
		renderer=0;
	}
	if(window!=0)
	{
		SDL_DestroyWindow(window);
		window = 0;
	}

	window = SDL_CreateWindow("Blip&Blop", x, y, x, y, SDL_WINDOW_SHOWN);
	if (window == 0){
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	renderer = 0;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == 0){
		std::cout << SDL_GetError() << std::endl;
		return false;
	}



	return true;
}

void Graphics::Close()
{
	if(renderer!=0)
	{
		SDL_DestroyRenderer(renderer);
		renderer=0;
	}
	if(window!=0)
	{
		SDL_DestroyWindow(window);
		window = 0;
	}
}

SDL::Surface *	Graphics::CreatePrimary()
{
	/**/
	debug << "CreatePrimary() - Creating a 640 x 480 Surface" << "\n";
	return CreateSurface(WIDTH, HEIGHT, 0);
	//return 0;
}

SDL::Surface *	Graphics::CreatePrimary(SDL::Surface * & back)
{
	debug << "Graphics::CreatePrimary(SDL::Surface * & back) - Creating a 640x480 surface" << "\n";
	SDL::Surface * tmp = CreateSurface(WIDTH,HEIGHT);
	back = CreateSurface(WIDTH, HEIGHT);
	tmp->SetBackBuffer(back);
	return tmp;
	//return 0;
}

SDL::Surface *	Graphics::CreateSurface(int x, int y)
{
	return CreateSurface(x, y, 0);
}

SDL::Surface *	Graphics::CreateSurface(int x, int y, int flags)
{
	Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif
	SDL_Surface* surf = SDL_CreateRGBSurface(0,
			x, y, 32, rmask, gmask, bmask, amask);



	SDL::Surface *tmp= new SDL::Surface(surf);
	tmp->FillRect(0, 0xFF000000);
	return tmp;
}

SDL_Surface *	Graphics::CreateSDLSurface(int x, int y)
{
	Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif
	SDL_Surface* surf = SDL_CreateRGBSurface(0,
		x, y, 32, rmask, gmask, bmask, amask);
	return (surf);
}

SDL::Surface *	CreateSDLSurface(int x, int y, int b)
{
	Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	SDL_Surface* surf = SDL_CreateRGBSurface(0, x, y, b, rmask, gmask, bmask, amask);
	SDL::Surface* tmp= new SDL::Surface(surf);

	return tmp;
}

SDL::Surface *	Graphics::LoadBMP(char * file)
{
	return this->LoadBMP(file,0);
}

SDL::Surface *	Graphics::LoadBMP(char * file, int flags)
{
	/*SDL_Surface *bmp = 0;
	  bmp = SDL_LoadBMP(file);
	  if (bmp == 0){
	  std::cout << SDL_GetError() << std::endl;
	  return 0;
	  }
	  SDL_Texture *tex = 0;
	  tex = SDL_CreateTextureFromSurface(ren, bmp);
	  SDL_FreeSurface(bmp);
	  return new SDL::Surface(tex);*/
	SDL_Surface *bmp = 0;
	bmp = SDL_LoadBMP(file);

	if (bmp == 0){
		std::cout << SDL_GetError() << std::endl;
		return 0;
	}
	return new SDL::Surface(bmp);
}

HRESULT					Graphics::CopyBMP(SDL::Surface *surf, HBITMAP hbm)
{
	//Seems not used
	return 0;
}

void *	Graphics::LoadPalette(char * file)
{
	//Seems not used
	return 0;
}

DWORD					Graphics::FindColor(SDL::Surface *surf, COLORREF rgb)
{
	//Seems not used
	return 0;
}

HRESULT					Graphics::SetColorKey(SDL::Surface *surf, COLORREF rgb)
{
	SDL_SetColorKey(surf->Get(), SDL_TRUE, SDL_MapRGB(surf->Get()->format, (rgb & 0xFF), ((rgb >> 8) & 0xFF), ((rgb >> 16) & 0xFF)));
	//TODO: set color key
	return true;
}

void					Graphics::Flip()
{
    ///TODO creer une texture static, et la modifier
    /**
    CHUNK
    SDL_CreateTextureFromSurface

    SDL_UpdateTexture

    sdlTexture = SDL_CreateTexture(sdlRenderer,
                               SDL_PIXELFORMAT_ARGB8888,
                               SDL_TEXTUREACCESS_STATIC//SDL_TEXTUREACCESS_STREAMING,
                               myWidth, myHeight);

    **/

    static int ttt = GetTickCount();
    static int ccc = 0;
    ccc++;
    if(GetTickCount() - ttt > 1000)
    {
        LOGI("FPS : %d", ccc);
        ccc = 0;
        ttt = GetTickCount();
    }


	SDL_Texture *tex = 0;
	tex = SDL_CreateTextureFromSurface(renderer, backSurface->Get());
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, tex, NULL, NULL);
	SDL_RenderPresent(renderer);

	SDL_DestroyTexture(tex);
	//SDL_Delay(1);

	//SDL_SaveBMP(backSurface->Get(), "test/draw.bmp");
}

void					Graphics::FlipV()
{
	Flip();
	//SDL_RenderPresent(renderer);
}

void Graphics::Clear(int r,int g,int b)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void Graphics::Clear(int c)
{
	int r = (c>>16)&0xFF;
	int g = (c >> 8) & 0xFF;
	int b = (c >> 0) & 0xFF;

	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void Graphics::Clear(RenderRect r2)
{
	int r = (r2.dwFillColor >> 16) & 0xFF;
	int g = (r2.dwFillColor >> 8) & 0xFF;
	int b = (r2.dwFillColor >> 0) & 0xFF;

	SDL_Rect rect;
	rect.x = r2.left;
	rect.y = r2.top;
	rect.w = r2.right-r2.left;
	rect.h = r2.bottom-r2.top;


	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderDrawRect(renderer, &rect);

}
