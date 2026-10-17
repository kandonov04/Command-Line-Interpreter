#ifndef Types_h
#define Types_h

#include <string>
#include <vector>

class Types
{
public:

	//This struct is used to gather all parts of a single command into one place.
	struct Data {
		std::string cmd;
		std::string opt;
		std::vector<std::string> arg;
		std::string inputRedir;
		std::string outputRedir;
	};

};

#endif
