#ifndef LIST_H_
#define LIST_H_

#pragma once

#include "iterator.h"

#define list_type(type) list_##type
#define list_node_type(type) list_node_##type
#define list_vtbl(type) list_type(type)##_vtbl
#define list_function(type, name) list_type(type)##_##name
#define list_function_signature(type, ...) (struct list_type(type) *list, __VA_ARGS__)

#define list_import_type(type)																																																	\
struct iterator_vtbl(list_type(type)) {																																															\
	void(*next)  iterator_function_signature(list_type(type));																																									\
	void(*prev)  iterator_function_signature(list_type(type));																																									\
	int(*value) iterator_function_signature(list_type(type));																																									\
};																																																								\
struct reverse_iterator_vtbl(list_type(type)) {																																													\
	void(*next) reverse_iterator_function_signature(list_type(type));																																							\
	void(*prev) reverse_iterator_function_signature(list_type(type));																																							\
	type(*value) reverse_iterator_function_signature(list_type(type));																																							\
};																																																								\
extern const struct iterator_vtbl(list_type(type)) iterator_vtbl(list_type(type));																																				\
extern const struct reverse_iterator_vtbl(vector_type(type)) reverse_iterator_vtbl(list_type(type));																															\
struct iterator_type(list_type(type)) {																																															\
	const struct iterator_vtbl(list_type(type)) *vtbl;																																											\
	type *ptr;																																																					\
};																																																								\
struct reverse_iterator_type(list_type(type)){																																													\
	const struct reverse_iterator_vtbl(list_type(type)) *vtbl;																																									\
	type *ptr;																																																					\
};																																																								\
struct list_vtbl(type) {																																																		\
	int(*init)													list_function_signature(type, uint32_t);																														\
	int(*init_from_array)										list_function_signature(type, type*, uint32_t);																													\
	struct iterator_type(list_type(type))(*begin)				list_function_signature(type);																																	\
	struct iterator_type(list_type(type))(*end)					list_function_signature(type);																																	\
	struct reverse_iterator_type(list_type(type))(*rbegin)		list_function_signature(type);																																	\
	struct reverse_iterator_type(list_type(type))(*rend)		list_function_signature(type);																																	\
	struct iterator_type(vector_type(type))(*insert)			list_function_signature(type, struct iterator_type(vector_type(type))*, int);																					\
	struct iterator_type(vector_type(type))(*insert_range)		list_function_signature(type, struct iterator_type(vector_type(type))*, struct iterator_type(vector_type(type))*, struct iterator_type(vector_type(type))*);	\
	struct iterator_type(vector_type(type))(*erase)				list_function_signature(type, struct iterator_type(vector_type(type))*);																						\
	struct iterator_type(vector_type(type))(*erase_range)		list_function_signature(type, struct iterator_type(vector_type(type))*, struct iterator_type(vector_type(type))*);												\
	void(*clear)												list_function_signature(type);																																	\
};																																																								\
extern const struct list_vtbl(type) list_vtbl(type);																																											\
struct list_node_type(type)																																																		\
{																																																								\
	list_node_type(type) *next, *prev;																																															\
};\
struct list_type(type) {																																																		\
	struct list_vtbl(type) *vtbl;																																																\
	uint32_t size;																																																				\
	list_node_type(type) *head, *tail;																																																					\
};

#define list(type, name)	struct list_type(type) name

#define list_generate_prototypes(type)																																																						\
int														list_function(type, init) list_function_signature(type, uint32_t);																																	\
int														list_function(type, init_from_array) list_function_signature(type, type*, uint32_t);																												\
struct iterator_type(list_type(type))					list_function(type, begin) list_function_signature(type);																																			\
struct iterator_type(list_type(type))					list_function(type, end) list_function_signature(type);																																				\
struct reverse_iterator_type(list_type(type))			list_function(type, rbegin) list_function_signature(type);																																			\
struct reverse_iterator_type(list_type(type))			list_function(type, rend) list_function_signature(type);\

#define list_generate_definitions(type)	\
int list_function(type, init) list_function_signature(type, uint32_t) \
{ \
	\
}\

#endif