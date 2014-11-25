#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cassert>
#include <unistd.h>

///MODIF SDL
#include "../../SDL/include/SDL.h"
///MODIF SDL_MIXER
#include "../../SDL_mixer/SDL_mixer.h" ///USELESS ?

#include "windows.h"

#define STUB { \
    printf("stub %s %d\n", __func__, __LINE__); \
}

void stop_music()
{
    Mix_PauseMusic();
}
void resume_music()
{
    Mix_ResumeMusic();
}


HANDLE WINAPI CreateFile(LPCTSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, void* unused, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
    assert(dwDesiredAccess == GENERIC_READ);
    assert(dwCreationDisposition == OPEN_EXISTING);
    const char* mode = "r";
    FILE* file = fopen(lpFileName, mode);
    if (!file) {
        printf("[PORTAGE] CreateFile can't create %s\n", lpFileName);
    }
    return file;
}

BOOL WINAPI ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped)
{
    FILE* file = (FILE*) hFile;
    *lpNumberOfBytesRead = fread(lpBuffer, nNumberOfBytesToRead, 1, file);
    return *lpNumberOfBytesRead > 0;
}

BOOL WINAPI CloseHandle(HANDLE hObject)
{
    FILE* file = (FILE*) hObject;
    return fclose(file) == 0;
}

long _filelength(int fd)
{
    long size = lseek(fd, 0L, SEEK_END);
    lseek(fd, 0L, SEEK_SET);
    return size;
}

void ZeroMemory(PVOID Destination, SIZE_T Length) {
    memset(Destination, 0, Length);
}

LONG ChangeDisplaySettings(DEVMODE *lpDevMode, DWORD dwflags) STUB
int MessageBox(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType)
{
    printf("MessageBox(%s)\n", lpText);
}

void SetCursor(void*) STUB
WORD HIWORD(DWORD dwValue) STUB
VOID WINAPI PostQuitMessage(int nExitCode) STUB
LRESULT WINAPI DefWindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) STUB
ATOM WINAPI RegisterClass(const WNDCLASS *lpWndClass) STUB
int WINAPI GetSystemMetrics(int nIndex) STUB
HWND WINAPI CreateWindowEx(DWORD dwExStyle, LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam) STUB
BOOL WINAPI ShowWindow(HWND hWnd, int nCmdShow) STUB
BOOL UpdateWindow(HWND hWnd) {
}
UINT_PTR WINAPI SetTimer(HWND hWnd, UINT_PTR nIDEvent, UINT uElapse, TIMERPROC lpTimerFunc) STUB
BOOL WINAPI DestroyWindow(HWND hWnd) STUB
void Sleep(int ms)
{
    SDL_Delay(ms);
}
DWORD WINAPI GetTickCount(void) {
    return SDL_GetTicks();
}

COLORREF RGB(BYTE byRed, BYTE byGreen, BYTE byBlue) {
    return byRed | (byGreen << 8) | (byBlue << 16);
}

HMODULE WINAPI GetModuleHandle(LPCTSTR lpModuleName) STUB

HANDLE WINAPI LoadImage(HINSTANCE hinst, LPCTSTR lpszName, UINT uType, int cxDesired, int cyDesired, UINT fuLoad) STUB

int GetObject(HGDIOBJ hgdiobj, int cbBuffer, LPVOID lpvObject) STUB
BOOL DeleteObject(HGDIOBJ hObject) STUB
HDC CreateCompatibleDC(HDC hdc) STUB
HGDIOBJ SelectObject(HDC hdc, HGDIOBJ hgdiobj) STUB

BOOL StretchBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, DWORD dwRop) STUB

COLORREF GetPixel(HDC hdc, int nXPos, int nYPos) STUB
COLORREF SetPixel(HDC hdc, int X, int Y, COLORREF crColor) STUB
BOOL SetPixelV(HDC hdc, int X, int Y, COLORREF crColor) STUB

BOOL DeleteDC(HDC hdc) STUB
LPVOID WINAPI LockResource(HGLOBAL hResData) STUB
HGLOBAL WINAPI LoadResource(HMODULE hModule, HRSRC hResInfo) STUB
HRSRC WINAPI FindResource(HMODULE hModule, LPCTSTR lpName, LPCTSTR lpType) STUB

DWORD timeGetTime(void) {
    return SDL_GetTicks();
}
BOOL WINAPI QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency) {
    *lpFrequency = SDL_GetPerformanceFrequency();
    return true;
}
BOOL WINAPI QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount) {
    *lpPerformanceCount = SDL_GetPerformanceCounter();
    return true;
}

BOOL WINAPI PeekMessage(LPMSG lpMsg,HWND hWnd,UINT wMsgFilterMin,UINT wMsgFilterMax,UINT wRemoveMsg) {}
LRESULT WINAPI DispatchMessage(const MSG *lpmsg) STUB
BOOL WINAPI TranslateMessage(const MSG *lpMsg) STUB
BOOL WINAPI GetMessage(LPMSG lpMsg,HWND hWnd,UINT wMsgFilterMin,UINT wMsgFilterMax) {}

char* _itoa(int value, char* str, int base) {
    SDL_itoa(value, str, base);
}


#include "../fmod.h"
extern "C" {
    struct FMUSIC_MODULE {
    };
    struct FSOUND_STREAM {
        Mix_Music* music;
    };
    struct FSOUND_SAMPLE {
        Mix_Chunk* chunk;
        int loop;
    };

    typedef struct FMUSIC_MODULE FMUSIC_MODULE;
    typedef struct FSOUND_STREAM FSOUND_STREAM;
    typedef struct FSOUND_SAMPLE FSOUND_SAMPLE;

    FSOUND_SAMPLE * FSOUND_Sample_Load(int index, const char *buffer, unsigned int mode, int memlength) {
        FSOUND_SAMPLE* sample = new FSOUND_SAMPLE;

        sample->loop = 0;
        LOGI("FSOUND_Sample_Load");
        sample->chunk=Mix_LoadWAV_RW(SDL_RWFromConstMem(buffer, memlength), 1);
        if(!sample->chunk) {
            printf("Mix_LoadWAV_RW: %s\n", Mix_GetError());
        }

        return sample;
    }
    int FSOUND_PlaySound(int channel, FSOUND_SAMPLE *sptr) {
        return Mix_PlayChannel(channel, sptr->chunk, sptr->loop);
    }
    signed char FSOUND_Sample_SetLoopMode(FSOUND_SAMPLE *sptr, unsigned int loopmode) {
        if (loopmode = FSOUND_LOOP_NORMAL) {
            sptr->loop = 0;
        } else {
            sptr->loop = 0;
        }
    }

    signed char FSOUND_StopSound(int channel) {
        Mix_HaltChannel(channel);
    }

    void FSOUND_Sample_Free(FSOUND_SAMPLE *sptr) {
        Mix_FreeChunk(sptr->chunk);
        delete sptr;
    }

    FSOUND_STREAM * FSOUND_Stream_OpenFile(const char *filename, unsigned int mode, int memlength) {
        FSOUND_STREAM* stream = new FSOUND_STREAM;
        ///MODIF fsound
        //stream->music=Mix_LoadMUS(filename);
        stream->music = Mix_LoadMUS_RW( AAsset_RWFromAsset(filename), 1);
        LOGI("FSOUND_Stream_OpenFile");
        if(!stream->music) {
            printf("Mix_LoadMUS(\"%s\"): %s\n", filename, Mix_GetError());
        }
        return stream;
    }
    int FSOUND_Stream_Play(int channel, FSOUND_STREAM *stream) {
        Mix_PlayMusic(stream->music, 0);
    }
    signed char FSOUND_Stream_Stop(FSOUND_STREAM *stream) {
        Mix_HaltMusic();
    }
    signed char FSOUND_Stream_Close(FSOUND_STREAM *stream) {
        Mix_FreeMusic(stream->music);
    }

    signed char FMUSIC_PlaySong(FMUSIC_MODULE *mod) STUB
    ///MODIF prototyp
    FMUSIC_MODULE * FMUSIC_LoadSong(const char *name)
    {
        LOGI("FMUSIC_LoadSong");
    }

    signed char FMUSIC_SetMasterVolume(FMUSIC_MODULE *mod, int volume) STUB
    signed char FMUSIC_StopSong(FMUSIC_MODULE *mod) STUB
    signed char FMUSIC_FreeSong(FMUSIC_MODULE *mod) STUB

    signed char FSOUND_Init(int mixrate, int maxsoftwarechannels, unsigned int flags) {
        int f = MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG;
        int initted = Mix_Init(f);
        if(initted&flags != flags) {
            printf("Mix_Init: Failed to init required ogg and mod support!\n");
            printf("Mix_Init: %s\n", Mix_GetError());
            return 0;
        }

        if(Mix_OpenAudio(mixrate, MIX_DEFAULT_FORMAT, 2, 1024)==-1) {
            printf("Mix_OpenAudio: %s\n", Mix_GetError());
            return 0;
        }
        return 1;
    }
    void FSOUND_Close() {
        Mix_CloseAudio();
        while(Mix_Init(0))
            Mix_Quit();
    }
    int FSOUND_GetError() {}
    signed char FSOUND_SetPriority(int channel, int priority) STUB
}

