#include "../h/LexicalError.h"

LexicalError::LexicalError(std::string line, int cnt)
{
	this->line = line;
	position = cnt;
}

const char* LexicalError::what() const noexcept
{
	std::cout << line << std::endl;
	std::cout << std::string(position, ' ') << "^" << std::endl;
	return "Lexical error! Unexpected character";
}
