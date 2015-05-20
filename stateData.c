#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void toXMLFile(char states[][35], int *populations, int numStates);
char * rtrim(char *str);

int main(int argc, char **argv[]) 
{
  int const size = 200;
  int const numStates = 50;
  char fileName[] = "stateData.txt";
  char tempBuffer[size];
  char tmp[size];

  char states[numStates][35];
  int  states_pops[numStates];

  //open the file, quit if it fails...
  FILE *instream = fopen(fileName, "r");
  if(instream == NULL) {
    fprintf(stderr, "Unable to open file: %s\n", fileName);
    exit(1);
  }

  //read the file, line by line
  int i=0;
  while(fgets(tempBuffer, size, instream) != NULL) {
    //remove the endline character from the line
    tempBuffer[strlen(tempBuffer)-1] = '\0';
	//tokenize the line, breaking along commas:
    char *stateToken = strtok(tempBuffer, ",");
    strcpy(states[i], stateToken);
    char *popToken = strtok(NULL, ",");
    states_pops[i] = atoi(popToken);
    i++;
  }
  fclose(instream);

  //output to the standard output
  int total = 0;
  for(i=0; i<numStates; i++) {
    printf("%15s %10d\n", states[i], states_pops[i]);
    total += states_pops[i];
  }
  printf("%-15s  %10d\n", "TOTAL", total);

  //output to a binary datafile
  FILE *outstream = fopen("stateData.dat", "wb");
  for(i=0; i<numStates; i++) {
    //limit the state name to 15 characters
    fwrite(states[i], sizeof(char), 15, outstream);
	//output a single int type
    fwrite(&states_pops, sizeof(int), 1, outstream);
  }
  fclose(outstream);

  toXMLFile(states, states_pops, 50);

  return 0;
}

void toXMLFile(char states[][35], int *populations, int numStates) {
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
