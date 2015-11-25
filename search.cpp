#include "multiwin.h"
#include <QApplication>

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	char* config = "config.txt";
	// if config file is provided
	if (argc != 1) {
		config = argv[1];
	}

	Multiwin multiWin(config);
	multiWin.show();
	
	return app.exec();
}