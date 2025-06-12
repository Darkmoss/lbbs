/***************************************************************************
						memory_pool.h  -  description
							 -------------------
	copyright            : (C) 2004-2025 by Leaflet
	email                : leaflet@leafok.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef _MEMORY_POOL_H_
#define _MEMORY_POOL_H_

#include <stddef.h>

struct memory_pool_t
{
	size_t node_size;
	size_t node_count_per_chunk;
	int chunk_count;
	int chunk_count_limit;
	void **p_chunks;
	void *p_free;
	int node_count_allocated;
	int node_count_free; 
	int node_count_total;
};
typedef struct memory_pool_t MEMORY_POOL;

extern MEMORY_POOL *memory_pool_init(size_t node_size, size_t node_count_per_chunk, int chunk_count_limit);
extern void memory_pool_cleanup(MEMORY_POOL *p_pool);

extern void *memory_pool_alloc(MEMORY_POOL *p_pool);
extern void memory_pool_free(MEMORY_POOL *p_pool, void *p_node);

// For debug only
extern int memory_pool_check_node(MEMORY_POOL *p_pool, void *p_node);

#endif //_MEMORY_POOL_H_
