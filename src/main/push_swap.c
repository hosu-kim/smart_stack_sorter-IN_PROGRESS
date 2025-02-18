/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 00:30:06 by hoskim            #+#    #+#             */
/*   Updated: 2025/02/18 19:59:26 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/**
 * @brief Main function of push_swap program
 * 
 * This program sorts integers using two stacks (A and B)
 * and a limited set of operations.
 * 
 * @note Algorithm steps:
 * -# Initialize stacks
 * -# Insert numbers to stack A in reverse order
 * -# Check for duplicate numbers
 * -# Sort the stack if not already sorted
 * -# Clean up allocated memory
 * 
 * @warning All input numbers must be valid integers
 * @warning No duplicate numbers
 */
int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		i;

	if (argc < 2)
		return (0);
	stack_a = create_stack();
	stack_b = create_stack();
	i = argc - 1;
	while (i > 0)
	{
		insert_number_into_stack(stack_a, ft_atoi(argv[i]));
		i--;
	}
	same_number_checker(stack_a);
	if (!is_sorted(stack_a))
		sort_stacks(stack_a, stack_b);
	print_stack_a(stack_a);
	free_stacks(stack_a, stack_b);
	return (0);
}
/* @note 
	- function usage steps
		1. create_stack()		     | stack_manager.c
		2. insert_number_into_stack()| stack_manager.c
		3. ft_atoi() 			     | general_utils.c
		4. same_number_checker()       | general_utils.c
		5. is_sorted()			     | general_utils.c
		6. sort_stack() -CORE FUNC.  | sort_manager.c
		7. free_stacks()		     | stack_manager.c
*/
