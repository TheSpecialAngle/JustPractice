#include <iostream>
using namespace std;

//首先用一个容易理解的字符串对该变量赋值，游戏开始后再将其转化为其他形式。
//字符串换行现实时 ： '\'

//可以用另一个数据文件来描述，并在程序中读取。
const char gStageData[] = "\
########\n\
# ..   #\n\
# oo   #\n\
# p    #\n\
########";

const int gStageWidth = 8;
const int gStageHeight = 5;

enum Object {
	GOAL,
	WALL,
	SPACE,
	MAN,
	MAN_ON_GOAL,
	BOX,
	BOX_ON_GOAL,

	UNKNOWN,
};


void initialize(Object* state, int w, int h, const char* stageData) {
	const char* d = stageData;
	int x = 0;
	int y = 0;
	while (*d != '\0') {
		Object t;
		switch (*d) {
		case '#': t = WALL; break;
		case ' ': t = SPACE; break;
		case 'p': t = MAN; break;
		case 'P': t = MAN_ON_GOAL; break;
		case 'o': t = BOX; break;
		case 'O': t = BOX_ON_GOAL; break;
		case '\n': 
			//如果换行了，x要归零，y加一
			x = 0;
			++y;
			//注意此时也要对t进行赋值
			t = UNKNOWN;
			break;
		default: t = UNKNOWN; break;
		}
		//移动指针位置并将读取的数据写入
		++d;
		if (t != UNKNOWN) {
			state[y * w + x] = t;
			//注意修改x 的位置
			++x;
		}
	}
}

void draw(const Object* state, int w, int h) {
	const char font[] = { ' ', '#', 'p', 'P', 'o', 'O' };
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			Object o = state[y * w + x];
			cout << font[o];
		}
		cout << endl;
	}
}

void update(Object* s, int w, int h, char input) {

	//声明移动量
	int dx = 0;
	int dy = 0;

	switch (input) {
	case 'a':dx = 1; break;
	case 'd':dx = -1; break;
	case 'w':dy = 1; break;
	case 's':dy = -1; break;
	};

//初始化坐标位置
	int i = -1;

	//计算当前坐标
	for (i = 0; i < w * h; ++i) {
		if (s[i] == MAN || s[i] == MAN_ON_GOAL) {
			break;
		}
	}
	int x = i % w;
	int y = i / w;

	//进行两次条件判断，先是判断位移后是否合法，再根据具体情况判断如何位移
	int tx = x + dx;
	int ty = y + dy;
	//是否合法
	if(tx<0||ty<0||)


}