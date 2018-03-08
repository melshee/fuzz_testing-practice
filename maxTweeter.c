#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
	char *name;
	int count;
} tweeter;

int get_tweeter_col(char *line);
const char* getfield(char* line, int num);
int find_name(char *name, tweeter** tweeters, int tweeterCount);
void sort_desc(tweeter **tweeters, int tweeterCount);
void print_tweeters(tweeter **tweeters, int tweeterCount);

int main(int argc, char* argv[]) {

	if (argc != 2) {
		printf("usage: maxTweeter <filename.csv> \n");
		return -1;
	}

  	FILE *fp = fopen(argv[1], "r");

  	if (!fp) {
  		printf("Could not open file\n");
  		return -1;
  	}

  	tweeter **tweeters = malloc(sizeof(tweeter*) * 20000);
  	int tweeterCount = 0;


  	char line[1024];
  	fgets(line, 1024, fp);

  	int nameCol = get_tweeter_col(line);
  	char name[64];
  	tweeter *curr = NULL;


   	while (fgets(line, 1024, fp)) {

   		strcpy(name, getfield(line, nameCol));

   		if (find_name(name, tweeters, tweeterCount) == 1) {
   			continue;
   		} else {
	   		tweeter *curr = malloc(sizeof(tweeter));
	   		curr->name = malloc(strlen(name) + 1);
	   		strcpy(curr->name, name);
	   		curr->count = 1;
	   		tweeters[tweeterCount] = curr;
	   		tweeterCount++;
   		}
   	}

   	sort_desc(tweeters, tweeterCount);
   	//print_tweeters(tweeters, tweeterCount);
   	print_tweeters(tweeters, 10);

   	for(int i = 0; i < tweeterCount; i++) {
   		free(tweeters[i]->name);
   		free(tweeters[i]);
   	}
   	free(tweeters);

	fclose(fp);
  	return 0;
}

void print_tweeters(tweeter **tweeters, int tweeterCount) {
	for (int i = 0; i < tweeterCount; i++) {
		printf("%s: %d\n", tweeters[i]->name, tweeters[i]->count);
	}
	return;
}

void sort_desc(tweeter **tweeters, int tweeterCount) {

	for (int i = 0; i < tweeterCount; i++) {                
		for (int j = 0; j < tweeterCount; j++)          
		{
			if (tweeters[j]->count < tweeters[i]->count)             
			{
				tweeter *tmp = tweeters[i];       
				tweeters[i] = tweeters[j];          
				tweeters[j] = tmp;           
			}
		}
	}
	return;
}

int find_name(char *name, tweeter** tweeters, int tweeterCount) {

	if (!name || !tweeters) {
		return 0;
	}

	for (int i = 0; i < tweeterCount; i++) {
		if (strcmp(tweeters[i]->name, name) == 0) {
			tweeters[i]->count++;
			return 1;
		}
	}
	return 0;
}


const char* getfield(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, ","); ; tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

int get_tweeter_col(char *line) {

	if (!line)
		return -1;

 	int count = 0;
  	const char *tok;
  	char name[7] = "\"name\"\0";
  	tok = strtok(line, ",");

  	if (strcmp(tok, "\"\"") != 0) {
  		printf("Invalid Input Format\n");
  		exit(1);
  	}

	for (; ; tok = strtok(NULL, ",\n")) {
		if (strcmp(tok, name) == 0) {
	  		return count + 1;
	  	} else {
	  		count++;
	  	}
	}
	return -1;
}
