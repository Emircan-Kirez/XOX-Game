/* Emircan KİREZ - Ch3rry */
/* Last Update: 04/07/2022 */
/*
----------------------- INFORMATION ---------------------------
• It is recommended to read the README.md file before proceeding to the project.
• For any questions and suggestions related to the project, via the e-mail address "emircan200123@hotmail.com", you can contact me by
typing "Github | C-EN / XOX Game" to the subject line 
*/

#include <stdio.h>																											                                                        //E.K.
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

//Function Prototypes
char **createBoard();
void printBoard(char **board);
void resetBoard(char **board);
void chooseYourSign(char *userSign, char *computerSign);
char checkWhetherThereIsAWinner(char **board);
void userMove(char **board, char userSign, int *freeSpaces);
void computerMove(char **board, char computerSign, int *freeSpaces);

int main(){
	srand(time(NULL));
	char **board = createBoard();
	char userSign, computerSign, winner, response;
	int freeSpaces, i;
	
	do{
		winner = ' ';
		freeSpaces = 9;
		resetBoard(board);
		chooseYourSign(&userSign, &computerSign);
		
		printf("First Situation: \n");
		printBoard(board);
		
		//We don't need to control whether there is a winner at the end of the  first 4 moves.
		for(i = 0; i < 2; i++){
			userMove(board, userSign, &freeSpaces);
			printBoard(board);
			computerMove(board, computerSign, &freeSpaces);
			printBoard(board);
		}
		
		while(winner == ' ' && freeSpaces != 0){
			userMove(board, userSign, &freeSpaces);
			printBoard(board);
			winner = checkWhetherThereIsAWinner(board);
			if(winner == ' ' && freeSpaces != 0){
				computerMove(board, computerSign, &freeSpaces);
				printBoard(board);
				winner = checkWhetherThereIsAWinner(board);
			}
		} 
		
		if(winner == userSign){
			printf("You won\n");
		}else if(winner == computerSign){
			printf("You lost\n");
		}else{
			printf("There is no place to play. That\'s why it\'s a draw :)\n");
		}
		
		do{
			printf("\nWould you like to play again? (Y/N): ");
			scanf(" %c", &response);
			response = toupper(response);
			if(response != 'Y' && response != 'N'){
				printf("Invalid choice. Try again...");
			}
		}while(response != 'Y' && response != 'N');
		
	}while(response == 'Y');
	
	printf("Thanks for playing :)");
	return 0;
}

char **createBoard(){
	char **tmp;
	int i;
	tmp = (char **)calloc(3, sizeof(char *));
	for(i = 0; i < 3; i++){
		tmp[i] = (char *)calloc(3, sizeof(char));
	}
	return tmp;
}

void printBoard(char **board){
	int i, j;
	printf("---------------\n");
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			printf("%3c |", board[i][j]);
		}
		printf("\n---------------\n");
	}
	printf("\n");
}

void resetBoard(char **board){
	int i, j;
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			board[i][j] = ' ';
		}
	}
}

void chooseYourSign(char *userSign, char *computerSign){ //the choice of which sign the user will use
	do{
		printf("Press X to be X, press O to be O: ");
		scanf(" %c", userSign);
		
		*userSign = toupper(*userSign);
		if(*userSign != 'X' && *userSign != 'O'){
			printf("Invalid choice. Try again...\n");
		}
	}while(*userSign != 'X' && *userSign != 'O');
	
	if(*userSign == 'X'){
		*computerSign = 'O';
	}else{
		*computerSign = 'X';
	}
}

char checkWhetherThereIsAWinner(char **board){
	int i;
	
	//row control
	for(i = 0; i < 3; i++){
		if(board[i][0] == board[i][1] && board[i][0] == board[i][2]){
			return board[i][0];
		}
	}
	
	//column control
	for(i = 0; i < 3; i++){
		if(board[0][i] == board[1][i] && board[0][i] == board[2][i]){
			return board[0][i];
		}
	}
	
	//diagonal control from top left to bottom right
	if(board[0][0] == board[1][1] && board[0][0] == board[2][2]){
		return board[0][0];
	}
	
	//diagonal control from top right to bottom left
	if(board[0][2] == board[1][1] && board[0][2] == board[2][0]){
		return board[0][2];
	}
	
	return ' '; //If there are no winners
}

void userMove(char **board, char userSign, int *freeSpaces){
	int x, y;

	printf("It\'s your turn.\n");
	do{
		printf("Write the row and column numbers of the place you want to play: ");
		scanf("%d %d", &x, &y);
		
		if(board[x-1][y-1] != ' '){
			printf("The place you want to play is not empty. Please select an empty place.\n");
		}
	}while(board[x-1][y-1] != ' ');
	
	board[x-1][y-1] = userSign;
	(*freeSpaces)--;
}

void computerMove(char **board, char computerSign, int *freeSpaces){
	int x, y;
	
	do{
		x = rand() % 3;
		y = rand() % 3;
	}while(board[x][y] != ' ');
	
	board[x][y] = computerSign;
	printf("Computer moves.\n");
	(*freeSpaces)--;
}

