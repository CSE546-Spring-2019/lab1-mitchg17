//CSE 5462 Lab 1
//Author: Mitchell Giese
#include <stdio.h>
#include <string.h>

//Maximum size of search string
int MAX_SEARCH = 20;

int main(int argc, char *argv[]){

	//Improper number of arguments
	if(argc != 4){
		printf("Improper number of arguments.\nPlease excute program using the command \"count <input-filename> <search-string> <output-filename>\"");
		return;
	}

	unsigned char buffer[100];
	FILE *inFile;
	FILE *outFile;
	char *inFilename = argv[1];
	char *outFilename = argv[3];

	//Try to open input file
	inFile = fopen(inFilename, "rb");
	if(inFile == NULL){
		printf("Could not open input file \"%s\".\nPlease execute the program using the command \"count <input-filename> <search-string> <output-filename>\"", inFilename);
		return;
	}
	
	//Try to open output file
	outFile = fopen(outFilename, "w");
	if(outFile == NULL){
		printf("Could not open output file \"%s\".\nPlease execute the program using the command \"count <input-filename> <search-string> <output-filename>\"", outFilename);
		
		fclose(inFile);
		return;
	}
	else{
		//All files have been opened

		int readLen;
		int i;
		unsigned long count = 0;
		char *searchTerm = argv[2];
		int checking[MAX_SEARCH];
		for(i = 0; i < MAX_SEARCH; i++){
			checking[i] = -1;
		} 
		unsigned long foundCount = 0;

		//Iterate through file in buffer reads of 100 bytes
		do{
			readLen = fread(buffer, 1, sizeof(buffer), inFile);
			//Iterate through buffer
			for(i = 0; i < readLen; i++){
				count++;
				int j;
				int added = 0;
				int start = buffer[i] == (searchTerm[0] & 0xff);
				
				//Iterate through currently tracked search terms in checking[] -- checking stores the index in the search term that the next byte should match
				for(j = 0; j < MAX_SEARCH; j++){
					//If checking is -1 no term being checked
					if(checking[j] != -1){
						//Compare next byte in input to next byte in search term
						if(buffer[i] == (searchTerm[checking[j] + 1] & 0xff)){
							//Check if entire term has been found
							if(checking[j] + 2 == strlen(searchTerm)){
								foundCount++;
								checking[j] = -1;
							}
							else{
								checking[j]++;
							}
						}
						//If not matching reset to -1
						else{
							checking[j] = -1;
						}
					}
					
					//If byte matches first byte of search term set an empty index of the checking array to 0
					if(checking[j] == -1){
						if(!added && start){
							checking[j] = 0;
							added = 1;
						}
					}
				}	
			}
		}while(readLen > 0);
		//Execution ends when there is nothing left to read in input

		//Write to output
		fprintf(outFile, "Length in bytes: %lu\n", count);
		fprintf(outFile, "Number of matches: %lu\n", foundCount);
		
		//Close files
		fclose(inFile);
		fclose(outFile);
		return;
	}
}
