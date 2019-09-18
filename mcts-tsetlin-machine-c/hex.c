#include <stdio.h>
#include <stdlib.h>

#define BOARD_DIM 11

struct hex_game {
	int board[BOARD_DIM*BOARD_DIM*2];
	int open_positions[BOARD_DIM*BOARD_DIM];
	int number_of_open_positions;
};

void hg_init(struct hex_game *hg)
{
	for (int i = 0; i < BOARD_DIM*BOARD_DIM; i += BOARD_DIM) {
		for (int j = 0; j < BOARD_DIM; ++j) {
			hg->board[(i + j) * 2] = 0;
			hg->board[(i + j) * 2 + 1] = 0;
			hg->open_positions[i + j] = i + j;
		}
	}
	hg->number_of_open_positions = BOARD_DIM*BOARD_DIM;
}

// To avoid determine a winner in each and every round of the game,
// only check who won when the board is full, and then backtrack to prune redundant positions?
// Or can winner be determined fast in an incremental manner?
void hg_winner(struct hex_game *hg)
{

}

void hg_place_piece_randomly(struct hex_game *hg, int player)
{
	int random_empty_position_index = rand() % hg->number_of_open_positions;

	int empty_position = hg->open_positions[random_empty_position_index];

	//printf("P%d (%d,%d)\n", player, empty_position / BOARD_DIM, empty_position % BOARD_DIM);

	hg->board[empty_position * 2 + player] = 1;

	hg->open_positions[random_empty_position_index] = hg->open_positions[hg->number_of_open_positions-1];
	hg->number_of_open_positions--;
}

void hg_place_piece_based_on_tm_input(struct hex_game *hg, int player)
{
	printf("TM!\n");
}

static inline int hg_full_board(struct hex_game *hg)
{
	return hg->number_of_open_positions == 0;
}

int main() {
	struct hex_game hg; 

	for (int game = 0; game < 1000000; ++game) {
		hg_init(&hg);

		int player = 0;
		while (!hg_full_board(&hg)) {
			hg_place_piece_randomly(&hg, player);
			player = 1 - player;
		}
	}
}