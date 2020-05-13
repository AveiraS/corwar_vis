/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizator.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 14:10:35 by asmall            #+#    #+#             */
/*   Updated: 2020/05/13 20:24:54 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZATOR_H
# define VISUALIZATOR_H

# include "../include/corewar.h"
# include "../libft/include/libft.h"

/*
** If you work on Linux/Ubuntu:
*/

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>

/*
** If you work on Mac:
** # include "../visualizator/SDL2.framework/Headers/SDL.h"
** # include "../visualizator/SDL2_ttf.framework/Headers/SDL_ttf.h"
*/

# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 700
# define SCREEN_FPS 244
# define SCREEN_TICKS_PER_FRAME 1000 / SCREEN_FPS
# define INFORMATION_SIZE 350
# define WHITE (SDL_Color){255, 255, 255, 255}

SDL_Window		*g_main_window;
SDL_Renderer	*g_main_render;
TTF_Font		*g_font;

void			choose_color_pt3(t_battlefield *cell, int i);
void			choose_color_pt2(t_battlefield *cell, int i);
void			choose_color(t_battlefield *cell, int i);
char			choose_color_char(int i);
int				choose_reverse_color_pt3(t_battlefield *cell);
int				choose_reverse_color_pt2(t_battlefield *cell);
int				choose_reverse_color(t_battlefield *cell);
int				init(t_vm *vm);

void			push_to_render_battlefield(t_vm *vm);
void			push_info(t_vm *vm, char *status);
void			push_int_text(int data, char *info_text,
					float y, SDL_Color color);
void			push_int_slash_data(float y, int data_1,
					int data_2, char *text);
void			push_char_text(char *text, float y, SDL_Color color);
void			push_live_breakdown(t_vm *vm, int y);
void			push_pause(void);
void			push_distribution(t_battlefield *arena, float y);
void			push_players(t_vm *vm, int start_y);
void			push_winner_vis(t_vm *vm);
void			set_render_draw_color(char color);
void			set_sdl_color(SDL_Color *color, int i);
void			put_text_texture(float y, char *temp_2,
					char *temp_3, SDL_Texture *text_texture);
void			key_pause_quite(t_vm *vm);
void			visualisator_event(t_vm *vm);
void			live_players(t_vm *vm, SDL_FRect coor, int sum);

#endif
