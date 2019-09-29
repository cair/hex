#include <stdio.h>
#include <stdlib.h>

#define BOARD_DIM 11

int neighbors[] = {-(BOARD_DIM+2) + 1, -(BOARD_DIM+2), -1, 1, (BOARD_DIM+2), (BOARD_DIM+2) - 1};

struct hex_game {
	int board[(BOARD_DIM+2)*(BOARD_DIM+2)*2];
	int open_positions[BOARD_DIM*BOARD_DIM];
	int number_of_open_positions;

	int connected[(BOARD_DIM+2)*(BOARD_DIM+2)*2];
	int list[BOARD_DIM*BOARD_DIM];
	int list_size;
};

void hg_init(struct hex_game *hg)
{
	for (int i = 0; i < BOARD_DIM+2; ++i) {
		for (int j = 0; j < BOARD_DIM+2; ++j) {
			hg->board[(i*(BOARD_DIM + 2) + j) * 2] = 0;
			hg->board[(i*(BOARD_DIM + 2) + j) * 2 + 1] = 0;

			if (i > 0 && i < BOARD_DIM + 1 && j > 0 && j < BOARD_DIM + 1) {
				hg->open_positions[(i-1)*BOARD_DIM + j - 1] = i*(BOARD_DIM + 2) + j;
			}

			if (i == 0) {
				hg->connected[(i*(BOARD_DIM + 2) + j) * 2] = 1;
			} else {
				hg->connected[(i*(BOARD_DIM + 2) + j) * 2] = 0;
			}
			
			if (j == 0) {
				hg->connected[(i*(BOARD_DIM + 2) + j) * 2 + 1] = 1;
			} else {
				hg->connected[(i*(BOARD_DIM + 2) + j) * 2 + 1] = 0;
			}
		}
	}
	hg->number_of_open_positions = BOARD_DIM*BOARD_DIM;
}

int hg_winner(struct hex_game *hg, int player, int position)
{
	for (int i = 0; i < 6; ++i) {
		int neighbor = position + neighbors[i];
		if (hg->connected[neighbor*2 + player]) {
			hg->connected[position*2 + player] = 1;

			if (player == 0 && position / (BOARD_DIM + 2) == BOARD_DIM) {
				return 1;
			}

			if (player == 1 && position % (BOARD_DIM + 2) == BOARD_DIM) {
				return 1;
			}

			for (int k = 0; k < 6; ++k) {
				int neighbor = position + neighbors[k];
				if (hg->board[neighbor*2 + player] && !hg->connected[neighbor*2 + player]) {
					if (hg_winner(hg, player, neighbor)) {
						return 1;
					}
				}
			}
			break;
		}
	}
	return 0;
}

int hg_place_piece_randomly(struct hex_game *hg, int player)
{
	int random_empty_position_index = rand() % hg->number_of_open_positions;

	int empty_position = hg->open_positions[random_empty_position_index];

	hg->board[empty_position * 2 + player] = 1;

	hg->open_positions[random_empty_position_index] = hg->open_positions[hg->number_of_open_positions-1];
	hg->number_of_open_positions--;

	return empty_position;
}

void hg_place_piece_based_on_tm_input(struct hex_game *hg, int player)
{
	printf("TM!\n");
}

int hg_full_board(struct hex_game *hg)
{
	return hg->number_of_open_positions == 0;
}

void hg_print(struct hex_game *hg)
{
	for (int i = 0; i < BOARD_DIM; ++i) {
		for (int j = 0; j < i; j++) {
			printf(" ");
		}

		for (int j = 0; j < BOARD_DIM; ++j) {
			if (hg->board[((i+1)*(BOARD_DIM+2) + j + 1)*2] == 1) {
				printf(" X");
			} else if (hg->board[((i+1)*(BOARD_DIM+2) + j + 1)*2 + 1] == 1) {
				printf(" O");
			} else {
				printf(" ·");
			}
		}
		printf("\n");
	}
}

int main() {
	struct hex_game hg;

	int winner = -1;

	for (int game = 0; game < 1000000; ++game) {
		hg_init(&hg);

		int player = 0;
		while (!hg_full_board(&hg)) {
			int position = hg_place_piece_randomly(&hg, player);
			
			if (hg_winner(&hg, player, position)) {
				winner = player;
				break;
			}

			player = 1 - player;
		}
		
		if (hg.number_of_open_positions >= 80) {
			printf("\nPlayer %d wins!\n\n", winner);
			hg_print(&hg);
		}
	}
}