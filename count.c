#include <stdio.h>
#include <string.h>

int MAX_SEARCH = 20;

int main(int argc, char *argv[]){

	if(argc != 4){
		printf("Improper number of arguments.\nPlease excute program using the command \"count <input-filename> <search-string> <output-filename>\"");
		return;
	}

	unsigned char buffer[100];
	FILE *inFile;
	FILE *outFile;
	char *inFilename = argv[1];
	char *outFilename = argv[3];

	inFile = fopen(inFilename, "rb");
	if(inFile == NULL){
		printf("Could not open input file \"%s\".\nPlease execute the program using the command \"count <input-filename> <search-string> <output-filename>\"", inFilename);
		return;
	}
	
	outFile = fopen(outFilename, "w");
	if(outFile == NULL){
		printf("Could not open output file \"%s\".\nPlease execute the program using the command \"count <input-filename> <search-string> <output-filename>\"", outFilename);
		
		fclose(inFile);
		return;
	}
	else{
		
		int readLen;
		int i;
		int count = 0;
		char *searchTerm = argv[2];
		int checking[MAX_SEARCH];
		for(i = 0; i < MAX_SEARCH; i++){
			checking[i] = -1;
		} 
		int foundCount = 0;
		do{
			readLen = fread(buffer, 1, sizeof(buffer), inFile);
			for(i = 0; i < readLen; i++){
				count++;
				int j;
				int added = 0;
				int start = buffer[i] == (searchTerm[0] & 0xff);
				for(j = 0; j < MAX_SEARCH; j++){
					if(checking[j] != -1){
						if(buffer[i] == (searchTerm[checking[j] + 1] & 0xff)){
							if(checking[j] + 2 == strlen(searchTerm)){
								foundCount++;
								checking[j] = -1;
							}
							else{
								checking[j]++;
							}
						}
						else{
							checking[j] = -1;
						}
					}
					
					if(checking[j] == -1){
						if(!added && start){
							checking[j] = 0;
							added = 1;
						}
					}
				}	
			}
		}while(readLen > 0);

		fprintf(outFile, "Length in bytes: %i\n", count - 1);
		fprintf(outFile, "Number of matches: %i\n", foundCount);
		fclose(inFile);
		fclose(outFile);
		return;
	}
}
