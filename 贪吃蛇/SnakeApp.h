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
	HINSTANCE m_hins;  //ʵ�����
	HWND m_hMainwnd;  //��ǰ����
	HDC dc; //����dc
	HDC hMemDc;  //������dc
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

