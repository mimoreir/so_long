/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimoreir <mimoreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:23:29 by mimoreir          #+#    #+#             */
/*   Updated: 2023/05/06 14:57:44 by mimoreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_win(t_gamestate *game)
{
	game->mlx = mlx_init();
	if (game->mlx == NULL)
	{
		ft_printf("Error\nCannot create MLX\n");
		free_game(game);
		return (0);
	}
	game->win = mlx_new_window(game->mlx, game->x * WIDTH, \
	game->y * HEIGHT, "so_long");
	if (game->win == NULL)
	{
		ft_printf("Error\nCannot create Window\n");
		free_game(game);
		return (0);
	}
	return (1);
}

t_textures	*setup_images(t_gamestate *game)
{
	int			imgw;
	int			imgh;
	t_textures	*img;

	img = malloc(sizeof(t_textures));
	img->player = mlx_xpm_file_to_image(game->mlx, \
	"./textures/player.xpm", &imgw, &imgh);
	img->floor = mlx_xpm_file_to_image(game->mlx, \
	"./textures/floor.xpm", &imgw, &imgh);
	img->wall = mlx_xpm_file_to_image(game->mlx, \
	"./textures/wall.xpm", &imgw, &imgh);
	img->col = mlx_xpm_file_to_image(game->mlx, \
	"./textures/col.xpm", &imgw, &imgh);
	img->exit_closed = mlx_xpm_file_to_image(game->mlx, \
	"./textures/exit_closed.xpm", &imgw, &imgh);
	img->exit_open = mlx_xpm_file_to_image(game->mlx, \
	"./textures/exit_open.xpm", &imgw, &imgh);
	img->player_exit = mlx_xpm_file_to_image(game->mlx, \
	"./textures/player_exit.xpm", &imgw, &imgh);
	return (img);
}

void	put_image(int i, int j, char img, t_gamestate *game)
{
	if (img == '1')
		mlx_put_image_to_window(game->mlx, game->win, \
		game->img->wall, i * WIDTH, j * HEIGHT);
	else if (img == 'P')
		mlx_put_image_to_window(game->mlx, game->win, \
		game->img->player, i * WIDTH, j * HEIGHT);
	else if (img == 'C')
		mlx_put_image_to_window(game->mlx, game->win, \
		game->img->col, i * WIDTH, j * HEIGHT);
	else if (img == 'E' && game->n_col == 0)
		mlx_put_image_to_window(game->mlx, game->win, \
		game->img->exit_open, i * WIDTH, j * HEIGHT);
	else if (img == 'E' && game->n_col > 0)
		mlx_put_image_to_window(game->mlx, game->win, \
		game->img->exit_closed, i * WIDTH, j * HEIGHT);
	else if (img == '0')
		mlx_put_image_to_window(game->mlx, game->win, \
		game->img->floor, i * WIDTH, j * HEIGHT);
	else if (img == 'F')
		mlx_put_image_to_window(game->mlx, game->win, \
		game->img->player_exit, i * WIDTH, j * HEIGHT);
}

void	draw_map(t_gamestate *game)
{
	int		i;
	int		j;
	char	*str;
	char	*mov;

	i = 0;
	j = 0;
	mov = ft_itoa(game->moves);
	str = ft_strjoin("Moves: ", mov);
	while (j < game->y)
	{
		while (i < game->x)
		{
			put_image(i, j, game->map[j][i], game);
			i++;
		}
		j++;
		i = 0;
	}
	mlx_string_put(game->mlx, game->win, 30, 30, 0xFF0000, str);
	free(mov);
	free(str);
}

void	so_long(t_gamestate *game)
{
	if (!init_win(game))
		return ;
	game->img = setup_images(game);
	draw_map(game);
	mlx_hook(game->win, 2, 1L << 0, handle_event, game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_loop(game->mlx);
}
