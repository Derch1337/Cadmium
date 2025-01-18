#pragma once
#include <D3D9/d3d9.h>
#include <D3D9/d3dx9.h>
#include <Imgui/imgui.h>


class BImage
{
public:
	BImage(IDirect3DDevice9* g_pd3dDevice, const unsigned char* bytes, const int size);
	
	void Draw(ImVec2 size);

	IDirect3DTexture9* out_texture = nullptr;

private:
	
};
