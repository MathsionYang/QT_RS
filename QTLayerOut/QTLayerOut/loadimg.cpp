#include "loadimg.h"

LoadImg::LoadImg(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	
	//AddMenu_win();
}

LoadImg::~LoadImg()
{
}
//void LoadImg::AddMenu_win() {
//	QMenu *file = menuBar()->addMenu(tr("文件"));
//	// 菜单动作
//	QAction *Act_file_new = new QAction(QIcon("../Image/file/New.png"), tr("新建"), this);
//	Act_file_new->setShortcuts(QKeySequence::New);  // 快捷键 Ctrl+N
//	connect(Act_file_new, SIGNAL(triggered()), this, SLOT(File_new()));
//	
//	file->addAction(Act_file_new);
//}
