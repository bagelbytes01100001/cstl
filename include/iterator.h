#ifndef ITERATOR_H_
#define ITERATOR_H_

#pragma once

#define iterator_type_helper(container) container##_##iterator
#define iterator_type(container)	iterator_type_helper(container)
#define iterator_vtbl_helper(container) container##_##iterator_vtbl
#define iterator_vtbl(container)	iterator_vtbl_helper(container)
#define iterator_function(container, name) iterator_type(container)##_##name
#define iterator_function_signature(container) (struct iterator_type(container) *it)

#define reverse_iterator_type_helper(container) container##_##reverse_iterator
#define reverse_iterator_type(container)	reverse_iterator_type_helper(container)
#define reverse_iterator_vtbl_helper(container) container##_##reverse_iterator_vtbl
#define reverse_iterator_vtbl(container)	reverse_iterator_vtbl_helper(container)
#define reverse_iterator_function(container, name) reverse_iterator_type(container)##_##name
#define reverse_iterator_function_signature(container) (struct reverse_iterator_type(container) *it)

#define for_each()

#endif