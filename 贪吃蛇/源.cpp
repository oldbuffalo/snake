#pragma once
#include <windows.h>
#include<ctime>
#include"resource.h"
#include"SnakeApp.h"
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HINSTANCE g_hIns = 0;
CSnakeApp*snake = NULL;
int g_a;

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR pCmdLine, int nCmdShow)
{
	g_hIns = hInstance;
	srand((unsigned)time(NULL));
	//  1.  设计窗口
	WNDCLASSEX wnd;
	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.cbSize = sizeof(WNDCLASSEX);
	wnd.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wnd.hCursor = ::LoadCursor(NULL, (LPCTSTR)IDC_ARROW);   //  加载系统光标
	wnd.hIcon = 0;
	wnd.hIconSm = 0;
	wnd.hInstance = hInstance;
	wnd.lpfnWndProc = WndProc;
	wnd.lpszClassName = "lele";
	wnd.lpszMenuName = 0;
	wnd.style = CS_HREDRAW | CS_VREDRAW;

	//  2.  注册
	if (::RegisterClassEx(&wnd) == FALSE)
	{
		::MessageBox(NULL,"注册失败", "提示", MB_OK);
		return 0;
	}
	//  3.  创建
	HWND hwnd = ::CreateWindow("lele", "猪^_^猪", WS_OVERLAPPEDWINDOW,100, 100, 600+16, 600+35, 0, 0, hInstance, 0);
	if (hwnd == 0)
	{
		::MessageBox(NULL, "创建失败", "提示", MB_OK);
		return 0;
	}

	//  4.  显示
	
	::ShowWindow(hwnd, SW_SHOW);


	
	//  5.  消息循环
	MSG msg;
	while (::GetMessage(&msg, 0, 0, 0))
	{
		//  翻译
		::TranslateMessage(&msg);
		//  分发
		::DispatchMessage(&msg);
	}

	return 0;
}




LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{	
	switch (uMsg) 
	{
	case WM_CLOSE:
		::PostQuitMessage(0);   //  发送一个退出的消息
		break;
	case WM_CREATE:    //在createwindow之后发送  在显示窗口之前
		//创建蛇对象
		snake = new CSnakeApp;

		//设置句柄
		snake->SetHandle(g_hIns, hwnd);

		//初始化游戏
		snake->InitGame();

		break;
	case WM_PAINT:
		snake->Show();
		break;
	case WM_TIMER:
		g_a = 1;
		snake->Show();
		snake->SnakeRun();  
		
		if (snake->SnakeEatApple())
		{
			snake->CreateApple();

			snake->SnakeGrow();
		}

		if (snake->IsGameOver())
		{
			KillTimer(hwnd, SNAKE_MOVE);
			MessageBox(hwnd, "垃圾啊", "战斗结束", MB_OK);	
			break;		
		}

		//移动之后就要重绘  
		snake->Show();
		break;
	case WM_KEYDOWN: 
		if(g_a == 1)  //防止在一个定时器消息中连续按两次不同的方向键 导致蛇撞到自己
			snake->ChangeFX(wParam);
		snake->FastAndSlow(wParam);   //加减速  w减  f加
		g_a = 0;
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}




