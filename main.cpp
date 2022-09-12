#include <stdio.h>
#include <unistd.h>
#include <string.h>

int SIZE = 70;

void prtscr(int screen[128][128]);

int main() {
	
	int speed = 1;
	
	int screen[128][128];
	int origin[2] = {35, 0};
	int live[][2] = {	// glider gun
		{5, 1},
		{5, 2},
		{6, 1},
		{6, 2},
		{5, 11},
		{6, 11},
		{7, 11},
		{4, 12},
		{3, 13},
		{3, 14},
		{8, 12},
		{9, 13},
		{9, 14},
		{6, 15},
		{4, 16},
		{5, 17},
		{6, 17},
		{7, 17},
		{6, 18},
		{8, 16},
		{3, 21},
		{4, 21},
		{5, 21},
		{3, 22},
		{4, 22},
		{5, 22},
		{2, 23},
		{6, 23},
		{1, 25},
		{2, 25},
		{6, 25},
		{7, 25},
		{3, 35},
		{4, 35},
		{3, 36},
		{4, 36}
	};

	for (int y = 0; y < SIZE; y++) { 	// screen init
		for (int x = 0; x < SIZE; x++) {
			screen[y][x] = 0;
		}
	}

	for (int i = 0; i < (sizeof(live) / sizeof(live[0])); i++) {
		screen[live[i][0] + origin[0]][live[i][1] + origin[1]] = 1;
		//upside down
		screen[origin[0] - live[i][0]][(origin[1] - live[i][1]) + SIZE] = 1;
	}


	int living = 1;

	while(living > 0) {

		int buffer[128][128] = {};
		living = 0;
		int neighbors;

		for (int y = 0; y < SIZE; y++) {
			for (int x = 0; x < SIZE; x++) {
				living += screen[y][x];
				neighbors = 0;
				for (int i = -1; i < 2; i++) {
					for (int j = -1; j < 2; j++) {
						if (!(i == 0 && j == 0)) {
							neighbors += screen[y + i][x + j];
						}
					}
				}
				if (screen[y][x] == 1) {
					if (neighbors == 2 || neighbors == 3) {
						buffer[y][x] = 1;
					}
				}
				else if (neighbors == 3) {
					buffer[y][x] = 1;
				}
				else {
					buffer[y][x] = 0;
				}
			}
		}
		prtscr(buffer);
		memcpy(screen, buffer, sizeof(buffer));
		usleep(1000000 / 10 / speed);
	}
}

void prtscr(int screen[128][128]) {

	int a = 29;
	while (a--) {
		printf("\n");
		}

	for (int y = 0; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++) {
			if (screen[y][x] == 0) {
				printf("  ");
			}
			else {
				printf("O ");
			}
		}
		printf("\n");
	}
	printf("zoom out\n");
}

