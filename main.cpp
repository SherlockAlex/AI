#include "AI.h"

int main(int argc,char * argv[]) {
	start();

	for (int i = 0; i < learnCount;i++) {
		learnLoop();
	}
	

	return 0;
}