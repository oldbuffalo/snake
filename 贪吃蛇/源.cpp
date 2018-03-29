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
	//  1.  ��ƴ���
	WNDCLASSEX wnd;
	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.cbSize = sizeof(WNDCLASSEX);
	wnd.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wnd.hCursor = ::LoadCursor(NULL, (LPCTSTR)IDC_ARROW);   //  ����ϵͳ���
	wnd.hIcon = 0;
	wnd.hIconSm = 0;
	wnd.hInstance = hInstance;
	wnd.lpfnWndProc = WndProc;
	wnd.lpszClassName = "lele";
	wnd.lpszMenuName = 0;
	wnd.style = CS_HREDRAW | CS_VREDRAW;

	//  2.  ע��
	if (::RegisterClassEx(&wnd) == FALSE)
	{
		::MessageBox(NULL,"ע��ʧ��", "��ʾ", MB_OK);
		return 0;
	}
	//  3.  ����
	HWND hwnd = ::CreateWindow("lele", "��^_^��", WS_OVERLAPPEDWINDOW,100, 100, 600+16, 600+35, 0, 0, hInstance, 0);
	if (hwnd == 0)
	{
		::MessageBox(NULL, "����ʧ��", "��ʾ", MB_OK);
		return 0;
	}

	//  4.  ��ʾ
	
	::ShowWindow(hwnd, SW_SHOW);


	
	//  5.  ��Ϣѭ��
	MSG msg;
	while (::GetMessage(&msg, 0, 0, 0))
	{
		//  ����
		::TranslateMessage(&msg);
		//  �ַ�
		::DispatchMessage(&msg);
	}

	return 0;
}




LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{	
	switch (uMsg) 
	{
	case WM_CLOSE:
		::PostQuitMessage(0);   //  ����һ���˳�����Ϣ
		break;
	case WM_CREATE:    //��createwindow֮����  ����ʾ����֮ǰ
		//�����߶���
		snake = new CSnakeApp;

		//���þ��
		snake->SetHandle(g_hIns, hwnd);

		//��ʼ����Ϸ
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
			MessageBox(hwnd, "������", "ս������", MB_OK);	
			break;		
		}

		//�ƶ�֮���Ҫ�ػ�  
		snake->Show();
		break;
	case WM_KEYDOWN: 
		if(g_a == 1)  //��ֹ��һ����ʱ����Ϣ�����������β�ͬ�ķ���� ������ײ���Լ�
			snake->ChangeFX(wParam);
		snake->FastAndSlow(wParam);   //�Ӽ���  w��  f��
		g_a = 0;
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}




