#include "AI.h"

int learnCount = 10;//学习十次

double xData[10] = {0.1,0.2,0.3,0.1,0.5,0.0,0.7,0.8,0.9};
double yData[10];



void start()
{
	//初始化
}

void learnLoop()
{
	//学习
}

double ReLU(double x)
{
	if (x <= 0) {
		return 0.0;
	}
	return x;
}