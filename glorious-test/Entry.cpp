#include "stdafx.h"
#include "GeneralTest.h"

int WINAPI wWinMain(HINSTANCE current, HINSTANCE, PWSTR, int show_mode)
{
	return pasha::GeneralTest{ current,show_mode, L"Glorious Test", 800,600 }.Main();
}