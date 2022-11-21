// Author: Gokul Raj, 235, R5A
// Directory Organization: Two Level

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

struct User{
	int uid;
	struct Dir **dirs;
	int n;
};

void main(){
	int user_n;
	printf("No: of users: ");
	scanf("%d", &user_n);
	
	// Get Users
	struct User **users = malloc(sizeof(users)*user_n);
	for(int j=0; j<user_n; j++){
		struct User *user = malloc(sizeof(struct User));
		printf("User%d ID: ", j+1);
		scanf("%d", &user->uid);
		
		printf("Number of directories: ");
		scanf("%d", &user->n);
		struct Dir **dirs = malloc(sizeof(dirs)*user->n);
		for(int k=0; k<user->n; k++){
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
			dirs[k] = d;
		}
		user->dirs = dirs;
		users[j] = user;
	}
	
	// Show directory tree
	for(int i=0; i<user_n; i++){
		struct User *user = users[i];
		printf("User %d\n", user->uid);
		for(int j=0; j<user->n; j++){
			struct Dir *d = user->dirs[j];
			printf("   |--- %s\n", d->name);
			for(int k=0; k<d->n; k++)
				printf("      |--- %s {%s}\tSize: %d\n", d->files[k]->name, d->files[k]->type, d->files[i]->size);
		}
	}
}
