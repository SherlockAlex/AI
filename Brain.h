#ifndef AI_BRAIN_H
#define AI_BRAIN_H

#include <iostream>
using namespace std;

#define WORDSCOUNT 12
#define BRAINCOUNT 30	//隐含层神经元个数

typedef long double diff;

extern const char englishTrain[WORDSCOUNT][5];
extern const string chinese[WORDSCOUNT];

extern diff t[WORDSCOUNT];
extern diff w[BRAINCOUNT][5];
extern diff b[BRAINCOUNT + 1];
extern diff g[BRAINCOUNT];
extern diff k[BRAINCOUNT];

#endif
