#include "./h/Interpreter.h"
#include <iostream>

int main() {
	Interpreter* interpreter = Interpreter::Instance();
	while (1) {
		std::string line = interpreter->prepare();
		if (std::cin.eof()) {
			break;
		}
		interpreter->run(line);
	}
	return 0;
}

