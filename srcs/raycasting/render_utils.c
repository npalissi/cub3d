/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:00:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/01 10:21:30 by edubois-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting.h"

// Structure définie dans raycasting.h - pas besoin de redéfinir

static void	init_render_data_optimized(t_optimized_render_data *data, t_game *game)
{
	data->fov_half = PI / 6.0f;  // 60 degrés FOV
	data->angle_step = (PI / 3.0f) / WIDTH;
	data->projection_dist = (WIDTH / 2.0f) / tan(data->fov_half);
	
	// Précalculs trigonometriques (optimisation majeure)
	data->cos_fov_half = cos(data->fov_half);
	data->sin_fov_half = sin(data->fov_half);
	data->player_cos = cos(game->player.angle);
	data->player_sin = sin(game->player.angle);
}

// Version de compatibilité
static void	init_render_data(t_render_data *data)
{
	data->fov_half = PI / 6;
	data->angle_step = (PI / 3) / WIDTH;
	data->projection_dist = (WIDTH / 2) / tan(data->fov_half);
}

// Version optimisée avec calculs vectoriels
static void	process_ray_optimized(t_game *game, t_optimized_render_data *data, int x)
{
	// Calcul angle avec lookup précalculé
	data->ray_angle = game->player.angle - data->fov_half + (x * data->angle_step);
	
	// Précalcul des directions de rayon
	data->ray_dir_x = cos(data->ray_angle);
	data->ray_dir_y = sin(data->ray_angle);
	
	// Cast du rayon avec la nouvelle implémentation DDA
	data->ray = cast_ray(game, data->ray_angle);
	
	// Validation et clamping corrigés pour éviter déformation
	data->ray.dist = (data->ray.dist == INFINITY || data->ray.dist <= 0) ? 1000.0f : data->ray.dist;
	// Distance minimale plus petite pour éviter le clamping agressif
	data->ray.dist = (data->ray.dist < 0.1f) ? 0.1f : data->ray.dist;
	
	// Calcul hauteur mur corrigé
	data->wall_height = (BLOCK_SIZE * data->projection_dist) / data->ray.dist;
	
	// Limitation plus raisonnable pour éviter l'étirement
	data->wall_height = (data->wall_height > HEIGHT * 8) ? HEIGHT * 8 : data->wall_height;
	data->wall_height = (data->wall_height < 1.0f) ? 1.0f : data->wall_height;
}

// Version compatible pour API existante
static void	process_ray(t_game *game, t_render_data *data, int x)
{
	data->ray_angle = game->player.angle - data->fov_half + (x * data->angle_step);
	data->ray = cast_ray(game, data->ray_angle);
	
	if (data->ray.dist == INFINITY || data->ray.dist <= 0)
		data->ray.dist = 1000.0f;
	// Distance minimale réduite pour éviter clamping
	if (data->ray.dist < 0.1f)
		data->ray.dist = 0.1f;
	
	data->wall_height = (BLOCK_SIZE * data->projection_dist) / data->ray.dist;
	
	// Limites ajustées pour éviter déformation
	if (data->wall_height > HEIGHT * 8)
		data->wall_height = HEIGHT * 8;
	if (data->wall_height < 1.0f)
		data->wall_height = 1.0f;
}


typedef struct 
{
	uint32_t x;
	uint32_t y;
}	vec2;

void put_region_to_array(mlx_color *fb, vec2 start, vec2 size, mlx_color *src)
{
	for (uint32_t y = 0; y < size.y; ++y)
	{
		for (uint32_t x = 0; x < size.x; ++x)
		{
			uint32_t sindex = y * size.x + x; // source = tmp[y][x]
			uint32_t index = (start.y + y) * WIDTH + (start.x + x); // dest = fb[y+start.y][x+start.x]

			if (!src[sindex].a)
				continue;
			fb[index] = src[sindex];
		}
	}
}

void	draw_crow(t_game *game)
{
	static mlx_color	tmp[WIDTH * HEIGHT] = {0};

	static int i = 1;
	static int dir = 1; // 1 = forward, -1 = backward
	
	if (current_time() - game->bar.time[0] > 200 && (game->player.key_up ||game->player.key_down|| game->player.key_left || game->player.key_right))
	{
		game->bar.time[0] = current_time();
		i += dir;
	
		if (i >= 4)
		{
			i = 3;
			dir = -1;
		}
		else if (i <= 1)
		{
			i = 1;
			dir = 1;
		}
	}
	else if (current_time() - game->bar.time[0] > 200)
		i = 1;
	mlx_get_image_region(game->mlx, game->bar.item[0], 140 * i, 0,  135, 271, tmp);			// cut 1st sprite
	put_region_to_array(game->frame_buffer, (vec2){WIDTH - 135, HEIGHT - 271}, (vec2){135, 271}, tmp);
}

void	draw_exit_kunai(t_game *game, bool *done)
{
	static mlx_color	tmp[WIDTH * HEIGHT] = {0};

	static int i = 0;
	if (current_time() - game->bar.time[game->bar.type] > game->bar.wait[game->bar.type] && (game->player.key_up ||game->player.key_down|| game->player.key_left || game->player.key_right))
	{
		game->bar.time[1] = current_time();
	
		if (i > 69)
		{
			i = 0;
			*done = true;
		}
		i++;
	}
	else if (current_time() - game->bar.time[1] > game->bar.wait[game->bar.type])
		i = 69;
	mlx_get_image_region(game->mlx, game->bar.item[1], 1920 * i, 0,  1920, 1080, tmp);			// cut 1st sprite
	put_region_to_array(game->frame_buffer, (vec2){0, 0}, (vec2){1920, 1080}, tmp);
}

void	draw_transition(t_game *game, bool *done)
{
	static mlx_color	tmp[WIDTH * HEIGHT] = {0};

	static int i = 0;
	if (current_time() - game->bar.time[game->bar.type] > game->bar.wait[game->bar.type] && (game->player.key_up ||game->player.key_down|| game->player.key_left || game->player.key_right))
	{
		game->bar.time[1] = current_time();
	
		i++;
	}
	mlx_get_image_region(game->mlx, game->bar.item[3], 1920 * i, 0,  1920, 1080, tmp);			// cut 1st sprite
	put_region_to_array(game->frame_buffer, (vec2){0, 0}, (vec2){1920, 1080}, tmp);
	if (i > 18)
	{
		i = 0;
		*done = true;
	}
}

void	draw_sprinting_kunai(t_game *game, bool is_moving)
{
	static mlx_color	tmp[WIDTH * HEIGHT] = {0};
	static int i = 0;

	if (current_time() - game->bar.time[game->bar.type] > game->bar.wait[game->bar.type] && is_moving)
	{
		game->bar.time[1] = current_time();
		if (i > 24)
			i = 0;
		i++;
	}
	else if (current_time() - game->bar.time[1] > game->bar.wait[game->bar.type])
		i = 0;
	mlx_get_image_region(game->mlx, game->bar.item[2], 1920 * i, 0,  1920, 1080, tmp);			// cut 1st sprite
	put_region_to_array(game->frame_buffer, (vec2){0, 0}, (vec2){1920, 1080}, tmp);
}


// Version hautement optimisée du rendu avec boucle déroulée et SIMD-friendly
void	render_frame_optimized(t_game *game)
{
	t_optimized_render_data	data;
	int						x;
	static bool				has_exit = false;
	static bool				has_trans = false;
	bool					is_moving;
	
	// Initialisation avec précalculs
	init_render_data_optimized(&data, game);
	
	// Rendu par blocs pour optimiser la cache localité
	const int BLOCK_SIZE_RENDER = 8;  // Rendu par blocs de 8 pixels
	
	// Boucle principale optimisée
	for (x = 0; x < WIDTH; x += BLOCK_SIZE_RENDER)
	{
		int end_x = (x + BLOCK_SIZE_RENDER > WIDTH) ? WIDTH : x + BLOCK_SIZE_RENDER;
		
		// Traitement par blocs (cache-friendly)
		for (int block_x = x; block_x < end_x; block_x++)
		{
			process_ray_optimized(game, &data, block_x);
			draw_vertical_line_optimized(game, block_x, data.wall_height, data.ray);
		}
	}
	
	// Rendu des sprites (inchangé pour compatibilité)
	is_moving = game->player.key_up || game->player.key_down || 
				game->player.key_left || game->player.key_right;
	
	if (game->bar.valid[1] && game->bar.valid[2] && game->bar.valid[3] && !game->bar.wheel)
	{
		if (is_moving && !has_exit)
			draw_exit_kunai(game, &has_exit);
		
		if (has_exit)
		{
			if (!has_trans)
				draw_transition(game, &has_trans);
			else
				draw_sprinting_kunai(game, is_moving);
		}
		
		if (!is_moving)
		{
			has_exit = false;
			has_trans = false;
		}
	}
	else if (game->bar.valid[0] && game->bar.wheel)
	{
		draw_crow(game);
	}
	
	// Transfert optimisé vers l'écran
	mlx_pixel_put_region(game->mlx, game->win, 0, 0, WIDTH, HEIGHT, game->frame_buffer);
}

// Version de compatibilité qui utilise la nouvelle implémentation
void	render_frame(t_game *game)
{
	render_frame_optimized(game);
}

