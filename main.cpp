#include <iostream>
#include <math.h>

#include "Brain.h"

diff loss = 0;


//学习次数
long int epochs = 100;
//学习率
diff rate = 0.001;

diff indexKey=50;

//初始化目标值
void initT();

//输入一个单词，返回一个数字,n表示第n个输出
diff layerOneModel(const char word[5],int n);
diff getIndex(const char word[5]);
diff sigmoid(diff x);
void updateK(diff y, int n);
//n表示更新第n个单词
void updateW(diff y,int n,const char word[5]);
void updateB(diff y,int n);
void test(int n);

void displayW();
void displayB();
void displayK();

int main(int argc,char * argv[]) {
	
	initT();
	
	//进行学习
	for (long int epoch = 0; epoch < epochs;epoch++)
	{
		//学习第i个单词
		for (int i = 0; i < WORDSCOUNT;i++) {
			//首先将单词给神经元,第一层开始工作
			
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

		//每10显示当前学习的进程
			//cout<<"学习次数 = "<< epoch+1<< " loss = "<< loss << endl;
		printf("\n学习次数 = %d,loss = %f\n", epoch + 1, loss);
		displayW();
		displayB();
		displayK();

	}

	

	

	

	cout << endl << "标签" << endl;
	for (int i = 0; i < WORDSCOUNT; i++)
	{
		cout <<englishTrain[i]<<" : " << t[i] << endl;
	}

	//应用测试
	while (1) {
		//cout << endl << "输入单词序号:"<<endl;
		//int i;
		//cin >> i;
		//test(i);
		cout <<endl<< "输入一个4字单词:" << endl;
		char s[5];
		cin>>s;
		diff index=getIndex(s);
		cout <<"输出index："<<index << " 识别到：" << chinese[(int)(indexKey * index)];
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
	//第二层输出
	for (int i = 0; i < BRAINCOUNT;i++) {
		y += k[i] * g[i];
	}
	y += b[BRAINCOUNT];
	return y;
}

diff layerOneModel(const char word[5], int n)
{

	//第一层的学习模型

	diff y = 0;
	//对输入的值进行一个归一化操作
	diff x[5];
	diff sum = word[0] + word[1] + word[2] + word[3] + word[4];
	for (int i = 0; i < 5; i++) {
		x[i] = word[i] / sum;
	}

	//开始学习
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
	//n表示第n个标签

	diff grad = 2 * (y - t[n]);
	//对输入特征进行归一化操作
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
	//学习第n个单词
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
		cout << "输入数值非法" << endl;
		return;
	}

	//输入一个n，就返回中文意思
	
	cout << "应用测试" << endl;
	cout << "真实值："<< t[n]<<" , 模型预测值： "<< getIndex(englishTrain[n]) << endl;
	printf("单词 = %s, ", englishTrain[n]);
	cout << "中文 = " << chinese[(int)round(indexKey * getIndex(englishTrain[n]))];
}

void displayW()
{
	//显示w
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
