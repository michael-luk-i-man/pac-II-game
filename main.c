/* A stylized implementation
* of
  Game of Life */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int count_neighbors(int cell_id, int width, int *gs) {
	int mod_width = cell_id%width;
	int neighbor_sum;

	// Matter of fact locations if they exist
	int left = cell_id - 1;
	int right = cell_id + 1;
	int top = cell_id - width;
	int bottom = cell_id + width; 

	int topleft = cell_id - width - 1;
	int topright = cell_id - width + 1;
	int bottomleft = cell_id + width - 1;
	int bottomright = cell_id + width + 1; 

	int dead = width*width+1;

	switch ( mod_width ) {

		case 0: // Cell is on the right edge
			printf(%s, 'right edge');
			if ( cell_id<width-1 ) { // Also on top edge
				printf(%s, 'top edge');
				neighbor_sum = sigma_neighbor(left,dead,dead,bottom,dead,dead,bottomleft,dead);
			}
			else if ( cell_id>width*(width-1)-1 ) { // Also on bottom edge
				printf(%s, 'top edge');
				neighbor_sum = sigma_neighbor(left,dead,top,dead,topleft,dead,dead,dead);
			}
			else neighbor_sum = sigma_neighbor(left,dead,top,bottom,topleft,dead,bottomleft,dead);

			
		case 1: // Cell is on the left edge
			printf(%s, 'left edge');
			if ( cell_id<width-1 ) { // Also on top edge
				printf(%s, 'top edge');
				neighbor_sum = sigma_neighbor(dead,right,dead,bottom,dead,dead,dead,bottomright);
			}
			else if ( cell_id<width+1 ) { // Also on top edge
				printf(%s, 'bottom edge');
				neighbor_sum = sigma_neighbor(dead,right,top,dead,topleft,topright,dead,dead);
			}
			else neighbor_sum = sigma_neighbor(dead,right,top,bottom,dead,topright,dead,bottomright);

	}

	return neighbor_sum;
}

int get_status(int cell_id) {
	return gridstream[cell_id];
}

int sigma_neighbor(int l, int r, int t, int b, int tl, int tr, int bl, int br) {
	int total = get_status(l) + get_status(r) + get_status(t) 
	+ get_status(b) + get_status(tl) + get_status(tr)
	+ get_status(bl) + get_status(br);
	return total;
}

int scan_grid(char *file, int width, int *gs) {

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
	  	*(gs+i-1) = c; // Save it to its rightful place in the array
	  }

	}
	fclose(fp); // Close the file
	return(0); // Obligatory (negligible) return
}

int main(int argc, char *argv[]) {

	int width = (argc<4)?10:(int)strtol(argv[3], NULL, 10);
	int gridstream[width*width+1];
	gridstream[width*width] = 0; // The default dead cell.

	// struct cell {
	// 	int left_edge;
	// 	int right_edge;
	// 	int top_edge;
	// 	int bottom_edge;
	// }

	scan_grid(argv[2],width,gridstream);

	printf("%c%c%c",' ',gridstream[0],'c');

}
