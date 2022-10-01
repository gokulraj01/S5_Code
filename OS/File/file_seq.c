#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define LINE_LEN 10

void main(){
    int memSize, blkSize, fileSize;
	printf("Total Mem Size: ");
    scanf("%d", &memSize);
	printf("Block Size: ");
    scanf("%d", &blkSize);
	printf("File Size: ");
    scanf("%d", &fileSize);

    int blks = ceil(memSize/blkSize);
    char *allocList = malloc(blks);
	int i = 0;
	while(i < blks)
		allocList[i++] = 0;
	int file_blk = ceil(fileSize/blkSize);
	
	int n = 0; i = 0;
	while(n < file_blk && i < blks){
		if(allocList[i] == 0){
			allocList[i] = 1;
			n++; i++;
		}
	}

	if(n < file_blk-1)
		printf("Cannot allocate!!\n");
	else
		printf("Allocation complete!!\n");
	
	printf("\n%d blocks, %db each. Size: %db\n", blks, blkSize, blks*blkSize);
	printf("\nAllocations");
	for(i=0; i<blks; i++){
	    if(i%LINE_LEN == 0)
	        putchar('\n');
	    if(allocList[i])
		    printf("X ");
	    else
		    printf(". ");
	}
	putchar('\n');
}
