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

void initialize(Object* state, int w, int h, const char* stageData);
void draw(const Object* state, int w, int h);
void update(Object* state, char input, int w, int h);
void checkClear(const Object* state, int w, int h);



int main()
{
	//创建状态数组
	//逻辑上是二维数组，但是二维数组无法通过new动态创建，而如果写死则会让程序丧失灵活性
	Object* state = new Object[gStageWidth * gStageHeight];
	initialize(state, gStageWidth, gStageHeight, gStageData);
	//主循环

	//胜利时候的提示
	cout << "Congratulation's: you win." << endl;
	//通关
	delete[] state; //通过new创建的数组不能使用delete，而是delete[]
	state = 0;

	return 0;
}
