#include "Input.h"
#include <Windows.h>

#include <iostream>



void Input::MouseLeftClick()
{
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &input, sizeof(INPUT));

	ZeroMemory(&input, sizeof(INPUT));
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &input, sizeof(INPUT));
}

void Input::MoveMouseRCS(int dx, int dy)
{
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_MOVE;
	input.mi.dx = dx;
	input.mi.dy = dy;
	input.mi.dwExtraInfo = 0;
	SendInput(1, &input, sizeof(INPUT));
}



void Input::SendKeyPress(short key)
{
	INPUT ip = { 0 };
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = key;
	ip.ki.dwFlags = KEYEVENTF_SCANCODE;
	SendInput(1, &ip, sizeof(INPUT));
	ip.ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_SCANCODE;
	SendInput(1, &ip, sizeof(INPUT));
}

void Input::SendMouseScroll(bool down)
{
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_WHEEL;

	if (down)
		input.mi.mouseData = -WHEEL_DELTA;
	else
		input.mi.mouseData = WHEEL_DELTA;

	SendInput(1, &input, sizeof(INPUT));
}
