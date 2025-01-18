#include "Overlay.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);


using namespace OverlayBackgroundData;

Overlay::Overlay(int processId)
{
	std::cout << "[Overlay]: Open Counter-strike Source!" << std::endl;

	bool WindowFocus = false;
	while (WindowFocus == false) {
		DWORD ForegroundWindowProcessID;
		GetWindowThreadProcessId(GetForegroundWindow(), &ForegroundWindowProcessID);
		if (processId == ForegroundWindowProcessID) {
			ID = GetCurrentProcessId();
			Handle = GetCurrentProcess();
			Hwnd = GetForegroundWindow();

			RECT TempRect;
			GetWindowRect(Hwnd, &TempRect);
			WindowWidth = TempRect.right - TempRect.left;
			WindowHeight = TempRect.bottom - TempRect.top;
			WindowLeft = TempRect.left;
			WindowRight = TempRect.right;
			WindowTop = TempRect.top;
			WindowBottom = TempRect.bottom;

			WindowFocus = true;
		}
	}


	WindowClass = {
		sizeof(WNDCLASSEX), 0, WinProc, 0, 0, nullptr, LoadIcon(nullptr, IDI_APPLICATION), LoadCursor(nullptr, IDC_ARROW), nullptr, nullptr, OverlayName, LoadIcon(nullptr, IDI_APPLICATION)
	};

	RegisterClassEx(&WindowClass);
	if (Hwnd) {
		static RECT TempRect = { NULL };
		static POINT TempPoint;
		GetClientRect(Hwnd, &TempRect);
		ClientToScreen(Hwnd, &TempPoint);
		TempRect.left = TempPoint.x;
		TempRect.top = TempPoint.y;
		WindowWidth = TempRect.right;
		WindowHeight = TempRect.bottom;

	}

	WindowHandle = CreateWindowEx(NULL, OverlayName, OverlayName, WS_POPUP | WS_VISIBLE, WindowLeft, WindowTop, WindowWidth, WindowHeight, NULL, NULL, 0, NULL);
	DwmExtendFrameIntoClientArea(WindowHandle, &Margin);
	SetWindowLong(WindowHandle, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT);
	ShowWindow(WindowHandle, SW_SHOW);
	UpdateWindow(WindowHandle);



	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &Direct3D9))) {
		std::cout << "[Overlay]: Direct3DCreate failed!" << std::endl;
		exit(1);
	}
	std::cout << "[Overlay]: D3D Created!" << std::endl;

	D3DPRESENT_PARAMETERS Params = { 0 };
	Params.Windowed = TRUE;
	Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	Params.hDeviceWindow = WindowHandle;
	Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	Params.BackBufferFormat = D3DFMT_A8R8G8B8;
	Params.BackBufferWidth = WindowWidth;
	Params.BackBufferHeight = WindowHeight;
	Params.EnableAutoDepthStencil = TRUE;
	Params.AutoDepthStencilFormat = D3DFMT_D16;
	Params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;//old D3DPRESENT_INTERVAL_ONE
	Params.FullScreen_RefreshRateInHz = 0;//old D3DPRESENT_RATE_DEFAULT

	if (FAILED(Direct3D9->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, WindowHandle, D3DCREATE_HARDWARE_VERTEXPROCESSING, &Params, 0, &pDevice))) {
		Direct3D9->Release();
		std::cout << "[Overlay]: CreateDevice failed!" << std::endl;
		exit(1);
	}


	std::cout << "[Overlay]: D3D Device Created!" << std::endl;

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantTextInput || ImGui::GetIO().WantCaptureKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.Fonts->AddFontDefault();

	ImGui_ImplWin32_Init(WindowHandle);
	ImGui_ImplDX9_Init(pDevice);
	Direct3D9->Release();

	ZeroMemory(&Message, sizeof(MSG));

	std::cout << "[Overlay]: Imgui init!" << std::endl;
}

Overlay::~Overlay()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	if (pDevice != NULL) {
		pDevice->EndScene();
		pDevice->Release();
	}
	if (Direct3D9 != NULL) {
		Direct3D9->Release();
	}
	DestroyWindow(WindowHandle);
	UnregisterClass(WindowClass.lpszClassName, WindowClass.hInstance);
}

void Overlay::BeginDrawing()
{
	if (PeekMessage(&Message, WindowHandle, 0, 0, PM_REMOVE)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	HWND ForegroundWindow = GetForegroundWindow();
	if (ForegroundWindow == Hwnd) {
		HWND TempProcessHwnd = GetWindow(ForegroundWindow, GW_HWNDPREV);
		SetWindowPos(WindowHandle, TempProcessHwnd, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}

	RECT TempRect;
	POINT TempPoint;
	ZeroMemory(&TempRect, sizeof(RECT));
	ZeroMemory(&TempPoint, sizeof(POINT));

	GetClientRect(Hwnd, &TempRect);
	ClientToScreen(Hwnd, &TempPoint);

	TempRect.left = TempPoint.x;
	TempRect.top = TempPoint.y;
	ImGuiIO& io = ImGui::GetIO();
	//io.ImeWindowHandle = Hwnd;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	viewport->PlatformHandleRaw = Hwnd;


	POINT TempPoint2;
	GetCursorPos(&TempPoint2);
	io.MousePos.x = TempPoint2.x - TempPoint.x;
	io.MousePos.y = TempPoint2.y - TempPoint.y;

	if (GetAsyncKeyState(0x1)) {
		io.MouseDown[0] = true;
		io.MouseClicked[0] = true;
		io.MouseClickedPos[0].x = io.MousePos.x;
		io.MouseClickedPos[0].x = io.MousePos.y;

	}
	else {
		io.MouseDown[0] = false;
	}

	if (TempRect.left != OldRect.left || TempRect.right != OldRect.right || TempRect.top != OldRect.top || TempRect.bottom != OldRect.bottom) {
		OldRect = TempRect;
		WindowWidth = TempRect.right;
		WindowHeight = TempRect.bottom;
		pParams.BackBufferWidth = WindowWidth;
		pParams.BackBufferHeight = WindowHeight;
		SetWindowPos(WindowHandle, (HWND)0, TempPoint.x, TempPoint.y, WindowWidth, WindowHeight, SWP_NOREDRAW);
		pDevice->Reset(&pParams);
	}

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void Overlay::EndDrawing()
{
	ImGui::EndFrame();

	pDevice->SetRenderState(D3DRS_ZENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	pDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);

	pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
	if (pDevice->BeginScene() >= 0) {
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		pDevice->EndScene();
	}

	HRESULT result = pDevice->Present(NULL, NULL, NULL, NULL);
	if (result == D3DERR_DEVICELOST && pDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
		ImGui_ImplDX9_InvalidateDeviceObjects();
		pDevice->Reset(&pParams);
		ImGui_ImplDX9_CreateDeviceObjects();
	}
}

void Overlay::EnableInputMode(bool value)
{
	if (value)
		SetWindowLong(WindowHandle, GWL_EXSTYLE, WS_EX_TOPMOST);
	else
		SetWindowLong(WindowHandle, GWL_EXSTYLE, WS_EX_TRANSPARENT | WS_EX_LAYERED);
}

const Vector2 Overlay::GetScreenSize()
{
	return { (float)WindowWidth, (float)WindowHeight };
}

const Vector2 Overlay::GetScreenCenter()
{
	return { (float)WindowWidth / 2.f, (float)WindowHeight / 2.f };
}

const Vector4 Overlay::GetScreenRect()
{
	return Vector4((float)WindowLeft, (float)WindowRight, (float)WindowTop, (float)WindowBottom);
}



LRESULT __stdcall WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, Message, wParam, lParam))
		return true;

	switch (Message) {
	case WM_DESTROY:
		if (pDevice != NULL) {
			pDevice->EndScene();
			pDevice->Release();
		}
		if (Direct3D9 != NULL) {
			Direct3D9->Release();
		}
		PostQuitMessage(0);
		exit(1);
		break;
	case WM_SIZE:
		if (pDevice != NULL && wParam != SIZE_MINIMIZED) {
			ImGui_ImplDX9_InvalidateDeviceObjects();
			pParams.BackBufferWidth = LOWORD(lParam);
			pParams.BackBufferHeight = HIWORD(lParam);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
		break;

	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
		break;
	}
}
