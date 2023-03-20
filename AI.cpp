#include "AI.h"

int learnCount = 10;//学习十次

double xData[10] = {0.1,0.2,0.3,0.1,0.5,0.0,0.7,0.8,0.9};
double yData[1] = {0.5};

//训练模型,dim(x)=dim(w),dim(b)=神经元个数
double model(double * x,double * w,double b);

double loss(double y,double t);

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

double model(double* x, double* w, double b)
{
	//z=wx+b
	float z=0;

	for (int i = 0; i < 10; i++) {
		z += x[i] * w[i];
	}
	z += b;
	return z;
}

double loss(double y, double t)
{
	return 0.0;
}
