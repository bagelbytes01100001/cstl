#ifndef VECTOR_H_
#define VECTOR_H_

#pragma once

#include "iterator.h"

#include <assert.h>
#include <memory.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define vector_type(type) vector_##type
#define vector_vtbl(type) vector_type(type)##_vtbl
#define vector_function(type, name) vector_type(type)##_##name
#define vector_function_signature(type, ...) (struct vector_type(type) *vec, __VA_ARGS__)

#define vector_import_type(type)																																																		\
struct iterator_vtbl(vector_type(type)) {																																																\
	void(*next)  iterator_function_signature(vector_type(type));																																										\
	void(*prev)  iterator_function_signature(vector_type(type));																																										\
	int(*value) iterator_function_signature(vector_type(type));																																											\
};																																																										\
struct reverse_iterator_vtbl(vector_type(type)) {																																														\
	void(*next) reverse_iterator_function_signature(vector_type(type));																																									\
	void(*prev) reverse_iterator_function_signature(vector_type(type));																																									\
	type(*value) reverse_iterator_function_signature(vector_type(type));																																								\
};																																																										\
extern const struct iterator_vtbl(vector_type(type)) iterator_vtbl(vector_type(type));																																					\
extern const struct reverse_iterator_vtbl(vector_type(type)) reverse_iterator_vtbl(vector_type(type));																																	\
struct iterator_type(vector_type(type)) {																																																\
	const struct iterator_vtbl(vector_type(type)) *vtbl;																																												\
	type *ptr;																																																							\
};																																																										\
struct reverse_iterator_type(vector_type(type)){																																														\
	const struct reverse_iterator_vtbl(vector_type(type)) *vtbl;																																										\
	type *ptr;																																																							\
};																																																										\
struct vector_vtbl(type) {																																																				\
	int(*init)														vector_function_signature(type, uint32_t);																															\
	int(*init_from_array)											vector_function_signature(type, type*, uint32_t);																													\
	struct iterator_type(vector_type(type))(*begin)					vector_function_signature(type);																																	\
	struct iterator_type(vector_type(type))(*end)					vector_function_signature(type);																																	\
	struct reverse_iterator_type(vector_type(type))(*rbegin)		vector_function_signature(type);																																	\
	struct reverse_iterator_type(vector_type(type))(*rend)			vector_function_signature(type);																																	\
	uint32_t(*size)													vector_function_signature(type);																																	\
	void(*resize)													vector_function_signature(type, uint32_t);																															\
	uint32_t(*capacity)												vector_function_signature(type);																																	\
	int(*empty)														vector_function_signature(type);																																	\
	void(*reserve)													vector_function_signature(type, uint32_t);																															\
	uint32_t(*alloc_size)											vector_function_signature(type);																																	\
	type(*at)														vector_function_signature(type, uint32_t);																															\
	type(*front)													vector_function_signature(type);																																	\
	type(*back)														vector_function_signature(type);																																	\
	type*(*data)													vector_function_signature(type);																																	\
	void(*push_back)												vector_function_signature(type, type);																																\
	void(*pop_back)													vector_function_signature(type);																																	\
	struct iterator_type(vector_type(type))(*insert)				vector_function_signature(type, struct iterator_type(vector_type(type))*, int);																						\
	struct iterator_type(vector_type(type))(*insert_range)			vector_function_signature(type, struct iterator_type(vector_type(type))*, struct iterator_type(vector_type(type))*, struct iterator_type(vector_type(type))*);		\
	struct iterator_type(vector_type(type))(*erase)					vector_function_signature(type, struct iterator_type(vector_type(type))*);																							\
	struct iterator_type(vector_type(type))(*erase_range)			vector_function_signature(type, struct iterator_type(vector_type(type))*, struct iterator_type(vector_type(type))*);												\
	void(*clear)													vector_function_signature(type);																																	\
};																																																										\
extern const struct vector_vtbl(type) vector_vtbl(type);																																												\
struct vector_type(type) {																																																				\
	struct vector_vtbl(type) *vtbl;																																																		\
	uint32_t size;																																																						\
	uint32_t capacity;																																																					\
	type *data;																																																							\
};																																																										

#define vector(type, name)	struct vector_type(type) name

#define vector_generate_prototypes(type)																																																						\
int														vector_function(type, init) vector_function_signature(type, uint32_t);																																	\
int														vector_function(type, init_from_array) vector_function_signature(type, type*, uint32_t);																												\
struct iterator_type(vector_type(type))					vector_function(type, begin) vector_function_signature(type);																																			\
struct iterator_type(vector_type(type))					vector_function(type, end) vector_function_signature(type);																																				\
struct reverse_iterator_type(vector_type(type))			vector_function(type, rbegin) vector_function_signature(type);																																			\
struct reverse_iterator_type(vector_type(type))			vector_function(type, rend) vector_function_signature(type);																																			\
uint32_t												vector_function(type, size) vector_function_signature(type);																																			\
void													vector_function(type, resize) vector_function_signature(type, uint32_t);																																\
uint32_t												vector_function(type, capacity) vector_function_signature(type);																																		\
int														vector_function(type, empty) vector_function_signature(type);																																			\
void													vector_function(type, reserve) vector_function_signature(type, uint32_t);																																\
uint32_t												vector_function(type, alloc_size) vector_function_signature(type);																																		\
type													vector_function(type, at) vector_function_signature(type, uint32_t);																																	\
type													vector_function(type, front) vector_function_signature(type);																																			\
type													vector_function(type, back) vector_function_signature(type);																																			\
type*													vector_function(type, data) vector_function_signature(type);																																			\
void													vector_function(type, push_back) vector_function_signature(type, type);																																	\
void													vector_function(type, pop_back) vector_function_signature(type);																																		\
struct iterator_type(vector_type(int))                  vector_function(type, insert) vector_function_signature(type, struct iterator_type(vector_type(type))*, type);																							\
struct iterator_type(vector_type(int))					vector_function(type, insert_range) vector_function_signature(type, struct iterator_type(vector_type(type))*, struct iterator_type(vector_type(type))*, struct iterator_type(vector_type(type))*);		\
struct iterator_type(vector_type(int))					vector_function(type, erase) vector_function_signature(type, struct iterator_type(vector_type(type))*);																									\
struct iterator_type(vector_type(int))					vector_function(type, erase_range) vector_function_signature(type, struct iterator_type(vector_type(type))*, struct iterator_type(vector_type(type))*);													\
void													vector_function(type, clear) vector_function_signature(type);																																			\
void													iterator_function(vector_type(type), next) iterator_function_signature(vector_type(type));																												\
void													iterator_function(vector_type(type), prev) iterator_function_signature(vector_type(type));																												\
int														iterator_function(vector_type(type), value) iterator_function_signature(vector_type(type));																												\
void													reverse_iterator_function(vector_type(type), next) reverse_iterator_function_signature(vector_type(type));																								\
void													reverse_iterator_function(vector_type(type), prev) reverse_iterator_function_signature(vector_type(type));																								\
int														reverse_iterator_function(vector_type(type), value) reverse_iterator_function_signature(vector_type(type));																								

#define vector_generate_definitions(type)																																																						\
const struct vector_vtbl(type) vector_vtbl(type) = {																																																			\
	&vector_function(type, init),																																																								\
	&vector_function(type, init_from_array),																																																					\
	&vector_function(type, begin),																																																								\
	&vector_function(type, end),																																																								\
	&vector_function(type, rbegin),																																																								\
	&vector_function(type, rend),																																																								\
	&vector_function(type, size),																																																								\
	&vector_function(type, resize),																																																								\
	&vector_function(type, capacity),																																																							\
	&vector_function(type, empty),																																																								\
	&vector_function(type, reserve),																																																							\
	&vector_function(type, alloc_size),																																																							\
	&vector_function(type, at),																																																									\
	&vector_function(type, front),																																																								\
	&vector_function(type, back),																																																								\
	&vector_function(type, data),																																																								\
	&vector_function(type, push_back),																																																							\
	&vector_function(type, pop_back),																																																							\
	&vector_function(type, insert),																																																								\
	&vector_function(type, insert_range),																																																						\
	&vector_function(type, erase),																																																								\
	&vector_function(type, erase_range),																																																						\
	&vector_function(type, clear)																																																								\
};																																																																\
const struct iterator_vtbl(vector_type(type)) iterator_vtbl(vector_type(type)) = {																																												\
	&iterator_function(vector_type(type), next),																																																				\
	&iterator_function(vector_type(type), prev),																																																				\
	&iterator_function(vector_type(type), value)																																																				\
};																																																																\
const struct reverse_iterator_vtbl(vector_type(type)) reverse_iterator_vtbl(vector_type(type)) = {																																								\
	&reverse_iterator_function(vector_type(type), next),																																																		\
	&reverse_iterator_function(vector_type(type), prev),																																																		\
	&reverse_iterator_function(vector_type(type), value)																																																		\
};																																																																\
int vector_function(type, init) vector_function_signature(type, uint32_t capacity)																																												\
{																																																																\
	vec->size = 0;																																																												\
	vec->capacity = capacity;																																																									\
	vec->data = malloc(vec->capacity * sizeof(type));																																																			\
																																																																\
	return 0;																																																													\
}																																																																\
int vector_function(type, init_from_array) vector_function_signature(type, type *arr, uint32_t size)																																							\
{																																																																\
	vec->size = size;																																																											\
	vec->capacity = size;																																																										\
	vec->data = malloc(vec->capacity * sizeof(int));																																																			\
	memcpy(vec->data, arr, vec->size * sizeof(int));																																																			\
																																																																\
	return 0;																																																													\
}																																																																\
struct iterator_type(vector_type(type)) vector_function(type, begin) vector_function_signature(type)																																							\
{																																																																\
	struct iterator_type(vector_type(type)) it = { &iterator_vtbl(vector_type(type)), vec->data };																																								\
																																																																\
	return it;																																																													\
}																																																																\
struct iterator_type(vector_type(type)) vector_function(type, end) vector_function_signature(type)																																								\
{																																																																\
	struct iterator_type(vector_type(type)) it = { &iterator_vtbl(vector_type(type)), vec->data + vec->size };																																					\
																																																																\
	return it;																																																													\
}																																																																\
struct reverse_iterator_type(vector_type(type)) vector_function(type, rbegin) vector_function_signature(type)																																					\
{																																																																\
	struct reverse_iterator_type(vector_type(type)) it = { &reverse_iterator_vtbl(vector_type(type)), vec->data + vec->size };																																	\
																																																																\
	return it;																																																													\
}																																																																\
struct reverse_iterator_type(vector_type(type)) vector_function(type, rend) vector_function_signature(type)																																						\
{																																																																\
	struct reverse_iterator_type(vector_type(type)) it = { &reverse_iterator_vtbl(vector_type(type)), vec->data };																																				\
																																																																\
	return it;																																																													\
}																																																																\
uint32_t vector_function(type, size) vector_function_signature(type)																																															\
{																																																																\
	return vec->size;																																																											\
}																																																																\
void vector_function(type, resize) vector_function_signature(type, uint32_t size)																																												\
{																																																																\
	if ((vec->size = size) >= vec->capacity) {																																																					\
		vec->capacity = vec->size;																																																								\
		vec->capacity *= (uint32_t)(3 / 2.0f);																																																					\
		type *new_data = malloc(vec->capacity * sizeof(type));																																																	\
		memcpy(new_data, vec->data, vec->size * sizeof(type));																																																	\
		free(vec->data);																																																										\
		vec->data = new_data;																																																									\
	}																																																															\
}																																																																\
uint32_t vector_function(type, capacity) vector_function_signature(type)																																														\
{																																																																\
	return vec->capacity;																																																										\
}																																																																\
int vector_function(type, empty) vector_function_signature(type)																																																\
{																																																																\
	return vec->size != 0;																																																										\
}																																																																\
void vector_function(type, reserve) vector_function_signature(type, uint32_t capacity)																																											\
{																																																																\
	if (vec->capacity != capacity) {																																																							\
		vec->size = vec->size < capacity ? vec->size : capacity;																																																\
		vec->capacity = capacity;																																																								\
		type *new_data = malloc(vec->capacity * sizeof(type));																																																	\
		memcpy(new_data, vec->data, vec->size * sizeof(type));																																																	\
		free(vec->data);																																																										\
		vec->data = new_data;																																																									\
	}																																																															\
}																																																																\
uint32_t vector_function(type, alloc_size) vector_function_signature(type)																																														\
{																																																																\
	return 	vec->capacity * sizeof(int);																																																						\
}																																																																\
type vector_function(type, at) vector_function_signature(type, uint32_t index)																																													\
{																																																																\
	return vec->data[index];																																																									\
}																																																																\
type vector_function(int, front) vector_function_signature(type)																																																\
{																																																																\
	return *(vec->data);																																																										\
}																																																																\
type vector_function(type, back) vector_function_signature(type)																																																\
{																																																																\
	return *(vec->data + vec->size - 1);																																																						\
}																																																																\
type* vector_function(type, data) vector_function_signature(type)																																																\
{																																																																\
	return vec->data;																																																											\
}																																																																\
void vector_function(type, push_back) vector_function_signature(type, type value)																																												\
{																																																																\
	if(vec->size >= vec->capacity) {																																																							\
		vec->capacity *= 3 / 2.0f;																																																						\
		type *new_data = malloc(vec->capacity * sizeof(type));																																																			\
		memcpy(new_data, vec->data, vec->size * sizeof(type));																																																	\
		free(vec->data);																																																										\
		vec->data = new_data;																																																									\
	}																																																															\
																																																																\
	vec->data[vec->size++] = value;																																																								\
}																																																																\
void vector_function(type, pop_back)(struct vector_type(type)* vec)																																																\
{																																																																\
	if(vec->size > 0) {																																																											\
		vec->size--;																																																											\
	}																																																															\
}																																																																\
struct iterator_type(vector_type(type)) vector_function(type, insert) vector_function_signature(type, struct iterator_type(vector_type(type)) *position, type value)																							\
{																																																																\
	ptrdiff_t from_end = (vector_end(*vec).ptr) - position->ptr;																																																		\
	memcpy(position->ptr, position->ptr, from_end * sizeof(type));																																																\
	memcpy(position->ptr, &value, sizeof(type)); ++vec->size;																																																	\
																																																																\
	ptrdiff_t from_beginning = position->ptr - vector_end(*vec).ptr;																																																\
	struct iterator_type(vector_type(type)) it = { &iterator_vtbl(vector_type(type)), vec->data + from_beginning };																																				\
																																																																\
	return it;																																																													\
}																																																																\
struct iterator_type(vector_type(type)) vector_function(type, insert_range) vector_function_signature(type, struct iterator_type(vector_type(type))* position, struct iterator_type(vector_type(type))* begin, struct iterator_type(vector_type(type))* end)	\
{																																																																\
	return *position;																																																											\
}																																																																\
struct iterator_type(vector_type(type)) vector_function(type, erase) vector_function_signature(type, struct iterator_type(vector_type(type))* position)																											\
{																																																																\
	memcpy(position->ptr, position->ptr + 1, (vector_end(*vec).ptr - position->ptr) * sizeof(type));																																							\
	vec->size--;																																																												\
																																																																\
	struct iterator_type(vector_type(type)) it = { &iterator_vtbl(vector_type(type)), position->ptr == vector_end(*vec).ptr ? vector_end(*vec).ptr : position->ptr + 1 };																						\
																																																																\
	return it;																																																													\
}																																																																\
struct iterator_type(vector_type(type)) vector_function(type, erase_range) vector_function_signature(type, struct iterator_type(vector_type(type))* begin, struct iterator_type(vector_type(type))* end)														\
{																																																																\
	ptrdiff_t difference = end->ptr - begin->ptr;																																																				\
	memcpy(begin->ptr, end->ptr, (difference + 1) * sizeof(type));																																																\
	vec->size -= difference;																																																									\
																																																																\
	struct iterator_type(vector_type(type)) it = { &iterator_vtbl(vector_type(type)), begin->ptr == vector_end(*vec).ptr ? vector_end(*vec).ptr : begin->ptr + 1 };																								\
																																																																\
	return it;																																																													\
}																																																																\
void vector_function(type, clear) vector_function_signature(type)																																																\
{																																																																\
	vec->size = 0;																																																												\
}																																																																\
void iterator_function(vector_type(type), next) iterator_function_signature(vector_type(type))																																									\
{																																																																\
	++(it->ptr);																																																												\
																																																																\
}																																																																\
void iterator_function(vector_type(type), prev) iterator_function_signature(vector_type(type))																																									\
{																																																																\
	--(it->ptr);																																																												\
}																																																																\
type iterator_function(vector_type(type), value) iterator_function_signature(vector_type(type))																																									\
{																																																																\
	return *(it->ptr);																																																											\
}																																																																\
void reverse_iterator_function(vector_type(type), next) reverse_iterator_function_signature(vector_type(type))																																					\
{																																																																\
	--(it->ptr);																																																												\
}																																																																\
void reverse_iterator_function(vector_type(type), prev) reverse_iterator_function_signature(vector_type(type))																																					\
{																																																																\
	++(it->ptr);																																																												\
}																																																																\
type reverse_iterator_function(vector_type(type), value) reverse_iterator_function_signature(vector_type(type))																																					\
{																																																																\
	return *(it->ptr - 1);																																																										\
}																																																																

#define vector_link(type, name) (name).vtbl = &vector_vtbl(type);																																																	
																																																																
#define vector_init(vec, capacity)				(vec).vtbl->init(&vec, capacity)																																												
#define vector_init_from_array(vec, arr, size)	(vec).vtbl->init_from_array(&vec, arr, size)																																									
																																																																
#define vector_begin(vec)						(vec).vtbl->begin(&vec)																																															
#define vector_end(vec)							(vec).vtbl->end(&vec)																																															
#define vector_rbegin(vec)						(vec).vtbl->rbegin(&vec)																																														
#define vector_rend(vec)						(vec).vtbl->rend(&vec)																																															
																																																																
#define vector_size(vec)						(vec).vtbl->size(&vec)																																															
#define vector_resize(vec, size)				(vec).vtbl->resize(&vec, size)																																													
#define vector_capacity(vec)					(vec).vtbl->capacity(&vec)																																														
#define vector_reserve(vec, capacity)			(vec).vtbl->reserve(&vec, capacity)																																												
#define vector_alloc_size(vec)					(vec).vtbl->alloc_size(&vec)

#define vector_at(vec, index)					(vec).vtbl->at(&vec, index)
#define vector_front(vec)						(vec).vtbl->front(&vec)
#define vector_back(vec)						(vec).vtbl->back(&vec)
#define vector_data(vec)						(vec).vtbl->data(&vec)

#define vector_push_back(vec, val)				(vec).vtbl->push_back(&vec, val)
#define vector_pop_back(vec)					(vec).vtbl->pop_back(&vec)
#define vector_insert(vec, position, val)		(vec).vtbl->insert(&vec, &position, val)
#define vector_erase(vec, position)				(vec).vtbl->erase(&vec, &position)
#define vector_erase_range(vec, begin, end)		(vec).vtbl->erase_range(&vec, &begin, &end)
#define vector_clear(vec)

#define vector_iterator(type)					iterator_type(vector_type(type))
#define vector_reverse_iterator(type)			reverse_iterator_type(vector_type(type))


#define iterator_does_not_equal(it_a, it_b)		((it_a).ptr != (it_b).ptr)

#define iterator_next(it)						(it).vtbl->next(&it)
#define iterator_prev(it)						(it).vtbl->prev(&it)

#define iterator_value(it)						(it).vtbl->value(&it)

#endif