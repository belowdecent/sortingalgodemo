#include <chrono>
#include <iostream>
#include <cstdlib>
#include <string>
#include <thread>

#include "print.hpp"
#include "types.hpp"

void delay(int delay) {
	std::this_thread::sleep_for(std::chrono::milliseconds(delay));
}

void delay_print(int delay_time, std::string text) {
	delay(delay_time);

	std::cout << "\033c" << text << std::flush;
}

void reset_compared(Array<Column> arr) {
	for (int clear = 0; clear < arr.size; clear++) {
		arr.data[clear].compared = false;
	}
}

void shuffle(Array<Column> arr, int shuffle_times) {
	for (int i = 0; i < shuffle_times; i++) {
		int index1 = std::rand() % arr.size;
		int index2;
		do {
			index2 = std::rand() % arr.size;
		} while (index1 == index2);

		int buf = arr.data[index1].value;
		arr.data[index1].value = arr.data[index2].value;
		arr.data[index2].value = buf;

		delay_print(10, render_columns(arr));
	}
}

void insertion_sort_partial(Array<Column> arr, int d, int offset) {
	for (int i = 1; i < arr.size / d; i++) {
		if (d * i + offset >= arr.size) break;

		reset_compared(arr);

		int val = arr.data[d * i + offset].value;

		int j = i - 1;

		for (j = i - 1; j >= 0; j--) {
			reset_compared(arr);
			arr.data[d * i + offset].compared = true;
			arr.data[d * j + offset].compared = true;
			delay_print(60, render_columns(arr));

			if (val > arr.data[d * j + offset].value) {
				break;
			}
		}

		j += 1;

		if (j < i) {
			for (int k = i; k > j; k--) {
				arr.data[k*d + offset].value = arr.data[(k-1)*d + offset].value;
			}
		}
		arr.data[j*d + offset].value = val;
	}
}

void insertion_sort(Array<Column> arr) {
	insertion_sort_partial(arr, 1, 0);
}

void shell_sort(Array<Column> arr) {
	int d = arr.size / 2;

	for (d = arr.size / 2; d > 1; d /= 2) {
		for (int offset = 0; offset < d; offset++) {
			insertion_sort_partial(arr, d, offset);
		}
	}

	insertion_sort(arr);
}

void bubble_sort(Array<Column> arr) {
	bool swapped = true;

	for (int i = arr.size - 1; i > 0; i--) {
		if (!swapped) {
			return;
		} else {
			swapped = false;
		}
		for (int j = 0; j < i; j++) {
			reset_compared(arr);
			arr.data[j].compared = true;
			arr.data[j + 1].compared = true;
			delay_print(60, render_columns(arr));

			if (arr.data[j].value > arr.data[j + 1].value) {
				int buf = arr.data[j].value;
				arr.data[j].value = arr.data[j + 1].value;
				arr.data[j + 1].value = buf;

				swapped = true;
			}
		}
	}
}

void finish(Array<Column> columns) {
	reset_compared(columns);
	for (int i = 0; i < columns.size; i++) {
		columns.data[i].completed = true;
		delay_print(30, render_columns(columns));
	}
}


int main() {
	delay_print(10, "Shell sort\n");
	delay(3000);

	Array<Column> arr = create_array<Column>(40);
	for (int i = 0; i < arr.size; i++) {
		arr.data[i].value = i + 1;
	}
	delay_print(60, render_columns(arr));
	delay(1000);

	shuffle(arr, 500);
	delay(1000);

	shell_sort(arr);

	finish(arr);
	delay(3000);

	for (int i = 0; i < arr.size; i++) {
		arr.data[i].completed = false;
	}

	delay_print(10, "Bubble sort\n");
	delay(3000);

	delay_print(60, render_columns(arr));
	delay(1000);

	shuffle(arr, 500);
	delay(1000);

	bubble_sort(arr);
	finish(arr);

	std::free(arr.data);
}
