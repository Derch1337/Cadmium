#include "Image.h"


BImage::BImage(IDirect3DDevice9* g_pd3dDevice, const unsigned char* bytes, const int size)
{
	auto* temp_texture = LPDIRECT3DTEXTURE9();
	D3DXCreateTextureFromFileInMemory(g_pd3dDevice, bytes, size, &temp_texture);

	out_texture = temp_texture;
}

void BImage::Draw(ImVec2 size)
{
	ImGui::Image((ImTextureID)out_texture, size);
}
