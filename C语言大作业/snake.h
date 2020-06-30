#pragma once
#ifndef __SNAKE__H
#define __SNAKE__H

/*---------------ͷ�ļ�---------------*/
#include <stdio.h>			//��׼�������
#include <easyx.h>			//ͼ�ν���(graphics.h)
#include <conio.h>			//���̽���
#include <time.h>			//���������ʹ��
#include <mmsystem.h>		//��ý���豸�ӿ�ͷ�ļ�
#pragma comment(lib, "winmm.lib")	//�������ֿ��ļ�	


/*---------------�궨��----------------*/
#define SnakeMaxLenth 100	//�ߵ���󳤶�
#define SnakeMaxSpeed 50
//	������������ֵ
#define	INPUT_UP 72
#define	INPUT_DOWN 80
#define INPUT_LEFT 75
#define	INPUT_RIGHT 77
#define INPUT_PAUSE 32


/*---------------�ṹ��----------------*/
//	��ʾ����
typedef struct Point
{
	int x;
	int y;
}point;

//	�ߵ�����
typedef struct Snake
{
	int lenth;						//�ߵĽ���
	point xy[SnakeMaxLenth];		//����󳤶�
	char direct;					//��Ƿ���
	int speed;						//�ߵ��ٶ�
	int color[3] = {88, 88, 88};	//�ߵ���ɫ
}Snake;

//	ʳ�������
typedef struct Food
{
	point foodxy;	//ʳ������
	int flag;		//ʳ����ڱ�־
	int grade;		//����
}Food;

//	���ߵķ����ж�ö��
enum SnakeDirection { right, left, up, down, pause };



/*------���ܺ�����ģ�黯��ƣ�--------*/
void GameInit();			//��Ϸ��ʼ��
void GameMenu();			//��Ϸ�˵�����
void GameStart();			//��ʼ��Ϸ
void GameSettint();			//��Ϸ����
void GameOver();			//��Ϸ����
void ModeChoose();			//ģʽѡ��
void ShowMessage();			//��ʾ��Ϣ
void CreateMap();			//������ͼ

void SnakeInit();			//��ʼ����
void SnakeDraw();			//ͼ�λ���
void SnakeMove();			//�ߵ��ƶ�
void KeyInput();			//���̽���

void FoodInit();			//��ʼ��ʳ��
void FoodDraw();			//ͼ�λ�ʳ��
void EatFood();				//��ʳ��

void IfHitWall();			//�ж�ײǽ


#endif