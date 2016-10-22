/********************************************************************************
** Form generated from reading UI file 'crop_split.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CROP_SPLIT_H
#define UI_CROP_SPLIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Crop_SplitClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;
    QSlider *verticalSlider_zoom;
    QToolButton *toolButton_zoomOut;
    QPushButton *pushButton_openFile;
    QToolButton *toolButton_dragMode;
    QToolButton *toolButton_selectMode;
    QToolButton *toolButton_zoomIn;
    QPushButton *pushButton_setPath;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Crop_SplitClass)
    {
        if (Crop_SplitClass->objectName().isEmpty())
            Crop_SplitClass->setObjectName(QStringLiteral("Crop_SplitClass"));
        Crop_SplitClass->resize(587, 423);
        Crop_SplitClass->setMinimumSize(QSize(400, 300));
        centralWidget = new QWidget(Crop_SplitClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        gridLayout->addWidget(graphicsView, 3, 0, 6, 1);

        verticalSlider_zoom = new QSlider(centralWidget);
        verticalSlider_zoom->setObjectName(QStringLiteral("verticalSlider_zoom"));
        verticalSlider_zoom->setValue(0);
        verticalSlider_zoom->setSliderPosition(0);
        verticalSlider_zoom->setOrientation(Qt::Vertical);

        gridLayout->addWidget(verticalSlider_zoom, 7, 1, 1, 2);

        toolButton_zoomOut = new QToolButton(centralWidget);
        toolButton_zoomOut->setObjectName(QStringLiteral("toolButton_zoomOut"));

        gridLayout->addWidget(toolButton_zoomOut, 8, 1, 1, 2);

        pushButton_openFile = new QPushButton(centralWidget);
        pushButton_openFile->setObjectName(QStringLiteral("pushButton_openFile"));
        pushButton_openFile->setMinimumSize(QSize(80, 30));

        gridLayout->addWidget(pushButton_openFile, 3, 1, 1, 2);

        toolButton_dragMode = new QToolButton(centralWidget);
        toolButton_dragMode->setObjectName(QStringLiteral("toolButton_dragMode"));
        toolButton_dragMode->setMinimumSize(QSize(20, 0));
        toolButton_dragMode->setCheckable(true);
        toolButton_dragMode->setChecked(true);
        toolButton_dragMode->setToolButtonStyle(Qt::ToolButtonIconOnly);
        toolButton_dragMode->setAutoRaise(false);

        gridLayout->addWidget(toolButton_dragMode, 5, 2, 1, 1);

        toolButton_selectMode = new QToolButton(centralWidget);
        toolButton_selectMode->setObjectName(QStringLiteral("toolButton_selectMode"));
        toolButton_selectMode->setMinimumSize(QSize(20, 0));
        toolButton_selectMode->setCheckable(true);
        toolButton_selectMode->setChecked(false);

        gridLayout->addWidget(toolButton_selectMode, 5, 1, 1, 1);

        toolButton_zoomIn = new QToolButton(centralWidget);
        toolButton_zoomIn->setObjectName(QStringLiteral("toolButton_zoomIn"));

        gridLayout->addWidget(toolButton_zoomIn, 6, 1, 1, 2);

        pushButton_setPath = new QPushButton(centralWidget);
        pushButton_setPath->setObjectName(QStringLiteral("pushButton_setPath"));

        gridLayout->addWidget(pushButton_setPath, 4, 1, 1, 2);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        Crop_SplitClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Crop_SplitClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Crop_SplitClass->setStatusBar(statusBar);

        retranslateUi(Crop_SplitClass);

        QMetaObject::connectSlotsByName(Crop_SplitClass);
    } // setupUi

    void retranslateUi(QMainWindow *Crop_SplitClass)
    {
        Crop_SplitClass->setWindowTitle(QApplication::translate("Crop_SplitClass", "Crop_Split", 0));
#ifndef QT_NO_TOOLTIP
        toolButton_zoomOut->setToolTip(QApplication::translate("Crop_SplitClass", "<html><head/><body><p>\347\274\251\345\260\217</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        toolButton_zoomOut->setText(QApplication::translate("Crop_SplitClass", "-", 0));
        pushButton_openFile->setText(QApplication::translate("Crop_SplitClass", "\346\211\223\345\274\200\345\233\276\347\211\207", 0));
        toolButton_dragMode->setText(QApplication::translate("Crop_SplitClass", "\346\211\230\346\213\275", 0));
        toolButton_selectMode->setText(QApplication::translate("Crop_SplitClass", "\351\200\211\347\202\271", 0));
#ifndef QT_NO_TOOLTIP
        toolButton_zoomIn->setToolTip(QApplication::translate("Crop_SplitClass", "<html><head/><body><p>\346\224\276\345\244\247</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        toolButton_zoomIn->setText(QApplication::translate("Crop_SplitClass", "+", 0));
        pushButton_setPath->setText(QApplication::translate("Crop_SplitClass", "\346\233\264\346\224\271\350\276\223\345\207\272\347\233\256\345\275\225", 0));
    } // retranslateUi

};

namespace Ui {
    class Crop_SplitClass: public Ui_Crop_SplitClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CROP_SPLIT_H
