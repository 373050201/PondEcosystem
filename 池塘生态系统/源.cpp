#include <graphics.h> 
#include <conio.h>
#include<iostream>
#include<time.h>
#pragma comment( lib, "MSIMG32.LIB")
using namespace std;



/*����������*/
#define MAXSTAR 800//��������
#define screenWidth 1401//��Ļ���
#define screenHeight 701//��Ļ�߶�
#define maxCreatureNum 100000//���������



/*��ȫ�ֱ�������*/
IMAGE pool;
IMAGE grass;
IMAGE fishYou[2];
IMAGE fishOther[3];
bool flagInitMyFish = 0;
int score = 0;
int HP = 3;
int grassNum = 0;
int fishNum = 0;
int fishYouState = 0;
int fishNumRec = 0;
int grassNumRec = 0;
bool breakFlag = 0;
int scene = 0;
int richTime = 0;
struct STAR
{
	double	x;
	int y;
	double	step;
	int color;
};
STAR star[MAXSTAR];
struct creatures
{
	int x;
	int y;
	int fishOtherStyle = 0;
};
creatures myFish = { 0,0,-1 };
creatures* pGrass = new creatures[maxCreatureNum];
creatures* pFishOther = new creatures[maxCreatureNum];
int* pm = new int[maxCreatureNum];
int* moveFlag = new int[maxCreatureNum];
bool* posGrassRec = new bool[maxCreatureNum];
bool* posFishRec = new bool[maxCreatureNum];



/*��������������*/
void init();//��ʼ��
void initWindowSettings();//��ʼ�Ӵ��趨
void drawStarBackground();//�����Ǳ���
void InitStar(int i);//��ʼ������
void MoveStar(int i);//�ƶ�����
void drawBorder();//���߿�
void drawWelcomeText();//����ӭ�ı�
void loadImage();//����ͼƬ
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor);//ͼƬ͸����
void initP();//��ʼ������

void mainWindow();//������
void fresh();//ˢ�½���
void drawExpl();//��˵��
void drawGame();//����Ϸ����
void running();//��Ϸ�����߼�
void createFishYou();//�����Լ�
void createGrass();//����ˮ��
void drawGrass();//��ˮ��
void createFishOther();//����������
void drawFishOther();//��������
void textFishNum();//�������ı�
void textGrassNum();//ˮ�������ı�
void textRich();//���Ķ��ı�
void textScore();//��ǰ������ı�
void textHP();//��ǰ����ֵ�ı�
void move();//�ƶ���
void checkPos();//������λ��ͬʱ������Ӧ
void checkHP();//���HP
void checkScore();//������
void checkRich();//��鸻�Ķ�
void pauseWindow();//��ͣҳ��

void endWindow();//��������
void winWindow();//ʤ������
void loseWindow();//ʧ�ܽ���

void deleteP();//�黹����ѿռ�



/*����������*/
int main()
{
	init();
	cleardevice();//����
	mainWindow();
	cleardevice();
	deleteP();
	endWindow();
	closegraph();//�رջ�ͼ����
	return 0;
}



/*��������������*/
void init()//��ʼ��
{
	srand((unsigned)time(NULL));
	loadImage();
	initWindowSettings();
	initP();
	_getch();
}



void loadImage()//����ͼƬ
{
	loadimage(&pool, _T("res\\pool.jpg"));
	loadimage(&grass, _T("res\\grass.png"));
	loadimage(&fishYou[0], _T("res\\fishYou_0.png"));
	loadimage(&fishYou[1], _T("res\\fishYou_1.png"));
	loadimage(&fishOther[0], _T("res\\fishOther_0.png"));
	loadimage(&fishOther[1], _T("res\\fishOther_1.png"));
	loadimage(&fishOther[2], _T("res\\fishOther_2.png"));
}



void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor)//ͼƬ͸����
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	TransparentBlt(dstDC, x, y, w, h, srcDC, 0, 0, w, h, transparentcolor);// ʹ�� Windows GDI ����ʵ��͸��λͼ
}



void initWindowSettings()//��ʼ�Ӵ��趨
{
	initgraph(screenWidth, screenHeight);//����1401*701pixel���Ӵ�
	drawBorder();
	drawWelcomeText();
	drawStarBackground();
}



void drawStarBackground()//�����Ǳ���
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < MAXSTAR; i++)
	{
		InitStar(i);
		star[i].x = rand() % screenWidth;
	}
	while (!_kbhit())
	{
		for (int i = 0; i < MAXSTAR; i++)
			MoveStar(i);
		Sleep(30);
	}
}



void InitStar(int i)//��ʼ������
{
	star[i].x = 0;
	star[i].y = rand() % screenHeight;
	star[i].step = (rand() % 5000) / 1000.0 + 1;
	star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5);
	star[i].color = RGB(star[i].color, star[i].color, star[i].color);
}



void MoveStar(int i)//�ƶ�����
{
	putpixel((int)star[i].x, star[i].y, 0);
	star[i].x += star[i].step;
	if (star[i].x > screenWidth)	InitStar(i);
	putpixel((int)star[i].x, star[i].y, star[i].color);
}



void drawBorder()//���߿�
{
	setlinestyle(PS_DASH, 3);//����3����
	rectangle(0, screenHeight - 1, screenWidth - 1, 0);//������
}



void drawWelcomeText()//����ӭ�ı�
{
	for (float L = 0; L <= 0.6; L += 0.002)
	{
		settextcolor(HSLtoRGB(200, 1, L));//����
		settextstyle(40, 15, _T("΢���ź�"));
		TCHAR welcome[] = _T("��ӭ����wyw�ĳ�����̬ϵͳ");
		outtextxy(475, 250, welcome);
		Sleep(1);
	}
	for (float L = 0; L <= 0.7; L += 0.002)
	{
		settextcolor(HSLtoRGB(170, 1, L));//ǳ��
		settextstyle(30, 12, _T("΢���ź�"));
		TCHAR by[] = _T("By:15������ΰ");
		outtextxy(775, 300, by);
		Sleep(1);
	}
	for (float L = 0; L <= 0.2; L += 0.0005)
	{
		settextcolor(HSLtoRGB(100, 1, L));//ǳ��
		settextstyle(25, 10, _T("΢���ź�"));
		TCHAR PTC[] = _T("������������Կ�ʼ...��");
		outtextxy(580, 340, PTC);
		Sleep(0.8);
	}
}



void initP()//��ʼ������
{
	for (int i = 0; i < 100000; i++)
	{
		pm[i] = 0;
		posGrassRec[i] = 0;
		posFishRec[i] = 0;
	}
}



void mainWindow()//������
{
	drawBorder();
	Sleep(200);
	drawExpl();
	drawGame();
	Sleep(40);
	running();
}



void fresh()//ˢ�½���
{
	drawExpl();
	drawGame();
	textFishNum();
	textGrassNum();
	textRich();
	textScore();
	textHP();
	createFishYou();
	drawGrass();
	drawFishOther();
	checkPos();
	checkRich();
	checkHP();
	checkScore();
	move();
}



void drawExpl()//��˵��
{
	settextcolor(WHITE);
	setlinestyle(PS_DOT, 3);
	rectangle(1040, 600, 1340, 100);//��˵���߿�
	RECT recExpl = { 1050, 110, 1401, 701 };
	settextstyle(22, 8, _T("΢���ź�"));
	TCHAR expl[] = _T("///��ϷĿ�꣺��С�����ȥ������///\n\n\n///* ��ǰ����״̬///\nС�����ȣ�         / 10000\nС������ֵ��  / 3\nˮ������\n��������\nˮ�帻�Ķȣ�\n\n\n///����˵��///\n1 - Ͷ��ˮ��\n2 - Ͷ��С��\nWASD - �ƶ������\nspace - ��ͣ/����\n\n\n///����̽��~HAVE FUN������///");
	drawtext(expl, &recExpl, DT_LEFT);
}



void drawGame()//����Ϸ����
{
	setlinestyle(PS_DOT, 3);
	rectangle(50, 650, 950, 50);//����Ϸ�߿�
	setfillstyle(BS_DIBPATTERN, NULL, &pool);
	fillrectangle(50, 650, 950, 50);//��poolͼƬ�����Ϸ����
}



void running()//��Ϸ�����߼�
{
	createFishYou();
	while (breakFlag == 0)
	{
		fresh();
		if (_kbhit())
		{
			int a = _getch();
			switch (a)
			{
			case 32://space
			{
				cleardevice();
				pauseWindow();
				break;
			}
			case 49://1
			{
				createGrass();
				break;
			}
			case 50://2
			{
				createFishOther();
				break;
			}
			case 97://a
			{
				myFish.x -= 20;
				if (myFish.x < 55)
				{
					myFish.x = 55;
				}
				fishYouState = 1;
				break;
			}
			case 100://d
			{
				myFish.x += 20;
				if (myFish.x > 805)
				{
					myFish.x = 805;
				}
				fishYouState = 0;
				break;
			}
			case 115://s
			{
				myFish.y += 20;
				if (myFish.y > 515)
				{
					myFish.y = 515;
				}
				break;
			}
			case 119://w
			{
				myFish.y -= 20;
				if (myFish.y < 55)
				{
					myFish.y = 55;
				}
				break;
			}
			}
		}
		Sleep(16);//��֤FPSԼ����60
	}
}



void createFishYou()//�����Լ�
{
	if (flagInitMyFish == 0)
	{
		myFish.x = 55 + rand() % 751;
		myFish.y = 70 + rand() % 251;
		flagInitMyFish = 1;
	}
	transparentimage(NULL, myFish.x, myFish.y, &fishYou[fishYouState], 0xffc4c4);
}



void createGrass()//����ˮ��
{
	pGrass[grassNum].x = 55 + rand() % 801;
	pGrass[grassNum].y = 310 + rand() % 251;
	grassNum++;
}



void createFishOther()//����������
{
	pFishOther[fishNum].fishOtherStyle = rand() % 3;
	pFishOther[fishNum].x = 55 + rand() % 751;
	pFishOther[fishNum].y = 70 + rand() % 401;
	fishNum++;
}



void textFishNum()//�������ı�
{
	settextcolor(YELLOW);
	TCHAR fishNumText[10];
	_itow_s(fishNum + 1 - fishNumRec, fishNumText, 10);
	outtextxy(1110, 257, fishNumText);
}



void textGrassNum()//ˮ�������ı�
{
	settextcolor(YELLOW);
	TCHAR grassNumText[10];
	_itow_s(grassNum - grassNumRec, grassNumText, 10);
	outtextxy(1110, 236, grassNumText);
}



void textRich()//���Ķ��ı�
{
	if (float(grassNum - grassNumRec) / float(fishNum - fishNumRec + 1) >= 5 || float(grassNum - grassNumRec) / float(fishNum - fishNumRec + 1) <= 0.2)
	{
		settextcolor(LIGHTRED);
		TCHAR richText[] = _T("��ƽ��");
		outtextxy(1145, 278, richText);
	}
	else
	{
		settextcolor(LIGHTGREEN);
		TCHAR richText[] = _T("��ƽ��");
		outtextxy(1145, 278, richText);
	}
}



void textScore()//��ǰ������ı�
{
	settextcolor(YELLOW);
	TCHAR scoreText[10];
	_itow_s(score, scoreText, 10);
	outtextxy(1142, 194, scoreText);
}



void textHP()//��ǰ����ֵ�ı�
{
	settextcolor(YELLOW);
	TCHAR HPText[10];
	_itow_s(HP, HPText, 10);
	outtextxy(1142, 215, HPText);
}



void drawGrass()//��ˮ��
{
	for (int i = 0; i < grassNum + 1; i++)
	{
		transparentimage(NULL, pGrass[i].x, pGrass[i].y, &grass, 0xffc4c4);
	}
}



void drawFishOther()//��������
{
	for (int i = 0; i < fishNum; i++)
	{
		transparentimage(NULL, pFishOther[i].x, pFishOther[i].y, &fishOther[pFishOther[i].fishOtherStyle], 0xffc4c4);
	}
}



void move()//�ƶ���
{
	for (int i = 0; i < fishNum + 1; i++)
	{
		if (posFishRec[i] == 1)
		{
			continue;
		}
		if (pm[i] == 0)
		{
			moveFlag[i] = rand() % 4;
		}
		pm[i]++;
		if (pm[i] == 20)
		{
			pm[i] = 0;
		}
		if (moveFlag[i] == 0)
		{
			pFishOther[i].x += 7;
			if (pFishOther[i].x > 805)
			{
				pFishOther[i].x = 805;
			}
		}
		if (moveFlag[i] == 1)
		{
			pFishOther[i].x -= 7;
			if (pFishOther[i].x < 55)
			{
				pFishOther[i].x = 55;
			}
		}
		if (moveFlag[i] == 2)
		{
			pFishOther[i].y += 7;
			if (pFishOther[i].y > 515)
			{
				pFishOther[i].y = 515;
			}
		}
		if (moveFlag[i] == 3)
		{
			pFishOther[i].y -= 7;
			if (pFishOther[i].y < 55)
			{
				pFishOther[i].y = 55;
			}
		}
		if (pFishOther[i].x < 205 && pFishOther[i].y < 205)
		{
			if (pFishOther[i].x < 190)
			{
				pFishOther[i].y = 205;
			}
			if (pFishOther[i].y < 190)
			{
				pFishOther[i].x = 205;
			}
		}
	}
}



void checkPos()//������λ��ͬʱ������Ӧ
{
	for (int i = 0; i < fishNum; i++)
	{
		if (myFish.x >= pFishOther[i].x - 120 && myFish.x <= pFishOther[i].x + 120 && myFish.y >= pFishOther[i].y - 120 && myFish.y <= pFishOther[i].y + 100)
		{
			if (score <= 6000)//6000�������޷��Ե��㣬�ᱻ���
			{
				myFish.x = 56;
				myFish.y = 60;
				HP -= 1;
			}
			else
			{
				pFishOther[i].x = -300;//������ʧ
				pFishOther[i].y = -300;
				posFishRec[i] = 1;
				fishNumRec++;
				score += 500;
			}
		}
	}
	for (int i = 0; i < grassNum; i++)
	{
		if (myFish.x >= pGrass[i].x - 130 && myFish.x <= pGrass[i].x + 45 && myFish.y >= pGrass[i].y - 120 && myFish.y <= pGrass[i].y + 45)
		{
			pGrass[i].x = -500;//�ò���ʧ
			pGrass[i].x = -500;
			posGrassRec[i] = 1;
			grassNumRec++;
			if (score < 6000)//6000�����³Բ�+200�֣����ϳͷ���50��
			{
				score += 200;
			}
			else
			{
				score += 50;
			}
		}
		for (int j = 0; j < fishNum; j++)
		{
			if (pFishOther[j].x >= pGrass[i].x - 120 && pFishOther[j].x <= pGrass[i].x + 65 && pFishOther[j].y >= pGrass[i].y - 120 && pFishOther[j].y <= pGrass[i].y + 80)
			{
				pGrass[i].x = -500;//�ò���ʧ
				pGrass[i].x = -500;
				grassNumRec++;
			}
		}
	}
}



void checkHP()//���HP
{
	if (HP <= 0)
	{
		breakFlag = 1;
		scene = 1;
	}
}



void checkScore()//������
{
	if (score >= 10000)
	{
		breakFlag = 1;
		scene = 2;
	}
}



void checkRich()//��鸻�Ķ�
{
	if (float(grassNum - grassNumRec) / float(fishNum - fishNumRec + 1) >= 5 || float(grassNum - grassNumRec) / float(fishNum - fishNumRec + 1) <= 0.2)
	{
		richTime++;
	}
	if ((float(grassNum - grassNumRec) / float(fishNum - fishNumRec + 1) >= 25 || float(grassNum - grassNumRec) / float(fishNum - fishNumRec + 1) <= 0.04) && grassNum - grassNumRec != 0)
	{
		HP = 0;
	}
	if (richTime == 120)//����ƽ��ʱ��ﵽ20s����HP-1
	{
		HP--;
		richTime = 0;
	}
}



void pauseWindow()//��ͣҳ��
{
	drawBorder();
	while (1)
	{
		settextcolor(YELLOW);
		settextstyle(40, 15, _T("΢���ź�"));
		TCHAR pauseText[] = _T("����ͣ...������ո���Լ�����");
		outtextxy(475, 250, pauseText);
		if (_kbhit())
		{
			int a = _getch();
			if (a == 32)
			{
				break;
			}
		}
		Sleep(40);
	}


}



void endWindow()//��������
{
	drawBorder();
	if (scene == 1)
	{
		loseWindow();
	}
	else
	{
		winWindow();
	}
}



void winWindow()//ʤ������
{
	while (1)
	{
		settextcolor(LIGHTGREEN);
		settextstyle(40, 15, _T("΢���ź�"));
		TCHAR winText[] = _T("You Win������������ո���Խ�����");
		outtextxy(475, 250, winText);
		int a = _getch();
		if (a == 32)
		{
			break;
		}
		Sleep(40);
	}
}



void loseWindow()//ʧ�ܽ���
{
	while (1)
	{
		settextcolor(LIGHTRED);
		settextstyle(40, 15, _T("΢���ź�"));
		TCHAR loseText[] = _T("You Lose...������ո���Խ�����");
		outtextxy(475, 250, loseText);
		int a = _getch();
		if (a == 32)
		{
			break;
		}
		Sleep(40);
	}
}



void deleteP()//�黹����ѿռ�
{
	delete[] pGrass;
	delete[] pFishOther;
	delete[] pm;
	delete[] moveFlag;
	delete[] posFishRec;
	delete[] posGrassRec;
}