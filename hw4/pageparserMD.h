#ifndef MD_PARSER_H
#define MD_PARSER_H

#include <string>
#include "myset.h"
#include "pageparser.h"

class PageParserMD : public PageParser {
 public:
 	virtual void parse(std::string filename, MySetString& allWords, 
 		MySetString& allLinks);
};

#endif
