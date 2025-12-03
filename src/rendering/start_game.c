/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:10:04 by yhajbi            #+#    #+#             */
/*   Updated: 2025/12/03 17:11:18 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	start_game(t_game *gm)
{
	// 1. Initialize MLX
    gm->mlx = mlx_init();
    if (!gm->mlx)
    {
        printf("Error\nMLX init failed\n");
        exit(1);
    }

    // 2. Create Window
    gm->win = mlx_new_window(gm->mlx, WIDTH, HEIGHT, "CUB3D");
    if (!gm->win)
    {
        printf("Error\nWindow creation failed\n");
        exit(1);
    }

    // 3. Create Image Buffer
    gm->frame.img = mlx_new_image(gm->mlx, WIDTH, HEIGHT);
    gm->frame.data_img = mlx_get_data_addr(gm->frame.img, &gm->frame.bpp, 
                                           &gm->frame.line_len, &gm->frame.endian);

    // 4. Load Textures (Uses the paths you merged into gm->tex_path)
    if (load_textures(gm))
    {
        // Make sure destroy_game uses gc_free_all if you want clean exit
        printf("Error\nTexture load failed\n");
        exit(1); 
    }

    // 5. Setup Hooks & Loop
    mlx_mouse_hide(gm->mlx, gm->win);
    mlx_loop_hook(gm->mlx, main_function, gm); // Assuming main_function is visible
    mlx_hook(gm->win, 2, KeyPressMask, key_press, gm);
    mlx_hook(gm->win, 3, KeyReleaseMask, key_release, gm);
    
    // IMPORTANT: Ensure close_win calls gc_free_all() before exit(0)
    mlx_hook(gm->win, 17, 0, close_win, gm); 
    mlx_hook(gm->win, MotionNotify, PointerMotionMask, mouse_move, gm);

    mlx_loop(gm->mlx);
}
