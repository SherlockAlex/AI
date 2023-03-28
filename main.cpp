#include <iostream>
#include <math.h>

#define WORDSCOUNT 12

using namespace std;

typedef long double diff;

//ѧϰ����
	//[���ʸ���][���ʳ���]
const char englishTrain[WORDSCOUNT][5] = {
	"best",
	"I",
	"you",
	"need",
	"test",
	"nice",
	"evil",
	"mood",
	"view",
	"easy",
	"mix",
	"holy"
};

//Ŀ��ֵ
const string chinese[WORDSCOUNT] = {
	"�õ�",
	"��",
	"��",
	"��Ҫ",
	"����",
	"Ư��",
	"а���",
	"����",
	"�羰",
	"��",
	"���",
	"��ʥ��"

};

//��ǩ��
diff t[WORDSCOUNT];

diff w[2][5] = {
	{ 0.01,0.02,0.05,0.06,0.02 },
	{ 0.01,0.02,0.05,0.06,0.02 }
};
diff b[3] = {0.2,0.3,0.4};
diff g[2];
diff k[2] = {0.03,0.05};

diff loss = 0;



//ѧϰ����
long int epochs = 60000000;
//ѧϰ��
diff rate = 0.001;

diff indexKey=0;

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

int main(int argc,char * argv[]) {
	
	initT();
	
	//����ѧϰ
	for (long int epoch = 0; epoch < epochs;epoch++)
	{
		//ѧϰ��i������
		for (int i = 0; i < WORDSCOUNT;i++) {
			//���Ƚ����ʸ���Ԫ,��һ�㿪ʼ����
			
			diff y = getIndex(englishTrain[i]);

			//double y = sigmoid(z1);
			//printf("���� = %s, ѵ����� = ", englishTrain[i]);
			//cout << y <<"���� = " << chinese[(int)round(indexKey * y)] << endl;
			//�����ݶ��½������и���Ȩ��
			updateK(y, i);
			updateB(y, i);
			updateW(y, i, englishTrain[i]);
			loss = (y - t[i]) * (y - t[i]);
		}

		if ((epoch+1)%20==0) {
			//ÿ10��ʾ��ǰѧϰ�Ľ���
			//cout<<"ѧϰ���� = "<< epoch+1<< " loss = "<< loss << endl;
			printf("ѧϰ���� = %d,loss = %f\n", epoch + 1, loss);
		}

	}

	//��ʾw
	cout << "W" << endl;

	for (int i = 0; i < 2;i++) {
		for (int j = 0; j < 5;j++) {
			cout << w[i][j] << " ";
		}
		cout << endl;
	}

	cout << "B" << endl;
	for (int i = 0; i < 3;i++) {
		cout << b[i] << " ";
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
	indexKey = (0 + WORDSCOUNT - 1) * WORDSCOUNT * 0.5;
	for (int i = 0; i < WORDSCOUNT;i++) {
		t[i] = (i/indexKey);
	}
}

diff getIndex(const char word[5]) {
	diff z1 = layerOneModel(word, 0);
	diff z2 = layerOneModel(word, 1);
	g[0] = sigmoid(z1);
	g[1] = sigmoid(z2);
	//g[0] = (z1);
	//g[1] = (z2);
	//cout <<endl<< "g1 = " << g[0] << endl;
	//cout << "g2 = " << g[1] << endl;

	//�ڶ������
	diff y = k[0] * g[0] + k[1] * g[1] + b[2];
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
	for (int i = 0; i < 2;i++) {
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

	for (int i = 0; i < 2; i++) {
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
	
	for (int i = 0; i < 2;i++) {
		b[i] = b[i] - rate * grad * g[i] * (1 - g[i]) * k[i];
		//b[i] = b[i] - rate * grad * k[i];
	}
	b[2] = b[2] - rate * grad;
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
	cout << "���� = " << chinese[(int)(indexKey * getIndex(englishTrain[n]))];
}
