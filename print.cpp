#include "print.hpp"

std::string render_columns(Array<Column> columns) {
	int max_height = 0;

	for (int i = 0; i < columns.size; i++) {
		if (columns.data[i].value > max_height) max_height = columns.data[i].value;
	}

	std::string buf = "";

	for (int line = max_height / 2; line > 0; line--) {
		for (int i = 0; i < columns.size; i++) {
			if (columns.data[i].completed) {
				buf += KNTR_GREEN;
			} else if (columns.data[i].compared) {
				buf += KNTR_RED;
			} else {
				buf += KNTR_NORMAL;
			}
			
			if (columns.data[i].value >= line * 2) {
				// print full block
				buf += "█▌";
			} else if (columns.data[i].value == line * 2 - 1) {
				// print half block
				buf += "▄▖";
			} else {
				buf += "  ";
			}
		}
		buf += "\n";
	}

	return buf;
}
