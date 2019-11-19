

#ifndef CIRCULARQ_H_
#define CIRCULARQ_H_

#include <stdarg.h>
#include <stddef.h>


#define circularq_type(type)                        circularq_##type
#define circularq_vtbl_helper(type)                 type##_vtbl
#define circularq_vtbl(type)                        circularq_vtbl_helper(type)
#define circularq_function_helper_two(type, name)   type##_##name
#define circularq_function_helper_one(type, name)   circularq_function_helper_two(type, name)
#define circularq_function(type, name)              circularq_function_helper_one(circularq_type(type), name)
#define circularq_function_signature(type, ...)     struct circularq_type(type) *queue, ##__VA_ARGS__

#define circularq_import_type(type)						                                            \
struct circularq_type(type);                                                                        \
struct circularq_vtbl(type) {								                                        \
	int   (*init)   (circularq_function_signature(type, size_t));                                   \
    int   (*empty)  (circularq_function_signature(type));		                                    \
	int   (*full)   (circularq_function_signature(type));		                                    \
	int   (*put)    (circularq_function_signature(type, type));		                                \
	type *(*get)    (circularq_function_signature(type));			                                \
};                                                                                                  \
                                                                                                    \
extern const struct circularq_vtbl(type) circularq_vtbl(type);	                                    \
struct circularq_type(type) {									                                    \
	struct circularq_vtbl(type) *vtbl;							                                    \
	type *data;													                                    \
	size_t rd, wr;											                                        \
	size_t capacity;											                                    \
    int empty, full;                                                                                \
};

#define circularq_import_type_aliased(type, alias)                                                  \
typedef type alias;                                                                                 \
circularq_import_type(alias)                                                                        \

#define circularq(type, name) struct circularq_type(type) name

#define circularq_generate_prototypes(type)										    \
int  circularq_function(type, init)  (circularq_function_signature(type, size_t));	\
int  circularq_function(type, empty) (circularq_function_signature(type));		    \
int  circularq_function(type, full)  (circularq_function_signature(type));			\
int  circularq_function(type, put)   (circularq_function_signature(type, type));	\
type *circularq_function(type, get)  (circularq_function_signature(type));

#define circularq_generate_definitions(type)														\
const struct circularq_vtbl(type) circularq_vtbl(type) = {									        \
	&circularq_function(type, init),																\
    &circularq_function(type, empty),																\
	&circularq_function(type, full),																\
	&circularq_function(type, put),																    \
	&circularq_function(type, get)																    \
};																									\
int circularq_function(type, init)(circularq_function_signature(type, size_t capacity)) {		    \
    memset(queue, 0, sizeof(*queue));																\
    queue->capacity = capacity;                                                                     \
    queue->data = (type *)malloc(sizeof(type) * queue->capacity);                                   \
    if (!queue->data) {                                                                             \
        return -1;                                                                                  \
    }                                                                                               \
    return 0;                                                                                       \
}																									\
int circularq_function(type, empty)(circularq_function_signature(type)) {						    \
	return queue->empty;																		    \
}	                                                                                                \
int circularq_function(type, full)(circularq_function_signature(type)) {						    \
	return queue->full;																		        \
}																									\
int circularq_function(type, put)(circularq_function_signature(type, type data)) {					\
    if (queue->vtbl->full(queue)) {                                                                 \
        return -1;                                                                                  \
    }                                                                                               \
    queue->data[queue->wr] = data;                                                                  \
    queue->wr = (queue->wr + 1) & (queue->capacity - 1);                                            \
    queue->empty = 0;                                                                               \
    queue->full = (queue->wr == queue->rd);                                                         \
    return 0;                                                                                       \
}																									\
type *circularq_function(type, get)(circularq_function_signature(type)) {	                        \
    if (queue->vtbl->empty(queue)) {                                                                \
        return NULL;                                                                                \
    }                                                                                               \
    queue->rd = (queue->rd + 1) & (queue->capacity - 1);                                            \
    queue->full = 0;                                                                                \
    queue->empty = (queue->wr == queue->rd);                                                        \
    return &queue->data[(queue->rd - 1) & (queue->capacity - 1)];                                   \
}


#define circularq_link(type, name)  (name).vtbl = &circularq_vtbl(type);
#define circularq_init(queue, size) (queue).vtbl->init(&buf, size)
#define circularq_empty(queue)		(queue).vtbl->empty(&buf)
#define circularq_full(queue)		(queue).vtbl->full(&buf)
#define circularq_put(queue, data)  (queue).vtbl->put(&queue, data)
#define circularq_get(queue)		(queue).vtbl->get(&buf)

#endif
