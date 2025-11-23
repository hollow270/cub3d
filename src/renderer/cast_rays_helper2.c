/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays_helper2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 00:00:02 by yhajbi            #+#    #+#             */
/*   Updated: 2025/11/10 16:11:22 by yhajbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	set_tip(t_pos *dst, t_pos *src,
			t_wall_type *wall_type_dst, t_wall_type wall_type)
{
	dst->x = src->x;
	dst->y = src->y;
	*wall_type_dst = wall_type;
}
