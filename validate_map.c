/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimoreir <mimoreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:18:13 by mimoreir          #+#    #+#             */
/*   Updated: 2023/05/06 15:48:23 by mimoreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	validate_extension(char const *str)
{
	int	len;

	len = ft_strlen(str);
	if (ft_strnstr(str + (len - 4), ".ber", 4))
		return (1);
	else
		return (0);
}

char	**read_map(int fd)
{
	char	**map;
	char	*file_content;
	char	*line;
	char	*aux;

	file_content = ft_calloc(sizeof(char), 1);
	if (fd < 0)
	{
		ft_printf("Error\nCannot open file\n");
		free(file_content);
		return (NULL);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		aux = ft_strjoin(file_content, line);
		free(file_content);
		file_content = aux;
		free(line);
	}
	map = ft_split(file_content, '\n');
	free(file_content);
	return (map);
}

int	verify_len(t_gamestate *game)
{
	int		i;
	int		j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen(game->map[i++]);
	if (len < 3)
		return (0);
	j++;
	while (game->map[i])
	{
		if (ft_strlen(game->map[i]) != len)
			return (0);
		i++;
		j++;
	}
	if (j < 3)
		return (0);
	game->x = len;
	game->y = j;
	return (1);
}

int	verify_borders(t_gamestate *game)
{
	char	*it;
	int		i;

	i = 0;
	if (!check_first_last_row(game->map[0]))
		return (0);
	it = game->map[++i];
	while (i != (game->y - 1))
	{
		if (*it != '1')
			return (0);
		if (*(it + game->x - 1) != '1')
			return (0);
		i++;
		it = game->map[i];
	}
	if (!check_first_last_row(game->map[i]))
		return (0);
	return (1);
}

int	validate_map(t_gamestate *game)
{
	if (!check_empty(game->map))
		return (0);
	if (game->map != NULL)
	{
		if (verify_len(game))
		{
			if (verify_borders(game))
				check_map(game);
			else
				return (0);
		}
		else
			return (0);
	}
	else
		return (0);
	player_position(game);
	if (!validate_map_items(game))
		return (0);
	if (!validate_player_path(game))
		return (0);
	return (1);
}
