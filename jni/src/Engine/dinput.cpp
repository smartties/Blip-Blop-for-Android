#include "windows.h"
#include "dinput.h"

CDIDATAFORMAT c_dfDIKeyboard, c_dfDIJoystick;

HRESULT IDirectInputDevice8::SetDataFormat(LPCDIDATAFORMAT lpdf)
{
    return DI_OK;
}

HRESULT IDirectInputDevice8::SetCooperativeLevel(HWND hwnd,DWORD dwFlags)
{
    return DI_OK;
}
HRESULT IDirectInputDevice8::Acquire()
{
}
HRESULT IDirectInputDevice8::Unacquire()
{
}
HRESULT IDirectInputDevice8::SetProperty(/*REFGUID*/int rguidProp,LPCDIPROPHEADER pdiph)
{
}
HRESULT IDirectInputDevice8::GetDeviceState(DWORD cbData,LPVOID lpvData)
{
}
HRESULT IDirectInputDevice8::Poll()
{
}
void IDirectInputDevice8::Release()
{
}

HRESULT IDirectInput8::CreateDevice(/*REFGUID*/int rguid,LPDIRECTINPUTDEVICE * lplpDirectInputDevice,LPUNKNOWN pUnkOuter)
{
    return DI_OK;
}
HRESULT IDirectInput8::EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACK lpCallback,LPVOID pvRef,DWORD dwFlags)
{
}
void IDirectInput8::Release()
{
}

HRESULT DirectInput8Create(HINSTANCE hinst,DWORD dwVersion,/*REFIID*/int riidltf,LPVOID * ppvOut, void* unused)
{
    return DI_OK;
}

