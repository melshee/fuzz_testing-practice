//Calculate the top 10 tweeters (by volume of tweets) in a given CSV file of tweets
 
// takes one command line argument, the path of the csv file.
// It should gracefully handle both valid and invalid inputs. For valid inputs
// it should produce 10 lines of output (most frequent to least frequent): <tweeter>: <count of tweets> 
// A valid csv file will have a header, and the tweeter column will be called “name”.

//Allowed assumptions:
// max  valid line length = no longer than the longest line in the csv file provided for Homework 3
// max length of the file = 20,000 lines
// max number of tweeters = no larger than the set of tweeters in the cl­tweets­short.csv file
// a valid file will not have additional commas inside the tweet

// Program should not crash on ANY input, even invalid ones.
// Program should work with the provided Ubuntu afl docker, which is where it will be fuzz tested by your assigned testing team.
 
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
tweeter* find_name(char *name, tweeter* tweeters);

int main(int argc, char* argv[]) {

	if (argc != 2) {
		printf("usage: maxTweeter <filename.csv> \n");
		return -1;
	}

  	printf("%s", argv[1]);
  	printf("<tweeter>: <count of tweets>n\n");
  	FILE *fp = fopen(argv[1], "r");

  	if (!fp) {
  		printf("Could not open file\n");
  		return -1;
  	}

  	tweeter *tweeters = malloc(sizeof(tweeter) * 20000);
  	int tweeterCount = 0;


  	char line[1024];
  	fgets(line, 1024, fp);

  	int nameCol = get_tweeter_col(line);
  	printf("nameCol: %d\n", nameCol);

  	char name[64];
  	tweeter *curr = NULL;


   	while (fgets(line, 1024, fp)) {
   		strcpy(name, getfield(line, nameCol));
   		//printf("current name: %s\n", (char*) getfield(line, nameCol));
   		//curr = find_name(name, tweeters);
   		//tweeters[tweeterCount] = malloc(sizeof(tweeter));
   		strcpy(tweeters[tweeterCount].name, name);
   		tweeters[tweeterCount].count = 1;
   		tweeterCount++;

   }



  	fclose(fp);

}

tweeter* find_name(char *name, tweeter* tweeters) {

	if (!name || !tweeters) {
		return NULL;
	}



  return NULL;
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

//returns column number that's titled "name"
int get_tweeter_col(char *line) {

	if (!line)
		return -1;

 	int count = 0;
  	const char *tok;
  	char name[7] = "\"name\"\0";
  	tok = strtok(line, ",");

  	if (strcmp(tok, "\"\"") != 0) {
  		printf("Invalid Input Format\n");
  		return -1;
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

char * calc_top_N_tweeters(int top_N) {
  static char *list = "";
  return list;
}


//