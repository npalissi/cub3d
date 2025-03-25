
#include "cub3d.h"

#include <stdio.h>

void close_win(int event, void *params)
{
	t_game *game;

	game = params;
	if(event == 0)
		mlx_loop_end(game->mlx);
}

int main(void)
{
	t_game game;

	game.str_map = recover_file(&game, "test.txt");
	init_data(&game);
	
	// game.mlx = mlx_init();
	// mlx_window_create_info info = {
	// 	.title = "CUB3D",
	// 	.width = 1000,
	// 	.height = 1000,
	// 	.is_resizable = false
	// };
	// game.win = mlx_new_window(game.mlx, &info);
	// mlx_on_event(game.mlx, game.win, MLX_WINDOW_EVENT, close_win, &game);
	// mlx_loop(game.mlx);
	// printf("4");
}