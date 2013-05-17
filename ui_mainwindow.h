/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Feb 11 12:45:42 2010
**      by: Qt User Interface Compiler version 4.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *averageDisplay;
    QLabel *brightnessDisplay;
    QLabel *differenceDisplay;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *averageQuadDisplay;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *moodDisplay;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_2;
    QPushButton *saveButton;
    QLabel *label_5;
    QSpinBox *spinBox;
    QPushButton *pushButton;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(596, 622);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/main/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setAutoFillBackground(true);
        label->setScaledContents(true);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        averageDisplay = new QLabel(centralWidget);
        averageDisplay->setObjectName(QString::fromUtf8("averageDisplay"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(averageDisplay->sizePolicy().hasHeightForWidth());
        averageDisplay->setSizePolicy(sizePolicy1);
        averageDisplay->setMinimumSize(QSize(0, 20));
        averageDisplay->setScaledContents(true);

        gridLayout->addWidget(averageDisplay, 2, 0, 1, 1);

        brightnessDisplay = new QLabel(centralWidget);
        brightnessDisplay->setObjectName(QString::fromUtf8("brightnessDisplay"));
        sizePolicy1.setHeightForWidth(brightnessDisplay->sizePolicy().hasHeightForWidth());
        brightnessDisplay->setSizePolicy(sizePolicy1);
        brightnessDisplay->setMinimumSize(QSize(0, 20));
        brightnessDisplay->setScaledContents(true);

        gridLayout->addWidget(brightnessDisplay, 6, 0, 1, 1);

        differenceDisplay = new QLabel(centralWidget);
        differenceDisplay->setObjectName(QString::fromUtf8("differenceDisplay"));
        sizePolicy1.setHeightForWidth(differenceDisplay->sizePolicy().hasHeightForWidth());
        differenceDisplay->setSizePolicy(sizePolicy1);
        differenceDisplay->setMinimumSize(QSize(0, 20));
        differenceDisplay->setScaledContents(true);

        gridLayout->addWidget(differenceDisplay, 8, 0, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 5, 0, 1, 1);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        averageQuadDisplay = new QLabel(centralWidget);
        averageQuadDisplay->setObjectName(QString::fromUtf8("averageQuadDisplay"));
        sizePolicy1.setHeightForWidth(averageQuadDisplay->sizePolicy().hasHeightForWidth());
        averageQuadDisplay->setSizePolicy(sizePolicy1);
        averageQuadDisplay->setMinimumSize(QSize(0, 40));
        averageQuadDisplay->setScaledContents(true);

        gridLayout->addWidget(averageQuadDisplay, 4, 0, 1, 1);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 7, 0, 1, 1);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 9, 0, 1, 1);

        moodDisplay = new QLabel(centralWidget);
        moodDisplay->setObjectName(QString::fromUtf8("moodDisplay"));
        sizePolicy1.setHeightForWidth(moodDisplay->sizePolicy().hasHeightForWidth());
        moodDisplay->setSizePolicy(sizePolicy1);
        moodDisplay->setMinimumSize(QSize(0, 20));
        moodDisplay->setScaledContents(true);

        gridLayout->addWidget(moodDisplay, 10, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout, 0, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(0, 30));
        QFont font;
        font.setPointSize(9);
        font.setBold(true);
        font.setWeight(75);
        pushButton_2->setFont(font);

        gridLayout_2->addWidget(pushButton_2, 0, 0, 1, 1);

        saveButton = new QPushButton(centralWidget);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setEnabled(false);
        saveButton->setMinimumSize(QSize(0, 30));
        saveButton->setFont(font);

        gridLayout_2->addWidget(saveButton, 1, 0, 1, 1);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_5, 0, 1, 1, 1);

        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMaximum(999999999);
        spinBox->setSingleStep(10);
        spinBox->setValue(200);

        gridLayout_2->addWidget(spinBox, 0, 2, 1, 1);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setEnabled(false);
        pushButton->setMinimumSize(QSize(0, 30));
        pushButton->setFont(font);

        gridLayout_2->addWidget(pushButton, 1, 2, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(statusBar->sizePolicy().hasHeightForWidth());
        statusBar->setSizePolicy(sizePolicy2);
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Cinemana", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        averageDisplay->setText(QString());
        brightnessDisplay->setText(QString());
        differenceDisplay->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "Average Color (Whole Image)", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Brightness (Grayscale)", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Average Color (Quartiles)", 0, QApplication::UnicodeUTF8));
        averageQuadDisplay->setText(QString());
        label_6->setText(QApplication::translate("MainWindow", "Difference between every 2 Frames", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "MoodBar", 0, QApplication::UnicodeUTF8));
        moodDisplay->setText(QString());
        pushButton_2->setText(QApplication::translate("MainWindow", "Start Analysis", 0, QApplication::UnicodeUTF8));
        saveButton->setText(QApplication::translate("MainWindow", "Save bars next to video at full resolution", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Skip Frames: ", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "Skip the next Frames", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
