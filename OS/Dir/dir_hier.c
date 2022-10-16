#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TREE_INDENT 3
#define MAX_FOLD_SIZE 10

struct Inode{
	char type;
	char *name;
	char *ext;
	int size;
	struct Inode **links;
	struct Inode *parent;
	int n;
};

void mkfile(struct Inode *node){
	struct Inode *f = malloc(sizeof(struct Inode));
	f->type = 0;
	f->name = malloc(256);
	f->ext = malloc(128);
	f->links = NULL;
	f->n = -1;
	f->parent = node;
	scanf("%s %s %d", f->name, f->ext, &f->size);
	node->links[node->n++] = f;
}

struct Inode *cd(struct Inode *node, char *loc){
	if(!strcmp(loc, "..")){
		if(node->parent != NULL)
			return node->parent;
		else{
			printf("Already at root.\n");
			return node;
		}
	}
	for(int i=0; i<node->n; i++){
		if(!strcmp(node->links[i]->name, loc) && node->links[i]->type)
			return node->links[i];
	}
	printf("Directory '%s' not found!!\n", loc);
	return node;
}

void mkdir(struct Inode *node){
	struct Inode *f = malloc(sizeof(struct Inode));
	f->type = 1;
	f->name = malloc(256);
	f->ext = NULL;
	f->links = malloc(sizeof(f->links)*MAX_FOLD_SIZE);
	f->size = -1;
	f->n = 0;
	f->parent = node;
	scanf("%s", f->name);
	node->links[node->n++] = f;
}

void indentPrint(char *msg, int indent){
	for(int i=0; i<indent; i++)
		putchar(' ');
	printf("|-- %s\n", msg);
}

void tree(struct Inode *node, int indent){
	char *fs = malloc(1024);
	indentPrint(node->name, indent);
	for(int i=0; i<node->n; i++){
		// If folder, recurse tree
		if(node->links[i]->type)
			tree(node->links[i], indent+TREE_INDENT);
		// Else, show the file stats
		else{
			sprintf(fs, "%s {%s}\tSize: %d", node->links[i]->name, node->links[i]->ext, node->links[i]->size);
			indentPrint(fs, indent+TREE_INDENT);
		}
	}
	free(fs);
}

void main(){
	struct Inode *root = malloc(sizeof(struct Inode));
	char *cmd = malloc(256);
	char *loc = malloc(256);
	root->name = malloc(256);
	// Initialize Defaults for Root folder
	root->type = 1; root->n = 0; root->ext = NULL; root->size = -1;
	root->links = malloc(sizeof(root->links)*MAX_FOLD_SIZE);
	printf("Root name: ");
	scanf("%s", root->name);

	struct Inode *current = root;
	while(1){
		printf("\n(%s) > ", current->name);
		scanf("%s", cmd);
		if(!strcasecmp(cmd, "mkdir"))
			mkdir(current);
		else if(!strcasecmp(cmd, "mkfile"))
			mkfile(current);
		else if(!strcasecmp(cmd, "cd")){
			scanf("%s", loc);
			current = cd(current, loc);
		}
		else if(!strcasecmp(cmd, "tree"))
			tree(root, 0);
		else if(!strcasecmp(cmd, "ls"))
			tree(current, 0);
		else if(!strcasecmp(cmd, "exit"))
			break;
		else if(!strcasecmp(cmd, "help")){
			printf("\nHierarchial Directory Simulation\n----------\n");
			printf("mkdir <dirname> -- Make a directory\n");
			printf("mkfile <name> <type> <size> -- Make a file\n");
			printf("cd <dirname> -- Move into directory (Use .. to goto parent)\n");
			printf("ls -- List current directory recursively\n");
			printf("tree -- Show whole directory tree\n");
			printf("exit -- Exit program\n");
		}
		else
			printf("Invalid Command [%s]!!\nUse 'help' for usage instructions.\n", cmd);
	}
}
