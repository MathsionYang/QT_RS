/********************************************************************************
** Form generated from reading UI file 'LoadImgWin.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADIMGWIN_H
#define UI_LOADIMGWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoadImg
{
public:

    void setupUi(QWidget *LoadImg)
    {
        if (LoadImg->objectName().isEmpty())
            LoadImg->setObjectName(QStringLiteral("LoadImg"));
        LoadImg->resize(676, 579);

        retranslateUi(LoadImg);

        QMetaObject::connectSlotsByName(LoadImg);
    } // setupUi

    void retranslateUi(QWidget *LoadImg)
    {
        LoadImg->setWindowTitle(QApplication::translate("LoadImg", "LoadImg", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoadImg: public Ui_LoadImg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADIMGWIN_H
