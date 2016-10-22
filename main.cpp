#include "crop_split.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Crop_Split w;
	w.show();
	return a.exec();
}
