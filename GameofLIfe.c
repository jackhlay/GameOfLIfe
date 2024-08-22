#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define WIDTH 50
#define HEIGHT 50
#define DELAY 200000  // microseconds

void print_grid(int grid[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf(grid[i][j] ? "O" : ".");
        }
        printf("\n");
    }
}

void copy_grid(int src[HEIGHT][WIDTH], int dest[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

int count_neighbors(int grid[HEIGHT][WIDTH], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int nx = x + i, ny = y + j;
            if (nx >= 0 && nx < HEIGHT && ny >= 0 && ny < WIDTH) {
                count += grid[nx][ny];
            }
        }
    }
    return count;
}

void update_grid(int grid[HEIGHT][WIDTH]) {
    int new_grid[HEIGHT][WIDTH] = {0};

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int neighbors = count_neighbors(grid, i, j);
            if (grid[i][j]) {
                if (neighbors == 2 || neighbors == 3) {
                    new_grid[i][j] = 1;
                }
            } else {
                if (neighbors == 3) {
                    new_grid[i][j] = 1;
                }
            }
        }
    }


    copy_grid(new_grid, grid);
}

int main() {
    int grid[HEIGHT][WIDTH] = {0};
    srand(time(NULL));

    //Randomly Generate a board
    for(int i=0; i<WIDTH; i++){
	    for(int j=0; j<HEIGHT;j++){
		    int  r = rand();
		    
		    if(r%2==1){
			    grid[i][j]=1;
		    }
	    }
    }


    // Or alternatively initialize a glider pattern
    //grid[1][2] = 1;
    //grid[2][3] = 1;
    //grid[3][1] = 1;
    //grid[3][2] = 1;
    //grid[3][3] = 1;

    while (1) {
        system("clear");  // clear the screen (for Linux and macOS)
        print_grid(grid);
        update_grid(grid);
        usleep(DELAY);  // delay in microseconds
    }

    return 0;
}

