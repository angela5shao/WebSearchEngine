#ifndef SEARCHENG_H
#define SEARCHENG_H

#include <map>
#include <vector>
#include <string>
#include "webpage.h"
#include "myset.h"
#include "pageparser.h"
using namespace std;

/* Store all webpages and indexing data
  and perform search operations 
  and return appropriate webpages
*/

class SearchEng {
 public:
  SearchEng();
  ~SearchEng();
  
  void add_parse_from_index_file(std::string index_file, PageParser* parser);
  void add_parse_page(std::string filename, PageParser* parser);
  
  MySetWebPage findPg(string words);
  MySetWebPage findANDPg(std::string words);
  MySetWebPage findORPg(std::string words);

  WebPage* findWebPage(std::string filename);

 private:
  MySetWebPage allPages_;
  map<string, vector<WebPage*> > myMap_; // maps search word to matching webpages
  map<string, WebPage*> fileMap_; // maps filename to corresponding WebPage*
  map<string, MySetString> outLink_; // maps filename to set of names of outlinks
};

#endif
