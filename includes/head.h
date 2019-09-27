/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 13:21:20 by ldevelle          #+#    #+#             */
/*   Updated: 2019/09/28 01:16:33 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_H
# define HEAD_H


# define PLAYER_ONE				1
# define PLAYER_TWO				-1
# define PLAYER_NONE			0

# define ROWS_NB				6
# define COLS_NB				7


# define COMPUTER				0
# define HUMAN					1

# define CORNER					0

# define FAILURE				0
# define SUCCESS				1

# define UNSET					-1
# define ERROR					-1
# define VALID					0

# define PTR_ERROR				NULL

# define REFRESH_TIME			1 //0.X seconds
# define CHEAT					5 //grow size
# define PLAYER_TURN(c_four)	c_four->turn % 2 ? PLAYER_TWO : PLAYER_ONE
# define PILE_HEIGHT(c_four, move)	c_four->pile_size[move]

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>

#define BAUDRATE				B38400
#define MODEMDEVICE				"/dev/ttyS1"
#define _POSIX_SOURCE			1 /* code source conforme à POSIX */

#define FALSE					0
#define TRUE					1

# include "../../libft/includes/libft.h"
# include <sys/ioctl.h>
# include <stdio.h>

typedef int* 					t_ints;

typedef struct					s_connect
{
	char						board[ROWS_NB][COLS_NB];
	int							turn;
	int							winner;

	int							player_type[2];
	int							print;

	int							last_move;
	int							pile_size[ROWS_NB];
}								t_connect;

/*
******************************************************************************
**																			**
**								----------									**
**								PROTOTYPES									**
**								----------									**
**																			**
******************************************************************************
*/


void		init(t_connect *c_four);

void		print_board(t_connect *c_four);

int			is_valid_position(int row, int row_mod, int col, int col_mod);
int			is_horizontal_win(t_connect *c_four, int player, int row, int col);
int			is_vertical_win(t_connect *c_four, int player, int row, int col);
int			is_diagonal_pos_win(t_connect *c_four, int player, int row, int col);
int			is_diagonal_neg_win(t_connect *c_four, int player, int row, int col);
int			is_game_won(t_connect *c_four);
int 		get_input(t_connect *c_four);
int			play_move(t_connect *c_four, int move);



#endif
