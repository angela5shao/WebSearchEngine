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
  
  myset<WebPage*> findPg(string words);
  myset<WebPage*> findANDPg(std::string words);
  myset<WebPage*> findORPg(std::string words);

  WebPage* findWebPage(std::string filename);

 private:
  myset<WebPage*> allPages_;
  map<string, vector<WebPage*> > myMap_; // maps search word to matching webpages
  map<string, WebPage*> fileMap_; // maps filename to corresponding WebPage*
  map<string, myset<std::string> > outLink_; // maps filename to set of names of outlinks
};

#endif
