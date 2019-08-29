#include "qtlayerout.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
	QTLayerOut w;
	w.show();
	//GDALAllRegister();
	return a.exec();
}
