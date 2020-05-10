/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_new_dynamic_buffer.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:05:27 by asmall            #+#    #+#             */
/*   Updated: 2020/05/10 17:05:30 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

t_dynamic_buffer	make_new_dynamic_buffer(void)
{
	t_dynamic_buffer	buffer;

	buffer.amount_chars = 0;
	buffer.size_for_malloc = 50;
	buffer.overflow_counter = 1;
	return (buffer);
}
