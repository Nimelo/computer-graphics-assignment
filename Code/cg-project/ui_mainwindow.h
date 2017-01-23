/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionRot_45_about_y;
    QAction *actionRot_45_about_x;
    QAction *actionRot_45_about_z;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuRotation;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        actionRot_45_about_y = new QAction(MainWindow);
        actionRot_45_about_y->setObjectName(QStringLiteral("actionRot_45_about_y"));
        actionRot_45_about_x = new QAction(MainWindow);
        actionRot_45_about_x->setObjectName(QStringLiteral("actionRot_45_about_x"));
        actionRot_45_about_z = new QAction(MainWindow);
        actionRot_45_about_z->setObjectName(QStringLiteral("actionRot_45_about_z"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        menuRotation = new QMenu(menuBar);
        menuRotation->setObjectName(QStringLiteral("menuRotation"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuRotation->menuAction());
        menuRotation->addSeparator();
        menuRotation->addAction(actionRot_45_about_y);
        menuRotation->addAction(actionRot_45_about_x);
        menuRotation->addAction(actionRot_45_about_z);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionRot_45_about_y->setText(QApplication::translate("MainWindow", "Rot 45 about y", 0));
        actionRot_45_about_x->setText(QApplication::translate("MainWindow", "Rot 45 about x", 0));
        actionRot_45_about_z->setText(QApplication::translate("MainWindow", "Rot 45 about z", 0));
        menuRotation->setTitle(QApplication::translate("MainWindow", "Rotation", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
