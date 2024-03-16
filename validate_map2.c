/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimoreir <mimoreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:54:09 by mimoreir          #+#    #+#             */
/*   Updated: 2023/04/27 16:28:22 by mimoreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	player_position(t_gamestate *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < game->y)
	{
		while (i < game->x)
		{
			if (game->map[j][i] == 'P')
				break ;
			i++;
		}
		if (game->map[j][i] == 'P')
		{
			game->player_pos.x = i;
			game->player_pos.y = j;
			break ;
		}
		i = 0;
		j++;
	}
}

int	check_map(t_gamestate *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < game->y)
	{
		while (i < game->x)
		{
			if (game->map[j][i] != 'E' && game->map[j][i] != 'C'
			&& game->map[j][i] != 'P' && game->map[j][i] != '1'
			&& game->map[j][i] != '0')
				return (0);
			if (game->map[j][i] == 'E')
				game->n_exits++;
			if (game->map[j][i] == 'C')
				game->n_col++;
			if (game->map[j][i] == 'P')
				game->n_player++;
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}

int	check_first_last_row(char *str)
{
	char	*it;

	it = str;
	while (*it)
	{
		if (*it != '1')
			return (0);
		it++;
	}
	return (1);
}

int	validate_map_items(t_gamestate *game)
{
	if (game->n_player != 1)
		return (0);
	if (game->n_col < 1)
		return (0);
	if (game->n_exits != 1)
		return (0);
	return (1);
}
