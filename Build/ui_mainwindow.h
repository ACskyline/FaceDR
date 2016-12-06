/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QLabel *videoLabel;
    QTextBrowser *resultTextBrowser;
    QWidget *captureRecordButtonWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *captureButton;
    QPushButton *matchRealTimeButton;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *pictureLabel;
    QListWidget *trainListWidget;
    QWidget *trainButtonwidget;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *addTrainPictureButton;
    QPushButton *clearTrainButton;
    QPushButton *matchPictureButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(552, 505);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        videoLabel = new QLabel(groupBox);
        videoLabel->setObjectName(QStringLiteral("videoLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(videoLabel->sizePolicy().hasHeightForWidth());
        videoLabel->setSizePolicy(sizePolicy1);
        videoLabel->setMinimumSize(QSize(0, 300));
        videoLabel->setMaximumSize(QSize(16777215, 300));
        videoLabel->setFrameShape(QFrame::Box);
        videoLabel->setFrameShadow(QFrame::Sunken);
        videoLabel->setLineWidth(3);
        videoLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(videoLabel);

        resultTextBrowser = new QTextBrowser(groupBox);
        resultTextBrowser->setObjectName(QStringLiteral("resultTextBrowser"));
        sizePolicy.setHeightForWidth(resultTextBrowser->sizePolicy().hasHeightForWidth());
        resultTextBrowser->setSizePolicy(sizePolicy);
        resultTextBrowser->setMaximumSize(QSize(16777215, 120));

        verticalLayout->addWidget(resultTextBrowser);

        captureRecordButtonWidget = new QWidget(groupBox);
        captureRecordButtonWidget->setObjectName(QStringLiteral("captureRecordButtonWidget"));
        sizePolicy.setHeightForWidth(captureRecordButtonWidget->sizePolicy().hasHeightForWidth());
        captureRecordButtonWidget->setSizePolicy(sizePolicy);
        captureRecordButtonWidget->setMaximumSize(QSize(16777215, 50));
        horizontalLayout = new QHBoxLayout(captureRecordButtonWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        captureButton = new QPushButton(captureRecordButtonWidget);
        captureButton->setObjectName(QStringLiteral("captureButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(captureButton->sizePolicy().hasHeightForWidth());
        captureButton->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(captureButton);

        matchRealTimeButton = new QPushButton(captureRecordButtonWidget);
        matchRealTimeButton->setObjectName(QStringLiteral("matchRealTimeButton"));
        sizePolicy2.setHeightForWidth(matchRealTimeButton->sizePolicy().hasHeightForWidth());
        matchRealTimeButton->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(matchRealTimeButton);


        verticalLayout->addWidget(captureRecordButtonWidget);


        horizontalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        pictureLabel = new QLabel(groupBox_2);
        pictureLabel->setObjectName(QStringLiteral("pictureLabel"));
        sizePolicy1.setHeightForWidth(pictureLabel->sizePolicy().hasHeightForWidth());
        pictureLabel->setSizePolicy(sizePolicy1);
        pictureLabel->setMinimumSize(QSize(0, 300));
        pictureLabel->setMaximumSize(QSize(16777215, 300));
        pictureLabel->setFrameShape(QFrame::Box);
        pictureLabel->setFrameShadow(QFrame::Sunken);
        pictureLabel->setLineWidth(3);
        pictureLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(pictureLabel);

        trainListWidget = new QListWidget(groupBox_2);
        new QListWidgetItem(trainListWidget);
        trainListWidget->setObjectName(QStringLiteral("trainListWidget"));
        sizePolicy.setHeightForWidth(trainListWidget->sizePolicy().hasHeightForWidth());
        trainListWidget->setSizePolicy(sizePolicy);
        trainListWidget->setMaximumSize(QSize(16777215, 120));

        verticalLayout_2->addWidget(trainListWidget);

        trainButtonwidget = new QWidget(groupBox_2);
        trainButtonwidget->setObjectName(QStringLiteral("trainButtonwidget"));
        sizePolicy.setHeightForWidth(trainButtonwidget->sizePolicy().hasHeightForWidth());
        trainButtonwidget->setSizePolicy(sizePolicy);
        trainButtonwidget->setMaximumSize(QSize(16777215, 50));
        horizontalLayout_8 = new QHBoxLayout(trainButtonwidget);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        addTrainPictureButton = new QPushButton(trainButtonwidget);
        addTrainPictureButton->setObjectName(QStringLiteral("addTrainPictureButton"));

        horizontalLayout_8->addWidget(addTrainPictureButton);

        clearTrainButton = new QPushButton(trainButtonwidget);
        clearTrainButton->setObjectName(QStringLiteral("clearTrainButton"));

        horizontalLayout_8->addWidget(clearTrainButton);

        matchPictureButton = new QPushButton(trainButtonwidget);
        matchPictureButton->setObjectName(QStringLiteral("matchPictureButton"));

        horizontalLayout_8->addWidget(matchPictureButton);


        verticalLayout_2->addWidget(trainButtonwidget);


        horizontalLayout_2->addWidget(groupBox_2);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Match", 0));
        videoLabel->setText(QApplication::translate("MainWindow", "Video", 0));
        resultTextBrowser->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">real time information</p></body></html>", 0));
        captureButton->setText(QApplication::translate("MainWindow", "Snap", 0));
        matchRealTimeButton->setText(QApplication::translate("MainWindow", "Match Video", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Train", 0));
        pictureLabel->setText(QApplication::translate("MainWindow", "Picture", 0));

        const bool __sortingEnabled = trainListWidget->isSortingEnabled();
        trainListWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = trainListWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("MainWindow", "Please add pictures to train", 0));
        trainListWidget->setSortingEnabled(__sortingEnabled);

        addTrainPictureButton->setText(QApplication::translate("MainWindow", "Add Pic", 0));
        clearTrainButton->setText(QApplication::translate("MainWindow", "Clear", 0));
        matchPictureButton->setText(QApplication::translate("MainWindow", "Match Pic", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
