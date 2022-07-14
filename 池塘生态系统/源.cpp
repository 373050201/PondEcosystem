#include <graphics.h> 
#include <conio.h>
#include<iostream>
#include<time.h>
#pragma comment( lib, "MSIMG32.LIB")
using namespace std;



/*→定义区←*/
#define MAXSTAR 800//星星总数
#define screenWidth 1401//屏幕宽度
#define screenHeight 701//屏幕高度
#define maxCreatureNum 100000//最大生物量



/*→全局变量区←*/
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



/*→函数声明区←*/
void init();//初始化
void initWindowSettings();//初始视窗设定
void drawStarBackground();//画星星背景
void InitStar(int i);//初始化星星
void MoveStar(int i);//移动星星
void drawBorder();//画边框
void drawWelcomeText();//画欢迎文本
void loadImage();//加载图片
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor);//图片透明化
void initP();//初始化数据

void mainWindow();//主界面
void fresh();//刷新界面
void drawExpl();//画说明
void drawGame();//画游戏界面
void running();//游戏运行逻辑
void createFishYou();//产生自己
void createGrass();//产生水草
void drawGrass();//画水草
void createFishOther();//产生其他鱼
void drawFishOther();//画其他鱼
void textFishNum();//鱼总数文本
void textGrassNum();//水草总数文本
void textRich();//富饶度文本
void textScore();//当前成熟度文本
void textHP();//当前生命值文本
void move();//移动鱼
void checkPos();//检查鱼的位置同时做出响应
void checkHP();//检查HP
void checkScore();//检查分数
void checkRich();//检查富饶度
void pauseWindow();//暂停页面

void endWindow();//结束界面
void winWindow();//胜利界面
void loseWindow();//失败界面

void deleteP();//归还生物堆空间



/*→主函数←*/
int main()
{
	init();
	cleardevice();//清屏
	mainWindow();
	cleardevice();
	deleteP();
	endWindow();
	closegraph();//关闭绘图窗口
	return 0;
}



/*→函数定义区←*/
void init()//初始化
{
	srand((unsigned)time(NULL));
	loadImage();
	initWindowSettings();
	initP();
	_getch();
}



void loadImage()//加载图片
{
	loadimage(&pool, _T("res\\pool.jpg"));
	loadimage(&grass, _T("res\\grass.png"));
	loadimage(&fishYou[0], _T("res\\fishYou_0.png"));
	loadimage(&fishYou[1], _T("res\\fishYou_1.png"));
	loadimage(&fishOther[0], _T("res\\fishOther_0.png"));
	loadimage(&fishOther[1], _T("res\\fishOther_1.png"));
	loadimage(&fishOther[2], _T("res\\fishOther_2.png"));
}



void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor)//图片透明化
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	TransparentBlt(dstDC, x, y, w, h, srcDC, 0, 0, w, h, transparentcolor);// 使用 Windows GDI 函数实现透明位图
}



void initWindowSettings()//初始视窗设定
{
	initgraph(screenWidth, screenHeight);//绘制1401*701pixel的视窗
	drawBorder();
	drawWelcomeText();
	drawStarBackground();
}



void drawStarBackground()//画星星背景
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



void InitStar(int i)//初始化星星
{
	star[i].x = 0;
	star[i].y = rand() % screenHeight;
	star[i].step = (rand() % 5000) / 1000.0 + 1;
	star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5);
	star[i].color = RGB(star[i].color, star[i].color, star[i].color);
}



void MoveStar(int i)//移动星星
{
	putpixel((int)star[i].x, star[i].y, 0);
	star[i].x += star[i].step;
	if (star[i].x > screenWidth)	InitStar(i);
	putpixel((int)star[i].x, star[i].y, star[i].color);
}



void drawBorder()//画边框
{
	setlinestyle(PS_DASH, 3);//虚线3像素
	rectangle(0, screenHeight - 1, screenWidth - 1, 0);//画矩形
}



void drawWelcomeText()//画欢迎文本
{
	for (float L = 0; L <= 0.6; L += 0.002)
	{
		settextcolor(HSLtoRGB(200, 1, L));//亮蓝
		settextstyle(40, 15, _T("微软雅黑"));
		TCHAR welcome[] = _T("欢迎来到wyw的池塘生态系统");
		outtextxy(475, 250, welcome);
		Sleep(1);
	}
	for (float L = 0; L <= 0.7; L += 0.002)
	{
		settextcolor(HSLtoRGB(170, 1, L));//浅蓝
		settextstyle(30, 12, _T("微软雅黑"));
		TCHAR by[] = _T("By:15—王毅伟");
		outtextxy(775, 300, by);
		Sleep(1);
	}
	for (float L = 0; L <= 0.2; L += 0.0005)
	{
		settextcolor(HSLtoRGB(100, 1, L));//浅绿
		settextstyle(25, 10, _T("微软雅黑"));
		TCHAR PTC[] = _T("（输入任意键以开始...）");
		outtextxy(580, 340, PTC);
		Sleep(0.8);
	}
}



void initP()//初始化数据
{
	for (int i = 0; i < 100000; i++)
	{
		pm[i] = 0;
		posGrassRec[i] = 0;
		posFishRec[i] = 0;
	}
}



void mainWindow()//主界面
{
	drawBorder();
	Sleep(200);
	drawExpl();
	drawGame();
	Sleep(40);
	running();
}



void fresh()//刷新界面
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



void drawExpl()//画说明
{
	settextcolor(WHITE);
	setlinestyle(PS_DOT, 3);
	rectangle(1040, 600, 1340, 100);//画说明边框
	RECT recExpl = { 1050, 110, 1401, 701 };
	settextstyle(22, 8, _T("微软雅黑"));
	TCHAR expl[] = _T("///游戏目标：让小鱼活下去！！！///\n\n\n///* 当前池塘状态///\n小鱼成熟度：         / 10000\n小鱼生命值：  / 3\n水草数：\n鱼总数：\n水体富饶度：\n\n\n///操作说明///\n1 - 投放水草\n2 - 投放小鱼\nWASD - 移动你的鱼\nspace - 暂停/继续\n\n\n///自行探索~HAVE FUN！！！///");
	drawtext(expl, &recExpl, DT_LEFT);
}



void drawGame()//画游戏界面
{
	setlinestyle(PS_DOT, 3);
	rectangle(50, 650, 950, 50);//画游戏边框
	setfillstyle(BS_DIBPATTERN, NULL, &pool);
	fillrectangle(50, 650, 950, 50);//用pool图片填充游戏界面
}



void running()//游戏运行逻辑
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
		Sleep(16);//保证FPS约等于60
	}
}



void createFishYou()//产生自己
{
	if (flagInitMyFish == 0)
	{
		myFish.x = 55 + rand() % 751;
		myFish.y = 70 + rand() % 251;
		flagInitMyFish = 1;
	}
	transparentimage(NULL, myFish.x, myFish.y, &fishYou[fishYouState], 0xffc4c4);
}



void createGrass()//产生水草
{
	pGrass[grassNum].x = 55 + rand() % 801;
	pGrass[grassNum].y = 310 + rand() % 251;
	grassNum++;
}



void createFishOther()//产生其他鱼
{
	pFishOther[fishNum].fishOtherStyle = rand() % 3;
	pFishOther[fishNum].x = 55 + rand() % 751;
	pFishOther[fishNum].y = 70 + rand() % 401;
	fishNum++;
}



void textFishNum()//鱼总数文本
{
	settextcolor(YELLOW);
	TCHAR fishNumText[10];
	_itow_s(fishNum + 1 - fishNumRec, fishNumText, 10);
	outtextxy(1110, 257, fishNumText);
}



void textGrassNum()//水草总数文本
{
	settextcolor(YELLOW);
	TCHAR grassNumText[10];
	_itow_s(grassNum - grassNumRec, grassNumText, 10);
	outtextxy(1110, 236, grassNumText);
}



void textRich()//富饶度文本
{
	if (float(grassNum - grassNumRec) / float(fishNum - fishNumRec + 1) >= 5 || float(grassNum - grassNumRec) / float(fishNum - fishNumRec + 1) <= 0.2)
	{
		settextcolor(LIGHTRED);
		TCHAR richText[] = _T("不平衡");
		outtextxy(1145, 278, richText);
	}
	else
	{
		settextcolor(LIGHTGREEN);
		TCHAR richText[] = _T("已平衡");
		outtextxy(1145, 278, richText);
	}
}



void textScore()//当前成熟度文本
{
	settextcolor(YELLOW);
	TCHAR scoreText[10];
	_itow_s(score, scoreText, 10);
	outtextxy(1142, 194, scoreText);
}



void textHP()//当前生命值文本
{
	settextcolor(YELLOW);
	TCHAR HPText[10];
	_itow_s(HP, HPText, 10);
	outtextxy(1142, 215, HPText);
}



void drawGrass()//画水草
{
	for (int i = 0; i < grassNum + 1; i++)
	{
		transparentimage(NULL, pGrass[i].x, pGrass[i].y, &grass, 0xffc4c4);
	}
}



void drawFishOther()//画其他鱼
{
	for (int i = 0; i < fishNum; i++)
	{
		transparentimage(NULL, pFishOther[i].x, pFishOther[i].y, &fishOther[pFishOther[i].fishOtherStyle], 0xffc4c4);
	}
}



void move()//移动鱼
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



void checkPos()//检查鱼的位置同时做出响应
{
	for (int i = 0; i < fishNum; i++)
	{
		if (myFish.x >= pFishOther[i].x - 120 && myFish.x <= pFishOther[i].x + 120 && myFish.y >= pFishOther[i].y - 120 && myFish.y <= pFishOther[i].y + 100)
		{
			if (score <= 6000)//6000分以下无法吃到鱼，会被鱼吃
			{
				myFish.x = 56;
				myFish.y = 60;
				HP -= 1;
			}
			else
			{
				pFishOther[i].x = -300;//让鱼消失
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
			pGrass[i].x = -500;//让草消失
			pGrass[i].x = -500;
			posGrassRec[i] = 1;
			grassNumRec++;
			if (score < 6000)//6000分以下吃草+200分，以上惩罚至50分
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
				pGrass[i].x = -500;//让草消失
				pGrass[i].x = -500;
				grassNumRec++;
			}
		}
	}
}



void checkHP()//检查HP
{
	if (HP <= 0)
	{
		breakFlag = 1;
		scene = 1;
	}
}



void checkScore()//检查分数
{
	if (score >= 10000)
	{
		breakFlag = 1;
		scene = 2;
	}
}



void checkRich()//检查富饶度
{
	if (float(grassNum - grassNumRec) / float(fishNum - fishNumRec + 1) >= 5 || float(grassNum - grassNumRec) / float(fishNum - fishNumRec + 1) <= 0.2)
	{
		richTime++;
	}
	if ((float(grassNum - grassNumRec) / float(fishNum - fishNumRec + 1) >= 25 || float(grassNum - grassNumRec) / float(fishNum - fishNumRec + 1) <= 0.04) && grassNum - grassNumRec != 0)
	{
		HP = 0;
	}
	if (richTime == 120)//若不平衡时间达到20s，则HP-1
	{
		HP--;
		richTime = 0;
	}
}



void pauseWindow()//暂停页面
{
	drawBorder();
	while (1)
	{
		settextcolor(YELLOW);
		settextstyle(40, 15, _T("微软雅黑"));
		TCHAR pauseText[] = _T("已暂停...（输入空格键以继续）");
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



void endWindow()//结束界面
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



void winWindow()//胜利界面
{
	while (1)
	{
		settextcolor(LIGHTGREEN);
		settextstyle(40, 15, _T("微软雅黑"));
		TCHAR winText[] = _T("You Win！！！（输入空格键以结束）");
		outtextxy(475, 250, winText);
		int a = _getch();
		if (a == 32)
		{
			break;
		}
		Sleep(40);
	}
}



void loseWindow()//失败界面
{
	while (1)
	{
		settextcolor(LIGHTRED);
		settextstyle(40, 15, _T("微软雅黑"));
		TCHAR loseText[] = _T("You Lose...（输入空格键以结束）");
		outtextxy(475, 250, loseText);
		int a = _getch();
		if (a == 32)
		{
			break;
		}
		Sleep(40);
	}
}



void deleteP()//归还生物堆空间
{
	delete[] pGrass;
	delete[] pFishOther;
	delete[] pm;
	delete[] moveFlag;
	delete[] posFishRec;
	delete[] posGrassRec;
}