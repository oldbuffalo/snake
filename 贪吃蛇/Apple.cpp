#include "Apple.h"
#include"snake.h"



CApple::CApple()
{
	HbitApple = NULL;
	m_x = rand() % 18 + 1;
	m_y = rand() % 18 + 1;
}


CApple::~CApple()
{
	DeleteObject(HbitApple);
	HbitApple = NULL;
}

void CApple::ShowApple(HDC hMemDC)
{
	HDC tempdc = CreateCompatibleDC(hMemDC);

	//选入位图
	SelectObject(tempdc, HbitApple);

	//传输位图
	BitBlt(hMemDC, m_x*30, m_y*30, 30, 30, tempdc, 0, 0, SRCCOPY);


	DeleteDC(tempdc);
}

void  CApple::InitApple(HINSTANCE hInstance)
{
	HbitApple = ::LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_Apple));
}

CApple* CApple::RandomApple(Snake& snake)
{
	CApple* apple = new CApple;

	//m_x最小到1 最大到18
	do
	{
		apple->m_x = rand() % 18 + 1;
		apple->m_y = rand() % 18 + 1;

		//判断在不在蛇身上
		list<snakeinfo*> ::iterator ite = snake.GetSnakeList().begin();

		while (ite != snake.GetSnakeList().end())
		{
			if ((*ite)->x == apple->m_x && (*ite)->y == apple->m_y)
				break;
			ite++;
		}

		if (ite == snake.GetSnakeList().end())
			break;

	} while (1);

	

	return apple;
}

int CApple::GetAppleX()
{
	return m_x;
}
int CApple::GetAppleY()
{
	return m_y;
}