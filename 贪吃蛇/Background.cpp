#include "Background.h"




Background::Background()
{
	HbitBack = NULL;
}



Background::~Background()
{
	DeleteObject(HbitBack);
	HbitBack = NULL;
}

void Background::ShowBackGround(HDC hMemDC)
{
	HDC tempDC = CreateCompatibleDC(hMemDC);
	
	SelectObject(tempDC, HbitBack);

	BitBlt(hMemDC, 0, 0, 600, 600, tempDC, 0, 0, SRCCOPY);

	DeleteDC(tempDC);

}


void Background::InitBackground(HINSTANCE hInstance)
{
	HbitBack = ::LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BackGround));
}

