#include <iostream>
#include <math.h>

#define WORDSCOUNT 6

using namespace std;

//ѧϰ����
	//[���ʸ���][���ʳ���]
const char englishTrain[WORDSCOUNT][5] = {
	"best",
	"I",
	"you",
	"need",
	"test",
	"nice"
};

//��ǩ��
double t[WORDSCOUNT];

double w[5] = { 0.1,0.2,0.5,0.6,0.2 };
double b = 0.2;
double loss = 0;

//Ŀ��ֵ
const string chinese[WORDSCOUNT] = {
	"�õ�",
	"��",
	"��",
	"��Ҫ",
	"����",
	"Ư��"
};

//ѧϰ����
int epochs = 50;
//ѧϰ��
double rate = 0.001;

//��ʼ��Ŀ��ֵ
void initT();

//����һ�����ʣ�����һ������
double model(const char word[5]);

//n��ʾ���µ�n������
void updateW(double y,int n,const char word[5]);
void updateB(double y,int n);

void test(int n);

int main(int argc,char * argv[]) {
	
	initT();
	
	//����ѧϰ
	for (int epoch = 0; epoch < epochs;epoch++)
	{
		//ѧϰ��i������
		for (int i = 0; i < WORDSCOUNT;i++) {
			//���Ƚ����ʸ���Ԫ
			double y = model(englishTrain[i]);

			//�����ݶ��½������и���Ȩ��
			updateW(y, i, englishTrain[i]);
			updateB(y,i);
			loss = (y - t[i]) * (y - t[i]);
		}

		if ((epoch+1)%10==0) {
			//ÿ10��ʾ��ǰѧϰ�Ľ���
			//cout<<"ѧϰ���� = "<< epoch+1<< " loss = "<< loss << endl;
			printf("ѧϰ���� = %d,loss = %f\n", epoch + 1, loss);
		}

	}


	//Ӧ�ò���
	while (1) {
		cout << endl << "���뵥�����:"<<endl;
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
	//ѧϰ��n������
	double grad = 2 * (y - t[n]);
	b = b - rate * grad;
}

void test(int n)
{

	if (n>=WORDSCOUNT) {
		cout << "������ֵ�Ƿ�" << endl;
		return;
	}

	//����һ��n���ͷ���������˼
	cout << "Ӧ�ò���" << endl;

	printf("���� = %s, ", englishTrain[n]);
	cout << "���� = " << chinese[(int)round(10.0 * model(englishTrain[n]))];
}
