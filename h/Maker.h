#ifndef Maker_h
#define Maker_h

#include "Command.h"
#include "Types.h"

class Maker
{
public:

	//Constructor.
	Maker();

	//Destructor.
	~Maker() = default;

	//Calls the command constructor based on the command name in it's argument.
	Command* makeCmd(Types::Data* myData);

};

#endif

