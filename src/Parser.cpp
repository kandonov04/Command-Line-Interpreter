#include "../h/Parser.h"
#include "../h/ErrorHandler.h"

Parser::Parser()
{
    lexer = new Lexer();
    reader = new Reader();
}

Parser::~Parser()
{
    delete lexer;
    delete reader;
    for (Types::Data* ptr : myData) {
        delete ptr;
    }
}

void Parser::cutBlanco(std::string& line, int& cnt)
{
    bool onlyBlanco = true;
    for (char c : line) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            onlyBlanco = false;
            break;
        }
    }

    if (!onlyBlanco) {
        for (int i = 0; i < line.size(); i++) {
            if (!(std::isspace(static_cast<unsigned char>(line[i])))) {
                line = line.substr(i);
                return;
            }
            else {
                cnt++;
            }
        }
    }
    else {
        line.clear();
    }


}

std::string Parser::getWord(std::string& line)
{
    std::string word;

    if (line[0] == '\"') {
        for (int i = 1; i < line.size(); i++) {
            if (line[i] == '\"') {
                word = line.substr(0, i + 1);
                line = line.substr(i + 1);
                return word;
            }
        }
    }

    for (int i = 0; i < line.size(); i++) {
        if (std::isspace(static_cast<unsigned char>(line[i])) || line[i] == '|' || line[i] == '<' || line[i] == '>') {
            word = line.substr(0, i);
            line = line.substr(i);
            break;
        }
    }

    if (word.empty()) {
        word = line;
        line.clear();
    }

    return word;
}

void Parser::parse(std::string line)
{
    for (Types::Data* ptr : myData) {
        delete ptr;
    }
    myData.clear();

    std::string fullLine = line; //Used for lexical errors.
    std::string temp;

    bool flagPipe = false; //Used to indicate the entry into a pipe.
    bool optFlag = false; //True when option exists, used to check for multiple options error.
    bool inFlag = false; //True when input redirection exists, used to check for multiple redirection error.
    bool outFlag = false; //True when output redirection exists, used to check for multiple redirection error.
    bool inRdrFlag = false; //True when there are no arguments after input redirection, used to check the order.
    bool outRdrFlag = false;//True when there are no arguments after output redirection, used to check the order.

    int cnt = 0; //Keeps the order in the MyData* vector.
    int cnt2 = 0; //Used for lexical errors, keeps position of the first letter in current word.
    int wordCnt = 0; //Counts number of words in command, used to check the order.

    do {
        flagPipe = false;
        optFlag = false;
        inFlag = false;
        outFlag = false;
        inRdrFlag = false;
        outRdrFlag = false;
        wordCnt = 0;

        //At first, we check for lexical errors in the whole line, and later, for each part in a different way.
        lexer->checkWholeLine(line);

        //Loading the command name.
        cutBlanco(line, cnt2);
        myData.push_back(new Types::Data());
        myData[cnt]->cmd = getWord(line);
        lexer->check(fullLine, "cmd", cnt2, myData[cnt]->cmd); //Check for lexical errors in command name.
        cnt2 += myData[cnt]->cmd.length();
        wordCnt++;
        cutBlanco(line, cnt2);

        while (!line.empty()) {
            temp.clear();
            if (line[0] == '-') { //Loading the option.
                if (optFlag) {
                    throw ErrorHandler("multipleOpt");
                }
                if (wordCnt != 1) {
                    throw ErrorHandler("wOrder");
                }
                optFlag = true;
                myData[cnt]->opt = getWord(line);
                lexer->check(fullLine, "opt", cnt2, myData[cnt]->opt); //Check for lexical errors in option.
                cnt2 += myData[cnt]->opt.length();
                wordCnt++;
            }
            else if (line[0] == '<') { //Loading the input redirection.
                if (inFlag) {
                    throw ErrorHandler("multipleRdr");
                }
                inRdrFlag = true;
                inFlag = true;
                line = line.substr(1);
                cutBlanco(line, cnt2);
                temp = '<' + getWord(line);
                wordCnt++;
                myData[cnt]->inputRedir = temp;
                cnt2 += myData[cnt]->inputRedir.length();
            }
            else if (line[0] == '>') { //Loading the output redirection.
                if (outFlag) {
                    throw ErrorHandler("multipleRdr");
                }
                outRdrFlag = true;
                outFlag = true;
                line = line.substr(1);
                temp += '>';
                if (line[0] == '>') { //case when output redirection is "append"(>>).
                    line = line.substr(1);
                    temp += '>';
                }
                cutBlanco(line, cnt2);
                temp += getWord(line);
                wordCnt++;
                myData[cnt]->outputRedir = temp;
                cnt2 += myData[cnt]->outputRedir.length();
            }
            else if (line[0] == '|') { //Indicator for pipe, puts flagPipe to true.
                flagPipe = true;
                line = line.substr(1);
                cnt2++;
                break;
            }
            else { //Loading arguments.
                std::string arg = getWord(line);
                myData[cnt]->arg.push_back(arg);
                cnt2 += arg.length();
                inRdrFlag = false;
                outRdrFlag = false;
                wordCnt++;
                
            }
            cutBlanco(line, cnt2);
        }
        cnt++;


        if ((!inRdrFlag && inFlag) || (!outRdrFlag && outFlag)) {
            throw ErrorHandler("wOrder");
        }

    } while (flagPipe);

    if (cnt == 1) { //If command expect arguments in multiple rows, not allowed in pipe (that's what cnt == 1 is used for).
        std::string text;
        std::string temp;
        text += '"';
        if (oneArg.count(myData[0]->cmd) && myData[0]->inputRedir.empty() && myData[0]->arg.size() == 0) {
            temp = reader->readMultipleLines();
            text += temp + '"';
            if (!temp.empty()) {
                myData[0]->arg.insert(myData[0]->arg.begin(), text);
            }
        }
        else if (twoArg.count(myData[0]->cmd) && myData[0]->inputRedir.empty() && myData[0]->arg.size() == 1) {
            temp = reader->readMultipleLines();
            text += temp + '"';
            if (!temp.empty()) {
                myData[0]->arg.insert(myData[0]->arg.begin(), text);
            }
            
        }
    }
    cutBlanco(line, cnt2);
}
