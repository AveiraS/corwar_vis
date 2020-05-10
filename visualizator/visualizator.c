/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:06:18 by asmall            #+#    #+#             */
/*   Updated: 2020/05/10 17:06:20 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/visualizator.h"

void	push_info(t_vm *vm, char *status)
{
	SDL_Color	White = {255, 255, 255, 255};

	push_char_text(status, 20, White);
	push_int_text(vm->num_process, "Total processes: ", 40, White);
	push_int_text(vm->cycle, "Current cycle: ", 60, White);
	push_int_text(vm->cycles_to_die, "Cycle to die: ", 100, White);
	push_int_text(CYCLE_DELTA, "Cycle delta: ", 120, White);
	push_int_slash_data(160, vm->live_calls, NBR_LIVE, "NBR_live: ", White);
	push_int_slash_data(180, vm->amount_of_checks, MAX_CHECKS, "MAX_checks: ", White);
	push_char_text("Live breakdown for now:", SCREEN_HEIGHT - 80, White);
	push_live_breakdown(vm, SCREEN_HEIGHT - 60);
	push_char_text("Arena distribution: ", SCREEN_HEIGHT - 40, White);
	push_distribution(vm->arena, SCREEN_HEIGHT - 20);
	push_players(vm, 220);
}

void	push_to_render_battlefield(t_vm *vm)
{
	unsigned	i;
	unsigned 	j;
	int			lines_count;
	SDL_FRect	cell;

	cell.w = (float)(SCREEN_WIDTH - INFORMATION_SIZE) / 64;
	cell.h = (float)SCREEN_HEIGHT / 64;
	SDL_SetRenderDrawColor(g_main_render, 0, 0, 0, 255);
	SDL_RenderClear(g_main_render);
	i = -1;
	lines_count = 0;
	while (++i < (float)MEM_SIZE / 64)
	{
		j = -1;
		while (++j < (float)MEM_SIZE / 64)
		{
			cell.x = cell.w * j;
			cell.y = cell.h * i;
			SDL_SetRenderDrawColor(g_main_render,
				vm->arena[i + j + lines_count].color_r + vm->arena[i + j + lines_count].write_cycles,
				vm->arena[i + j + lines_count].color_g + vm->arena[i + j + lines_count].write_cycles,
				vm->arena[i + j + lines_count].color_b + vm->arena[i + j + lines_count].write_cycles, 255);
			if (!vm->vis_pause && vm->arena[i + j + lines_count].write_cycles > 0)
				vm->arena[i + j + lines_count].write_cycles--;
			SDL_RenderFillRectF(g_main_render, &cell);
		}
		lines_count += j - 1;
	}
	i = -1;
	SDL_SetRenderDrawColor(g_main_render, 0, 0, 0, 255);
	while (++i < (float)MEM_SIZE / 64)
	{
		SDL_RenderDrawLineF(g_main_render, cell.w * i, 0, cell.w * i, SCREEN_HEIGHT);
		SDL_RenderDrawLineF(g_main_render, 0, cell.h * i, SCREEN_WIDTH - INFORMATION_SIZE, cell.h * i);
	}
	i = -1;
	lines_count = 0;
	SDL_SetRenderDrawColor(g_main_render, 255, 255, 255, 255);
	while (++i < (float)MEM_SIZE / 64)
	{
		j = -1;
		while (++j < (float)MEM_SIZE / 64)
		{
			if (vm->arena[i + j + lines_count].cursor)
			{
				cell.x = cell.w * j;
				cell.y = cell.h * i;
				SDL_RenderDrawRectF(g_main_render, &cell);
			}
		}
		lines_count += j - 1;
	}
}

void	push_pause(void)
{
	SDL_Rect	pause;
	SDL_Color	White = {255, 255, 255, 255};

	pause.h = 20;
	pause.w = 300;
	pause.y = 20;
	pause.x = SCREEN_WIDTH - INFORMATION_SIZE + 50;
	SDL_SetRenderDrawColor(g_main_render, 0, 0, 0, 255);
	SDL_RenderFillRect(g_main_render, &pause);
	push_char_text("**Pause**", 20, White);
	SDL_RenderPresent(g_main_render);
}
