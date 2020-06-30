#include "snake.h"

Snake snake;	//������
Food food;		//����ʳ��
int Pflag = 0;	//��ͣ��
int Bite = 0;	//ҧ���Լ�
					//Ŀ����Ϊ��ˢ����ʾ�ǿ��ҧ���Լ���������Ϊײǽ��

//	��Ϸ��ʼ��
void GameInit()
{
	srand((unsigned int)time(NULL));
	mciSendString("open �˵�BGM.mp3", 0, 0, 0);	//�˵�BGM
	mciSendString("play �˵�BGM.mp3 repeat", 0, 0, 0);
	initgraph(800, 600);
	setbkcolor(RGB(46, 33, 33));	//����ɫ
	cleardevice();	//����
	ModeChoose();
	CreateMap();
}

//	�˵�����
void GameMenu()
{
	char gname[] = "̰����";
	char choice[2][50] = { "1.��ʼ��Ϸ", "2.��Ϸ����(δ���)" };
	settextstyle(80, 0, "��������");
	settextcolor(COLORREF RGB(134, 235, 246));
	outtextxy(280, 125, gname);
	settextstyle(25, 0, "����");
	settextcolor(COLORREF RGB(205, 179, 107));
	outtextxy(220, 550, "��ܰ��ʾ: ֻ��ʹ��Ӣ�����뷨Ŷ");
	settextcolor(COLORREF RGB(144, 236, 194));
	//outtextxy(320, 285, "���������ʼ");
	outtextxy(250, 285, choice[0]);
	outtextxy(400, 285, choice[1]);
	outtextxy(330, 350, "[��Ϸ˵��]");
	outtextxy(320, 380, "w��;�����ƶ�");
	outtextxy(320, 410, "s��;�����ƶ�");
	outtextxy(320, 440, "a��;�����ƶ�");
	outtextxy(320, 470, "d��;�����ƶ�");
}

//	��ʼ��Ϸ
void GameStart()
{
	mciSendString("open BGM.mp3 alias BGM", 0, 0, 0);	//��BGM
	mciSendString("play BGM repeat", 0, 0, 0);			//����BGM
	SnakeInit();	//��ʼ����
	while (1)
	{
		cleardevice();	//ˢ��֡
		CreateMap();	//���Ƶ�ͼ
		SnakeDraw();	//ͼ�λ���
		FoodDraw();		//ͼ�λ�ʳ��
		ShowMessage();	//��ʾ��Ϣ
		if (_kbhit()) {
			KeyInput();		//��������
		}
		SnakeMove();	//�ߵ��ƶ�
		if (food.flag == 0) {
			FoodInit();	//��ʼ��ʳ��
		}
		Sleep(snake.speed);
		EatFood();		//�Ե�ʳ���ж�
		IfHitWall();	//�ж��Ƿ�ײǽ
	}
}

//	 ��Ϸ����
void GameSetting()
{
	int speed;
	scanf_s("%d", &speed);

}

//	������ͼ
void CreateMap()
{
	//�滭��ͼ
	setlinecolor(COLORREF RGB(253, 236, 166));	//����������ɫ
	rectangle(90, 90, 510, 520);	//�����Σ��߿�
	rectangle(100, 100, 500, 510);	//˫��߿�
}

//	ģʽѡ��
void ModeChoose()
{
	char mode;
	GameMenu();
	mode = _getch();	
	/*-------�˴��ɽ��й�����չ---------*/
	mciSendString("stop �˵�BGM.mp3", 0, 0, 0);
	switch (mode) {
	case '1':
		GameStart(); break;
	case '2':
		GameSetting(); break;
	//case '3':
		//�ޱ߿�ģʽ...
	//case '4': 
		//��ͼ�ı�.�������ϰ������ʳ�����������࣬���ٹ�ʵ�����ٹ�ʵ����Ѫ��ʵ��
	}
}

//	��ʾ��Ϣ
void ShowMessage()
{
	char player_grade[] = "��ǰ����";
	char player_speed[] = "�ƶ��ٶ�";
	char grades[100];
	char speed[50];
	sprintf_s(grades, "%d", food.grade);
	sprintf_s(speed, "%d", snake.speed);
	outtextxy(530, 100, player_grade);	//�����Ͻǽ�����ʾ����
	outtextxy(530, 400, player_speed);	//�����½ǽ�����ʾ�ٶ�
	outtextxy(530, 200, "����˵��");
	outtextxy(530, 225, "w,s,a,d�ƶ�");
	outtextxy(530, 250, "���ո����ͣ");
	outtextxy(530, 275, "�����������");
	outtextxy(635, 100, grades);
	outtextxy(635, 400, speed);
}

//	��ʼ����
void SnakeInit()
{
	//��ʼ���ȣ�3��
	snake.xy[2].x = 100;
	snake.xy[2].y = 100;

	snake.xy[1].x = 110;
	snake.xy[1].y = 100;

	snake.xy[0].x = 120;
	snake.xy[0].y = 100;

	snake.lenth = 3;
	snake.direct = right;
	snake.speed = 200;
}

//	ͼ�λ���
void SnakeDraw()
{
	int i;
	for (i = 0; i < snake.lenth; i++) {
		setlinecolor(BLACK);
		setfillcolor(COLORREF RGB(snake.color[0], snake.color[1], snake.color[2]));
		//  �����Σ��ߵ�ÿһ�ڣ�
		fillrectangle(snake.xy[i].x, snake.xy[i].y, snake.xy[i].x + 10, snake.xy[i].y + 10);
	}
}

//	�ߵ��ƶ�
void SnakeMove()
{
	int i, j;
	//���˵�һ����,��һ�������������ǰһ�ڵ�����
	//�����ƶ�ԭ���滻
	for (i = snake.lenth - 1; i > 0; i--)
	{
		snake.xy[i].x = snake.xy[i - 1].x;
		snake.xy[i].y = snake.xy[i - 1].y;
	}
	//��ͷ�˶�����,���ݷ����־���ƶ�
	switch (snake.direct)
	{
		case up:
			snake.xy[0].y -= 10;break;
		case down:
			snake.xy[0].y += 10;break;
		case right:
			snake.xy[0].x += 10;break;
		case left:
			snake.xy[0].x -= 10;break;
		case pause:
			while (_getch() != INPUT_PAUSE);
			Pflag = 0;  break;
	}
	//�ж���ײ���Լ�ʱ
	//����ͷ�����������ʱ,ײ���Լ�
	for (j = 2; j < snake.lenth; j++)
	{
		if (snake.xy[0].x == snake.xy[j].x && snake.xy[0].y == snake.xy[j].y) {
			mciSendString("open ҧ.mp3 from 0", 0, 0, 0);	//ҧ���Լ���Ч
			mciSendString("play ҧ.mp3", 0, 0, 0);
			Bite = 1;	//�������ԭ��ҧ���Լ�������ײǽ
			GameOver();
		}
	}
}

//	��������
void KeyInput()
{
	//��ȡ��ֵ
	char key = _getch();
	//��ֵ��Ӧ����
	switch (key)
	{
		case INPUT_UP:
		case 'w':
		case 'W':
			//ʵ���ߵ��ƶ��߼��ж�,�������෴�ķ����ƶ�
			if (snake.direct != down)
				snake.direct = up;
			break;
		case INPUT_DOWN:
		case 's':
		case 'S':
			if (snake.direct != up)
				snake.direct = down;
			break;
		case INPUT_LEFT:
		case 'a':
		case 'A':
			if (snake.direct != right)
				snake.direct = left;
			break;
		case INPUT_RIGHT:
		case 'd':
		case 'D':
			if (snake.direct != left)
				snake.direct = right;
			break;
		case INPUT_PAUSE:
			if (!Pflag) {
				snake.direct = pause;
				Pflag = 1;
			}
			break;
	}
}

//	��ʼ��ʳ��
void FoodInit()
{
	int i;
	//	�������
	food.foodxy.x = (rand() % 40 + 10) * 10;	//[100, 490]
	food.foodxy.y = (rand() % 41 + 10) * 10;	//[100, 500]
	//ʳ�ﲻ�������ص�
	for (i = 0; i < snake.lenth; i++)
	{
		if (food.foodxy.x == snake.xy[i].x && food.foodxy.y == snake.xy[i].y)
		{
			food.foodxy.x = (rand() % 40 + 10) * 10;	//[100, 490]
			food.foodxy.y = (rand() % 41 + 10) * 10;	//[100, 500]
		}
	}
	//	ʳ�����
	food.flag = 1;
}

//	ͼ�λ�ʳ��
void FoodDraw()
{
	setfillcolor(COLORREF RGB(rand() % 255, rand() % 255, rand() % 255));
	//	�����Բ
	solidcircle(food.foodxy.x + 5, food.foodxy.y + 5, 5);
}

//	�жϳ�ʳ��
void EatFood()
{
	//	ԭ����ͷ����ʳ��
	if (snake.xy[0].x == food.foodxy.x && snake.xy[0].y == food.foodxy.y)
	{
		mciSendString("open start.mp3 from 0", 0, 0, 0);	//�Ե�ʳ����Ч
		mciSendString("play start.mp3", 0, 0, 0);
		snake.color[0] = rand() % 255;
		snake.color[1] = rand() % 255;
		snake.color[2] = rand() % 255;
		snake.lenth++;
		food.grade += 10;
		food.flag = 0;
		if(snake.speed > SnakeMaxSpeed){
			snake.speed -= 10;
		}
	}
}

//	�ж����Ƿ�ײǽ
void IfHitWall()
{
	if (snake.xy[0].x > 490 || snake.xy[0].x < 100 || snake.xy[0].y > 500 || snake.xy[0].y < 100)
	{
		//mciSendString("pause BGM", 0, 0, 0);	//��ͣBGM
		mciSendString("open boom.mp3 from 0", 0, 0, 0);	//ײǽ��Ч
		mciSendString("play boom.mp3", 0, 0, 0);
		GameOver();		//ײǽʱ,��Ϸ����
	}
}

//	��Ϸ����
void GameOver()
{
	char endWall[] = "ײ��ǽ��������ģ�";
	char endBite[] = "ҧ���Լ���������ģ�";
	char end1[] = "Ҳ����һ�������ĸ��á�";
	char tips[] = "�����������";
	settextstyle(25, 0, "����");
	outtextxy(530, 200, endWall);
	if (Bite)outtextxy(530, 200, endBite);
	outtextxy(530, 250, tips);
	outtextxy(530, 225, end1);
	_getch();
	cleardevice();
	mciSendString("pause BGM", 0, 0, 0);	//��ͣBGM
	mciSendString("open gameover.mp3 from 0", 0, 0, 0);	//ײǽ��Ч
	mciSendString("play gameover.mp3 repeat", 0, 0, 0);
	char choose;
	char End[] = "GAME OVER";
	char goon[] = "��y��ʼ��һ��";
	char gexit[] = "������������˳�";
	settextstyle(60, 0, "��������");
	settextcolor(COLORREF RGB(134, 235, 246));
	outtextxy(260, 125, End);
	settextstyle(25, 0, "����");
	outtextxy(330, 200, goon);
	outtextxy(320, 250, gexit);
	settextcolor(COLORREF RGB(144, 236, 194));
	choose = _getch();
	switch (choose)
	{
		case 'y':
		case 'Y':
			mciSendString("stop gameover.mp3", 0, 0, 0);
			mciSendString("play BGM from 0", 0, 0, 0);	//����BGM
			GameStart(); break;
		case 'n':
		case 'N':
			exit(0); break;
	}
	exit(0);
}
