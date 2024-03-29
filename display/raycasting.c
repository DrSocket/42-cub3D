/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucisanc <lucisanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 18:14:15 by lucisanc          #+#    #+#             */
/*   Updated: 2021/03/01 15:35:54 by lucisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	raycasting(t_display *display) // Envoi d'un rayon a partir du joueur (pour chaque pixel de ligne vertical)
{
	display->index = display->r1 - 1;
	while (display->index > 0)
	{
		display->camerax = 2 * display->index / (double)display->r1 - 1;
		display->d.x = display->dirx + display->planex * display->camerax;
		display->d.y = display->diry + display->planey * display->camerax;
		sendrayon(display);
		display->index--;
	}
	sendrayon(display);
	return (0);
}

int	sendrayon(t_display *display) // Calcul des coordonnées de l'intersection avec la prochaine case (deltadist)
{
	display->mapi.x = floor(display->player.x);
	display->mapi.y = floor(display->player.y);
	display->deltadist.x = sqrt(1 + ((display->d.y * display->d.y) /
				(display->d.x * display->d.x)));
	display->deltadist.y = sqrt(1 + ((display->d.x * display->d.x) /
				(display->d.y * display->d.y)));
	display->stepx = (display->d.x > 0) ? 1 : -1;
	display->stepy = (display->d.y > 0) ? 1 : -1;
	if (display->d.x > 0)
		display->sidedist.x = (display->mapi.x + 1 - display->player.x)
			* display->deltadist.x;
	else
		display->sidedist.x = (display->player.x - display->mapi.x)
			* display->deltadist.x;
	if (display->d.y > 0)
		display->sidedist.y = (display->mapi.y + 1 - display->player.y)
			* display->deltadist.y;
	else
		display->sidedist.y = (display->player.y - display->mapi.y)
			* display->deltadist.y;
	findwall(display);
	return (0);
}

int	findwall(t_display *display) // Boucle sur chaque case jusqu'a trouver un mur
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (((display->sidedist.y <= 0) || ((display->sidedist.x >= 0)
						&& display->sidedist.x < display->sidedist.y)))
		{
			display->sidedist.x += display->deltadist.x;
			display->mapi.x += display->stepx;
			display->side = 0;
		}
		else
		{
			display->sidedist.y += display->deltadist.y;
			display->mapi.y += display->stepy;
			display->side = 1;
		}
		if (display->map[display->mapi.y][display->mapi.x] == '1')
			hit = 1;
	}
	findtexturenum(display);
	return (0);
}

int	findtexturenum(t_display *display) // recherche de la texture correspondante au mur trouvé
{
	if (display->side == 0)
	{
		if (display->d.x >= 0)
			display->textnum = 3;
		else
			display->textnum = 2;
	}
	else
	{
		if (display->d.y >= 0)
			display->textnum = 1;
		else
			display->textnum = 0;
	}
	showraster(display);
	return (0);
}

int	showraster(t_display *display)
{
	if (display->side == 0)                                      // Perwalldist = distance final entre le joeur et le mur trouvé (pour un rayon)
		display->perwalldist = (display->mapi.x - display->player.x +
				(1 - display->stepx) / 2) / display->d.x;
	else
		display->perwalldist = (display->mapi.y - display->player.y +
				(1 - display->stepy) / 2) / display->d.y;
	display->lineheight = (int)(display->r2 / display->perwalldist);     // Calcul de la hauteur du mur (plus perwalldist est grand, plus le mur est petit >raycasting)
	display->startline = -display->lineheight / 2 + display->r2 / 2;
	if (display->startline < 0)
		display->startline = 0;
	display->endline = display->lineheight / 2 + display->r2 / 2;
	if (display->endline >= display->r2)
		display->endline = display->r2 - 1;
	if (display->side == 0)
		display->wallx = display->player.y +
		display->perwalldist * display->d.y;
	else
		display->wallx = display->player.x +
		display->perwalldist * display->d.x;
	display->wallx -= floor((display->wallx));
	draw_line(display, display->index);
	return (1);
}
