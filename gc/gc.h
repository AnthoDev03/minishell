/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:06:05 by anthrodr          #+#    #+#             */
/*   Updated: 2023/10/09 12:08:57 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GC_H
# define GC_H

# include <stdio.h>
# include <stdlib.h>

void					gc_init(void);
void					*gc_malloc(size_t size);
void					gc_free_all(void);

typedef struct s_memoryblock
{
	void				*addr;
	struct memoryblock	*next;
}						t_memoryblock;

typedef struct s_garbagecollector
{
	memoryblock			*head;
}						t_garbagecollector;

#endif
