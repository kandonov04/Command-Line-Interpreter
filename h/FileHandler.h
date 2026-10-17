#ifndef FileHandler_h
#define FileHandler_h

#include <string>

class FileHandler
{
public:

	//Constructor.
	FileHandler();

	//Destructor.
	~FileHandler() = default;

	//Reads from a file.
	std::string read(std::string filename);

	//Write text in a file.
	void write(std::string filename, std::string linija);

	//Append text in a file.
	void append(std::string filename, std::string linija);

};

#endif

