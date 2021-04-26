#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 150

typedef struct directory{
	
	char name[SIZE];
	struct directory *child;
	struct directory *sibling;
	struct directory *parent;
	
}DIR;



DIR* create(DIR*, char*);
void mkdir(char*, DIR*);
DIR* chdir(char*, DIR*);
void rmdir(char*, DIR*);
void dir(DIR*);
void count( DIR*);





int main(){
	
	DIR* root = (DIR*)malloc(sizeof(DIR));
	DIR* rootNull = NULL;
	root = create(rootNull, "/");
	
	char input[SIZE];
	strcpy(input, "");
	char *ptr;
	
	
	DIR *konum = (DIR*)malloc(sizeof(DIR));
	konum = root;
	
	printf("Kullanabileceginiz fonksiyonlar:\n"
		"mkdir\n"
		"chdir\n"
		"rmdir\n"
		"dir\n"
		"count\n"
		"exit\n"
		"----------------------------------------------------------------\n\n\n\n");
	
	while(strcmp(input, "exit")){
		
		
		gets(input);
		
		ptr = strtok(input, " ");		
		
		if(!strcmp(ptr, "mkdir")){
			ptr = strtok(NULL, " ");
			mkdir(ptr, konum);
		}
		else if(!strcmp(ptr, "chdir")){
			ptr = strtok(NULL, " "); 
			konum = chdir(ptr, konum);
		}
		
		else if(!strcmp(ptr, "rmdir")){
			ptr = strtok(NULL, " ");
			rmdir(ptr, konum);
		}
		
		else if(!strcmp(ptr, "dir")){
			ptr = strtok(NULL, " ");
			dir(konum);
		}
		
		else if(!strcmp(ptr, "count")){
			ptr = strtok(NULL, " "); 
			count(konum);
		}
				
		ptr = strtok(NULL, " ");
		

	}
	
	
	return 0;
}



DIR* create(DIR* parent, char* name){
	DIR* node = (DIR*)malloc(sizeof(DIR));
	strcpy(node->name, name);
	node->parent = parent;
	node->child = NULL;
	node->sibling = NULL;
	
	return node;
}


void mkdir(char* name, DIR* parent){
	
	DIR* node = (DIR*)malloc(sizeof(DIR));
	DIR* lastDir = (DIR*)malloc(sizeof(DIR));
	
	node = parent;
	lastDir = parent;
	 
	if(lastDir->child == NULL){
		node->child = create(lastDir, name);
		printf("Dosya olusturuldu.\n");
	}
	
	else{
		lastDir = lastDir->child;
		
		
		while(lastDir->sibling != NULL && strcmp(lastDir->name, name)){
			lastDir = lastDir->sibling;
		}
		if(!strcmp(lastDir->name, name)){
			printf("Istenilen dosya var.\n");
		}
		else{
		lastDir->sibling = create(lastDir, name);
		printf("Dosya olusturuldu.\n");
		}
	}
	
	
	return;
}


DIR* chdir(char* name, DIR* location){
	DIR* node = (DIR*)malloc(sizeof(DIR));
	DIR* tmp = (DIR*)malloc(sizeof(DIR));
	node = location;
	tmp = location;
	
	if(!strcmp(name, "..")){
		node = node->parent;
		while(node->sibling == tmp){
			tmp = node;
			node = node->parent;
		}
		printf("Istenilen konuma gidildi.\n");
		return node;
	}
	else{
		if(node->child == NULL){
			printf("Alt klasor yok\n");
			return location;
		}
		else{
			node = node->child;
			
			if(!strcmp(node->name, name)){
				printf("Istenilen konuma gidildi.\n");
				return node;
			}
			else{
				while(strcmp(node->name, name) && node->sibling!=NULL){
					node = node->sibling;
				}

				if(!strcmp(node->name, name)){
					printf("Istenilen konuma gidildi. while\n");
					return node;
				}
				else{
					printf("Istenilen isimde bir dosya yok.\n");
					return location;
				}
			}
		}
	}
}


void rmdir(char* name, DIR* location){
	DIR* node = (DIR*)malloc(sizeof(DIR));
	DIR* tmp = (DIR*)malloc(sizeof(DIR));
	node = location;
	tmp = location;
	
	node = node->child;
	
	while(strcmp(node->name, name) && node->sibling!=NULL){
		node = node->sibling;
	}
	if(!strcmp(node->name, name)){
		if(node->child == NULL){
			if(node->sibling == NULL){
				node = (DIR*)node->parent;
				node->child = NULL;
				return;
			}
			else{
				tmp = node;
				node = node->parent;
				if(node->child == tmp){
					node->child = tmp->sibling;
					return;
				}
				else{
					node->sibling = tmp->sibling;
					return;
				}
			}
		}
		else{
			printf("Istenilen dosyaya ait alt dosyalar olduğu için silinemedi.\n");
			return;
		}
	}
	else{
		printf("Istenilen dosya yok.\n");
		return;
	}
}


void dir(DIR* location){
	DIR* tmp = (DIR*)malloc(sizeof(DIR));
	tmp = location;
	
	if((tmp->child) != NULL){
		
		tmp = tmp->child;
		printf("Alt klasorler:\n");
		
		
		while(tmp->sibling != NULL){
			
			
			printf("%s - ", tmp->name);
			tmp = tmp->sibling;
		}
		printf("%s", tmp->name);
		printf("\n");
		return;
	}
	else{
		
		printf("Alt klasor yok\n");
		return;
		
	}
	
}


void count(DIR* location){
	DIR* tmp = (DIR*)malloc(sizeof(DIR));
	tmp = location;
	int i=0;
	if((tmp->child) != NULL){
		i++;
		tmp = tmp->child;
		while(tmp->sibling != NULL){
			tmp = tmp->sibling;
			i++;
		}
		
		printf("Alt klasor sayisi: %d\n", i);
		
		return;
	}
	else{
		printf("Alt klasor yok\n");
		return;
	}
	
}
