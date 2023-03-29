#include <iostream>
#include <math.h>

#include "Brain.h"

diff loss = 0;


//ѧϰ����
long int epochs = 100;
//ѧϰ��
diff rate = 0.001;

diff indexKey=50;

//��ʼ��Ŀ��ֵ
void initT();

//����һ�����ʣ�����һ������,n��ʾ��n�����
diff layerOneModel(const char word[5],int n);
diff getIndex(const char word[5]);
diff sigmoid(diff x);
void updateK(diff y, int n);
//n��ʾ���µ�n������
void updateW(diff y,int n,const char word[5]);
void updateB(diff y,int n);
void test(int n);

void displayW();
void displayB();
void displayK();

int main(int argc,char * argv[]) {
	
	initT();
	
	//����ѧϰ
	for (long int epoch = 0; epoch < epochs;epoch++)
	{
		//ѧϰ��i������
		for (int i = 0; i < WORDSCOUNT;i++) {
			//���Ƚ����ʸ���Ԫ,��һ�㿪ʼ����
			
			diff y = getIndex(englishTrain[i]);
			//cout << y<<endl;
			updateK(y, i);
			updateB(y, i);
			updateW(y, i, englishTrain[i]);
			loss = (y - t[i]) * (y - t[i]);

		}

		if ((epoch+1)%100000!=0)
		{
			continue;
		}

		//ÿ10��ʾ��ǰѧϰ�Ľ���
			//cout<<"ѧϰ���� = "<< epoch+1<< " loss = "<< loss << endl;
		printf("\nѧϰ���� = %d,loss = %f\n", epoch + 1, loss);
		displayW();
		displayB();
		displayK();

	}

	

	

	

	cout << endl << "��ǩ" << endl;
	for (int i = 0; i < WORDSCOUNT; i++)
	{
		cout <<englishTrain[i]<<" : " << t[i] << endl;
	}

	//Ӧ�ò���
	while (1) {
		//cout << endl << "���뵥�����:"<<endl;
		//int i;
		//cin >> i;
		//test(i);
		cout <<endl<< "����һ��4�ֵ���:" << endl;
		char s[5];
		cin>>s;
		diff index=getIndex(s);
		cout <<"���index��"<<index << " ʶ�𵽣�" << chinese[(int)(indexKey * index)];
	}
	
	

	return 0;
}

void initT()
{
	//
	//indexKey = (0 + WORDSCOUNT - 1) * WORDSCOUNT * 0.5;
	indexKey = 100;
	for (int i = 0; i < WORDSCOUNT;i++) {
		t[i] = (i/indexKey);
	}
}

diff getIndex(const char word[5]) {
	for (int i = 0; i < BRAINCOUNT; i++) {
		diff z = layerOneModel(word, i);
		g[i] = sigmoid(z);
	}
	diff y = 0;
	//�ڶ������
	for (int i = 0; i < BRAINCOUNT;i++) {
		y += k[i] * g[i];
	}
	y += b[BRAINCOUNT];
	return y;
}

diff layerOneModel(const char word[5], int n)
{

	//��һ���ѧϰģ��

	diff y = 0;
	//�������ֵ����һ����һ������
	diff x[5];
	diff sum = word[0] + word[1] + word[2] + word[3] + word[4];
	for (int i = 0; i < 5; i++) {
		x[i] = word[i] / sum;
	}

	//��ʼѧϰ
	for (int i = 0; i < 5;i++) {
		y += w[n][i] * x[i];
	}
	y += b[n];
	return y;
}

diff sigmoid(diff x)
{
	diff z = 1 / (1 + exp2l(-x));
	return z;
}

void updateK(diff y,int n) {
	diff grad = 2 * (y - t[n]);
	for (int i = 0; i < BRAINCOUNT;i++) {
		k[i] = k[i] - rate * grad * g[i];
	}
}

void updateW(diff y,int n, const char word[5])
{
	//n��ʾ��n����ǩ

	diff grad = 2 * (y - t[n]);
	//�������������й�һ������
	diff x[5];
	diff sum = word[0] + word[1] + word[2] + word[3] + word[4];
	for (int i = 0; i < 5; i++) {
		x[i] = word[i] / sum;
	}

	for (int i = 0; i < BRAINCOUNT; i++) {
		for (int j = 0; j < 5; j++) {
			//w[i][j] = w[i][j] - rate * grad* k[i] * x[j];
			w[i][j] = w[i][j] - rate * grad*g[i]*(1-g[i]) * k[i] * x[j];
		}
	}
	
}

void updateB(diff y,int n)
{
	//ѧϰ��n������
	diff grad = 2 * (y - t[n]);
	
	for (int i = 0; i < BRAINCOUNT;i++) {
		b[i] = b[i] - rate * grad * g[i] * (1 - g[i]) * k[i];
		//b[i] = b[i] - rate * grad * k[i];
	}
	b[BRAINCOUNT] = b[BRAINCOUNT] - rate * grad;
}

void test(int n)
{

	if (n<0||n>=WORDSCOUNT) {
		cout << "������ֵ�Ƿ�" << endl;
		return;
	}

	//����һ��n���ͷ���������˼
	
	cout << "Ӧ�ò���" << endl;
	cout << "��ʵֵ��"<< t[n]<<" , ģ��Ԥ��ֵ�� "<< getIndex(englishTrain[n]) << endl;
	printf("���� = %s, ", englishTrain[n]);
	cout << "���� = " << chinese[(int)round(indexKey * getIndex(englishTrain[n]))];
}

void displayW()
{
	//��ʾw
	cout << "W" << endl;

	for (int i = 0; i < BRAINCOUNT; i++) {
		for (int j = 0; j < 5; j++) {
			cout << w[i][j] << ", ";
		}
		cout << endl;
	}
}

void displayB()
{
	cout << endl << "B" << endl;
	for (int i = 0; i < BRAINCOUNT + 1; i++) {
		cout << b[i] << ", ";
		if ((i + 1) % 5 == 0) {
			cout << endl;
		}
	}
}

void displayK()
{
	cout << endl << "K" << endl;
	for (int i = 0; i < BRAINCOUNT; i++) {
		cout << k[i] << ", ";
		if ((i + 1) % 5 == 0) {
			cout << endl;
		}
	}
}
