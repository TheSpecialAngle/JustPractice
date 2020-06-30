#include <iostream>
using namespace std;

//������һ�����������ַ����Ըñ�����ֵ����Ϸ��ʼ���ٽ���ת��Ϊ������ʽ��
//�ַ���������ʵʱ �� '\'

//��������һ�������ļ������������ڳ����ж�ȡ��
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
			//��������ˣ�xҪ���㣬y��һ
			x = 0;
			++y;
			//ע���ʱҲҪ��t���и�ֵ
			t = UNKNOWN;
			break;
		default: t = UNKNOWN; break;
		}
		//�ƶ�ָ��λ�ò�����ȡ������д��
		++d;
		if (t != UNKNOWN) {
			state[y * w + x] = t;
			//ע���޸�x ��λ��
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

	//�����ƶ���
	int dx = 0;
	int dy = 0;

	switch (input) {
	case 'a':dx = 1; break;
	case 'd':dx = -1; break;
	case 'w':dy = 1; break;
	case 's':dy = -1; break;
	};

//��ʼ������λ��
	int i = -1;

	//���㵱ǰ����
	for (i = 0; i < w * h; ++i) {
		if (s[i] == MAN || s[i] == MAN_ON_GOAL) {
			break;
		}
	}
	int x = i % w;
	int y = i / w;

	//�������������жϣ������ж�λ�ƺ��Ƿ�Ϸ����ٸ��ݾ�������ж����λ��
	int tx = x + dx;
	int ty = y + dy;
	//�Ƿ�Ϸ�
	if(tx<0||ty<0||)


}