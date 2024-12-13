#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "17-compareAVL.h"

main(int argc, char* argv[]) {
	Node* root = NULL;
	srand(time(NULL));
	float allCount = 0.0;

	doAVLBatch(root);
	allCount = (float)compareCount / searchCount;
	printf("average AVL compare count: %.2f\n", allCount);

	freeTree(root);
	root = NULL;
	compareCount = 0;
	allCount = 0;

	doBinaryBatch(root);
	allCount = (float)compareCount / searchCount;
	printf("average Bin compare count: %.2f\n", allCount);

	freeTree(root);
	return 0;
}