#ifndef ErrorHandler_h
#define ErrorHandler_h

#include <string>
#include <exception>

class ErrorHandler : public std::exception
{
public:

	//Constructor.
	ErrorHandler(std::string arg);

	//Destructor.
	~ErrorHandler() = default;

	//Returns description of an error based on helper, that is passed to the constructor as an argument.
	virtual const char* what() const noexcept;

private:

	std::string helper;
};

#endif