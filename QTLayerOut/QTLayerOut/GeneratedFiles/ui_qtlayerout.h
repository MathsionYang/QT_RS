/********************************************************************************
** Form generated from reading UI file 'qtlayerout.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTLAYEROUT_H
#define UI_QTLAYEROUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QTLayerOutClass
{
public:
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_3;
    QDockWidget *dockWidget_2;
    QWidget *dockWidgetContents_2;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QRadioButton *radioButton_2;
    QTreeWidget *treeWidget;
    QListWidget *listWidget;
    QRadioButton *radioButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *QTLayerOutClass)
    {
        if (QTLayerOutClass->objectName().isEmpty())
            QTLayerOutClass->setObjectName(QStringLiteral("QTLayerOutClass"));
        QTLayerOutClass->resize(910, 735);
        QTLayerOutClass->setMinimumSize(QSize(910, 735));
        QTLayerOutClass->setMaximumSize(QSize(910, 735));
        centralWidget = new QWidget(QTLayerOutClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(290, 0, 611, 671));
        gridLayout_3 = new QGridLayout(gridLayoutWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setSizeConstraint(QLayout::SetMinimumSize);
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        dockWidget_2 = new QDockWidget(gridLayoutWidget);
        dockWidget_2->setObjectName(QStringLiteral("dockWidget_2"));
        dockWidget_2->setMinimumSize(QSize(590, 650));
        dockWidget_2->setMaximumSize(QSize(590, 650));
        dockWidget_2->setFloating(false);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        dockWidget_2->setWidget(dockWidgetContents_2);

        gridLayout_3->addWidget(dockWidget_2, 0, 0, 1, 1);

        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 13, 258, 661));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        radioButton_2 = new QRadioButton(layoutWidget);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));

        gridLayout->addWidget(radioButton_2, 1, 1, 1, 1);

        treeWidget = new QTreeWidget(layoutWidget);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);

        gridLayout->addWidget(treeWidget, 0, 0, 1, 2);

        listWidget = new QListWidget(layoutWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        gridLayout->addWidget(listWidget, 2, 0, 1, 2);

        radioButton = new QRadioButton(layoutWidget);
        radioButton->setObjectName(QStringLiteral("radioButton"));

        gridLayout->addWidget(radioButton, 1, 0, 1, 1);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 3, 0, 1, 1);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 3, 1, 1, 1);

        QTLayerOutClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QTLayerOutClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 910, 23));
        QTLayerOutClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QTLayerOutClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QTLayerOutClass->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(QTLayerOutClass);

        QMetaObject::connectSlotsByName(QTLayerOutClass);
    } // setupUi

    void retranslateUi(QMainWindow *QTLayerOutClass)
    {
        QTLayerOutClass->setWindowTitle(QApplication::translate("QTLayerOutClass", "QTLayerOut", nullptr));
        dockWidget_2->setWindowTitle(QApplication::translate("QTLayerOutClass", "\345\233\276\345\203\217", nullptr));
        radioButton_2->setText(QApplication::translate("QTLayerOutClass", "\345\275\251\350\211\262\345\233\276\345\203\217", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("QTLayerOutClass", "Filename", nullptr));
        radioButton->setText(QApplication::translate("QTLayerOutClass", "\347\201\260\345\272\246\345\233\276\345\203\217", nullptr));
        pushButton_2->setText(QApplication::translate("QTLayerOutClass", "\345\212\240\350\275\275", nullptr));
        pushButton->setText(QApplication::translate("QTLayerOutClass", "\345\205\263\351\227\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QTLayerOutClass: public Ui_QTLayerOutClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTLAYEROUT_H
