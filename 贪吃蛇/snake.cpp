#include "Snake.h"


int Snake::m_fx = 0;
int Snake::m_time = 0;
Snake::Snake()
{
	hBitmapBody = NULL;
	HBitmapUpHead = NULL;
	HBitmapDownHead = NULL;
	HBitmapLeftHead = NULL;
	HBitmapRightHead = NULL;
}


Snake::~Snake()
{
	list<snakeinfo*> ::iterator ite = m_listSnake.begin();

	while (ite != m_listSnake.end())
	{
		delete *ite;
		ite = m_listSnake.erase(ite);		
	}


}


/*
m_fx 
1 ---------上
2 ---------下
3 ---------左
4 ---------右
*/
void Snake::InitSnake(HINSTANCE hins)
{
	hBitmapBody = LoadBitmap(hins,MAKEINTRESOURCE(IDB_Body));
	HBitmapUpHead = LoadBitmap(hins, MAKEINTRESOURCE(IDB_UpHead));
	HBitmapDownHead = LoadBitmap(hins, MAKEINTRESOURCE(IDB_DownHead));
	HBitmapLeftHead = LoadBitmap(hins, MAKEINTRESOURCE(IDB_LeftHead));
	HBitmapRightHead = LoadBitmap(hins, MAKEINTRESOURCE(IDB_RightHead));
	m_fx = 4;
	//创建蛇
	snakeinfo* head = new snakeinfo;   //fx  和 位图可以做一个匹配 map
	head->x = 3;
	head->y = 1;
	
	m_listSnake.push_back(head);

	snakeinfo* body1 = new snakeinfo;
	body1->x = 2;
	body1->y = 1;
	m_listSnake.push_back(body1);

	snakeinfo* body2 = new snakeinfo;
	body2->x = 1;
	body2->y = 1;
	m_listSnake.push_back(body2);
}



void Snake::ShowSnake(HDC hMemDC)
{
	
	//显示头
	HDC tempdc = CreateCompatibleDC(hMemDC);

	switch (m_fx)
	{
		case 1:
			SelectObject(tempdc, HBitmapUpHead);
			break;
		case 2:
			SelectObject(tempdc, HBitmapDownHead);
			break;
		case 3:
			SelectObject(tempdc, HBitmapLeftHead);
			break;
		case 4:
			SelectObject(tempdc, HBitmapRightHead);
			break;
		default:
			break;
	}
	BitBlt(hMemDC,m_listSnake.front()->x*30, m_listSnake.front()->y * 30, 30, 30, tempdc, 0, 0, SRCCOPY);
	DeleteDC(tempdc);
	//显示身子
	tempdc = CreateCompatibleDC(hMemDC);
	SelectObject(tempdc, hBitmapBody);
	list<snakeinfo*> ::iterator ite = m_listSnake.begin();
	ite++;
	while (ite != m_listSnake.end())
	{
		BitBlt(hMemDC, (*ite)->x * 30,(*ite)->y * 30, 30, 30, tempdc, 0, 0, SRCCOPY);
		ite++;
	}
	DeleteDC(tempdc);	
}

void Snake::ChangeHead(WPARAM wParam)
{
	switch (wParam)
	{
		case VK_UP:
			if(m_fx != 2)
				m_fx = 1;
			break;
		case VK_DOWN:
			if(m_fx != 1)
			m_fx = 2;
			break;
		case VK_LEFT:
			if(m_fx != 4)
			m_fx = 3;
			break;
		case VK_RIGHT:
			if(m_fx != 3)
			m_fx = 4;
			break;
	}

}

void Snake::SnakeMove()
{
	list<snakeinfo*> ::iterator ite = m_listSnake.end();
	ite--;
	list<snakeinfo*> ::iterator tempite = ite;
	tempite--;
	//挪动身子  后面一截往前面移动
	while (ite != m_listSnake.begin())
	{
		(*ite)->x=(*tempite)->x;
		(*ite)->y=(*tempite)->y;
		if (tempite == m_listSnake.begin())
			break;
		tempite--;
		ite--;
	}

	switch (m_fx)
	{
	case 1:
		m_listSnake.front()->y--;
		break;
	case 2:
		m_listSnake.front()->y++;
		break;
	case 3:
		m_listSnake.front()->x--;
		break;
	case 4:
		m_listSnake.front()->x++;
		break;
	}

}   //每次收到定时器消息就移动一次

void Snake::SnakeGrow()
{
	snakeinfo* body = new snakeinfo;
	m_listSnake.push_back(body);
}

bool Snake::IsEatApple(CApple* &apple)
{
	if (apple->GetAppleX() == m_listSnake.front()->x&&
		apple->GetAppleY() == m_listSnake.front()->y)
	{
		
		return true;
	}
	return false;
}

bool Snake::IsSnakeHitWall()
{
	
	if (m_listSnake.front()->x < 1 || m_listSnake.front()->x>18
		|| m_listSnake.front()->y < 1 || m_listSnake.front()->y>18)
		return true;

	return false;
}


bool Snake::IsHitItself()
{
	list<snakeinfo*> ::iterator ite = m_listSnake.begin();
	ite++;
	while (ite != m_listSnake.end())
	{
		if ((*ite)->x == m_listSnake.front()->x &&
			(*ite)->y == m_listSnake.front()->y)
		{
			return true;
		}
		ite++;
	}


	return false;

}
