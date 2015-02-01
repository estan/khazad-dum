#include "Input.h"

#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>

namespace kd {

namespace input {

std::string line(std::string prompt) {
    std::string result;

    if (char *line = readline(prompt.c_str())) {
        if (*line) {
            add_history(line);
            result = std::string(line);
        }
        free(line);
    }

    return result;
}

void clear() {
    clear_history();
}

} // namespace input

} // namespace kd
