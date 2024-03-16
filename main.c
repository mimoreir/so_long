/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimoreir <mimoreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:17:59 by mimoreir          #+#    #+#             */
/*   Updated: 2023/04/25 16:17:59 by mimoreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_gamestate	*init_game(void)
{
	t_gamestate	*game;

	game = malloc(sizeof(t_gamestate));
	game->mlx = NULL;
	game->win = NULL;
	game->map = NULL;
	game->n_col = 0;
	game->n_exits = 0;
	game->n_player = 0;
	game->player_pos.x = 0;
	game->player_pos.y = 0;
	game->moves = 0;
	game->x = 0;
	game->y = 0;
	game->img = NULL;
	return (game);
}

static int	open_read(t_gamestate *game, char const *map_file)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	game->map = read_map(fd);
	return (fd);
}

int	main(int argc, char const *argv[])
{
	t_gamestate	*game;
	int			fd;

	game = init_game();
	if (argc == 2)
	{
		if (validate_extension(argv[1]))
		{
			fd = open_read(game, argv[1]);
			if (fd > 0)
			{
				close(fd);
				if (validate_map(game))
					so_long(game);
				else
					ft_printf("Error\nMap invalid\n");
			}
		}
		else
			ft_printf("Error\nMap extension error\n");
	}
	else
		ft_printf("Error\nNumber of arguments invalid\n");
	free_game(game);
	return (0);
}
