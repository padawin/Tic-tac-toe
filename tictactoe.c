#include <stdio.h>

/*
Grid layout:

876
543
210

*/

#define UNKNOWN_VALUE -1
#define ALREADY_USED_CASE -2
#define NO_WINNER -3
#define CONTINUE 0
#define WINNING_PLAY 1

int _play(int c, int *player, int board);
void display(int p1, int p2);

int winpatterns[8] = {
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
	int p1=0b000000000;
	int p2=0b000000000;
	int result;

	int* winner = NULL;
	int* turn=&p1;
	int* other=&p2;
	int* tmp;
	char c;

	do {
		scanf("%c", &c);
		if (c < '0' || c > '8')
			continue;

		c = c - '0';
		result = _play(c, turn, *turn | *other);

		if (result == UNKNOWN_VALUE || result == ALREADY_USED_CASE)
			continue;
		else if (result == NO_WINNER) {
			printf("Draw\n");
			return result;
		}
		else if (result == WINNING_PLAY)
			winner = turn;

		tmp = turn;
		turn = other;
		other = tmp;

		display(p1, p2);

	} while (winner == NULL && (c >= '0' || c <= '8'));

	if (*winner == p1)
		printf("Winner is p1\n");
	else if(*winner == p2)
		printf("Winner is p2\n");

	return 1;
}

/**
 * Game engine
 */
int _play(int c, int *player, int board)
{
	int playedcase;
	extern int winpatterns[8];

	if (c < 0 || c > 8)
		return UNKNOWN_VALUE;

	playedcase = 1 << c;
	if ((playedcase | board) == board)
		return ALREADY_USED_CASE;

	*player = *player | playedcase;

	int i;
	for (i = 0; i < 8 && (winpatterns[i] & *player) != winpatterns[i]; i++);

	if (i < 8)
		return WINNING_PLAY;
	else if (~(board | playedcase) == (~0 << 9))
		return NO_WINNER;

	return CONTINUE;
}

/**
 * Display the grid
 */
void display(int p1, int p2)
{
	int disp;

	disp = 0b100000000;
	while (disp > 0) {
		if ((disp & p1) == disp)
			printf("X");
		else if ((disp & p2) == disp)
			printf("O");
		else
			printf(".");

		if ((disp & 0b001001001) == disp)
			printf("\n");
		disp = disp >> 1;
	}
}
