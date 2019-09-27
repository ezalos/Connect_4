/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 12:01:39 by ezalos            #+#    #+#             */
/*   Updated: 2019/09/27 23:17:36 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

void		init(t_connect *c_four)
{
	int		row;

	row = -1;
	while (++row < ROWS_NB)
		ft_memset(c_four->board[row], PLAYER_NONE, sizeof(char) * COLS_NB);
	row = -1;
	while (++row < ROWS_NB)
		ft_bzero(c_four->pile_size, sizeof(int) * COLS_NB);
	c_four->player_type[0] = HUMAN;
	c_four->player_type[1] = HUMAN;
	c_four->turn = 0;
	c_four->winner = PLAYER_NONE;
	c_four->last_move = UNSET;
	c_four->print = SUCCESS;
}
