#include "AI.h"

int learnCount = 10;//ѧϰʮ��

double xData[10] = {0.1,0.2,0.3,0.1,0.5,0.0,0.7,0.8,0.9};
double yData[1] = {0.5};

//ѵ��ģ��,dim(x)=dim(w),dim(b)=��Ԫ����
double model(double * x,double * w,double b);

double loss(double y,double t);

void start()
{
	//��ʼ��
}

void learnLoop()
{
	//ѧϰ
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
