// Author: Gokul Raj, 235, R5A
// Directory Organization: Single Level

#include <stdio.h>
#include <stdlib.h>

struct File{
	char *name;
	char *type;
	int size;
};

struct Dir{
	char *name;
	struct File **files;
	int n;
};


void main(){
	struct Dir *d = malloc(sizeof(struct Dir));
	char *name = malloc(256);
	printf("Enter directory name: ");
	scanf("%s", name);
	d->name = name;
	
	printf("Number of files: ");
	scanf("%d", &d->n);
	
	
	// Get files
	struct File **files = malloc(sizeof(files)*d->n);
	printf("Enter {Name, Type, Size} of files\n");
	for(int i=0; i<d->n; i++){
		struct File *f = malloc(sizeof(struct File));
		char *filename = malloc(256);
		char *filetype = malloc(256);
		printf("File%d: ", i+1);
		scanf("%s %s %d", filename, filetype, &f->size);
		f->name = filename;
		f->type = filetype;
		files[i] = f;
	}
	d->files = files;
	
	// Show directory
	printf("%s\n", d->name);
	for(int i=0; i<d->n; i++)
		printf("    |--- %s {%s}\tSize: %d\n", d->files[i]->name, d->files[i]->type, d->files[i]->size);
}
