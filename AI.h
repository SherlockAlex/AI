#ifndef AI_AI_H
#define AI_AI_H

/*
*这个为底本模块，将不会在引用其他的头函数
*/

#include <iostream>

using namespace std;

//学习次数
extern int learnCount;

//激活函数
extern double ReLU(double x);

//初始化
extern void start();

//学习
extern void learnLoop();

#endif // !AI_AI_H

