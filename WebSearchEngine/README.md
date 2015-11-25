
**To run search engine: **
- qmake -project
- qmake
- make 
- ./hw6 # may provide path to a configuration file; if not, default is config.txt

**To run crawler:**
- g++ -g -Wall crawler.cpp pageparserMD.cpp webpage.cpp myset.h openConfig.h -o crawler
- ./crawler # may provide path to seed file; if not, default is configCrawler.txt