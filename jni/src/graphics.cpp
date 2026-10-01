#include "graphics.h"
#include "log.h"

extern SDL::Surface	*	backSurface;

#define WIDTH  640
#define HEIGHT 480

//-----------------------------------------------------------------------------
// Presentation: the game draws a 640x480 software surface. It is uploaded to
// one streaming texture, scaled up with nearest filtering to the next integer
// multiple, then scaled down with linear filtering into a letterboxed 4:3
// rectangle ("sharp bilinear"). Pixels stay crisp at any resolution (720p,
// 1080p, 4K TV, 20:9 phones) without the uneven pixels of plain nearest.
//-----------------------------------------------------------------------------

static SDL_Texture *	frame_tex = NULL;	// 640x480, updated every frame
static SDL_Texture *	up_tex = NULL;		// (640*k)x(480*k) render target
static int				up_k = 0;
static SDL_Rect			dst_rect = { 0, 0, WIDTH, HEIGHT };
static int				out_w = WIDTH, out_h = HEIGHT;

void Graphics_RenderReset()
{
	if (frame_tex) SDL_DestroyTexture(frame_tex);
	if (up_tex) SDL_DestroyTexture(up_tex);
	frame_tex = NULL;
	up_tex = NULL;
	up_k = 0;
}

// Touch coordinates are normalised to the window; map them to the picture.
void Graphics_MapTouch(float &x, float &y)
{
	if (dst_rect.w <= 0 || dst_rect.h <= 0)
		return;
	x = (x * out_w - dst_rect.x) / (float)dst_rect.w;
	y = (y * out_h - dst_rect.y) / (float)dst_rect.h;
	if (x < 0) x = 0;
	if (x > 1) x = 1;
	if (y < 0) y = 0;
	if (y > 1) y = 1;
}

static void present_frame(SDL_Renderer *renderer, SDL_Surface *surf)
{
	if (renderer == NULL || surf == NULL)
		return;

	if (frame_tex == NULL) {
		frame_tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888,
		                              SDL_TEXTUREACCESS_STREAMING, surf->w, surf->h);
		if (frame_tex == NULL) {
			LOGI("SDL_CreateTexture failed: %s", SDL_GetError());
			return;
		}
		SDL_SetTextureScaleMode(frame_tex, SDL_ScaleModeNearest);
	}

	SDL_UpdateTexture(frame_tex, NULL, surf->pixels, surf->pitch);

	// Letterboxed 4:3 destination rectangle
	if (SDL_GetRendererOutputSize(renderer, &out_w, &out_h) != 0 || out_w <= 0 || out_h <= 0) {
		out_w = surf->w;
		out_h = surf->h;
	}
	float scale = SDL_min(out_w / (float)surf->w, out_h / (float)surf->h);
	dst_rect.w = (int)(surf->w * scale + 0.5f);
	dst_rect.h = (int)(surf->h * scale + 0.5f);
	dst_rect.x = (out_w - dst_rect.w) / 2;
	dst_rect.y = (out_h - dst_rect.h) / 2;

	SDL_SetRenderTarget(renderer, NULL);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	int k = (int)SDL_ceilf(scale - 0.01f);
	bool integer = SDL_fabsf(scale - SDL_roundf(scale)) < 0.01f;

	if (k > 1 && !integer) {
		SDL_RendererInfo info;
		if (SDL_GetRendererInfo(renderer, &info) == 0 && info.max_texture_width > 0) {
			while (k > 1 && (surf->w * k > info.max_texture_width ||
			                 surf->h * k > info.max_texture_height))
				k--;
		}
	}

	if (k > 1 && !integer) {
		if (up_tex == NULL || up_k != k) {
			if (up_tex) SDL_DestroyTexture(up_tex);
			up_tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888,
			                           SDL_TEXTUREACCESS_TARGET, surf->w * k, surf->h * k);
			up_k = k;
			if (up_tex)
				SDL_SetTextureScaleMode(up_tex, SDL_ScaleModeLinear);
			else
				LOGI("Upscale texture failed: %s", SDL_GetError());
		}
	}

	if (k > 1 && !integer && up_tex != NULL &&
	    SDL_SetRenderTarget(renderer, up_tex) == 0) {
		SDL_RenderCopy(renderer, frame_tex, NULL, NULL);
		SDL_SetRenderTarget(renderer, NULL);
		SDL_RenderCopy(renderer, up_tex, NULL, &dst_rect);
	} else {
		SDL_RenderCopy(renderer, frame_tex, NULL, &dst_rect);
	}

	SDL_RenderPresent(renderer);
}

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

	// Full screen: on Android this also hides the status and navigation bars
	// (immersive mode). The picture is letterboxed in Flip().
	window = SDL_CreateWindow("Blip&Blop", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	                          x, y, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
	if (window == 0){
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	Graphics_RenderReset();
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
	Graphics_RenderReset();
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
	present_frame(renderer, backSurface->Get());
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
