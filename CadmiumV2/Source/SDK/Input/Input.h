#pragma once




class Input
{
public:
	static void SendKeyPress(short key);
	static void MouseLeftClick();
	static void MoveMouseRCS(int dx, int dy);
	static void SendMouseScroll(bool down = true);
private:


};

