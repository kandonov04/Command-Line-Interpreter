#include <iostream>
#include "../h/Reader.h"

Reader::Reader()
{
}

std::string Reader::read(){
	std::string line;

	std::getline(std::cin,line);
	if (line.length() > 512) {
		line.resize(512);
	}

	return line;
}

std::string Reader::readMultipleLines()
{
	std::string line;
	std::string text;

	while (std::getline(std::cin, line)) {
		if (line.length() > 512) {
			line.resize(512);
		}
		text += line + '\n';
	}
	text = text.substr(0, text.length() - 1);
	std::cin.clear();

	return text;
}