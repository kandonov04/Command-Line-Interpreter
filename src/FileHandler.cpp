#include <fstream>
#include "../h/FileHandler.h"
#include "../h/ErrorHandler.h"

FileHandler::FileHandler()
{
}

std::string FileHandler::read(std::string filename)
{
	std::ifstream fileStream(filename);
	std::string text;
	std::string line;

	if (!fileStream.is_open()) {
		throw ErrorHandler("notExists");
	}
	else {
		while (std::getline(fileStream, line)) {
			text += line + '\n';
		}
		if (!text.empty()) {
			text = text.substr(0, text.length() - 1);
		}
	}

	return text;
}

void FileHandler::write(std::string filename, std::string line)
{
	filename = filename.substr(1);
	std::ofstream file(filename);
	if (file.is_open()) {
		file << line;
		file.close();
	}
	else {
		throw ErrorHandler("notExists");
	}
}

void FileHandler::append(std::string filename, std::string line)
{
	filename = filename.substr(2);
	std::ofstream file(filename, std::ios::app);
	if (file.is_open()) {
		file << line;
		file.close();
	}
	else {
		throw ErrorHandler("notExists");
	}
}
