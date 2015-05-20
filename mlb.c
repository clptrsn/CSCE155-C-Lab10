#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void sortMLB(char teams[][20], double winPerc[], int numTeams);
void printMLB(char teams[][20], double winPerc[], int numTeams);

int main(int argc, char **argv[]) 
{
  int const size = 200;
  int const numTeams = 16;
  char fileName[] = "mlb_nl_2011.txt";
  char tempBuffer[size];
  char tmp[size];

  char teams[numTeams][20];
  double winPercentages[numTeams];

  //TODO: open the file, read it line by line, tokenize it to get the 
  //      team name, wins, and losses, and store the results into
  //      teams[] and winPercentagesp[]

  //sort them
  sortMLB(teams, winPercentages, numTeams);
  //print them out
  printMLB(teams, winPercentages, numTeams);

  return 0;
}

/**
 * A sorting function to sort the teams and their win percentages
 * using the selection sort algorithm which successively finds the
 * "maximum" element and places it at the front of the array
 */
void sortMLB(char teams[][20], double winPerc[], int numTeams) {

  int i, j, max_index;
  char tmp_str[100];
  double tmp_dbl;
  //for each element i
  for(i=0; i<numTeams-1; i++) {
    max_index = i;
	//find the maximum element among elements i+1 thru n-2
    for(j=i+1; j<numTeams; j++) {
      if(winPerc[max_index] < winPerc[j]) {
        max_index = j;
      }
    }
	//swap the ith element and the maximum element
	//in this case, elements from both arrays need to be swapped
	//at the same time
    tmp_dbl = winPerc[i];
    winPerc[i] = winPerc[max_index];
    winPerc[max_index] = tmp_dbl;
    strcpy(tmp_str, teams[i]);
    strcpy(teams[i], teams[max_index]);
    strcpy(teams[max_index], tmp_str);
  }

}

void printMLB(char teams[][20], double winPerc[], int numTeams) {

  int i=0;
  printf("%-12s %-10s\n", "TEAM", "WIN PERC");
  for(i=0; i<numTeams; i++) {
    printf("%-12s %.3f%%\n", teams[i], winPerc[i]*100.0);
  }
  
}
