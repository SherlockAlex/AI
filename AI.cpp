#include "AI.h"

int learnCount = 10;//ѧϰʮ��

double w[2] = { 0.3, 0.4 };
double xData[2] = { 0.2,0.4 };
double t[1] = { 0.5 };
double b = 0.45;

void grad(double y);//�����ݶ�

void start()
{
	//��ʼ��
}

void learnLoop()
{
	//ѧϰ
	double z = w[0] * xData[0] + w[1] * xData[1] + b;
	double y = ReLU(z);


}

double ReLU(double x)
{
	if (x <= 0) {
		return 0.0;
	}
	return x;
}

void grad(double z,double y)
{
	b = b - 0.01 * (y - t[0]);
	w[0] = w[0] - 0.01 * (y - t[0]) * xData[0];
	w[1] = w[1] - 0.01 * (y - t[1]) * xData[1];
}
