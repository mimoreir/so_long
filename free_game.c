/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimoreir <mimoreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:18:06 by mimoreir          #+#    #+#             */
/*   Updated: 2023/05/06 15:50:48 by mimoreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_images(t_gamestate *game)
{
	if (game->img != NULL)
	{
		mlx_destroy_image(game->mlx, game->img->col);
		mlx_destroy_image(game->mlx, game->img->player);
		mlx_destroy_image(game->mlx, game->img->exit_closed);
		mlx_destroy_image(game->mlx, game->img->exit_open);
		mlx_destroy_image(game->mlx, game->img->floor);
		mlx_destroy_image(game->mlx, game->img->wall);
		mlx_destroy_image(game->mlx, game->img->player_exit);
		free(game->img);
	}
}

void	free_game(t_gamestate *game)
{
	char	*it;
	int		i;

	i = 0;
	if (game->map != NULL)
	{
		it = game->map[0];
		while (game->map[i])
		{
			i++;
			free(it);
			it = game->map[i];
		}
	}
	free_images(game);
	if (game->mlx && game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
	}
	if (game->mlx)
		free(game->mlx);
	if (game->map)
		free(game->map);
	free(game);
}

void	free_map(char **map)
{
	char	*it;
	int		i;

	i = 0;
	it = map[0];
	while (map[i])
	{
		i++;
		free(it);
		it = map[i];
	}
	free(map);
}

void	win_and_destroy(t_gamestate *game, int px, int py)
{
	game->map[game->player_pos.y][game->player_pos.x] = '0';
	game->map[py][px] = 'P';
	draw_map(game);
	ft_printf("Movements: %d\nYOU WIN!!!\n", game->moves);
	close_window(game);
}

int	check_empty(char **map)
{
	int	i;

	i = 0;
	if (map[0] == NULL || map == NULL)
		return (0);
	while (map[i])
	{
		if (map[i] == NULL)
			return (0);
		i++;
	}
	return (1);
}
