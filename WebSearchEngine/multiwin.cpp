#include <QString>
#include <fstream>
#include <iostream>
#include <sstream>

#include "multiwin.h"
#include "pageparser.h"
#include "pagerank.h"
#include "openConfig.h"
using namespace std;

struct AlphaStrComp { // given filenames
  bool operator() (const WebPage* page1, const WebPage* page2) {
    return page1->filename() < page2->filename();
  }
};
struct LTCompIn { // given size of set of webpages
    bool operator() (const WebPage* page1, const WebPage* page2) {
      return page1->incoming_links().size() < page2->incoming_links().size();
    }
};
struct LTCompOut { // given size of set of webpages
    bool operator() (const WebPage* page1, const WebPage* page2) {
      return page1->outgoing_links().size() < page2->outgoing_links().size();
    }
};
struct PRComp { // given size of set of webpages
    bool operator() (const WebPage* page1, const WebPage* page2) {
      return page1->PR() > page2->PR();
    }
};

Multiwin::Multiwin(char* argv) : QWidget(NULL)
{ 
  config = argv;

  openConfig oc(config);
  configMap = oc.returnMap();

  // Title
  setWindowTitle("Search Engine");
  QHBoxLayout* mainLayout = new QHBoxLayout;
  setLayout(mainLayout);


  // // Form to add webpages
  // Layout
  formLayout = new QVBoxLayout();
  mainLayout->addLayout(formLayout);
  formLayout->addStretch();
  // Search title
  QLabel* wordSearchLabel = new QLabel("Word search:");
  formLayout->addWidget(wordSearchLabel);
  // Filename input
  wordInput = new QLineEdit();
  connect(wordInput, SIGNAL(returnPressed()), this, SLOT(search()));
  formLayout->addWidget(wordInput);
  // Search button
  searchButton = new QPushButton("Search");
  QObject::connect(searchButton, SIGNAL(clicked()), this, SLOT(search()));
  formLayout->addWidget(searchButton);
  // sort buttons
  QGroupBox* searchSortButtons = new QGroupBox(tr("Search criteria"));
  QVBoxLayout* searchButLayout = new QVBoxLayout();
  searchSortButtons->setLayout(searchButLayout);

  searchBut1 = new QRadioButton("single");
  searchBut2 = new QRadioButton("AND");
  searchBut3 = new QRadioButton("OR");
  searchBut1->setChecked(true);
  searchButLayout->addWidget(searchBut1);
  searchButLayout->addWidget(searchBut2);
  searchButLayout->addWidget(searchBut3);
  formLayout->addWidget(searchSortButtons);



  // // List of filenames
  QVBoxLayout* listLayout = new QVBoxLayout;
  fileListWidget = new QListWidget();
  QObject::connect(fileListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(displayPage()));
  listLayout->addWidget(fileListWidget);
  mainLayout->addLayout(listLayout);
  // sort buttons
  QGroupBox* listSortButtons = new QGroupBox(tr("Sort criteria"));
  QVBoxLayout* sortButLayout = new QVBoxLayout();
  listSortButtons->setLayout(sortButLayout);

  sortBut1 = new QRadioButton("Filename");
  sortBut2 = new QRadioButton("Incoming links");
  sortBut3 = new QRadioButton("Outgoing links");
  sortBut4 = new QRadioButton("Pagerank");
  sortBut1->setChecked(true);
  sortButLayout->addWidget(sortBut1);
  sortButLayout->addWidget(sortBut2);
  sortButLayout->addWidget(sortBut3);
  sortButLayout->addWidget(sortBut4);
  QObject::connect(sortBut1, SIGNAL(toggled(bool)), this, SLOT(sortButClicked(bool))); 
  QObject::connect(sortBut2, SIGNAL(toggled(bool)), this, SLOT(sortButClicked(bool)));
  QObject::connect(sortBut3, SIGNAL(toggled(bool)), this, SLOT(sortButClicked(bool)));
  QObject::connect(sortBut4, SIGNAL(toggled(bool)), this, SLOT(sortButClicked(bool)));
  listLayout->addWidget(listSortButtons);
  

  // // Buttons (to new window & quit)
  QVBoxLayout* buttonLayout = new QVBoxLayout;
  mainButton = new QPushButton("&Open OtherWin");
  buttonLayout->addWidget(mainButton);
  QObject::connect(mainButton, SIGNAL(clicked()), this, SLOT(mainButtonClicked()));
  QPushButton* quitBut = new QPushButton("Quit");
  connect(quitBut, SIGNAL(clicked()), this, SLOT(close()));
  buttonLayout->addWidget(quitBut);
  mainLayout->addLayout(buttonLayout);


  // // Page window
  // Layout
  QHBoxLayout* otherLayout = new QHBoxLayout;
  otherLayout->addStretch();
  otherWin = new QWidget;
  otherWin->setLayout(otherLayout);
  otherWin->setAttribute(Qt::WA_QuitOnClose, false);
  // Content + title
  QVBoxLayout* contentLayout = new QVBoxLayout;
  fileTitle = new QLabel;
  content = new QTextEdit;
  contentLayout->addWidget(fileTitle);
  contentLayout->addWidget(content);
  otherLayout->addLayout(contentLayout);
  // sort buttons
  QGroupBox* listSortButtons2a = new QGroupBox(tr("Sort criteria"));
  QVBoxLayout* sortButLayout2a = new QVBoxLayout();
  listSortButtons2a->setLayout(sortButLayout2a);
  sortButO1 = new QRadioButton("Filename");
  sortButO2 = new QRadioButton("Incoming links");
  sortButO3 = new QRadioButton("Outgoing links");
  sortButO1->setChecked(true);
  sortButLayout2a->addWidget(sortButO1);
  sortButLayout2a->addWidget(sortButO2);
  sortButLayout2a->addWidget(sortButO3);
  QObject::connect(sortButO1, SIGNAL(toggled(bool)), this, SLOT(sortButClickedOtherOut(bool)));  
  QObject::connect(sortButO2, SIGNAL(toggled(bool)), this, SLOT(sortButClickedOtherOut(bool))); 
  QObject::connect(sortButO3, SIGNAL(toggled(bool)), this, SLOT(sortButClickedOtherOut(bool)));

  QGroupBox* listSortButtons2 = new QGroupBox(tr("Sort criteria"));
  QVBoxLayout* sortButLayout2 = new QVBoxLayout();
  listSortButtons2->setLayout(sortButLayout2);
  sortButI1 = new QRadioButton("Filename");
  sortButI2 = new QRadioButton("Incoming links");
  sortButI3 = new QRadioButton("Outgoing links");
  sortButI1->setChecked(true);
  sortButLayout2->addWidget(sortButI1);
  sortButLayout2->addWidget(sortButI2);
  sortButLayout2->addWidget(sortButI3);
  QObject::connect(sortButI1, SIGNAL(toggled(bool)), this, SLOT(sortButClickedOtherIn(bool)));
  QObject::connect(sortButI2, SIGNAL(toggled(bool)), this, SLOT(sortButClickedOtherIn(bool)));
  QObject::connect(sortButI3, SIGNAL(toggled(bool)), this, SLOT(sortButClickedOtherIn(bool)));

  // Button (close)
  otherButton = new QPushButton("&Close");
  QObject::connect(otherButton, SIGNAL(clicked()), this, SLOT(otherButtonClicked()));

  // Lists: incoming & outgoing files
  QVBoxLayout* inLayout = new QVBoxLayout;
  inListWidget = new QListWidget();
  inLayout->addWidget(inListWidget);
  inLayout->addWidget(listSortButtons2);
  QVBoxLayout* outLayout = new QVBoxLayout;
  outListWidget = new QListWidget();
  outLayout->addWidget(outListWidget);
  outLayout->addWidget(listSortButtons2a);
  otherLayout->addLayout(inLayout);
  otherLayout->addLayout(outLayout);
  // List clicked
  QObject::connect(inListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(displayPageIn()));
  QObject::connect(outListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(displayPageOut()));

  otherLayout->addWidget(otherButton);

  // set overall layout
  setLayout(mainLayout);
}

Multiwin::~Multiwin() {
  delete mainButton;
  /*for (set<WebPage*>::iterator it = matchingPages.begin(); it != matchingPages.end(); ++it) {
    delete (*it);
  }*/

  // Form for search
  delete wordInput;
  delete searchButton;
  delete searchBut1;
  delete searchBut2;
  delete searchBut3;

  // List of filenames
  delete sortBut1;
  delete sortBut2;
  delete sortBut3;
  delete sortBut4;

  // Page 
  delete otherButton;
  delete fileTitle;
  delete content;
  delete sortButO1;
  delete sortButO2;
  delete sortButO3;
  delete sortButI1;
  delete sortButI2;
  delete sortButI3;

  // Data
  delete myEngine;

  delete formLayout;

}

void Multiwin::search() { 
  PageParser* parser = NULL;
  myEngine = new SearchEng;
  myEngine->add_parse_from_index_file(configMap.find("INDEX_FILE")->second, parser);
  matchingPages.clear();

  // if user left input blank
  if (wordInput->text().isEmpty()) return;

  // get form value
  std::string input = wordInput->text().toStdString();

  // convert search word to lower case
  for (unsigned int i=0; i<input.length(); i++) 
    input[i] = tolower(input[i]);

  // perform search based on search criteria
  if (searchBut2->isChecked()) {
    matchingPages = myEngine->findANDPg(input);
  } else if (searchBut3->isChecked()) {
    matchingPages = myEngine->findORPg(input);
  } else {// for single word input
      matchingPages = myEngine->findPg(input);
    }
  
  bool b = true;
  sortButClicked(b);

  // Clear the form inputs
  wordInput->setText("");
}




void Multiwin::sortButClicked(bool) {
  filenames.clear();
  myset<WebPage*>::iterator it;
  for(it=matchingPages.begin(); it!=matchingPages.end(); it++){
    filenames.push_back(*it);
  }
  if(sortBut1->isChecked()) {  
    AlphaStrComp comp1;
    mergeSort (filenames, comp1);
  } else if(sortBut2->isChecked()) {  
    LTCompIn comp2;
    mergeSort (filenames, comp2);
  } else if(sortBut3->isChecked()) {  
    LTCompOut comp3;
    mergeSort (filenames, comp3);
  } else if(sortBut4->isChecked()) {
    pagerank(matchingPages, 
      atof(configMap.find("STEP_NUMBER")->second.c_str()), 
      atof(configMap.find("RESTART_PROBABILITY")->second.c_str())
      );
    filenames.clear();
    for(it=matchingPages.begin(); it!=matchingPages.end(); it++){
      filenames.push_back(*it);
    }

    PRComp comp4;
    mergeSort (filenames, comp4);
  }
   
  fileListWidget->clear();
  for(int i=0 ;i <(signed)filenames.size(); i++){
    string str = filenames[i]->filename();
    ostringstream iss;
    iss << " | in: " << filenames[i]->incoming_links().size();
    iss << " | out: " << filenames[i]->outgoing_links().size();
    str += iss.str();
    QString qstr = QString::fromStdString(str);
    fileListWidget->addItem(qstr);
  }  
}

void Multiwin::sortButClickedOtherIn(bool) {
  if (sortButI1->isChecked()) {  
    AlphaStrComp comp1;
    mergeSort (filenamesIn, comp1);
  } else if(sortButI2->isChecked()){  
    LTCompIn comp2;
    mergeSort (filenamesIn, comp2);
  } else if(sortButI3->isChecked()){  
    LTCompOut comp3;
    mergeSort (filenamesIn, comp3);
  }
   
  inListWidget->clear();
  for(int i=0 ;i <(signed)filenamesIn.size(); i++){
    string str = filenamesIn[i]->filename();
    ostringstream iss;
    iss << " | in: " << filenamesIn[i]->incoming_links().size();
    iss << " | out: " << filenamesIn[i]->outgoing_links().size();
    str += iss.str();
    QString qstr = QString::fromStdString(str);
    inListWidget->addItem(qstr);
  }  
}

void Multiwin::sortButClickedOtherOut(bool) {
  if (sortButO1->isChecked()) {  
    AlphaStrComp comp1;
    mergeSort (filenamesOut, comp1);
  } else if(sortButO2->isChecked()){ 
    LTCompIn comp2;
    mergeSort (filenamesOut, comp2);
  } else if(sortButO3->isChecked()){  
    LTCompOut comp3;
    mergeSort (filenamesOut, comp3);
    }
   
  outListWidget->clear();
  for(int i=0 ;i <(signed)filenamesOut.size(); i++){
    string str = filenamesOut[i]->filename();
    ostringstream iss;
    iss << " | in: " << filenamesOut[i]->incoming_links().size();
    iss << " | out: " << filenamesOut[i]->outgoing_links().size();
    str += iss.str();
    QString qstr = QString::fromStdString(str);
    outListWidget->addItem(qstr);
  }  
}



void Multiwin::displayPage() { 
  filenamesOut.clear();
  filenamesIn.clear();
  inListWidget->clear();
  outListWidget->clear();

  stringstream iss;
  WebPage* page = myEngine->findWebPage(filenames[fileListWidget->currentRow()]->filename()); 
  iss << (*page);

  // set content
  QString qstr = QString::fromStdString(iss.str());
  content->setText(qstr);
  // set title
  qstr = QString::fromStdString(page->filename());
  fileTitle->setText(qstr);

  // 2 lists of incoming and outgoing links
  set<WebPage*>::iterator it;
  myset<WebPage*> inPages = page->incoming_links();
  for (it = inPages.begin(); it != inPages.end(); ++it) {
    filenamesIn.push_back(*it);

    string str = (*it)->filename();
    ostringstream iss;
    iss << " | in: " << (*it)->incoming_links().size();
    iss << " | out: " << (*it)->outgoing_links().size();
    str += iss.str();
    QString qstr = QString::fromStdString(str);
    inListWidget->addItem(qstr);
  }
  myset<WebPage*> outPages = page->outgoing_links();
  for (it = outPages.begin(); it != outPages.end(); ++it) {
    filenamesOut.push_back(*it);

    string str = (*it)->filename();
    ostringstream iss;
    iss << " | in: " << (*it)->incoming_links().size();
    iss << " | out: " << (*it)->outgoing_links().size();
    str += iss.str();
    QString qstr = QString::fromStdString(str);
    outListWidget->addItem(qstr);
  }

  otherWin->show();
}

void Multiwin::displayPageIn() {
  WebPage* page = myEngine->findWebPage(filenamesIn[inListWidget->currentRow()]->filename());

  filenamesOut.clear();
  filenamesIn.clear();
  inListWidget->clear();
  outListWidget->clear();

  stringstream iss;
  iss << (*page);

  // set content
  QString qstr = QString::fromStdString(iss.str());
  content->setText(qstr);
  // set title
  qstr = QString::fromStdString(page->filename());
  fileTitle->setText(qstr);

  // 2 lists of incoming and outgoing links
  set<WebPage*>::iterator it;
  myset<WebPage*> inPages = page->incoming_links();
  for (it = inPages.begin(); it != inPages.end(); ++it) {
    filenamesIn.push_back(*it);

    string str = (*it)->filename();
    ostringstream iss;
    iss << " | in: " << (*it)->incoming_links().size();
    iss << " | out: " << (*it)->outgoing_links().size();
    str += iss.str();
    QString qstr = QString::fromStdString(str);
    inListWidget->addItem(qstr);
  }
  myset<WebPage*> outPages = page->outgoing_links();
  for (it = outPages.begin(); it != outPages.end(); ++it) {
    filenamesOut.push_back(*it);

    string str = (*it)->filename();
    ostringstream iss;
    iss << " | in: " << (*it)->incoming_links().size();
    iss << " | out: " << (*it)->outgoing_links().size();
    str += iss.str();
    QString qstr = QString::fromStdString(str);
    outListWidget->addItem(qstr);
  }

  otherWin->show();
}
void Multiwin::displayPageOut() {
  WebPage* page = myEngine->findWebPage(filenamesOut[outListWidget->currentRow()]->filename());

  filenamesOut.clear();
  filenamesIn.clear();
  inListWidget->clear();
  outListWidget->clear();

  stringstream iss;
  iss << (*page);

  // set content
  QString qstr = QString::fromStdString(iss.str());
  content->setText(qstr);
  // set title
  qstr = QString::fromStdString(page->filename());
  fileTitle->setText(qstr);

  // 2 lists of incoming and outgoing links
  set<WebPage*>::iterator it;
  myset<WebPage*> inPages = page->incoming_links();
  for (it = inPages.begin(); it != inPages.end(); ++it) {
    filenamesIn.push_back(*it);

    string str = (*it)->filename();
    ostringstream iss;
    iss << " | in: " << (*it)->incoming_links().size();
    iss << " | out: " << (*it)->outgoing_links().size();
    str += iss.str();
    QString qstr = QString::fromStdString(str);
    inListWidget->addItem(qstr);
  }
  myset<WebPage*> outPages = page->outgoing_links();
  for (it = outPages.begin(); it != outPages.end(); ++it) {
    filenamesOut.push_back(*it);

    string str = (*it)->filename();
    ostringstream iss;
    iss << " | in: " << (*it)->incoming_links().size();
    iss << " | out: " << (*it)->outgoing_links().size();
    str += iss.str();
    QString qstr = QString::fromStdString(str);
    outListWidget->addItem(qstr);
  }

  otherWin->show();
}



void Multiwin::mainButtonClicked()
{
  setWindowTitle("Search Engine");
  otherWin->show();
}
void Multiwin::otherButtonClicked()
{
  otherWin->hide();
}
