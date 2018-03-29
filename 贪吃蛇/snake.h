#pragma once
#include"sys.h"
#include"Apple.h"

class Snake
{
public:
	Snake();
	~Snake();
private:
	HBITMAP hBitmapBody;
	HBITMAP HBitmapUpHead;
	HBITMAP HBitmapDownHead;
	HBITMAP HBitmapLeftHead;
	HBITMAP HBitmapRightHead;
	static int m_fx;
	static int m_time;
	list<snakeinfo*> m_listSnake;
public:
	list<snakeinfo*>& GetSnakeList()
	{
		return m_listSnake;
	}
public:
	void InitSnake(HINSTANCE hins);
	void ShowSnake(HDC hMemDC);
	void ChangeHead(WPARAM wParam);
	void SnakeMove();
	void SnakeGrow();
	bool IsEatApple(CApple* &apple);
	bool IsSnakeHitWall();
	bool IsHitItself();
};

