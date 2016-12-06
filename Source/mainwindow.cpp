#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    DisplayHeight(300)
{
    code = QTextCodec::codecForName("gb18030");
    log = 0;
    captureCount = 0;//1;
    realTimeMatch = false;
    recording = false;
    capturing = false;
    ui->setupUi(this);
    ui->matchRealTimeButton->setEnabled(false);
    ui->matchPictureButton->setEnabled(false);
    UpdateTimer.setInterval(30);
    connect(&UpdateTimer, &QTimer::timeout, this, &Update);
    connect(&faceD,SIGNAL(capture_done()),this,SLOT(capture_done()));
    connect(&faceD,SIGNAL(capture_allDone()),this,SLOT(capture_allDone()));
    connect(&faceD,SIGNAL(match_done()),this,SLOT(match_done()));
    UpdateTimer.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Update()
{
    if(faceD.run()==0)
    {
        Mat temp;
        temp = faceD.input_image.clone();
        if(temp.data!=0)
        {
            temp.copyTo(DisplayMat);
            Size temps((int)((float)DisplayMat.cols * (float)DisplayHeight/(float)DisplayMat.rows),DisplayHeight);
            cv::resize(DisplayMat,DisplayMat,temps);
            QImage img = Mat2QImage(DisplayMat);
            QPixmap pixmap = QPixmap::fromImage(img);
            ui->videoLabel->setPixmap(pixmap);
        }
    }
}

void MainWindow::capture_done()
{
    QString filename;
    captureCount = 0;
    do
    {
        captureCount++;
        filename = captureName + "_" + QString::number(captureCount) + ".jpg";
    }
    while(QFile::exists(filename));
    string filenameC = code->fromUnicode(filename).data();
    faceD.captureEnd(filenameC);
    ui->resultTextBrowser->append(QString::number(faceD.go) + " left...");

}

void MainWindow::capture_allDone()
{
    ui->captureButton->setText("Snap");
    ui->resultTextBrowser->append("All done!");
}

void MainWindow::match_done()
{
    string temp;
    vector<string> tempN;
    tempN.push_back("temp.jpg");
    imwrite("temp.jpg",faceD.match_image);
    faceR.reloadAndMatchPCAFromNames(tempN,temp);
    //faceR.matchPCAFromMat(faceD.match_image.clone(), temp);
    if(!temp.empty())
    {
        Mat tempm = imread(temp);
        if(tempm.data!=0)
        {
            Size temps((int)((float)tempm.cols * (float)DisplayHeight/(float)tempm.rows),DisplayHeight);
            cv::resize(tempm,tempm,temps);
            QImage img = Mat2QImage(tempm);
            QPixmap pixmap = QPixmap::fromImage(img);
            ui->pictureLabel->setPixmap(pixmap);
        }
        stringstream ss;
        ss<<"----------\nlog#"<< ++log <<"\n" << temp;
        temp = ss.str();
        QString tempC = code->toUnicode(temp.c_str());
        ui->resultTextBrowser->append(tempC);
    }
    else
    {
        QMessageBox mb;
        mb.setText("No result.");
        mb.exec();
    }
}

QImage MainWindow::Mat2QImage(Mat& image)
{
    QImage img;
    if (image.channels()==3)
    {
        cvtColor(image, image, CV_BGR2RGB);
        img = QImage((const unsigned char *)(image.data), image.cols, image.rows,image.cols*image.channels(), QImage::Format_RGB888);
    }
    else if (image.channels()==1)
    {
        img = QImage((const unsigned char *)(image.data), image.cols, image.rows,image.cols*image.channels(), QImage::Format_ARGB32);
    }
    else
    {
        img = QImage((const unsigned char *)(image.data), image.cols, image.rows,image.cols*image.channels(), QImage::Format_RGB888);
    }
    return img;
}

void MainWindow::on_captureButton_clicked()
{
    capturing = !capturing;
    if(capturing)
    {
        QString filename = QFileDialog::getSaveFileName(0, "Save Capture", capturePath, "*.jpg");
        if(filename.isEmpty())
        {
            capturing = false;
            return;
        }
        captureName = filename;
        capturePath = QFileInfo(filename).absolutePath();
        faceD.captureBegin();
        ui->captureButton->setText("Cancel");
        ui->matchRealTimeButton->setEnabled(false);
        ui->addTrainPictureButton->setEnabled(false);
        ui->clearTrainButton->setEnabled(false);
        ui->matchPictureButton->setEnabled(false);
    }
    else
    {
        faceD.captureCancell();
        ui->captureButton->setText("Snap");
        ui->matchRealTimeButton->setEnabled(true);
        ui->addTrainPictureButton->setEnabled(true);
        ui->clearTrainButton->setEnabled(true);
        ui->matchPictureButton->setEnabled(true);
    }
}

void MainWindow::on_matchPictureButton_clicked()
{
    QStringList matchFileNames = QFileDialog::getOpenFileNames(0, "Match Picture", matchPath, "*.jpg *.png *.bmp");
    if(matchFileNames.isEmpty())
    {
        return;
    }
    matchPath = QFileInfo(matchFileNames.at(0)).absolutePath();
    vector<string> temp;
    string result;
    for(int i = 0;i<matchFileNames.size();i++)
    {
        string matchFileNameC = code->fromUnicode(matchFileNames.at(i)).data();
        temp.push_back(matchFileNameC);
    }
    faceR.reloadAndMatchPCAFromNames(temp,result);
    if(!result.empty())
    {
        QMessageBox mb;
        QString resultC = code->toUnicode(result.c_str());
        mb.setText(resultC);
        mb.exec();
    }
    else
    {
        QMessageBox mb;
        mb.setText("No result.");
        mb.exec();
    }
}

void MainWindow::on_addTrainPictureButton_clicked()
{
    if(realTimeMatch){
        realTimeMatch = !realTimeMatch;
        faceD.matchEnd();
        ui->matchRealTimeButton->setText("Match Video");
    }
    QStringList trainFileNames = QFileDialog::getOpenFileNames(0, "Open Pictures", trainPath, "*.jpg *.png *.bmp");
    if(trainFileNames.isEmpty())
    {
        return;
    }
    trainPath = QFileInfo(trainFileNames.at(0)).absolutePath();
    vector<string> temp;
    for(int i = 0;i<trainFileNames.size();i++)
    {
        string trainFileNameC = code->fromUnicode(trainFileNames.at(i)).data();
        temp.push_back(trainFileNameC);
    }
    faceR.loadAndTrainPCAFromNames(temp);
    QStringList trainFileNamesEX;
    for(unsigned int i = 0;i<faceR.trainPicsNames.size();i++)
    {
        trainFileNamesEX.append(code->toUnicode(faceR.trainPicsNames.at(i).c_str()));//(QString::fromStdString(faceR.trainPicsNames.at(i)));
    }
    ui->trainListWidget->clear();//清空当前显示
    ui->trainListWidget->addItems(trainFileNamesEX);//重新显示所有
    ui->trainListWidget->scrollToBottom();//滚动到最下面
    if(faceR.trainPics.size()>1)//投影训练样本
    {
        ui->matchPictureButton->setEnabled(true);
        ui->matchRealTimeButton->setEnabled(true);
    }
}

//void MainWindow::on_trainListWidget_itemActivated(QListWidgetItem *item)
//{
//    Mat temp = imread(item->text().toStdString());
//    if(temp.data!=0)
//    {
//        Size temps((int)((float)temp.cols * (float)DisplayHeight/(float)temp.rows),DisplayHeight);
//        cv::resize(temp,temp,temps);
//        QImage img = Mat2QImage(temp);
//        QPixmap pixmap = QPixmap::fromImage(img);
//        ui->pictureLabel->setPixmap(pixmap);
//    }
//    else
//    {
//        QMessageBox mb;
//        mb.setText("Can not open that picture.");
//        mb.exec();
//    }
//}

void MainWindow::on_clearTrainButton_clicked()
{
    faceD.matchEnd();
    ui->matchRealTimeButton->setText("Match Video");
    faceR.clearTrain();
    ui->trainListWidget->clear();
    ui->pictureLabel->clear();
    ui->matchPictureButton->setEnabled(false);
    ui->matchRealTimeButton->setEnabled(false);
}

void MainWindow::on_matchRealTimeButton_clicked()
{
    realTimeMatch = !realTimeMatch;
    if(realTimeMatch)
    {
        faceD.matchBegin();
        ui->matchRealTimeButton->setText("Stop");
        ui->captureButton->setEnabled(false);
        ui->addTrainPictureButton->setEnabled(false);
        ui->clearTrainButton->setEnabled(false);
        ui->matchPictureButton->setEnabled(false);
    }
    else {
        faceD.matchEnd();
        ui->matchRealTimeButton->setText("Match Video");
        ui->captureButton->setEnabled(true);
        ui->addTrainPictureButton->setEnabled(true);
        ui->clearTrainButton->setEnabled(true);
        ui->matchPictureButton->setEnabled(true);
        log = 0;
    }
}

void MainWindow::on_trainListWidget_currentTextChanged(const QString &currentText)
{
    if(!currentText.isEmpty())
    {
        string currentTextC = code->fromUnicode(currentText).data();
        Mat temp = imread(currentTextC);
        if(temp.data!=0)
        {
            Size temps((int)((float)temp.cols * (float)DisplayHeight/(float)temp.rows),DisplayHeight);
            cv::resize(temp,temp,temps);
            QImage img = Mat2QImage(temp);
            QPixmap pixmap = QPixmap::fromImage(img);
            ui->pictureLabel->setPixmap(pixmap);
        }
        else
        {
            QMessageBox mb;
            mb.setText("Can not open that picture.");
            mb.exec();
        }
    }
}
