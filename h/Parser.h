#ifndef Parser_h
#define Parser_h

#include <set>
#include <vector>
#include <regex>

#include "Reader.h"
#include "Types.h"
#include "Lexer.h"

class Parser
{
public:

	//Constructor.
	Parser();

	//Destructor.
	~Parser();

	//Removes whitespace until it encounters the first non-whitespace character.
	void cutBlanco(std::string& linija, int& cnt);

	//Removes all characters up to the first whitespace from the line and returns them as a new word.
	std::string getWord(std::string& linija);

	//Parses the line and inserts the values into a vector myData.
	void parse(std::string linija);

	//Pushes new argument if needed.
	inline void pushArgument(std::string argument, int i) { myData[i]->arg.push_back(argument); };

	//Replaces argument vector if needed.
	inline void changeArgument(std::vector<std::string> arg, int i) { myData[i]->arg = arg; };

	//Returns myData vector.
	inline std::vector<Types::Data*> getData() const { return this->myData; };

private:

	Reader* reader;
	Lexer* lexer;
	std::vector< Types::Data*> myData;

	std::set<std::string> zeroArg = { "time", "date"};
	std::set<std::string> oneArgL = { "rm", "truncate", "touch",  "prompt" };
	std::set<std::string> oneArg = { "echo", "wc", "head", "batch"};
	std::set<std::string> twoArg = { "tr" };

	std::set<std::string> noArg = { "echo", "wc", "head", "batch", "rm", "truncate", "touch",  "prompt" };
	std::set<std::string> yesArg = { "tr" };

};

#endif


