/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npalissi <npalissi@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 19:00:00 by npalissi          #+#    #+#             */
/*   Updated: 2025/07/02 19:53:23 by npalissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycasting_bonus.h"
#include <math.h>

// Structures adaptées de ttranche
typedef struct s_vecd {
	double x;
	double y;
} t_vecd;

typedef struct s_ray_tt {
	t_vecd st_cos;  // Step vector for cos intersections
	t_vecd st_sin;  // Step vector for sin intersections  
	double ln_cos;  // Length of cos ray
	double ln_sin;  // Length of sin ray
} t_ray_tt;

typedef struct s_trace_tt {
	t_ray_tt ray;
	t_ray_tt step;
	t_vecd ref;     // Reference position (player)
	float cos_a;    // cos(angle)
	float sin_a;    // sin(angle)
	float newa;     // Normalized angle for fisheye correction
	double len;     // Final ray length
	int map_x;      // Map position X
	int map_y;      // Map position Y
	int wall_side;  // 0=N, 1=S, 2=W, 3=E
	float tex_offset; // Texture offset [0-1]
} t_trace_tt;

// Fonctions utilitaires
static double calc_sqrtlen(t_vecd v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

// Initialise un rayon selon l'approche ttranche
static t_ray_tt get_init_ray_tt(float cos_a, float sin_a, double x, double y)
{
	t_ray_tt ray;
	
	// Step vectors for cos intersections
	ray.st_cos.x = cos_a > 0 ? floor(x + 1) - x : ceil(x - 1) - x;
	ray.st_cos.y = ray.st_cos.x * (sin_a / cos_a);
	ray.ln_cos = calc_sqrtlen(ray.st_cos);
	
	// Step vectors for sin intersections
	ray.st_sin.y = sin_a > 0 ? floor(y + 1) - y : ceil(y - 1) - y;  
	ray.st_sin.x = ray.st_sin.y * (cos_a / sin_a);
	ray.ln_sin = calc_sqrtlen(ray.st_sin);
	
	return ray;
}

// Avance le rayon d'un pas
static void cast_forward_tt(t_ray_tt *ray, t_ray_tt *step)
{
	if (ray->ln_cos < ray->ln_sin)
	{
		ray->st_cos.x += step->st_cos.x;
		ray->st_cos.y += step->st_cos.y;
		ray->ln_cos += step->ln_cos;
	}
	else
	{
		ray->st_sin.x += step->st_sin.x;
		ray->st_sin.y += step->st_sin.y;
		ray->ln_sin += step->ln_sin;
	}
}

// Calcule la position de collision
static void get_collide_pos_tt(t_trace_tt *tr)
{
	if (tr->ray.ln_cos > tr->ray.ln_sin)
	{
		tr->map_x = floor(tr->ref.x + tr->ray.st_sin.x);
		tr->map_y = floor(tr->ref.y + tr->ray.st_sin.y + tr->sin_a / 2);
		tr->wall_side = (tr->sin_a > 0) ? 1 : 0; // Sud : Nord
	}
	else
	{
		tr->map_x = floor(tr->ref.x + tr->ray.st_cos.x + tr->cos_a / 2);
		tr->map_y = floor(tr->ref.y + tr->ray.st_cos.y);
		tr->wall_side = (tr->cos_a > 0) ? 3 : 2; // Est : Ouest
	}
}

// Calcule l'offset de texture
static float calc_tex_offset_tt(t_trace_tt *tr)
{
	double offset;
	
	if (tr->ray.ln_cos < tr->ray.ln_sin)
	{
		offset = tr->ref.x + tr->ref.y + tr->ray.st_cos.x + tr->ray.st_cos.y;
		offset -= (int)offset;
		if (tr->cos_a < 0)
			offset = 1 - offset;
	}
	else
	{
		offset = tr->ref.x + tr->ref.y + tr->ray.st_sin.x + tr->ray.st_sin.y;
		offset -= (int)offset;
		if (tr->sin_a > 0)
			offset = 1 - offset;
	}
	return (float)offset;
}

// Vérifie si la position est un mur
static int check_wall_tt(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map.w || y < 0 || y >= game->map.h)
		return 1;
	if (!game->map.map || !game->map.map[y])
		return 1;
	return (game->map.map[y][x] == '1');
}

// Fonction pour vérifier si une position correspond à une porte
int is_door_at_position(t_game *game, int map_x, int map_y)
{
	int i;

	if (!game->d)
		return (0);
	
	i = 0;
	while (game->d[i].x)
	{
		if (game->d[i].x == map_x && game->d[i].y == map_y)
			return (1);
		i++;
	}
	return (0);
}

// Version corrigée avec angle relatif pré-calculé
t_ray cast_ray_corrected(t_game *game, float angle, float relative_angle)
{
	t_trace_tt tr;
	t_ray result;
	int max_steps;
	int i;
	
	// Initialisation
	tr.cos_a = cos(angle);
	tr.sin_a = sin(angle);
	tr.newa = relative_angle; // Angle relatif pré-calculé pour correction fisheye
	tr.ref.x = game->player.x / BLOCK_SIZE;
	tr.ref.y = game->player.y / BLOCK_SIZE;
	
	// Initialiser les rayons
	tr.ray = get_init_ray_tt(tr.cos_a, tr.sin_a, tr.ref.x, tr.ref.y);
	tr.step = get_init_ray_tt(tr.cos_a, tr.sin_a, 0, 0);
	
	// Limite de distance
	max_steps = (game->map.w > game->map.h) ? game->map.w : game->map.h;
	max_steps = max_steps * 2 + 10;
	
	// raycasting_bonus loop
	i = 0;
	while (i < max_steps)
	{
		get_collide_pos_tt(&tr);
		if (check_wall_tt(game, tr.map_x, tr.map_y))
		{
			// Collision trouvée
			tr.len = fmin(tr.ray.ln_cos, tr.ray.ln_sin);
			tr.tex_offset = calc_tex_offset_tt(&tr);
			break;
		}
		cast_forward_tt(&tr.ray, &tr.step);
		i++;
	}
	
	// Si aucune collision trouvée
	if (i >= max_steps)
	{
		tr.len = max_steps;
		tr.wall_side = 0;
		tr.tex_offset = 0;
		tr.map_x = 0;
		tr.map_y = 0;
	}
	
	// Correction fisheye correcte selon la méthode de projection plane
	tr.len = tr.len / sqrt(1 + tr.newa * tr.newa);
	
	// Conversion vers notre format t_ray
	result.dist = tr.len * BLOCK_SIZE;
	result.wall_side = tr.wall_side;
	result.wall_x = tr.tex_offset;
	result.x = game->player.x + tr.cos_a * result.dist;
	result.y = game->player.y + tr.sin_a * result.dist;
	result.cos_angle = tr.cos_a;
	result.sin_angle = tr.sin_a;
	result.is_vertical = (tr.wall_side == 2 || tr.wall_side == 3) ? 0 : 1;
	result.is_door = is_door_at_position(game, tr.map_x, tr.map_y);
	
	return result;
}

// Fonction principale de raycasting_bonus
t_ray cast_ray(t_game *game, float angle)
{
	float relative_angle = angle - game->player.angle;
	return cast_ray_corrected(game, angle, relative_angle);
}

// Fonction supprimée - utilisation directe de cast_ray()

// Fonction de rendu optimisée selon leur approche
void render_frame(t_game *game)
{
	int x;
	float fov = PI / 3.0f; // 60 degrés total FOV
	float fov_half = fov / 2.0f;
	
	// Rendu par colonnes
	for (x = 0; x < WIDTH; x++)
	{
		// Calcul de l'angle selon l'approche correcte (plan perpendiculaire)
		float camera_x = 2 * x / (float)WIDTH - 1; // [-1, 1]
		float ray_angle = game->player.angle + atan(camera_x * tan(fov_half));
		
		// Lancer le rayon avec l'angle relatif pré-calculé
		t_ray ray = cast_ray_corrected(game, ray_angle, camera_x * tan(fov_half));
		
		// Calculer la hauteur du mur (la correction fisheye est déjà dans ray.dist)
		float projection_dist = (WIDTH / 2.0f) / tan(fov_half);
		float wall_height = (BLOCK_SIZE * projection_dist) / ray.dist;
		
		// Limiter la hauteur pour éviter les valeurs extrêmes
		if (wall_height > HEIGHT * 5)
			wall_height = HEIGHT * 5;
		if (wall_height < 1.0f)
			wall_height = 1.0f;
		
		// Dessiner la colonne
		draw_vertical_line_no_stretch(game, x, wall_height, ray);
	}
	
	// Rendu des sprites (copié du système existant)
	static bool has_exit = false;
	static bool has_trans = false;
	bool is_moving = game->player.key_up || game->player.key_down || 
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
	
	// Transférer à l'écran
	mlx_pixel_put_region(game->mlx, game->win, 0, 0, WIDTH, HEIGHT, game->frame_buffer);
}