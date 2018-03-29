#pragma once
#include"sys.h"
class Background
{
public:
	Background();
	~Background();
private:
	HBITMAP HbitBack;
public:
	void InitBackground(HINSTANCE hInstance);
	void ShowBackGround(HDC hMemDC);
};

