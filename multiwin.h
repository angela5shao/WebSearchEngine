#ifndef MULTIWIN_H
#define MULTIWIN_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QGroupBox>

#include <vector>
#include "searcheng.h"
#include "myset.h"
#include "webpage.h"
#include "msort.h"


class Multiwin : public QWidget
{
  Q_OBJECT
public:
  Multiwin(char* argv);
  ~Multiwin();

public slots:
  void mainButtonClicked();
  void otherButtonClicked();

  void displayPage(); 
  void displayPageIn();
  void displayPageOut();

  void search();
  void sortButClicked(bool);
  void sortButClickedOtherIn(bool);
  void sortButClickedOtherOut(bool);

private:
  QPushButton* mainButton;
  myset<WebPage*> matchingPages; 

  // Form for search
  QVBoxLayout* formLayout;
  QLineEdit* wordInput;
  QPushButton* searchButton;
  std::string searchSelect;
  QRadioButton* searchBut1;
  QRadioButton* searchBut2;
  QRadioButton* searchBut3;

  // List of filenames
  QListWidget* fileListWidget;
  QRadioButton* sortBut1;
  QRadioButton* sortBut2;
  QRadioButton* sortBut3;
  QRadioButton* sortBut4;

  // Page 
  QWidget* otherWin;
  QPushButton* otherButton;
  QLabel* fileTitle;
  QTextEdit* content;
  QListWidget* inListWidget;
  QListWidget* outListWidget;
  QRadioButton* sortButO1;
  QRadioButton* sortButO2;
  QRadioButton* sortButO3;
  QRadioButton* sortButI1;
  QRadioButton* sortButI2;
  QRadioButton* sortButI3;

  // Data
  SearchEng* myEngine;
  std::vector<WebPage*> filenames;
  std::vector<WebPage*> filenamesIn;
  std::vector<WebPage*> filenamesOut;
  char* config;
  map<string, string> configMap;

  // additional 
  /*QLabel* wordSearchLabel;
  QGroupBox* searchSortButtons;
  QVBoxLayout* searchButLayout;
  QVBoxLayout* listLayout;
  QGroupBox* listSortButtons;
  QVBoxLayout* sortButLayout;
  QVBoxLayout* buttonLayout;
  QPushButton* quitBut;
  QHBoxLayout* otherLayout;
  QVBoxLayout* contentLayout;
  QGroupBox* listSortButtons2a;
  QVBoxLayout* sortButLayout2a;
  QGroupBox* listSortButtons2;
  QVBoxLayout* sortButLayout2;
  QVBoxLayout* inLayout;
  QVBoxLayout* outLayout;*/

};

#endif