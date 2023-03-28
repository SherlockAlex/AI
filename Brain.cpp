#include "Brain.h"

//学习数据
	//[单词个数][单词长度]
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

//目标值
const string chinese[WORDSCOUNT] = {
	"好的",
	"我",
	"你",
	"需要",
	"测试",
	"漂亮",
	"邪恶的",
	"月亮",
	"风景",
	"简单",
	"混合",
	"神圣的"

};

diff t[WORDSCOUNT];

diff w[BRAINCOUNT][5] = {
	-1.21396, -0.0216232, 3.6699, -2.29456, 0.02,
	6.13914, -3.94363, -5.2897, 7.44959, 0.02,
	-0.618191, 0.169657, 0.253939, 1.69145, 0.02,
	-0.0953468, 0.268681, 0.584975, 0.704566, 0.02,
	-0.944404, -0.354805, 0.863293, 1.84206, 0.02,
	-0.944404, -0.354805, 0.863293, 1.84206, 0.02,
	-0.944404, -0.354805, 0.863293, 1.84206, 0.02,
	-0.944404, -0.354805, 0.863293, 1.84206, 0.02,
	-0.944404, -0.354805, 0.863293, 1.84206, 0.02,
	-0.944404, -0.354805, 0.863293, 1.84206, 0.02,
	-0.944404, -0.354805, 0.863293, 1.84206, 0.02,
	-0.944404, -0.354805, 0.863293, 1.84206, 0.02,
	-0.944404, -0.354805, 0.863293, 1.84206, 0.02,
	-0.944404, -0.354805, 0.863293, 1.84206, 0.02,
	-0.944404, -0.354805, 0.863293, 1.84206, 0.02,
	-0.944404, -0.354805, 0.863293, 1.84206, 0.02,
	-0.944404, -0.354805, 0.863293, 1.84206, 0.02,
	-0.944404, -0.354805, 0.863293, 1.84206, 0.02,
	-0.944404, -0.354805, 0.863293, 1.84206, 0.02,
	-0.944404, -0.354805, 0.863293, 1.84206, 0.02,
	-0.944404, -0.354805, 0.863293, 1.84206, 0.02,
	-0.944404, -0.354805, 0.863293, 1.84206, 0.02,
	-0.944404, -0.354805, 0.863293, 1.84206, 0.02,
	-0.944404, -0.354805, 0.863293, 1.84206, 0.02,
	-0.944404, -0.354805, 0.863293, 1.84206, 0.02,
	-0.944404, -0.354805, 0.863293, 1.84206, 0.02,
};
diff b[BRAINCOUNT + 1] = {
	0.199738, 4.41538, 1.65687, 1.6945, 3.49838,
	3.49838, 3.49838, 3.49838, 3.49838, 3.49838,
	3.49838, 3.49838, 3.49838, 3.49838, 3.49838,
	3.49838, 3.49838, 3.49838, 3.49838, 3.49838,
	3.49838, 3.49838, 3.49838, 3.49838, 3.49838,
	3.49838, 2.31661,
};

diff g[BRAINCOUNT];
diff k[BRAINCOUNT] = {
	-3.22879, -8.63857, -2.30567, 0.232925, 0.466697,
	0.466697, 0.466697, 0.466697, 0.466697, 0.466697,
	0.466697, 0.466697, 0.466697, 0.466697, 0.466697,
	0.466697, 0.466697, 0.466697, 0.466697, 0.466697,
	0.466697, 0.466697, 0.466697, 0.466697, 0.466697,
	0.466697,
};