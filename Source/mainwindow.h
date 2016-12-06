#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QTimer>
#include <QMessageBox>
#include "facedetector.h"
#include "facerecognizer.h"

using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void Update();
    void on_captureButton_clicked();
    void on_matchPictureButton_clicked();
    void on_addTrainPictureButton_clicked();
//    void on_trainListWidget_itemActivated(QListWidgetItem *item);
    void on_clearTrainButton_clicked();
    void on_matchRealTimeButton_clicked();
    void on_trainListWidget_currentTextChanged(const QString &currentText);

public slots:
    void capture_done();
    void capture_allDone();
    void match_done();

private:
    QTextCodec *code;
    Ui::MainWindow *ui;
    QTimer UpdateTimer;
    QTimer DisplayTimer;
    QImage Mat2QImage(Mat& image);
    QString trainPath;
    QString matchPath;
    QString capturePath;
    QString recordPath;
    QString captureName;
    FaceDetector faceD;
    FaceRecognizer faceR;
    Mat DisplayMat;
    bool realTimeMatch;
    bool recording;
    bool capturing;
    int captureCount;
    int log;
    const int DisplayHeight;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

};

#endif // MAINWINDOW_H
