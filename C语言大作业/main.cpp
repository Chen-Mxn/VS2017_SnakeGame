#include "snake.h"

extern Snake snake;
extern Food food;

int main()
{
	GameInit();		//��Ϸ��ʼ��
	_getch();
	closegraph();
	return 0;
}