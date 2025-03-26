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
	map[2] = "100010000001";
	map[3] = "100000001001";
	map[4] = "100100000001";
	map[5] = "100000000001";
	map[6] = "100000100001";
	map[7] = "100000000001";
	map[8] = "100000100001";
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
    float angle = atan2(delta_y, delta_x) - game->player.angle;
    float dist_squared = delta_x * delta_x + delta_y * delta_y;
    return sqrt(dist_squared) * cos(angle);
}
void draw_line(t_game *game, float start_x, int i, mlx_color *pixels)
{
    float ray_x = game->player.x;
    float ray_y = game->player.y;
    float cos_angle = cos(start_x);
    float sin_angle = sin(start_x);

    while (!touch(game, ray_x, ray_y))
    {
        ray_x += cos_angle;
        ray_y += sin_angle;
    }

    float delta_x = ray_x - game->player.x;
    float delta_y = ray_y - game->player.y;
    float dist = fixed_dist(delta_x, delta_y, game);
    float height = (BLOCK_SIZE / dist) * (WIDTH / 2);
    float start_y = (HEIGHT - height) / 2;
    int end = start_y + height;

    for (int y = start_y; y < end; y++)
    {
        if (y >= 0 && y < HEIGHT) // Vérifier que le pixel est dans les limites de l'écran
        {
            pixels[y * WIDTH + i].rgba = 0x00FF00FF; // Stocker la couleur dans le tableau
        }
    }
}

void draw_loop(void *params)
{
    t_game *game = params;
	mlx_clear_window(game->mlx, game->win, (mlx_color){.rgba = 0x000000FF});
	// Allouer un tableau de pixels pour l'écran entier
    mlx_color *pixels = malloc(WIDTH * HEIGHT * sizeof(mlx_color));
    if (!pixels)
        return;

    // Initialiser tous les pixels à une couleur de fond (par exemple, noir)
    for (int i = 0; i < WIDTH * HEIGHT; i++)
    {
        pixels[i].rgba = 0x000000FF; // Couleur de fond (noir)
    }

    float fraction = PI / 3 / WIDTH;
    float start_x = game->player.angle - PI / 6;

    for (int i = 0; i < WIDTH; i++)
    {
        draw_line(game, start_x, i, pixels);
        start_x += fraction;
    }

    // Afficher tous les pixels à l'écran
    mlx_pixel_put_array(game->mlx, game->win, 0, 0, pixels, WIDTH * HEIGHT);

    // Libérer le tableau de pixels
    free(pixels);

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
	mlx_set_fps_goal(game->mlx, 60);
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