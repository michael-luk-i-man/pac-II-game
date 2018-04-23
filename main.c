/* A stylized implementation
* of
  Game of Life */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int count_neighbors(int cell_id) {
	return 0;
}


int scan_grid(char *file, int width, int *gsptr) {

	FILE *fp;
	int c; // Init character reader
	fp = fopen(file,"r"); // Open file in same dir
	int i = 0;
	while(++i) { // Indefinitely:
	  c = fgetc(fp); // c is the next character of the file
	  if( feof(fp) ) { // If it's the end, exit loop
	     break;
	  }

	  if( isspace(c)==0 ) { // If the char's not a whitespace:
	  	printf("%c", c); // Print that character
	  	*(gsptr+i-1) = c; // Save it to its rightful place in the array
	  }

	}
	fclose(fp); // Close the file
	return(0); // Obligatory (negligible) return
}

int main(int argc, char *argv[]) {

	int width = (argc<4)?10:(int)strtol(argv[3], NULL, 10);
	int gridstream[width*width];

	// struct cell {
	// 	int left_edge;
	// 	int right_edge;
	// 	int top_edge;
	// 	int bottom_edge;
	// }

	scan_grid(argv[2],width,gridstream);

	printf("%c%c%c",' ',gridstream[0],'c');

}
