#ifndef MD_PARSER_H
#define MD_PARSER_H

#include <string>
#include "myset.h"
#include "pageparser.h"

class PageParserMD : public PageParser {
 public:
 	virtual void parseHelper(std::string word, myset<std::string>& allWords);
 	virtual void parse(std::string filename, myset<std::string>& allWords, 
 		myset<std::string>& allLinks);
};

#endif
