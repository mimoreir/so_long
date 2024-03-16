/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimoreir <mimoreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:38:14 by mimoreir          #+#    #+#             */
/*   Updated: 2023/05/06 15:01:46 by mimoreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	valid_move(t_gamestate *game, int xm, int ym)
{
	int	px;
	int	py;

	px = game->player_pos.x + xm;
	py = game->player_pos.y + ym;
	if (px > 0 && py > 0)
		if (px < game->x && py < game->y)
			if (game->map[py][px] != '1')
				return (1);
	return (0);
}

void	move_player_exit(int xm, int ym, t_gamestate *game)
{
	int	px;
	int	py;

	px = game->player_pos.x + xm;
	py = game->player_pos.y + ym;
	game->moves++;
	if (game->map[py][px] == 'E' && game->n_col == 0)
		win_and_destroy(game, px, py);
	if (game->map[py][px] == 'E')
	{
		game->map[game->player_pos.y][game->player_pos.x] = '0';
		game->map[py][px] = 'F';
	}
	if (game->map[game->player_pos.y][game->player_pos.x] == 'F')
	{
		if (game->map[py][px] == 'C')
				game->n_col--;
		game->map[game->player_pos.y][game->player_pos.x] = 'E';
		game->map[py][px] = 'P';
	}
}

void	move_player(int xm, int ym, t_gamestate *game)
{
	int	px;
	int	py;

	px = game->player_pos.x + xm;
	py = game->player_pos.y + ym;
	if (valid_move(game, xm, ym))
	{
		if (game->map[py][px] == 'E'
		|| game->map[game->player_pos.y][game->player_pos.x] == 'F')
			move_player_exit(xm, ym, game);
		else
		{
			if (game->map[py][px] == 'C')
				game->n_col--;
			game->map[game->player_pos.y][game->player_pos.x] = '0';
			game->map[py][px] = 'P';
			game->moves++;
		}
		game->player_pos.x = px;
		game->player_pos.y = py;
		ft_printf("Movements: %d\n", game->moves);
		draw_map(game);
	}
}

int	handle_event(int key, t_gamestate *game)
{
	(void)game;
	if (key == ESC)
		close_window(game);
	if (key == W || key == ARROW_UP)
		move_player(0, -1, game);
	if (key == D || key == ARROW_RIGHT)
		move_player(1, 0, game);
	if (key == S || key == ARROW_DOWN)
		move_player(0, +1, game);
	if (key == A || key == ARROW_LEFT)
		move_player(-1, 0, game);
	return (1);
}

int	close_window(t_gamestate *game)
{
	free_game(game);
	exit(EXIT_SUCCESS);
}
