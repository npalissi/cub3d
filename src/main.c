
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
	while (game->map.map[i])
	{
		while (game->map.map[i][j])
		{
			if (game->map.map[i][j] == '1')
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
	game->map.map = map;
}

bool touch(t_game *game, float x, float y)
{
	int i;
	int j;

	i = y / BLOCK_SIZE;
	j = x / BLOCK_SIZE;
	if (game->map.map[i][j] == '1')
		return true;
	return false;
}

float distance(float delta_x, float delta_y)
{
	return sqrt(delta_x * delta_x + delta_y * delta_y);
}

float fixed_dist(float delta_x, float delta_y, t_game *game)
{

	float angle;
	float dist;

	angle = atan2(delta_y, delta_x) - game->player.angle;
	dist = distance(delta_x,delta_y) * cos(angle);
	return dist;
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
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	float dist = fixed_dist(ray_x - game->player.x, ray_y - game->player.y, game);
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
	float fraction;
	float start_x;
	int i;
	
	i = 0;
	game = params;
	fraction = PI / 3 / WIDTH;
	start_x = game->player.angle - PI / 6;
	mlx_clear_window(game->mlx, game->win, (mlx_color){.rgba = 0x000000FF});
	while (i < WIDTH)
	{
		draw_line(game, start_x, i);
		start_x += fraction;
		i++;
	}
	pos_mouse(game);
	move_player(&game->player, game);	
}

void init_game(t_game *game)
{

	game->mlx = mlx_init();
	get_map(game);
	mlx_window_create_info info = {
		.title = "CUB3D",
		.width = WIDTH,
		.height = HEIGHT,
		.is_resizable = false
	};
	game->win = mlx_new_window(game->mlx, &info);
	mlx_mouse_get_pos(game->mlx, &game->mouse.x, &game->mouse.y);
	game->mouse.is_press = 0;
}




int main(void)
{
	t_game game;

	// game.str_map = recover_file(&game, "test.txt");
	// init_data(&game);
	init_player(&game.player);
	init_game(&game);
	
	
	
	mlx_on_event(game.mlx, game.win, MLX_WINDOW_EVENT, close_win, &game);
	mlx_on_event(game.mlx, game.win, MLX_KEYDOWN, &key_press, &game);
	mlx_on_event(game.mlx, game.win, MLX_KEYUP, &key_release, &game);
	mlx_on_event(game.mlx, game.win, MLX_MOUSEUP, &mouse_up, &game);
	mlx_on_event(game.mlx, game.win, MLX_MOUSEDOWN, &mouse_down, &game);
	mlx_add_loop_hook(game.mlx, &draw_loop, &game);

	mlx_loop(game.mlx);
}