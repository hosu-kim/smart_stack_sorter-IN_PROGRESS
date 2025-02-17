/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 02:12:57 by hoskim            #+#    #+#             */
/*   Updated: 2025/02/17 17:15:37 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static int	get_optimal_moves(int position, int stack_size)
{
	if (position <= stack_size / 2)
		return (position - 1);
	return (stack_size - position + 1);
}

static void	handle_stack_rotation(t_stack *stack_a, int position)
{
	if (position <= stack_a->total_nodes / 2)
		ra(stack_a);
	else
		rra(stack_a);
}

static void	push_numbers_to_b(t_stack *stack_a, t_stack *stack_b, t_range chunk)
{
	int	target;
	int	position;
	int	rotation_count;

	rotation_count = 0;
	while (stack_a->total_nodes > 0 && rotation_count < stack_a->total_nodes)
	{
		target = stack_a->head_node->stored_number;
		if (target >= chunk.min && target <= chunk.max)
		{
			pb(stack_a, stack_b);
			if (stack_b->head_node->stored_number < (chunk.min + chunk.max) / 2)
				rb(stack_b);
			rotation_count = 0;
		}
		else
		{
			position = get_target_position(stack_a, chunk.min);
			if (position > stack_a->total_nodes)
				position = stack_a->total_nodes;
			handle_stack_rotation(stack_a, position);
			rotation_count++;
		}
	}
}

static void	sort_back_to_a(t_stack *stack_a, t_stack *stack_b)
{
	int	max_position;
	int	moves;

	while (stack_b->total_nodes > 0)
	{
		max_position = find_max_position(stack_b);
		moves = get_optimal_moves(max_position, stack_b->total_nodes);
		while (moves > 0)
		{
			if (max_position <= stack_b->total_nodes / 2)
				rb(stack_b);
			else
				rrb(stack_b);
			moves--;
		}
		pa(stack_a, stack_b);
	}
}

void	sort_large(t_stack *stack_a, t_stack *stack_b)
{
	t_range	range;
	t_range	chunk;
	int		chunk_size;
	int		chunks;
	int		i;

	range = get_stack_range(stack_a);
	if (stack_a->total_nodes <= 100)
		chunks = 5;
	else
		chunks = 11;
	chunk_size = (range.max - range.min + 1) / chunks + 1;
	i = 0;
	while (i < chunks)
	{
		chunk.min = range.min + (i * chunk_size);
		chunk.max = chunk.min + chunk_size - 1;
		if (i == chunks - 1)
			chunk.max = range.max;
		push_numbers_to_b(stack_a, stack_b, chunk);
		i++;
	}
	sort_back_to_a(stack_a, stack_b);
}
