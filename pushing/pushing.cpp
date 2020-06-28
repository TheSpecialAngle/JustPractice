// pushing.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;

//首先用一个容易理解的字符串对该变量赋值，游戏开始后再将其转化为其他形式。
//字符串换行现实时 ： '\'

const char gStageData[] = "\
########\n\
# .. p #\n\
# oo   #\n\
#      #\n\
########";

const int gStageWidth = 8;
const int gStageHeight = 5;

//场景中的所有状态都被保存在容量等于 宽*高 的枚举类型数组中。
//直接使用数组的话，可能因为疏忽代入无意义的值，枚举类型不会出现这种问题，且在调试的时候可以看见枚举类型的名字
//是否在GOAL的BLOCK也可以用位运算来表示


enum Object {
	OBJ_SPACE,
	OBJ_WALL,
	OBJ_GOAL,
	OBJ_BLOCK,
	OBJ_BLOCK_ON_GOAL,
	OBJ_MAN,
	OBJ_MAN_ON_GOAL,

	OBJ_UNKNOWN,
};

void initialize(Object* state, int w, int h, const char* stageData) {
	const char* d = stageData; //读取指针
	int x = 0;
	int y = 0;
	while (*d != '\0') {
		//当字符不为NULL时
		Object t;
		switch(*d) {
		case '#':t = OBJ_WALL; break;
		case ' ':t = OBJ_SPACE; break;
		case 'o':t = OBJ_BLOCK; break;
		case 'O':t = OBJ_BLOCK_ON_GOAL; break;
		case '.':t = OBJ_GOAL; break;
		case 'p': t = OBJ_MAN; break;
		case 'P':t = OBJ_MAN_ON_GOAL; break;
		case '\n': //转到下一行
			x = 0;
			++y;
			t = OBJ_UNKNOWN;
			break;
		default: t = OBJ_UNKNOWN; break;

		}

		++d;
		//如果遇到未知字符，无视
		if (t != OBJ_UNKNOWN) {
			state[y * w + x] = t; //写入
			++x;
		}
	}
}

void draw(const Object* state, int w, int h) {
	//Object枚举类型的顺序
	const char font[] = { ' ', '#', '.', 'o','O','p','P' };
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			Object o = state[y * w + x];
			cout << font[o];
		}
		cout << endl;
	}
}

void update(Object* s, char input, int w, int h) {

	//第一个参数在其他函数中是state的形式，但由于在本函数中使用频率非常高，所以使用简短的s来表示。

	//移动量
	int dx = 0;
	int dy = 0;

	switch(input) {
		case 'a':dx = -1; break;
		case 's': dy = -1; break;
		case'w': dy = 1; break;
		case 'd': dx = 1; break;
	}

	//查找玩家的坐标——查找对应数据并通关运算得到其位置。

	int i = -1; //无具体意义，只是初始化

	//也可以直接维护一个变量来跟踪玩家位置，但那样太麻烦
	for (i = 0; i < w * h; ++i) {
		//两种情况，最好封装成isPlayer这样的函数。
		if (s[i] == OBJ_MAN || s[i] == OBJ_MAN_ON_GOAL) {
			break;
		}
	}
	int x = i % w;
	int y = i / w;


	//移动后的坐标是否在允许范围内
	int tx = x + dx;
	int ty = y + dy;
	//检查坐标的最大值和最小值，超出范围则不允许
	if (tx < 0 || ty < 0 || tx >= w || ty >= h) {
		return;
	}

	//A 要移动到的位置是空白或者目的地，玩家移动
	int p = y * w + x;	//玩家位置
	int tp = ty * w + tx;	//目标位置
	if (s[tp] == OBJ_SPACE || s[tp] == OBJ_GOAL) {
		//如果是目的地，则将该处设置为“OBJ_MAN_ON_GOAL
		s[tp] = (s[tp] == OBJ_GOAL) ? OBJ_MAN_ON_GOAL : OBJ_MAN;
		//如果已经在目的地了，则将玩家所在的位置设置为目的地
		s[p] = (s[p] == OBJ_MAN_ON_GOAL) ? OBJ_GOAL : OBJ_SPACE;
		//B. 要移动到的位置有箱子。如果沿该方向的下一个网格是空白或者目的地，则移动
	}
	else if (s[tp] == OBJ_BLOCK || s[tp] == OBJ_BLOCK_ON_GOAL) {
		//检测沿该方向的第二个网格的位置是否在允许范围内
		int tx2 = tx + dx;
		int ty2 = ty + dy;
		if (tx2 < 0 || ty2 < 0 || tx2 >= w || ty2 >= h) {
			return;
		}
		//沿该方向的第二个网格的位置
		int tp2 = (ty + dy) * w + (tx + dx);
		if (s[tp2]==)
	}

}

void checkClear(const Object* state, int w, int h);



int main()
{
	//创建状态数组
	//逻辑上是二维数组，但是二维数组无法通过new动态创建，而如果写死则会让程序丧失灵活性
	Object* state = new Object[gStageWidth * gStageHeight];
	initialize(state, gStageWidth, gStageHeight, gStageData);
	//主循环
	while (true) {
		//没有输入也要绘制
		draw(state, gStageWidth, gStageHeight);
		//通关检测
		if (checkClear(state, gStageWidth, gStageHeight)) {
			break;
		}
		//获取输入
		cout << "a:left d:right w:up s:down. Command?" << endl;
		char input;
		cin >> input;
		//更新
		update(state, input, gStageWidth, gStageHeight);
	}
	//胜利时候的提示
	cout << "Congratulation's: you win." << endl;
	//通关
	delete[] state; //通过new创建的数组不能使用delete，而是delete[]
	state = 0;

	return 0;
}
