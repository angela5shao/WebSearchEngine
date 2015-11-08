/* ./search data/index.txt
*/
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <sstream> // added

#include "webpage.h"
#include "searcheng.h"
#include "pageparser.h" // added

using namespace std;

void display_results(set<WebPage*>& results);

int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "usage: ./search index_file...Please provide an index file" << endl;
    return 1;
  }

  /* Initialize your search engine and parse all the pages */
  SearchEng myEngine;
  PageParser* parser = NULL;
  myEngine.add_parse_from_index_file(argv[1], parser);


  string myline;
  bool done = false;
  while( !done ){
    cout << "\n++++++++++++++++++++" << endl;
    cout << "Enter search terms: " << endl;
    getline(cin, myline);
    cout << "++++++++++++++++++++\n" << endl;

    // check if user inputs '.'
    if (myline == ".") done = true;

    set<WebPage*> aWebPageSet; // WebPage set to store results

    // convert user input to lower case
    for (unsigned int i=0; i<myline.length(); i++) 
      myline[i] = tolower(myline[i]);

    for (unsigned int i=0; i<myline.length(); i++) {
      // if there's a space and it's not at the end of string
      if (myline[i] == ' ' && i != myline.length()-1) {
        // if first word is AND or OR
        if (myline.substr(0, i) == "and") {
          aWebPageSet = myEngine.findANDPg(myline.substr(i+1, myline.length()-i));
        } else if (myline.substr(0, i) == "or") {
          aWebPageSet = myEngine.findORPg(myline.substr(i+1, myline.length()-i));
        } else {
          cout << "ERROR" << endl;
        }
        break;
      } else if (i == myline.length() - 1) { // else if end of word & no space, it's single word input
        aWebPageSet = myEngine.findPg(myline);
        break;
      }
    }

    display_results(aWebPageSet);
  }
  return 0;
}

void display_results(set<WebPage*>& results) {
  int hits = results.size();
  cout << hits << " hits." << endl;
  cout << "=====" << endl;
  int i=0;
  for(set<WebPage*>::iterator it = results.begin(); it != results.end(); ++it)
    {
      cout << (*it)->filename() << endl;
      cout << "+---+" << endl;
      cout << (**it) << "\n" << endl;
      i++;
    }
  
}
