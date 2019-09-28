/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 12:00:47 by ezalos            #+#    #+#             */
/*   Updated: 2019/09/28 02:52:36 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int		is_game_finished(t_connect *c_four)
{
	// DEBUG_FUNC;
	int		r_v;

	if (c_four->turn < 7)
		r_v = FAILURE;
	else if (c_four->turn >= ROWS_NB * COLS_NB)
		r_v = SUCCESS;
	else
		r_v = is_game_won(c_four);
	if (r_v == SUCCESS)
	{
		c_four->end = SUCCESS;
		c_four->turn--;
	}
	return (r_v);
}

int		play_move(t_connect *c_four, int move)
{
	// DEBUG_FUNC;
	int		row;
	int		col;
	int		r_v;

	r_v = FAILURE;
	col = move;
	// ft_printf("col: (col)%d\n", col);
	if (col >= 0 && col < COLS_NB)
	{
		row = c_four->pile_size[col];
		// ft_printf("Pile size (row): %d\n", row);
		if (row < ROWS_NB)
		{
			// ft_printf("PILE (col + 1)%d\tHEIGHT (r/ow)%d\n", col + 1, row);
			c_four->board[ROWS_NB - (row + 1)][col] = PLAYER_TURN(c_four);
			c_four->turn++;
			// print_board(c_four);
			c_four->last_move = col;

			c_four->pile_size[col]++;

			r_v = SUCCESS;
		}
	}
	return (r_v);
}

//wins_son is doubled to allow storage of 1/2 for draws
//n_dad number of visits of parent node, n_son for child node being considered;
double	UCB1(int n_dad, int n_son, int wins_son)
{
	if (n_son == 0)
		return (1000000000000.0);
	return ((double)wins_son / (2 * n_son) + C_EXPLO * (sqrt(log(n_dad) / n_son))); //n_dad should be > 0 because n_son is > 0
}

void	play(t_connect *c_four)
{
	// DEBUG_FUNC;
	if (c_four->player_type[c_four->turn % 2] == HUMAN)
		get_input(c_four);
	else
		while (play_move(c_four, rand() % 7) == FAILURE);

}

int		engine(t_connect *c_four)
{
	init_new_game(c_four);
	// print_board(c_four);
	while (is_game_finished(c_four) == FAILURE)
	{
		// DEBUG_COLOR;
		play(c_four);
		// print_board(c_four);
	}
	print_board(c_four);
	return (c_four->winner);
}
