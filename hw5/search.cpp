#include "multiwin.h"
#include <QApplication>

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	Multiwin multiWin(argv[1]);
	multiWin.show();
	
	return app.exec();
}