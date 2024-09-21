/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

For a C++ project simply rename the file to .cpp and re-run the build script 

-- Copyright (c) 2020-2024 Jeffery Myers
--
--This software is provided "as-is", without any express or implied warranty. In no event 
--will the authors be held liable for any damages arising from the use of this software.

--Permission is granted to anyone to use this software for any purpose, including commercial 
--applications, and to alter it and redistribute it freely, subject to the following restrictions:

--  1. The origin of this software must not be misrepresented; you must not claim that you 
--  wrote the original software. If you use this software in a product, an acknowledgment 
--  in the product documentation would be appreciated but is not required.
--
--  2. Altered source versions must be plainly marked as such, and must not be misrepresented
--  as being the original software.
--
--  3. This notice may not be removed or altered from any source distribution.

*/

#include "raylib.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir


const uint8_t alphabet[][8] = {\
	{ 0x7C, 0x82, 0x82, 0xFE, 0x82, 0x82, 0x82, 0x00},
	{ 0xFC, 0x82, 0x82, 0xFC, 0x82, 0x82, 0xFC, 0x00},
	{ 0x7E, 0x80, 0x80, 0x80, 0x80, 0x80, 0x7E, 0x00},
	{ 0xFC, 0x82, 0x82, 0x82, 0x82, 0x82, 0xFC, 0x00},
	{ 0xFE, 0x80, 0x80, 0xFC, 0x80, 0x80, 0xFE, 0x00},
	{ 0xFE, 0x80, 0x80, 0xFC, 0x80, 0x80, 0x80, 0x00},
	{ 0x7E, 0x80, 0x80, 0x8E, 0x82, 0x82, 0x7E, 0x00},
	{ 0x82, 0x82, 0x82, 0xFE, 0x82, 0x82, 0x82, 0x00},
	{ 0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x00},
	{ 0x3E, 0x08, 0x08, 0x08, 0x88, 0x88, 0x70, 0x00},
	{ 0x82, 0x84, 0x88, 0xF0, 0x88, 0x84, 0x82, 0x00},
	{ 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xFE, 0x00},
	{ 0x82, 0xC6, 0xAA, 0x92, 0x82, 0x82, 0x82, 0x00},
	{ 0x82, 0xC2, 0xA2, 0x92, 0x8A, 0x86, 0x82, 0x00},
	{ 0x7C, 0x82, 0x82, 0x82, 0x82, 0x82, 0x7C, 0x00},
	{ 0xFC, 0x82, 0x82, 0xFC, 0x80, 0x80, 0x80, 0x00},
	{ 0x7C, 0x82, 0x82, 0x82, 0x92, 0x8A, 0x7C, 0x00},
	{ 0xFC, 0x82, 0x82, 0xFC, 0x88, 0x84, 0x82, 0x00},
	{ 0x7E, 0x80, 0x80, 0x7C, 0x02, 0x02, 0xFC, 0x00},
	{ 0xFE, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00},
	{ 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x7C, 0x00},
	{ 0x82, 0x82, 0x82, 0x44, 0x44, 0x28, 0x10, 0x00},
	{ 0x82, 0x82, 0x82, 0x92, 0xAA, 0xC6, 0x82, 0x00},
	{ 0x82, 0x44, 0x28, 0x10, 0x28, 0x44, 0x82, 0x00},
	{ 0x82, 0x44, 0x28, 0x10, 0x10, 0x10, 0x10, 0x00},
	{ 0xFE, 0x02, 0x04, 0x08, 0x10, 0x20, 0xFE, 0x00},
	{ 0x18, 0x38, 0x58, 0x18, 0x18, 0x18, 0x7E, 0x00}, //Numbers from 1 - 9
	{ 0x7C, 0x82, 0x02, 0x1C, 0x30, 0x40, 0xFE, 0x00},
	{ 0x7C, 0x82, 0x02, 0x3C, 0x02, 0x82, 0x7C, 0x00},
	{ 0x1C, 0x2C, 0x4C, 0x8C, 0xFE, 0x0C, 0x0C, 0x00},
	{ 0xFE, 0x80, 0xFC, 0x02, 0x02, 0x82, 0x7C, 0x00},
	{ 0x3C, 0x40, 0x80, 0xFC, 0x82, 0x82, 0x7C, 0x00},
	{ 0xFE, 0x82, 0x04, 0x08, 0x10, 0x20, 0x40, 0x00},
	{ 0x7C, 0x82, 0x82, 0x7C, 0x82, 0x82, 0x7C, 0x00},
	{ 0x7C, 0x82, 0x82, 0x7E, 0x02, 0x04, 0x78, 0x00},
	{ 0x7C, 0x82, 0x82, 0x82, 0x82, 0x82, 0x7C, 0x00},
};

typedef struct {
    int x;
    int y;
} Point;

typedef struct{
	uint8_t row_state;
	uint8_t col_state;
}matrix_state;

Point** generate_Matrix_pos(int start_pointX, int start_pointY, int space, int matrix_size){

	Point** matrix = (Point**)malloc(sizeof(Point*)*matrix_size);
	for(int i = 0; i < matrix_size; i++){
		matrix[i] = (Point*)malloc(sizeof(Point)*matrix_size);
	}

	for(int row = 0; row < matrix_size; row++){
		for(int col = 0; col < matrix_size; col++){
			matrix[row][col].x = (col*space) + start_pointX;
			matrix[row][col].y = (row*space) + start_pointY;
		}
	}

	return matrix;
}

void freeMatrix(Point** matrix, int size){
	for (int i = 0; i < size; i++)
        free(matrix[i]);
    free(matrix);
}

void clearMatrixScreen(Point** matrix, int mat_size, int radius){
	//Drawing gray circles
	BeginDrawing();
	ClearBackground(RAYWHITE);
	for(int row = 0; row < mat_size; row++){
		for(int col = 0; col < mat_size; col++){
			DrawCircle(matrix[row][col].x , matrix[row][col].y, radius, GRAY );
		}
	}
	EndDrawing();
}

void DisplayMsgMatrix(Point** my_matrix, int matrix_size, int radius, char* message, int msg_size){

		//Render routine for letters and numbers, from top to bottom
		//ClearBackground(RAYWHITE);
		for(int letter = 0; letter < msg_size; letter++){
			clearMatrixScreen(my_matrix, matrix_size, radius);
			for(int row_index = 0; row_index < matrix_size; row_index++){
				BeginDrawing();
				for(int col = 0; col < matrix_size; col++){
					if( (alphabet[ message[letter] - 97 ][row_index] >> (7-col) & 1) == 1  )
						DrawCircle(my_matrix[row_index][col].x , my_matrix[row_index][col].y, radius, RED );
				}
				EndDrawing();
				//sleep(1);
			}
			sleep(1);
			// letter++;
			// letter%=msg_size;
			// letter%=36;
		}
}

void ShiftMsgMatrix(Point** my_matrix, int matrix_size, int radius, char* message, int msg_size, int space){

		uint16_t letter_shifted = 0;
		uint16_t shift_size = msg_size*matrix_size + 2*matrix_size;
		//uint16_t shift_size = msg_size*matrix_size + 2*matrix_size + (msg_size-1)*space;
		int index4letter = 0;
		int tmp = 0;

		// for(int letter = 0; letter < msg_size; letter++){
			for(int index_shift = 0; index_shift < shift_size; index_shift++){
				index4letter = index_shift/matrix_size;
				clearMatrixScreen(my_matrix, matrix_size, radius);
				tmp = index_shift%8;//1-16
				printf("ShiftIndex=%d Index4letter=%d tmp=%d\n", index_shift, index4letter,tmp);

				for(int row_index = 0; row_index < matrix_size; row_index++){
					//condition from right to center
					if( index_shift <8 ){
						// letter_shifted = (uint16_t)alphabet[ message[index4letter] - 97 ][row_index] >> (8-index_shift);
						letter_shifted = (uint16_t)alphabet[ message[index4letter] - 97 ][row_index] << (tmp);
					}
					else{
						// if(tmp == 0)
							// letter_shifted = (uint16_t)(alphabet[ message[index4letter-1] - 97 ][row_index]) << tmp || (uint16_t)alphabet[ message[index4letter] - 97 ][row_index];
						letter_shifted = (uint16_t)alphabet[ message[index4letter-1] - 97 ][row_index] << (tmp) || (uint16_t)alphabet[ message[index4letter] - 97 ][row_index];
					}

					BeginDrawing();
					for(int col = 0; col < matrix_size; col++){
						// if( (alphabet[ message[letter] - 97 ][row_index] >> (7-col) & 1) == 1  )
						if( ( letter_shifted >> (15-col) & 1) == 1  )
							DrawCircle(my_matrix[row_index][col].x , my_matrix[row_index][col].y, radius, RED );
					}
					EndDrawing();
				}
				sleep(1);
			}
			sleep(1);
		// }
}

void ShiftMsgMatrixByletter(Point** my_matrix, int matrix_size, int radius, char* message, int msg_size){
		uint16_t letter_shifted = 0;

		for(int letter = 0; letter < msg_size; letter++){
			for(int index_shift = 0; index_shift < 16; index_shift++){

				clearMatrixScreen(my_matrix, matrix_size, radius);

				for(int row_index = 0; row_index < matrix_size; row_index++){
					//condition from right to center
					if( index_shift <=8 )
						letter_shifted = (uint16_t)alphabet[ message[letter] - 97 ][row_index] >> (8-index_shift);
					else
						letter_shifted = (uint16_t)alphabet[ message[letter] - 97 ][row_index] << (index_shift-8);

					BeginDrawing();
					for(int col = 0; col < matrix_size; col++){
						// if( (alphabet[ message[letter] - 97 ][row_index] >> (7-col) & 1) == 1  )
						if( ( letter_shifted >> (7-col) & 1) == 1  )
							DrawCircle(my_matrix[row_index][col].x , my_matrix[row_index][col].y, radius, RED );
					}
					EndDrawing();
					//sleep(1);
				}
			}
			sleep(1);
		}
}

int main(int argc, char** argv)
{
	// // Tell the window to use vysnc and work on high DPI displays
	// SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// // Create the window and OpenGL context
	// InitWindow(1280, 800, "Hello Raylib");

	// // Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	// SearchAndSetResourceDir("resources");

	// // Load a texture from the resources directory
	// Texture wabbit = LoadTexture("wabbit_alpha.png");
	
	// // game loop
	// while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	// {
	// 	// drawing
	// 	BeginDrawing();

	// 	// Setup the backbuffer for drawing (clear color and depth buffers)
	// 	ClearBackground(BLACK);

	// 	// draw some text using the default font
	// 	DrawText("Hello Raylib", 200,200,20,WHITE);

	// 	// draw our texture to the screen
	// 	DrawTexture(wabbit, 400, 200, WHITE);
		
	// 	// end the frame and get ready for the next one  (display frame, poll input, etc...)
	// 	EndDrawing();
	// }

	// // cleanup
	// // unload our texture so it can be cleaned up
	// UnloadTexture(wabbit);

	// // destory the window and cleanup the OpenGL context
	// CloseWindow();

	char* my_message = *(argv+1);
	int my_msg_size = 0;

	while( *(my_message+my_msg_size) != '\0' )
		my_msg_size++;

	printf("The input message is %s and its size is %d", my_message, my_msg_size);
	
	const int screenWidth = 800;
    const int screenHeight = 450;
	const int matrix_size = 8;
	const int row_size = 8, col_size = 8;

	const int start_pointX = 30;
	const int start_pointY = 30;
	const int space = 50;
	const float radius = 20.0;

  	struct timespec ts;
	int milliseconds = 900;
    ts.tv_sec = 0;
    ts.tv_nsec = milliseconds * 1000 * 1000;	

    InitWindow(screenWidth, screenHeight, "Basic window");
    SetTargetFPS(60);

	Point** my_matrix = generate_Matrix_pos( (screenWidth - (8*space - 2*radius))/2,  (screenHeight - (8*space - 2*radius))/2, space, 8);
	// matrix_state my_matrix_sta;
	// my_matrix_sta.row_state = 0x00; 
	// my_matrix_sta.col_state = 0xFF;
	


    while(!WindowShouldClose()){

		//DisplayMsgMatrix(my_matrix, matrix_size, radius, my_message, my_msg_size);
		// ShiftMsgMatrixByLetter(my_matrix, matrix_size, radius, my_message, my_msg_size);
		ShiftMsgMatrix(my_matrix, matrix_size, radius, my_message, my_msg_size, 3);
		
    }

	freeMatrix(my_matrix,8);
    CloseWindow();


	return 0;
}