#include "../h/Lexer.h"
#include "../h/LexicalError.h"

Lexer::Lexer()
{
}

void Lexer::checkWholeLine(std::string line)
{
	std::string allowedChars = "-<>\"./\\|";
	size_t pos = std::string::npos;
	bool flag = false;
	for (size_t i = 0; i < line.size(); ++i) {
		char c = line[i];
		if (c == '"') {
			flag = !flag;
			continue;
		}
		if (!flag) {
			if (!std::isalnum(static_cast<unsigned char>(c)) && allowedChars.find(c) == std::string::npos && c != ' ') {
				pos = i;
				break;
			}
		}
	}

	if (!(pos == std::string::npos)) {
		throw LexicalError(line, pos);
	}
}

void Lexer::check(std::string line, std::string mode, int cnt, std::string arg)
{
	if (mode == "cmd") {
		for (size_t i = 0; i < arg.length(); i++) {
			if (!std::isalnum(static_cast<unsigned char>(arg[i]))) {
				throw LexicalError(line, cnt + i);
			}
		}
	}
	else if (mode == "opt") {
		for (size_t i = 1; i < arg.length(); i++) {
			if (!std::isalnum(static_cast<unsigned char>(arg[i]))) {
				throw LexicalError(line, cnt + i);
			}
		}
	}
}
