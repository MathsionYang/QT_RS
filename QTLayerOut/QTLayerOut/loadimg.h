#pragma once
#include <QtWidgets>
#include <QToolBar>
#include <QMenu>
#include <QAction>
#include <QtWidgets/QMainWindow>
#include "ui_LoadImgWin.h"
#include "ui_qtlayerout.h"
#pragma execution_character_set("utf-8")	
class LoadImg : public QMainWindow
{
	Q_OBJECT

public:
	LoadImg(QWidget *parent = Q_NULLPTR);
	~LoadImg();
	
private:
	Ui::LoadImg ui;
	//void AddMenu_win();
	QAction * test;   //�Զ����QAc

private slots:

};
