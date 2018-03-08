//Calculate the top 10 tweeters (by volume of tweets) in a given CSV file of tweets
 
// takes one command line argument, the path of the csv file.
// It should gracefully handle both valid and invalid inputs. For valid inputs
// it should produce 10 lines of output (most frequent to least frequent): <tweeter>: <count of tweets> 
// A valid csv file will have a header, and the tweeter column will be called “name”.

//Allowed assumptions:
// max valid line length = no longer than the longest line in the csv file provided for Homework 3
// max length of the file = 20,000 lines
// max number of tweeters = no larger than the set of tweeters in the cl­tweets­short.csv file
// a valid file will not have additional commas inside the tweet

// Program should not crash on ANY input, even invalid ones.
// Program should work with the provided Ubuntu afl docker, which is where it will be fuzz tested by your assigned testing team.
 
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_valid(char *input) {
  if(!input) {
    return false;
  }

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
