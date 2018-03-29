#include "SnakeApp.h"



CSnakeApp::CSnakeApp()
{
	m_hins = NULL;
	m_hMainwnd = NULL;
	dc = NULL;
	hMemDc = NULL;
	hbitmap = NULL;
	m_timectl = 300;
	
	for (int i = 0; i < 10; i++)
	{
		CApple* apple = new CApple;
		m_lisApple.push_back(apple);
	}

}


CSnakeApp::~CSnakeApp()
{
	DeleteObject(hbitmap);
	DeleteDC(hMemDc);
	ReleaseDC(m_hMainwnd, dc);

	list<CApple*> ::iterator ite = m_lisApple.begin();


	while (ite != m_lisApple.end())
	{
		delete *ite;
		ite = m_lisApple.erase(ite);
	}
}

bool CSnakeApp::InitGame()
{
	//创建dc   ---双缓冲
	dc = GetDC(m_hMainwnd);
	hMemDc = CreateCompatibleDC(dc);
	hbitmap = CreateCompatibleBitmap(dc, 600, 600);
	SelectObject(hMemDc, hbitmap);

	//加载位图资源
	back.InitBackground(m_hins);
	
	snake.InitSnake(m_hins);
	//apple->InitApple(m_hins);
	list<CApple*> ::iterator ite = m_lisApple.begin();
	while (ite != m_lisApple.end())
	{
		(*ite)->InitApple(m_hins);
		ite++;
	}




	//启动定时器
	//SetTimer(m_hMainwnd, APPLE_MOVE, 100, NULL);
	SetTimer(m_hMainwnd, SNAKE_MOVE, 150, NULL);
	return true;
}

void CSnakeApp::Show()
{


	back.ShowBackGround(hMemDc);
	//apple->ShowApple(hMemDc);
	snake.ShowSnake(hMemDc);

	list<CApple*> ::iterator ite = m_lisApple.begin();
	while (ite != m_lisApple.end())
	{
		(*ite)->ShowApple(hMemDc);
		ite++;
	}


	BitBlt(dc, 0, 0, 600, 600, hMemDc, 0, 0, SRCCOPY);

}
void CSnakeApp::SetHandle(HINSTANCE hins, HWND hwnd)
{
	this->m_hins = hins;
	this->m_hMainwnd = hwnd;
}

void CSnakeApp::ChangeFX(WPARAM wParam)
{
	snake.ChangeHead(wParam);
}

void CSnakeApp::SnakeRun()
{
	snake.SnakeMove();
}


//s 减速  f  加速
void CSnakeApp::FastAndSlow(WPARAM wParam) 
{
	switch (wParam)
	{
	case 'S':  
		m_timectl += 50;
		if (m_timectl >= 300)
		{
			break;
		}
		KillTimer(m_hMainwnd, SNAKE_MOVE);
		SetTimer(m_hMainwnd, SNAKE_MOVE, m_timectl, NULL);
		break;
	case 'F':
		m_timectl -= 50;
		if (m_timectl <= 50)
		{
			break;
		}
		KillTimer(m_hMainwnd, SNAKE_MOVE);
		SetTimer(m_hMainwnd, SNAKE_MOVE, m_timectl, NULL);
		break;
	}
}

bool CSnakeApp::SnakeEatApple()
{
	list<CApple*> ::iterator ite = m_lisApple.begin();
	while (ite != m_lisApple.end())
	{
		if (snake.IsEatApple(*ite))
		{
			ite = m_lisApple.erase(ite);
			return true;
		}
		ite++;
	}


	return false;

}

void CSnakeApp::SnakeGrow()
{
	snake.SnakeGrow();
}

bool CSnakeApp::IsGameOver()
{
	if (snake.IsSnakeHitWall()||snake.IsHitItself())
		return true;
	return false;
}

void CSnakeApp::CreateApple()
{
	CApple* apple = CApple::RandomApple(snake);
	apple->InitApple(m_hins);
	m_lisApple.push_back(apple);
}
