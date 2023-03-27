#include <iostream>
#include <math.h>

#define WORDSCOUNT 6

using namespace std;

//学习数据
	//[单词个数][单词长度]
const char englishTrain[WORDSCOUNT][5] = {
	"best",
	"I",
	"you",
	"need",
	"test",
	"nice"
};

//标签集
double t[WORDSCOUNT];

double w[5] = { 0.1,0.2,0.5,0.6,0.2 };
double b = 0.2;
double loss = 0;

//目标值
const string chinese[WORDSCOUNT] = {
	"好的",
	"我",
	"你",
	"需要",
	"测试",
	"漂亮"
};

//学习次数
int epochs = 50;
//学习率
double rate = 0.001;

//初始化目标值
void initT();

//输入一个单词，返回一个数字
double model(const char word[5]);

//n表示更新第n个单词
void updateW(double y,int n,const char word[5]);
void updateB(double y,int n);

void test(int n);

int main(int argc,char * argv[]) {
	
	initT();
	
	//进行学习
	for (int epoch = 0; epoch < epochs;epoch++)
	{
		//学习第i个单词
		for (int i = 0; i < WORDSCOUNT;i++) {
			//首先将单词给神经元
			double y = model(englishTrain[i]);

			//根据梯度下降法进行更新权重
			updateW(y, i, englishTrain[i]);
			updateB(y,i);
			loss = (y - t[i]) * (y - t[i]);
		}

		if ((epoch+1)%10==0) {
			//每10显示当前学习的进程
			//cout<<"学习次数 = "<< epoch+1<< " loss = "<< loss << endl;
			printf("学习次数 = %d,loss = %f\n", epoch + 1, loss);
		}

	}


	//应用测试
	while (1) {
		cout << endl << "输入单词序号:"<<endl;
		int i;
		cin >> i;
		test(i);
	}
	
	

	return 0;
}

void initT()
{
	double sum = (0 + WORDSCOUNT - 1) * WORDSCOUNT * 0.5;
	for (int i = 0; i < WORDSCOUNT;i++) {
		t[i] = (i/sum);
	}
}

double model(const char word[5])
{
	double y = 0;

	double x[5];

	double sum = word[0] + word[1] + word[2] + word[3] + word[4];

	for (int i = 0; i < 5; i++) {
		x[i] = word[i] / sum;
	}

	for (int i = 0; i < 5;i++) {
		y += w[i] * x[i];
	}
	y += b;
	return y;
}

void updateW(double y,int n, const char word[5])
{
	double grad = 2 * (y - t[n]);

	double x[5];

	double sum = word[0] + word[1] + word[2] + word[3] + word[4];

	for (int i = 0; i < 5; i++) {
		x[i] = word[i] / sum;
	}

	for (int i = 0; i < 5;i++) {
		w[i] = w[i] - rate* grad * x[i];
	}
}

void updateB(double y,int n)
{
	//学习第n个单词
	double grad = 2 * (y - t[n]);
	b = b - rate * grad;
}

void test(int n)
{

	if (n>=WORDSCOUNT) {
		cout << "输入数值非法" << endl;
		return;
	}

	//输入一个n，就返回中文意思
	cout << "应用测试" << endl;

	printf("单词 = %s, ", englishTrain[n]);
	cout << "中文 = " << chinese[(int)round(10.0 * model(englishTrain[n]))];
}
