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

int main(int argc, char* argv[]) {
  printf("%s", argv[1]);
  printf("<tweeter>: <count of tweets>n");

}

bool is_valid() {
  //does it have a header and a column called name?
  return false;
}

//returns column number that's titled "name"
int get_tweeter_col() {
  char *column_name = "name";
  return 0;
}

char * calc_top_N_tweeters(int top_N) {
  static char *list = "";
  return list;
}


//