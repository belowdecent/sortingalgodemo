#ifndef __KNTR_TYPES
#define __KNTR_TYPES

#include <cstdlib>

struct Column {
	int value;
	bool compared;
	bool completed;
};

template <typename T>
struct Array {
	T* data;
	int size;
};

template <typename T>
Array<T> create_array(int size) {
	return {
		.data = (T*)std::malloc(sizeof(T) * size),
		.size = size,
	};
}

#endif
