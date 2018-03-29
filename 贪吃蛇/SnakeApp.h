#pragma once
#include"Apple.h"
#include"Background.h"
#include"Snake.h"
#include"sys.h"
class CSnakeApp
{
private:
	//CApple* apple;
	list<CApple*> m_lisApple;
	Background back;
	Snake snake;
private:
	HINSTANCE m_hins;  //实例句柄
	HWND m_hMainwnd;  //当前窗口
	HDC dc; //窗口dc
	HDC hMemDc;  //兼容性dc
	HBITMAP hbitmap;
	int m_timectl;
public:
	CSnakeApp();
	~CSnakeApp();
public:
	bool InitGame();
	void Show();
	void ChangeFX(WPARAM wParam);
	void SetHandle(HINSTANCE hins,HWND hwnd);
	void SnakeRun();
	void FastAndSlow(WPARAM wParam);
	bool SnakeEatApple();
	void SnakeGrow();
	bool IsGameOver();
	void CreateApple();
};

