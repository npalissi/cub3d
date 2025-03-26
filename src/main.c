
#include "cub3d.h"

#include <stdio.h>

void close_win(int event, void *params)
{
	t_game *game;

	game = params;
	if(event == 0)
		mlx_loop_end(game->mlx);
}

void draw_map(t_game *game)
{
	int i = 0;
	int j = 0;
	while (game->map[i])
	{
		while (game->map[i][j])
		{
			if (game->map[i][j] == '1')
				draw_squar(game, j * BLOCK_SIZE, i * BLOCK_SIZE, BLOCK_SIZE);
			j++;
		}
		j = 0;
		i++;
	}
}

void get_map(t_game *game)
{
	char ** map = malloc(sizeof(char *) * 11);
	map[0] = "111111111111";
	map[1] = "100000000001";
	map[2] = "100000000001";
	map[3] = "100000000001";
	map[4] = "100000000001";
	map[5] = "100000000001";
	map[6] = "100000100001";
	map[7] = "100000000001";
	map[8] = "100000000001";
	map[9] = "100000000001";
	map[10] = "111111111111";
	map[11] = NULL;
	game->map = map;
}

bool touch(t_game *game, float x, float y)
{
	int i;
	int j;

	i = y / BLOCK_SIZE;
	j = x / BLOCK_SIZE;
	if (game->map[i][j] == '1')
		return true;
	return false;
}

void draw_line(t_game *game, float start_x, int i )
{

	float ray_x;
	float ray_y;
	float cos_angle;
	float sin_angle;

	ray_x = game->player.x;
	ray_y = game->player.y;
	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	while(!touch(game, ray_x, ray_y))
	{
		// mlx_pixel_put(game->mlx, game->win, ray_x, ray_y, (mlx_color){.rgba = 0x00FF00FF});
		ray_x += cos_angle;
		ray_y += sin_angle;
	}

	float dist = sqrt(pow(ray_x - game->player.x, 2) + pow(ray_y - game->player.y, 2));
	// float dist = (ray_x - game->player.x, ray_y - game->player.y);
	float height = (BLOCK_SIZE / dist) * (WIDTH / 2);
	int start_y = (HEIGHT - height) / 2;
	int end = start_y + height;
	while(start_y < end)
	{
		mlx_pixel_put(game->mlx, game->win, i , start_y, (mlx_color){.rgba = 0x00FF00FF});
		start_y++;
	}
}

void draw_loop(void *params)
{
	t_game *game;
	game = params;
	mlx_clear_window(game->mlx, game->win, (mlx_color){.rgba = 0x000000FF});
	float fraction;
	float start_x;
	int i;
	
	i = 0;
	fraction = PI / 3 / WIDTH;
	start_x = game->player.angle - PI / 6;
	while (i < WIDTH)
	{
		draw_line(game, start_x, i);
		start_x += fraction;
		i++;
	}
	
	pos_mouse(game);
	move_player(&game->player, game);
	// printf("x %f y %f\n", game->player.x, game->player.y);
	
	// draw_squar(game, game->player.x, game->player.y, 20);
	// draw_map(game);
}

int main(void)
{
	t_game game;

	game.str_map = recover_file(&game, "test.txt");
	// init_data(&game);
	init_player(&game.player);
	game.mouse.is_press = 0;
	mlx_mouse_get_pos(game.mlx, &game.mouse.x, &game.mouse.y);
	game.mlx = mlx_init();
	get_map(&game);
	mlx_window_create_info info = {
		.title = "CUB3D",
		.width = WIDTH,
		.height = HEIGHT,
		.is_resizable = false
	};
	game.win = mlx_new_window(game.mlx, &info);
	mlx_on_event(game.mlx, game.win, MLX_WINDOW_EVENT, close_win, &game);
	mlx_on_event(game.mlx, game.win, MLX_KEYDOWN, &key_press, &game);
	mlx_on_event(game.mlx, game.win, MLX_KEYUP, &key_release, &game);
	mlx_on_event(game.mlx, game.win, MLX_MOUSEUP, &mouse_up, &game);
	mlx_on_event(game.mlx, game.win, MLX_MOUSEDOWN, &mouse_down, &game);
	mlx_add_loop_hook(game.mlx, &draw_loop, &game);

	mlx_loop(game.mlx);
}