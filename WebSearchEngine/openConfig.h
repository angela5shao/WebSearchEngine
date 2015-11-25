#ifndef CONFIG_H
#define CONFIG_H

#include <map>
#include <iostream>
#include <fstream>
using namespace std;

class openConfig {
public: 
	openConfig(char* configFile) {
		ifstream cFile(configFile);
		if (!cFile) {
			cout << "Cannot open configuration file" << endl;
		}

		string buf;
		string key;
		while (cFile >> buf) {
			if (buf[0] == '#') {// if a comment, do nothing
			} else if (buf[0] == '=') {
				// read in next string and add pair to map
				string val;
				cFile >> val;
				map_.insert(pair<string, string>(key, val));
			} else { // store as key
				key = buf;
			}
		}
		cFile.close();
	}
	map<string, string> returnMap() {
		return map_;
	}
private:
	map<string, string> map_;
};

#endif