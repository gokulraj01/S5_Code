// Author: Gokul Raj, 235, R5A
// File Allocation: Linked

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define LINE_LEN 10

struct Block{
    char allocated;
    struct Block *next;
};

// Make a random int from min to max-1
int randint(int min, int max){
    int r = rand();
    return r%(max-min)+min;
}

void main(){
    // Seed time to pseudo-rand generator
    srand(time(0));
    
    // Input parameters
    int memSize, blkSize, fileSize;
	printf("Total Mem Size: ");
    scanf("%d", &memSize);
	printf("Block Size: ");
    scanf("%d", &blkSize);
	printf("File Size: ");
    scanf("%d", &fileSize);
    
    // Find block size and allocate in memory
    int blks = ceil(memSize/blkSize);
    struct Block **allocList = malloc(sizeof(allocList)*blks);
    for(int i=0; i<blks; i++){
        allocList[i] = malloc(sizeof(struct Block));
        allocList[i]->allocated = 0;
        allocList[i]->next = NULL;
    }
    
    // Allocate file
	int file_blk = ceil(fileSize/blkSize);
	int n = 0, ctr = 0;
	struct Block *lastBlock = NULL;
	printf("Link Order: ");
	while(n < file_blk && ctr < blks){
	    // Pick a random block to use
        int i = randint(0, blks);
	    // If not allocated, use it
		if(allocList[i]->allocated == 0){
		    // Link to previous block
		    if(lastBlock != NULL)
		        lastBlock->next = allocList[i];
			allocList[i]->allocated = 1;
			lastBlock = allocList[i];
		    n++; ctr++;
		    printf("%d->", i);
		}
	}
	printf("X\n");
	
	// Check allocation status
	if(n < file_blk-1)
		printf("Cannot allocate!!\n");
	else
		printf("Allocation complete!!\n");
	
	printf("\n%d blocks, %db each. Size: %db\n", blks, blkSize, blks*blkSize);
	printf("\nAllocations");
	for(int i=0; i<blks; i++){
	    if(i%LINE_LEN == 0)
	        putchar('\n');
	    if(allocList[i]->allocated)
		    printf("X ");
	    else
		    printf(". ");
	}
	putchar('\n');
}
