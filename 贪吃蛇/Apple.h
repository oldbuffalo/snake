#pragma once
#include"sys.h"


class Snake;
class CApple
{
public:
	CApple();
	~CApple();
public:
	void InitApple(HINSTANCE hInstance);
	void ShowApple(HDC hMemDC);
	static CApple* RandomApple(Snake& snake);
private:
	HBITMAP HbitApple;
	int m_x;
	int m_y;
public:
	int GetAppleX();
	int GetAppleY();
};

