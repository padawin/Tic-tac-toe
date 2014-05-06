#include <stdio.h>

/*
Grid layout:

8|7|6
-+-+-
5|4|3
-+-+-
2|1|0

*/

// Return states of played actions
#define UNKNOWN_VALUE -1
#define ALREADY_USED_CASE -2
#define CONTINUE 0
#define WINNING_PLAY 1
#define NO_WINNER 2

int _play(int c, int *player, int board);
void display(int p1, int p2);

// All the possible combinations to win the game
int winpatterns[] = {
	0b000000111,
	0b000111000,
	0b111000000,
	0b001001001,
	0b010010010,
	0b100100100,
	0b100010001,
	0b001010100
};

int main()
{
	// Each player is a 9-bytes integer representing the played cells
	// If a byte is at 1, it means the corresponding cell was played by the
	// Player
	// A same byte cannot be set to 1 for both players
	int p1=0b000000000;
	int p2=0b000000000;

	int result;

	// The winner is a pointer to a player
	int* winner = NULL;

	// Current turn's player
	int* turn=&p1;
	// Other player
	int* other=&p2;
	// Used for permut operation when swapping players in a new turn
	int* tmp;
	// Typed case
	char c;

	do {
		scanf("%c", &c);

		// Cast the typed char into an integer
		c = c - '0';
		// Call the engine
		result = _play(c, turn, *turn | *other);
		// Display only if the choice is correct
		if (result >= 0)
			display(p1, p2);

		// Result interpretation
		if (result == UNKNOWN_VALUE || result == ALREADY_USED_CASE)
			continue;
		else if (result == NO_WINNER) {
			printf("Draw\n");
			return result;
		}
		else if (result == WINNING_PLAY)
			winner = turn;

		// Switch the players for next turn
		tmp = turn;
		turn = other;
		other = tmp;
	} while (winner == NULL);

	// Tells who is the winner
	// @TODO Simplify this
	if (*winner == p1)
		printf("Winner is p1\n");
	else if (*winner == p2)
		printf("Winner is p2\n");

	return 1;
}

/**
 * Game engine
 *
 * @param c int Played case index
 * @param player int* Player who played this turn
 * @param board int Integer containing all the played cases
 *
 * @return int A result code < 0 if an error occured, >= 0 if everything's ok.
 */
int _play(int c, int *player, int board)
{
	int playedcase;
	extern int winpatterns[8];

	// The value must be an int between 0 and 8
	if (c < 0 || c > 8)
		return UNKNOWN_VALUE;

	// Initialize the played cell corresponding byte in an integer
	// Example: If the played cell is the 4 (middle column, middle line),
	// played cell will be equal to 0b000010000
	playedcase = 1 << c;
	// The played cell must not already be in the board
	if ((board | playedcase) == board)
		return ALREADY_USED_CASE;

	// Add the played cell to the player
	*player = *player | playedcase;

	// Checks if the board if full
	if (~(board | playedcase) == (~0 << 9))
		return NO_WINNER;

	// Checks if player matches a winpatterns to know if the player just won
	// the game.
	int i;
	int size = sizeof(winpatterns)/sizeof(int);
	for (i = 0; i < size && (winpatterns[i] & *player) != winpatterns[i]; i++);

	if (i < size)
		return WINNING_PLAY;

	return CONTINUE;
}

/**
 * Display the grid
 *
 * @param p1 int Player 1 game
 * @param 2 int Player 2 game
 */
void display(int p1, int p2)
{
	int disp;

	// Integer use to loop in the player games
	disp = 0b100000000;
	while (disp > 0) {
		if ((disp & p1) == disp)
			printf("X");
		else if ((disp & p2) == disp)
			printf("O");
		else
			printf(" ");

		// Every 3 cell, display a carriage return
		if ((disp & 0b001001001) == disp) {
			printf("\n");
			if ((disp & 0b001001000) == disp)
				printf("-+-+-\n");
		}
		else
			printf("|");
		disp = disp >> 1;
	}
	printf("\n");
}
