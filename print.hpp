#ifndef __KNTR_PRINT
#define __KNTR_PRINT

#include <string>
#include "types.hpp"

#define KNTR_GREEN "\x1b[32m"
#define KNTR_RED "\x1b[31m"
#define KNTR_NORMAL "\x1b[m"

std::string render_columns(Array<Column> columns);

#endif
