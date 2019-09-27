/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 12:00:47 by ezalos            #+#    #+#             */
/*   Updated: 2019/09/28 00:51:40 by ezalos           ###   ########.fr       */
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
			print_board(c_four);
			c_four->last_move = col;

			c_four->pile_size[col]++;
			c_four->turn++;

			r_v = SUCCESS;
		}
	}
	return (r_v);
}

void	play(t_connect *c_four)
{
	// DEBUG_FUNC;
	if (c_four->player_type[c_four->turn % 2] == HUMAN)
		get_input(c_four);
}

int		engine(t_connect *c_four)
{
	print_board(c_four);
	while (is_game_finished(c_four) == FAILURE)
	{
		// DEBUG_COLOR;
		play(c_four);
		// print_board(c_four);
	}
	print_board(c_four);
	if (CORNER)
		ft_printf("\n\n\n\n");
	if (c_four->winner == PLAYER_ONE)
		ft_printf("%~{255;0;0}WINNER IS X%~{}\n");
	else if (c_four->winner == PLAYER_TWO)
		ft_printf("%~{255;255;0}WINNER IS O%~{}\n");
	else if (c_four->winner == PLAYER_NONE)
		ft_printf("%~{150;150;255}NO WINNER%~{}\n", c_four->winner == PLAYER_ONE ? 'X' : 'O');
	return (c_four->winner);
}
