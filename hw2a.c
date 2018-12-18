#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define SIZE 24

/*global metavlites */
char game_board[SIZE][SIZE];
char displayed_board[SIZE][SIZE];

/* Ektupwsh menu epilogwn */
char menu() {
	
	char level;
	
	printf("\nChoose difficulty level:\nEASY (E/e)\nMEDIUM (M/m)\nEXPERT (X/x)\n==> ");
	scanf(" %c", &level);

	while(!(((level == 'E') || (level == 'e')) || ((level == 'M') || (level == 'm')) || ((level == 'X') || (level == 'x')))) {
		printf("\nChoose difficulty level:\nEASY (E/e)\nMEDIUM (M/m)\nEXPERT (X/x)\n==> ");
		scanf(" %c", &level);
	}
	
	printf("\n#\n");
	return(level);                                           
}

int level_selection(char level) {
	
	int row_and_col_num;
	
	if((level == 'e') || (level == 'E')) {
		row_and_col_num = (SIZE / 4);
	}
	else if ((level == 'M') || (level == 'm')) 
		row_and_col_num = (SIZE / 2);

	else
		row_and_col_num = (SIZE);
	
	return(row_and_col_num);
}

/* Arxikopoihsh pinakwn displayed_board kai game_board */
int initialization(char level, long unsigned int seed_number) {
	
	int row, col, result, random_row, random_col, i, num_row_col; // i: metrhths gia thn for
	double number_of_mines;
	const double TWENTY_PERCENT = 0.2;
	
	num_row_col = level_selection(level);

	for(row = 0; row < num_row_col; row++) {
		for(col = 0; col < num_row_col; col++) {
			displayed_board[row][col] = '-';
		}
	}
	
	for(row = 0; row < num_row_col; row++) {
		for(col = 0; col < num_row_col; col++) {
			game_board[row][col] = '-'; // Arxikopoihsh pinaka oste na mhn periexei kamia pliroforia
		}
	}
	
	if(seed_number == 0)
		srand(time(NULL));
	
	else // an to seed_number > 0
		srand(seed_number);
	
	number_of_mines = (num_row_col * num_row_col) * TWENTY_PERCENT;
	result = trunc(number_of_mines); // Ypologizei to 20% twn narkwn
	
	for(i = 0; i <= result; i++) {
		random_row = rand() % (num_row_col - 1);
		random_col = rand() % (num_row_col - 1);
		game_board[random_row][random_col] = '*';
	}
	return(result);
}

/*sxediash tou kamva */
int canvas_designing(char level, long unsigned int seed_number) {
		
	int i, row, col, num_row_col; // opou i metrhths gia thn for
	
	initialization(level, seed_number);
	num_row_col = level_selection(level);

	printf("\n");
	printf("  ");
	
	for(i = 1; i <= num_row_col; i++)
		printf("%4d", i);
	printf("\n\n");

	for(row = 0; row < num_row_col; row++) {
		printf("%2d", row + 1);	
		
		for(col = 0; col < num_row_col; col++) {
			printf("%4c", displayed_board[row][col]);
		}
		printf("\n");
	}
	return(0);
}

int finding_mines(char level) {
	
	int row, col, i, j, mines = 0, num_row_col;
	
	num_row_col = level_selection(level);
	
	for(row = 0; row < num_row_col; row++) {
		for(col = 0; col < num_row_col - 1; col++) {
			if(game_board[row][col] != '*') {
				for(i = -1; i <= 1; i++) {
					for(j = -1; j <= 1; j++) {
						if(game_board[row + i][col + j] == '*')
							mines++;
					}
				}
				
				game_board[row][col] = mines + '0';
				mines = 0;
			}
		}
	}
	
	col = num_row_col - 1; // elegxos ths teleftaias sthlhs ksexwrista
	for(row = 0; row < num_row_col; row++) {
		if(game_board[row][col] != '*') {
			for(i = -1; i <= 1; i++) {
					for(j = -1; j < 1; j++) {
						if(game_board[row + i][col + j] == '*')
							mines++;
					}
			}
			
			game_board[row][col] = mines + '0';
			mines = 0;
		}
	}
	return(0);
}

int solution(char level) {
	
	int row, col, i, num_row_col;

	finding_mines(level);
	num_row_col = level_selection(level);

	printf("\n");
	printf("  ");
	
	for(i = 1; i <= num_row_col; i++)
		printf("%4d", i);
	printf("\n\n");

	for(row = 0; row < num_row_col; row++) {
		printf("%2d", row + 1);	
		for(col = 0; col < num_row_col; col++) {
			printf("%4c", game_board[row][col]);
		}
		printf("\n");
	}
	return(0);
}

/* Epilogh grammhs kai sthlhs apo ton xrhsth. Tsekarei an oi times pou eisagei einai valid kai ektupwnei ta analoga mhnumata */
int row_and_col_selection(char level, long unsigned int seed_number) { 
	
	int row, col, i, grammh, sthlh, position = 0, num_of_mines, num_row_col; // opou position einai h thesh pou anoigei o xrhsths
	
	num_of_mines = initialization(level, seed_number);
	num_row_col = level_selection(level);
	
	do {
		printf("\nRow> ");
		scanf("%d", &row);
	
		if(row == 0) {
			printf("\nGame interrupted.\n");
			return(0);
		}

		while(!((row > 0) && (row <= num_row_col))){
		
			printf("\nInvalid Row. Try again!");
			printf("\n#\n");
			printf("\nRow> ");
			scanf("%d", &row);
		}
	
		printf("\nCol> ");
		scanf("%d", &col);
		
		while(!((col > 0) && (col <= num_row_col))){
		
			printf("\nInvalid Col. Try again!");
			printf("\n#\n");
			printf("\nCol> ");
			scanf("%d", &col);
		}
		
		finding_mines(level);

		displayed_board[row - 1][col - 1] = game_board[row - 1][col - 1];
		
		printf("\n");
		printf("  ");
	
		for(i = 1; i <= num_row_col; i++)
			printf("%4d", i);
		printf("\n\n");

		for(grammh = 0; grammh < num_row_col; grammh++) {
			printf("%2d", grammh + 1);	
			for(sthlh = 0; sthlh < num_row_col; sthlh++) {
				printf("%4c", displayed_board[grammh][sthlh]);
			}
			printf("\n");
		}
		position++;
		
		if(position == (num_row_col * num_row_col) - num_of_mines) {
			printf("\nCongratulations!\n");
			solution(level);
			return(0);
		}
	
	} while(game_board[row - 1][col - 1] != '*');

	printf("\nKABOOM!\n");
	solution(level);
	return(0);
}

int main(int argc, char *argv []) {
	
	char level, answer;
	long unsigned int seed_number;
	
	printf("\nSeed? ");
	scanf("%lu", &seed_number);
	do {
		
		level = menu();
		canvas_designing(level, seed_number);
		row_and_col_selection(level, seed_number);
		do {
			
			printf("\n#\n");
			printf("Play again? (y/n) ");
			scanf(" %c", &answer);

		} while(!(((answer == 'Y') || (answer == 'y')) || ((answer == 'N') || (answer == 'n'))));
	
	} while((answer == 'Y') || (answer == 'y'));
	return(0);
}
		
		
		
	
