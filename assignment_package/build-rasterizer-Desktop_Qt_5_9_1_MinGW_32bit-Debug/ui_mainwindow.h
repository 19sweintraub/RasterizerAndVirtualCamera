/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
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
    QAction *actionLoad_Scene;
    QAction *actionSave_Image;
    QAction *actionEquilateral_Triangle;
    QAction *actionQuit_Esc;
    QWidget *centralWidget;
    QGraphicsView *scene_display;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuScenes;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(612, 612);
        actionLoad_Scene = new QAction(MainWindow);
        actionLoad_Scene->setObjectName(QStringLiteral("actionLoad_Scene"));
        actionSave_Image = new QAction(MainWindow);
        actionSave_Image->setObjectName(QStringLiteral("actionSave_Image"));
        actionEquilateral_Triangle = new QAction(MainWindow);
        actionEquilateral_Triangle->setObjectName(QStringLiteral("actionEquilateral_Triangle"));
        actionQuit_Esc = new QAction(MainWindow);
        actionQuit_Esc->setObjectName(QStringLiteral("actionQuit_Esc"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        scene_display = new QGraphicsView(centralWidget);
        scene_display->setObjectName(QStringLiteral("scene_display"));
        scene_display->setEnabled(false);
        scene_display->setGeometry(QRect(50, 25, 512, 512));
        scene_display->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scene_display->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scene_display->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        scene_display->setInteractive(false);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 612, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuScenes = new QMenu(menuBar);
        menuScenes->setObjectName(QStringLiteral("menuScenes"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuScenes->menuAction());
        menuFile->addAction(actionLoad_Scene);
        menuFile->addAction(actionSave_Image);
        menuFile->addAction(actionQuit_Esc);
        menuScenes->addAction(actionEquilateral_Triangle);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionLoad_Scene->setText(QApplication::translate("MainWindow", "Load Scene (Ctrl+O)", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionLoad_Scene->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionSave_Image->setText(QApplication::translate("MainWindow", "Save Image (Ctrl+S)", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionSave_Image->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionEquilateral_Triangle->setText(QApplication::translate("MainWindow", "Equilateral Triangle", Q_NULLPTR));
        actionQuit_Esc->setText(QApplication::translate("MainWindow", "Quit (Esc)", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuScenes->setTitle(QApplication::translate("MainWindow", "Scenes", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
