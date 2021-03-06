#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int d_flag = 0; 
char buffer[4000];
char file_name[100];
int size;

struct menuItem
{
	char *action;
	void (*fun)();
};

void quit(){
	if (d_flag) 
		printf ("quitting");
	exit(0);
}

void changeDebugMode() {
	if (d_flag == 0) {
		d_flag = 1 ; 
		printf ("Debug flag now on\n");
	}
	else {
		d_flag = 0 ; 
		printf ("Debug flag now off\n");
	} 
}

void setFileName() {
	printf("please enter a valid file mame: \n");
	fgets(file_name, 100, stdin);
	if(d_flag) 
		printf("Debug: file name set to %s", file_name);
}

void setUnitsize() {
	char new_size[10];
	printf("please enter a valid size number: \n");
	fgets(new_size,10,stdin);
	int tmp_new_size = atoi (new_size);
	if (tmp_new_size ==1 || tmp_new_size ==2 || tmp_new_size ==4){
		size = tmp_new_size; 
		if (d_flag)
			printf ("Debug: set size to %d", size); 
	}
	else 
		perror("not valid size");

	
}
int main(int argc, char** argv){
	file_name[0] = '\n'; 
	struct menuItem menu[] = {{"Toggle Debug Mode", changeDebugMode}, {"Set File Name", setFileName}, {"Set Unit Size", setUnitsize}, {"Quit", quit}, {NULL , NULL}};
	char choose[10];
	size = 1;
	int i;

	while(1){
		if (d_flag){
			printf("unit size: %d\n", size);
			printf("file name: %s", file_name);
			printf("buffer address: %p\n", buffer);
		}
		printf("Choose action: \n");
		for(i = 0; menu[i].action != NULL ; i++){
			printf("%d-%s \n", i, menu[i].action);
		}
		fgets(choose,10, stdin);
		if (atoi(choose) >= 0 && atoi(choose) < (sizeof(menu)/ sizeof(menu[0])))
			menu[atoi(choose)].fun();
		else
			printf("Not an option. please select again\n ");
	}
}