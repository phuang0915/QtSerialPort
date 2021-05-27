#include "QtSerialPort.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtSerialPort w;
	w.show();
	return a.exec();
}
