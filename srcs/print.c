/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 12:00:51 by ezalos            #+#    #+#             */
/*   Updated: 2019/09/28 00:36:49 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

void	print_board(t_connect *c_four)
{
	struct winsize			w;
	int						j;
	int						i;

	if (CORNER)
	{
		ioctl(0, TIOCGWINSZ, &w);
		_C_CURSOR_SAVE;
		ft_place_cursor(2, w.ws_col - (((COLS_NB) + 2 + 1)));
	}
	if (c_four->print == FAILURE)
		return ;
	if (!c_four->turn ? c_four->turn % 2 : !(c_four->turn % 2))
		ft_printf("%~{255;255;0}O");
	else
		ft_printf("%~{255;0;0}X");
	i = -1;
	while (++i <= ROWS_NB)
	{
		if (CORNER)
			ft_place_cursor(i + 4, w.ws_col - ((COLS_NB * 2) + 2));
		else
			ft_printf("\t");
		j = -1;
		while (++j < COLS_NB)
		{
			if (i == ROWS_NB)
				ft_printf("%~{150;150;255}%d", j + 1);
			else if (c_four->board[i][j] == PLAYER_ONE)
				ft_printf("%~{255;0;0}X");
			else if (c_four->board[i][j] == PLAYER_TWO)
				ft_printf("%~{255;255;0}O");
			else
				ft_printf("%~{}.");
			ft_printf(" ");
		}
		if (!CORNER)
			ft_printf("\n");
	}
	if (CORNER)
	{
		_C_CURSOR_LOAD;
		ft_printf("%~{}");
	}
	else
		ft_printf("%~{}\n");
}