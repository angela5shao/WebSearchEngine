# CS 104 Class Project: Web Search Engine

**To run search engine: **
- qmake -project
- qmake
- make 
- ./hw6 

**To run crawler: **
- g++ -g -Wall crawler.cpp pageparserMD.cpp webpage.cpp myset.h openConfig.h -o crawler
- ./crawler # may provide path to seed file; if not, default is configCrawler.txt
