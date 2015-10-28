#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void toXMLFile(char **states, int *populations, int numStates);
char * rtrim(char *str);

int main(int argc, char **argv) 
{
  int const size = 200;
  int const numStates = 50;
  char fileName[] = "stateData.txt";
  char tempBuffer[size];
  char tmp[size];

  //setup arrays
  int i;
  char **states = (char **) malloc(sizeof(char*) * numStates);
  int *statePopulations = (int *) malloc(sizeof(int) * numStates);
  for(i=0; i<numStates; i++) {
    states[i] = (char *) malloc(sizeof(char) * size);
  }

  //open the file, quit if it fails...
  FILE *instream = fopen(fileName, "r");
  if(instream == NULL) {
    fprintf(stderr, "Unable to open file: %s\n", fileName);
    exit(1);
  }

  //read the file, line by line
  i=0;
  while(fgets(tempBuffer, size, instream) != NULL) {
    //remove the endline character from the line
    tempBuffer[strlen(tempBuffer)-1] = '\0';
	//tokenize the line, breaking along commas:
    char *stateToken = strtok(tempBuffer, ",");
    strcpy(states[i], stateToken);
    char *popToken = strtok(NULL, ",");
    statePopulations[i] = atoi(popToken);
    i++;
  }
  fclose(instream);

  //output to the standard output
  int total = 0;
  for(i=0; i<numStates; i++) {
    printf("%15s %10d\n", states[i], statePopulations[i]);
    total += statePopulations[i];
  }
  printf("%-15s  %10d\n", "TOTAL", total);

  //output to a binary datafile
  FILE *outstream = fopen("stateData.dat", "w");
  for(i=0; i<numStates; i++) {
    //limit the state name to 15 characters
    fwrite(states[i], sizeof(char), 15, outstream);
    //output a single int type
    fwrite(&statePopulations, sizeof(int), 1, outstream);
  }
  fclose(outstream);

  toXMLFile(states, statePopulations, 50);

  return 0;
}

void toXMLFile(char **states, int *populations, int numStates) {
  //TODO: you need to implement this
}

char * rtrim(char *str) {

  int n = strlen(str);
  while(isspace(str[n-1])) {
      n--;
  }
  char * trimmed = malloc(sizeof(char) * (n+1));
  strncpy(trimmed, str, n);
  trimmed[n] = '\0';
  return trimmed;
}
