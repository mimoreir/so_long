/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimoreir <mimoreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:18:08 by mimoreir          #+#    #+#             */
/*   Updated: 2023/04/25 16:18:08 by mimoreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"

# define Z 122
# define W 119
# define ARROW_UP 65362
# define S 115
# define ARROW_DOWN 65364
# define Q 113
# define A 97
# define ARROW_LEFT 65361
# define D 100
# define ARROW_RIGHT 65363
# define ESC 65307

# define WIDTH 60
# define HEIGHT 60

typedef struct s_position
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_textures
{
	char	*wall;
	char	*player;
	char	*col;
	char	*exit_closed;
	char	*exit_open;
	char	*player_exit;
	char	*floor;
}	t_textures;

typedef struct s_gamestate
{
	void		*mlx;
	void		*win;
	char		**map;
	int			n_col;
	int			n_exits;
	int			n_player;
	int			moves;
	int			x;
	int			y;
	t_pos		player_pos;
	t_textures	*img;
}	t_gamestate;

t_gamestate	*init_game(void);
int			validate_extension(char const *str);
int			validate_map(t_gamestate *game);
char		**read_map(int fd);
void		free_images(t_gamestate *game);
void		free_game(t_gamestate *game);
void		free_map(char **map);
int			verify_len(t_gamestate *game);
int			verify_borders(t_gamestate *game);
int			check_first_last_row(char *str);
void		player_position(t_gamestate *game);
int			check_map(t_gamestate *game);
int			validate_map_items(t_gamestate *game);
int			validate_player_path(t_gamestate *game);
char		**copymap(t_gamestate *game);
void		so_long(t_gamestate *game);
int			init_win(t_gamestate *game);
int			handle_event(int key, t_gamestate *game);
int			close_window(t_gamestate *game);
void		draw_map(t_gamestate *game);
void		win_and_destroy(t_gamestate *game, int px, int py);
void		move_player_exit(int xm, int ym, t_gamestate *game);
int			valid_move(t_gamestate *game, int xm, int ym);
void		move_player(int xm, int ym, t_gamestate *game);
int			check_empty(char **map);

#endif
