/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimoreir <mimoreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:39:35 by mimoreir          #+#    #+#             */
/*   Updated: 2023/04/27 17:41:14 by mimoreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**copymap(t_gamestate *game)
{
	char	**copy;
	int		i;

	i = 0;
	copy = malloc(sizeof(char *) * (game->y + 1));
	if (!copy)
		return (NULL);
	while (game->map[i])
	{
		copy[i] = ft_strdup(game->map[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	player_path(t_gamestate *game, char **cmap, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->x || y >= game->y)
		return ;
	if (cmap[y][x] == '1')
		return ;
	if (cmap[y][x] == 'E')
		game->n_exits--;
	if (cmap[y][x] == 'C')
		game->n_col--;
	cmap[y][x] = '1';
	player_path(game, cmap, x + 1, y);
	player_path(game, cmap, x - 1, y);
	player_path(game, cmap, x, y + 1);
	player_path(game, cmap, x, y - 1);
}

int	validate_player_path(t_gamestate *game)
{
	char	**cmap;

	cmap = copymap(game);
	player_path(game, cmap, game->player_pos.x, game->player_pos.y);
	if (game->n_col == 0 && game->n_exits == 0)
	{
		check_map(game);
		free_map(cmap);
		return (1);
	}
	free_map(cmap);
	return (0);
}
