——————————————————————README——————————————————————————
/*基本情况*/
项目名称：池塘生态系统
开发者：王毅伟
班级：15
学号：2019210463
语言：C++
开发环境：Microsoft Visual Studio 2019
总行数：734
第三方类库：EasyX图形库（用于图形界面显示）、MSIMG32静态库（用于透明背景图片的填充）



/*游戏规则*/（部分在游戏界面中有写）
·目的：让小鱼活下来，为了达到目的，你需要手动添加水草和其他鱼。

·成熟度（分数）达到10000时游戏胜利，3条HP耗尽后游戏失败。

·0~6000成熟度时，只能吃水草，吃一株水草+200分，碰到其他的鱼会被吃掉，HP会-1；
6000~10000成熟度时，水草和其他鱼都可以吃，吃一株水草+50分，吃一条鱼+500分。

·其他鱼也会吃草，相关数据会在状态区显示。

·当鱼或草比另一类生物多5倍或以上时，池塘的富饶度会变为“不平衡”，在此状态下的累计时间每达到15s，则HP会-1；如果
倍数达到了25，你的鱼会直接死亡。（如果只顾吃而忽略了平衡，很难赢下游戏）

·操作（大键盘）：WASD-控制小鱼移动，1-添加水草，2-添加其他鱼，空格-暂停/继续。



/*项目结构*/
1、欢迎页
①星空背景
②项目标题及作者文本
③欢迎文本

2、游戏页
①状态区
I.目的文本
II.操作帮助文本
III.状态数据
IV.零碎附加文本
②游戏区
I.池塘背景
II.单位显示
III.页面逻辑
*③暂停页

3、结束页
①胜利文本
②失败文本



/*关于创意*/
·在不偏离“池塘生态系统”主题的前提下做一个规则新颖的，功能与界面较完备的小游戏。

·为了解决透明背景图片填充问题，加入msimg32.lib后使用TransparentBit（）函数以实现。

·面向过程的结构化思想：将大项目分解为一个个小分区，分别去解决他们，最后用函数调用进行组装。

·为每个手动生成的生物用new函数分配了堆空间以避免栈空间溢出的问题。

·不同于传统的大鱼吃小鱼，玩家的鱼还可以吃草，不同成熟度的食物及奖励也不同，同时玩家也需要通过自己对生物的手动添加来
确保生态系统的平衡，最终赢下游戏。

·鱼死后会生成在游戏区左上角，我为左上角区域设计了一个安全区，其他鱼无法进入，从而避免“死后立刻再死”情况的出现。



/*关于感受*/
·导论课的大作业我是和同学一起合作完成的，合作的乐趣以及优势在此不多赘述，但这次cpp的大作业，我想选择一个人去完成，
自私地说，我想去体会独立完成一个大项目带给自己成就感，同时也可以最大限度地检验自己的能力。

·独立完成一个项目，从头到尾，要自己一个人计划并完成所有的工作，这真的需要找到一个强大且持久的动力的支持，
我想，我心里对编程，对计算机的热爱以及获取新知识时的满足感可以成为这份动力的源头，虽然很孤独，但乐在其中。

·cpp是一个面向对象的语言，然而我这次没有去选择面向对象的思路去解决问题，而去选择了一个更直接的面向过程的思路，
而这一点，我居然是写完了大半个程序之后才意识到的。为此我感到由衷的惋惜。

·但为了弥补，我写完项目之后又大致思考了一下，如果用面向对象的思路去改写程序会是如何：
1、聚焦点将不再是解决问题的过程，而是每一个存在的对象，再把每一个对象封装到相应的类里——界面类，鱼类，水草类。
2、每个类都会有对应的方法去替代原先的“把步骤写在函数里”的过程——界面类有“显示边框，显示状态数据，显示文本”等多个方法，
鱼类里有“显示，移动，检测坐标，消失”等多个方法，水草类里又有“显示，消失”等多个方法。
3、面向对象的继承特点也可以得到充分利用，玩家的鱼和其他鱼都有“拥有坐标属性”的共性，而玩家的鱼又可以被操控着移动，其他
鱼却可以随机移动，这些类似的异性同样存在，所以，可以把玩家的鱼类和其他鱼类封装为两个子类，继承“鱼类”这一父类，可以很
大程度简化解决问题的思路，也能减少程序冗余的可能。

·在程序中我使用了new函数分配堆空间，一次性的为所有生物分配了内存，这样做浪费了没有利用的空间，很大地降低了程序的运行效率，
后期我希望自己可以用链表的方式来解决这个问题，这次先用一个“笨方法”。（算是偷了个小懒）

·这次的池塘生态系统还有很多不完备的地方，比如“不平衡惩罚”的可见性，鱼、草总数文本的显示bug以及屏幕的闪动bug，这些都是
有待改进的方面。

·等期末考试过后，有了充足的时间，我希望自己可以如上所说，真正用面向对象的思路以及链表的方法去把这个生态系统写的更完美一些，
同时把上述的方面尽数完备。



//写的有点多，感谢您看到这里的耐心//
//快捷方式为debug版//



——————————————————————以下为cpp源代码———————————————————————————
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
	rectangle(0, screenHeight-1, screenWidth-1, 0);//画矩形
}



void drawWelcomeText()//画欢迎文本
{
	for (float L = 0;L <= 0.6;L += 0.002)
	{
		settextcolor(HSLtoRGB(200, 1, L));//亮蓝
		settextstyle(40, 15, _T("微软雅黑"));
		TCHAR welcome[] = _T("欢迎来到wyw的池塘生态系统");
		outtextxy(475, 250, welcome);
		Sleep(1);
	}
	for (float L = 0;L <= 0.7;L += 0.002)
	{
		settextcolor(HSLtoRGB(170, 1, L));//浅蓝
		settextstyle(30, 12, _T("微软雅黑"));
		TCHAR by[] = _T("By:15—王毅伟");
		outtextxy(775, 300, by);
		Sleep(1);
	}
	for (float L = 0;L <= 0.2;L += 0.0005)
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
	for (int i = 0;i < 100000;i++)
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
	while (breakFlag==0)
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
	pGrass[grassNum].y= 310 + rand() % 251;
	grassNum++;
}



void createFishOther()//产生其他鱼
{
	pFishOther[fishNum].fishOtherStyle=rand() % 3;
	pFishOther[fishNum].x = 55 + rand() % 751;
	pFishOther[fishNum].y = 70 + rand() % 401;
	fishNum++;
}



void textFishNum()//鱼总数文本
{
	settextcolor(YELLOW);
	TCHAR fishNumText[10];
	_itow_s(fishNum+1-fishNumRec, fishNumText, 10);
	outtextxy(1110, 257, fishNumText);
}



void textGrassNum()//水草总数文本
{
	settextcolor(YELLOW);
	TCHAR grassNumText[10];
	_itow_s(grassNum-grassNumRec, grassNumText, 10);
	outtextxy(1110, 236, grassNumText);
}



void textRich()//富饶度文本
{
	if (float(grassNum-grassNumRec) / float(fishNum-fishNumRec+1) >= 5 || float(grassNum-grassNumRec) / float(fishNum-fishNumRec+1) <= 0.2)
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
	for (int i = 0;i < grassNum + 1;i++)
	{
		transparentimage(NULL, pGrass[i].x, pGrass[i].y, &grass, 0xffc4c4);
	}
}



void drawFishOther()//画其他鱼
{
	for (int i = 0;i < fishNum;i++)
	{
		transparentimage(NULL, pFishOther[i].x, pFishOther[i].y, &fishOther[pFishOther[i].fishOtherStyle], 0xffc4c4);
	}
}



void move()//移动鱼
{
	for (int i = 0;i < fishNum + 1;i++)
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
	for (int i = 0;i < fishNum;i++)
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
	for (int i = 0;i < grassNum;i++)
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
		for (int j = 0;j < fishNum;j++)
		{
			if (pFishOther[j].x>= pGrass[i].x - 120 && pFishOther[j].x<= pGrass[i].x + 65 && pFishOther[j].y >= pGrass[i].y - 120 && pFishOther[j].y <= pGrass[i].y + 80)
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
	if (float(grassNum - grassNumRec) / float(fishNum - fishNumRec+1) >= 5 || float(grassNum - grassNumRec) / float(fishNum - fishNumRec+1) <= 0.2)
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