

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

#define circularq_import_type(type)						                                                    \
struct circularq_type(type);                                                                                \
struct circularq_vtbl(type) {								                                                \
	int     (*init)    (circularq_function_signature(type, size_t));                                        \
    void    (*free)    (circularq_function_signature(type));                                                \
	int     (*put)     (circularq_function_signature(type, type));                                          \
    ssize_t (*write)   (circularq_function_signature(type, type *, size_t));                                \
	int     (*get)     (circularq_function_signature(type, type *));		                                \
    ssize_t (*read)    (circularq_function_signature(type, type *, size_t));                                \
};                                                                                                          \
                                                                                                            \
extern struct circularq_vtbl(type) circularq_vtbl(type);	                                                \
struct circularq_type(type) {									                                            \
	struct circularq_vtbl(type) *vtbl;							                                            \
	type *data;													                                            \
	size_t rd, wr;											                                                \
	size_t size, capacity;											                                        \
    int empty, full;                                                                                        \
};

#define circularq_import_type_aliased(type, alias)                                                          \
typedef type alias;                                                                                         \
circularq_import_type(alias)                                                                                \

#define circularq(type, name) struct circularq_type(type) name

#define circularq_generate_prototypes(type)										                            \
int     circularq_function(type, init)    (circularq_function_signature(type, size_t));	                    \
void    circularq_function(type, free)    (circularq_function_signature(type));                             \
int     circularq_function(type, put)     (circularq_function_signature(type, type));	                    \
ssize_t circularq_function(type, write)   (circularq_function_signature(type, type *, size_t));             \
int     circularq_function(type, get)     (circularq_function_signature(type, type *));                     \
ssize_t circularq_function(type, read)    (circularq_function_signature(type, type *, size_t));

#define circularq_generate_definitions(type)														        \
struct circularq_vtbl(type) circularq_vtbl(type) = {									                    \
	&circularq_function(type, init),																        \
    &circularq_function(type, free),                                                                        \
	&circularq_function(type, put),																            \
    &circularq_function(type, write),                                                                       \
	&circularq_function(type, get),																            \
    &circularq_function(type, read)                                                                         \
};																									        \
int circularq_function(type, init)(circularq_function_signature(type, size_t capacity)) {		            \
    queue->rd = 0U;                                                                                         \
    queue->wr = 0U;                                                                                         \
    queue->empty = 1;                                                                                       \
    queue->full = 0;                                                                                        \
    queue->capacity = capacity;                                                                             \
    queue->data = (type *)malloc(sizeof(type) * queue->capacity);                                           \
    if (!queue->data) {                                                                                     \
        return -1;                                                                                          \
    }                                                                                                       \
    return 0;                                                                                               \
}																									        \
void circularq_function(type, free)(circularq_function_signature(type)) {                                   \
    free(queue->data);                                                                                      \
}                                                                                                           \
int circularq_function(type, put)(circularq_function_signature(type, type in)) {					        \
    if (queue->full) {                                                                                      \
        return -1;                                                                                          \
    }                                                                                                       \
    queue->data[queue->wr] = in;                                                                            \
    queue->wr = (queue->wr + 1U) & (queue->capacity - 1U);                                                  \
    queue->empty = 0;                                                                                       \
    queue->full = (queue->wr == queue->rd);                                                                 \
    queue ->size += 1U;                                                                                     \
    return 0;                                                                                               \
}																									        \
ssize_t circularq_function(type, write)(circularq_function_signature(type, type *buffer, size_t count)) {   \
    ssize_t ret, n = 0U;                                                                                    \
    for (; n < count; ++n) {                                                                                \
        if ((ret = circularq_put(*queue, buffer[n])) != 0) {                                                \
            return ret;                                                                                     \
        }                                                                                                   \
    }                                                                                                       \
    return n;                                                                                               \
}                                                                                                           \
int circularq_function(type, get)(circularq_function_signature(type, type *out)) {	                        \
    if (queue->empty) {                                                                                     \
        return -1  ;                                                                                        \
    }                                                                                                       \
    *out = queue->data[queue->rd];                                                                          \
    queue->rd = (queue->rd + 1U) & (queue->capacity - 1U);                                                  \
    queue->full = 0;                                                                                        \
    queue->empty = (queue->wr == queue->rd);                                                                \
    queue->size -= 1U;                                                                                      \
    return 0;                                                                                               \
}                                                                                                           \
ssize_t circularq_function(type, read) (circularq_function_signature(type, type *buffer, size_t count)) {   \
    ssize_t ret, n = 0U;                                                                                    \
    for (; n < count; ++n) {                                                                                \
        if ((ret = circularq_get(*queue, buffer + n)) != 0) {                                               \
            return ret;                                                                                     \
        };                                                                                                  \
    }                                                                                                       \
    return n;                                                                                               \
}

#define circularq_link(type, queue)       (queue).vtbl = &circularq_vtbl(type);
#define circularq_init(queue, size)       (queue).vtbl->init(&queue, size)
#define circularq_free(queue)             (queue).vtbl->free(&queue);
#define circularq_empty(queue)		      (queue).empty
#define circularq_full(queue)		      (queue).full
#define circularq_capacity(queue)         (queue).capacity
#define circularq_size(queue)		      (queue).size
#define circularq_put(queue, in)          (queue).vtbl->put(&queue, in)
#define circularq_write(queue, in, count) (queue).vtbl->write(&queue, in, count)
#define circularq_get(queue, out)		  (queue).vtbl->get(&queue, out)
#define circularq_read(queue, out, count) (queue).vtbl->read(&queue, out, count)

#endif
