#ifndef WEBPAGE_H
#define WEBPAGE_H
#include <string>
#include <iostream>
#include "myset.h"
using namespace std;

class WebPage
{
 public:
  WebPage();

  WebPage(std::string filename);

  ~WebPage();

  /**
   * Sets the filename/URL of this webpage
   */
  void filename(std::string fname);

  /**
   * Returns the filename/URL of this webpage
   */
  std::string filename() const;

  /**
   * Updates the set containing all unique words in the text
   *  with the contents of the input parameter words
   */
  void all_words(const myset<string>& words);

  /**
   * Returns all the unique, tokenized words in this webpage 
   */
  myset<string> all_words() const;

  /**
   * Adds a webpage that links to this page
   */
  void add_incoming_link(WebPage* wp);

  /**
   * Returns all webpages that link to this page
   */
  myset<WebPage*> incoming_links() const;

  myset<string> incomingLinkNames() const;
  void setIncomingLinkNames(myset<string>);

  /**
   * Adds a webpage that this page links to
   */
  void add_outgoing_link(WebPage* wp);

  /**
   * Returns all webpages this page links to
   */
  myset<WebPage*> outgoing_links() const;

  myset<string> outgoingLinkNames() const;
  void setOutgoingLinkNames(myset<string>);
  void setPR(double pr);
  double PR() const;

  /**
   * Displays the webpage text to the screen 
   */
  friend std::ostream & operator<< (std::ostream & os, const WebPage & page);


 private:
  /**** Add other desired data members here *****/
  std::string fname_;
  myset<string> wordSet_;

  myset<string> outLinkNames_;
  myset<string> inLinkNames_;

  myset<WebPage*> outWebSet_;
  myset<WebPage*> inWebSet_;

  double pr_;
};
#endif
