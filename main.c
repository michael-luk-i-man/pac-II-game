/* A stylized implementation
* of
  Game of Life 

  Michael Lukiman - mll469 - pacII - Courant Institute of Mathematical Sciences
  */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define X dead

int main(int argc, char *argv[]) {

	int width = (argc<4)?5:(int)strtol(argv[3], NULL, 10);
	int stream_length = width*width;
	int gridstream[stream_length+1];
	int gridstream_next[stream_length+1];
	gridstream[stream_length] = '0'; // The default dead cell.
	gridstream_next[stream_length] = '0'; 

	int display_array(int *arr,int width) {

		int current_id; 

		for ( int j=0; j<width; j++) {

			for ( int k=0; k<width; k++) {

				current_id = j*width + k;
			
				if ((current_id+1)%width!=0) {
					printf("%c ",gridstream[current_id]);
				}

				else printf("%c",gridstream[current_id]);

			} 

			printf("\n");

		}
		return('0');
	}

	int get_status(int cell_id) {
		// printf("%c%c",' ', gridstream[cell_id]);
		return gridstream[cell_id]-48;
	}

	int scan_grid(char *file, int width, int *gridstream, int *gridstream_next) {

		FILE *fp;
		int c; // Init character reader
		fp = fopen(file,"r"); // Open file in same dir
		int i = 0;
		while(1) { // Indefinitely:
		  c = fgetc(fp); // c is the next character of the file
		  if( feof(fp) ) { // If it's the end, exit loop
		     break;
		  }
		  // printf("%c",c);
		  if( isspace(c)==0 ) { // If the char's not a whitespace:
		  	gridstream[i] = c; // Save it to its rightful place in the array
		  	gridstream_next[i] = c;
		  	i++;
		  }

		  gridstream[i+1] = '0';
		  gridstream_next[i+1] = '0';

		}
		fclose(fp); // Close the file
		return(0); // Obligatory (negligible) return
	}

	scan_grid(argv[2],width,gridstream,gridstream_next);
	display_array(gridstream,width);

	int sigma_neighbor(int tl, int t, int tr, int l, int r, int bl, int b, int br) {
		int total = get_status(l) + get_status(r) + get_status(t) 
		+ get_status(b) + get_status(tl) + get_status(tr)
		+ get_status(bl) + get_status(br);
		return total;
	}

	// // struct cell {
	// // 	int left_edge;
	// // 	int right_edge;
	// // 	int top_edge;
	// // 	int bottom_edge;
	// // }

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

			case 4: // Cell is on the right edge

				// Uncomment to debug case decisions. 
				// printf("%s\n","Case 0" );

				if ( cell_id<width ) { // Also on top edge

					printf("%s\n", "tr corner");
					neighbor_sum = sigma_neighbor(X,			X,			X,
												  left,						X,
												  bottomleft,	bottom,		X);
				}
				else if ( cell_id>width*(width-1)-1 ) { // Also on bottom edge
					printf("%s\n", "br corner");
					neighbor_sum = sigma_neighbor(topleft,			top,			X,
									  			  left,								X,
									  			  X,				X,				X);
				}
				else neighbor_sum = sigma_neighbor(topleft,			top,			X,
									  			  left,								X,
									  			  bottomleft,		bottom,			X);
				break;

				
			case 0: // Cell is on the left edge
				// printf("%s\n", "Case 1");
				if ( cell_id<width ) { // Also on top edge
					printf("%s\n", "tl corner");
					neighbor_sum = sigma_neighbor(X,			X,			X,
												  X,						right,
												  X,			bottom,		bottomright);
				}
				else if ( cell_id>width*(width-1)-1 ) { // Also on bottom edge
					printf("%s\n", "bl corner");
					neighbor_sum = sigma_neighbor(X,			top,		topright,
												  X,						right,
												  X,			X,			X);
				}
				else neighbor_sum = sigma_neighbor(X,			top,		topright,
												   X,						right,
												   X,			bottom,		bottomright);
				break;

			default: 


				// printf("%s\n", "Case Default");
				if ( cell_id<width ) { // Also on top edge
					printf("%s\n", "top edge");
					neighbor_sum = sigma_neighbor(X,			X,			X,
												  left,						right,
												  bottomleft,	bottom,		bottomright);
				}
				else if ( cell_id>width*(width-1)-1 ) { // Also on bottom edge
					printf("%s\n", "bottom edge");
					neighbor_sum = sigma_neighbor(topleft,			top,		topright,
												  left,						right,
												  X,			X,			X);
				}
				else neighbor_sum = sigma_neighbor(topleft,			top,		topright,
												   left,						right,
												   bottomleft,		bottom,		bottomright);
				break;		

		}	

		return neighbor_sum;

	}

	printf("\n%s%c","Generation numbers: ", *argv[1] );
	int gen = *argv[1]-48;
	for ( int loopa_index = 0; loopa_index<gen-1; loopa_index++ ) { 

		// Uncomment to track loop_a iteration.
		printf("\n\n");
		// printf("%d\n", loopa_index);


		for ( int loopb_index = 0; loopb_index<stream_length; loopb_index++ ) {

			// Uncomment to track loop_b iteration.
			//printf("%d : ", loopb_index);
			int neighbors = count_neighbors(loopb_index, width,gridstream);

			switch( neighbors ) {
				case 0: gridstream_next[loopb_index] = '0'; 
					printf("%d : %d : %s\n", loopb_index, neighbors, "Zero because zero neighbors.");
					break; 
				case 1: gridstream_next[loopb_index] = '0'; 
					printf("%d : %d : %s\n", loopb_index, neighbors, "Zero because not enough neighbors (1)");
					break;
				case 2: 
					gridstream_next[loopb_index]= (gridstream[loopb_index]-48)?'1':'0'; 
					printf("%d : %d : %s\n", loopb_index, neighbors, "Two neighbors becomes one if alive, or stays zero if dead.");
					break;
				case 3:
					gridstream_next[loopb_index]= '1';
					printf("%d : %d : %s\n", loopb_index, neighbors, "One because three neighbors.");
					break;
				default: 
					gridstream_next[loopb_index]= '0'; 
					printf("%d : %d : %s\n", loopb_index, neighbors, "Zero because more than three neighbors.");
					break;
			}

		}

		for ( int loopc_index = 0; loopc_index<stream_length; loopc_index++){

			gridstream[loopc_index] = gridstream_next[loopc_index];

		}

		display_array(gridstream,width);

	}

	void output_file( int *gridstream , int width ) {

		int current_id;
		
		FILE *fp = fopen("filename.out", "w");
		if (fp == NULL)
		{
		    printf("Error opening file!\n");
		    exit(1);
		}

		for ( int j=0; j<width; j++) {

			for ( int k=0; k<width; k++) {

				current_id = j*width + k;
			
				if ((current_id+1)%width!=0) {
					fprintf(fp, "%c ",gridstream[current_id]);
				}

				else fprintf(fp, "%c",gridstream[current_id]);

			} 

			fprintf(fp, "\n");

		}

		fclose(fp);
	}

	output_file( gridstream, width );

}


