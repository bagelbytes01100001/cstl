#ifndef CIRCULAR_BUFFER_H_
#define CIRCULAR_BUFFER_H_

#pragma once

#include <memory.h>
#include <stdlib.h>
#include <stdint.h>

#define circular_buffer_type(type) circular_buffer_##type
#define circular_buffer_vtbl(type) circular_buffer_type(type)##_vtbl
#define circular_buffer_function(type, name) circular_buffer_type(type)##_##name
#define circular_buffer_function_signature(type, ...) (struct circular_buffer_type(type) *buf, __VA_ARGS__)

#define circular_buffer_import_type(type)									\
struct circular_buffer_vtbl(type) {											\
	int(*init)  circular_buffer_function_signature(type, uint32_t);			\
	int(*empty) circular_buffer_function_signature(type);					\
	void(*put)  circular_buffer_function_signature(type, type);				\
	int(*get)  circular_buffer_function_signature(type);					\
};																			\
extern const struct circular_buffer_vtbl(type) circular_buffer_vtbl(type);	\
struct circular_buffer_type(type) {											\
	struct circular_buffer_vtbl(type) *vtbl;								\
	type *data;																\
	uint32_t head, tail;													\
	uint32_t size;															\
	uint32_t capacity;														\
};												

#define circular_buffer(type, name) struct circular_buffer_type(type) name

#define circular_buffer_generate_prototypes(type)												\
int  circular_buffer_function(type, init)  circular_buffer_function_signature(type, uint32_t);	\
int  circular_buffer_function(type, empty) circular_buffer_function_signature(type);			\
void circular_buffer_function(type, put)   circular_buffer_function_signature(type);			\
int circular_buffer_function(type, get)   circular_buffer_function_signature(type);				

#define circular_buffer_generate_definitions(type)														\
const struct circular_buffer_vtbl(type) circular_buffer_vtbl(type) = {									\
	&circular_buffer_function(type, init),																\
	&circular_buffer_function(type, empty),																\
	&circular_buffer_function(type, put),																\
	&circular_buffer_function(type, get)																\
};																										\
int circular_buffer_function(type, init) circular_buffer_function_signature(type, uint32_t capacity)	\
{																										\
	buf->data = malloc(capacity * sizeof(type));														\
	buf->head = 0;																						\
	buf->tail = 0;																						\
	buf->size = 0;																						\
	buf->capacity = capacity;																			\
}																										\
int circular_buffer_function(type, empty) circular_buffer_function_signature(type)						\
{																										\
	return buf->size == 0;																				\
}																										\
void circular_buffer_function(type, put)   circular_buffer_function_signature(type, type data)			\
{																										\
	buf->data[buf->head] = data;																		\
	buf->head = (buf->head + 1) % buf->capacity;														\
	buf->tail = buf->size == buf->capacity ? (buf->tail + 1) % buf->capacity : buf->tail;				\
	buf->size = buf->size < buf->capacity ? buf->size + 1 : buf->size;									\
}																										\
int circular_buffer_function(type, get)   circular_buffer_function_signature(type)						\
{																										\
	--buf->size;																						\
																										\
	return buf->data[buf->tail++ % buf->capacity];														\
}

#define circular_buffer_link(type, name) (name).vtbl = &circular_buffer_vtbl(type);

#define circular_buffer_init(buf, size) (buf).vtbl->init(&buf, size)

#define circular_buffer_empty(buf)		(buf).vtbl->empty(&buf)

#define circular_buffer_put(buf, data)  (buf).vtbl->put(&buf, data)
#define circular_buffer_get(buf)		(buf).vtbl->get(&buf)

#endif