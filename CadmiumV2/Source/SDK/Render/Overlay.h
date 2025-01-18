#pragma once
#include "../Math/Math.h"
#include <string>
#include <Imgui/imgui.h>
#include <Imgui/imgui_impl_dx9.h>
#include <Imgui/imgui_impl_win32.h>
#include <Windows.h>
#include <D3D9/d3d9.h>
#include <dwmapi.h>
#include <iostream>



namespace OverlayBackgroundData {
	inline IDirect3D9Ex* Direct3D9 = NULL;
	inline IDirect3DDevice9Ex* pDevice = NULL;//read only
	inline D3DPRESENT_PARAMETERS pParams = { NULL };
	inline MARGINS Margin = { -1 };
	inline MSG Message = { NULL };
	inline DWORD ID;
	inline HANDLE Handle;
	inline HWND Hwnd;
	inline WNDPROC WndProc;
	inline RECT OldRect;
	inline DWORD WindowID;
	inline HWND WindowHandle = 0;
	inline WNDCLASSEX WindowClass;

	inline const wchar_t* OverlayName = L"Counter-strike";
}

class Overlay
{
public:
	
private:
	int WindowWidth;
	int WindowHeight;
	int WindowLeft;
	int WindowRight;
	int WindowTop;
	int WindowBottom;


	

public:
	Overlay(int processId);
	~Overlay();

	void BeginDrawing();
	void EndDrawing();

	void EnableInputMode(bool value);

	const Vector2 GetScreenSize();
	const Vector2 GetScreenCenter();
	const Vector4 GetScreenRect();

private:
	
};


