#include "AI.h"

int learnCount = 1000;//学习次数

double w[2] = { 0.3, 0.4 };
double xData[2] = { 0.2,0.4 };
double t[1] = { 0.5 };
double b = 0.45;

static int step=0;

void grad(double y);//计算梯度

void start()
{
	//初始化
}

void learnLoop()
{
	//学习
	step++;

	double z = w[0] * xData[0] + w[1] * xData[1] + b;
	double y = ReLU(z);
	grad(y);
	if (step%20!=0) {
		//每50次输出一次
		return;
	}
	cout <<"学习次数:" << step << endl;
	cout << "训练模型:"<<"y=("<<w[0]<<"X1)+("<<w[1]<<"X2)+"<<b << endl;
	cout << "loss=" << 0.5 * (y - t[0]) * (y - t[0]) << endl;
	cout <<"测试输出y="<< y << endl<<endl;
}

double ReLU(double x)
{
	if (x <= 0) {
		return 0.0;
	}
	return x;
}

void grad(double y)
{
	b = b - 0.01 * (y - t[0]);
	w[0] = w[0] - 0.01 * (y - t[0]) * xData[0];
	w[1] = w[1] - 0.01 * (y - t[1]) * xData[1];
}
