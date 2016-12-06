#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QTime>
#include <QTextCodec>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <string>

#define CENTER_BIAS 10
#define EDGE_BIAS 10
#define PIC_WIDTH 250
#define PIC_WIDTHEX 180
#define PIC_HEIGHTEX 200
#define NOSE_CENTER_BIAS 5
#define NOSE_EYES_BIAS 5

using namespace cv;
using namespace std;

class FaceDetector : public QObject
{
    Q_OBJECT

signals:
    void capture_done();
    void capture_allDone();
    void match_done();
private:
    QTextCodec *code;
    string face_cascade_name;
    string nose_cascade_name;
    string eyes_cascade_name;
    string capture_name;
    string record_name;
    CascadeClassifier face_cascade;
    CascadeClassifier nose_cascade;
    CascadeClassifier eyes_cascade;
    bool recording;
    bool match;
    bool record;
    bool ready;
    bool OK;
    VideoCapture cam;
    VideoWriter writer;
    //Rect cuttingArea;
    //Rect cuttingAreaEX;
    Rect faceArea;
    Rect eyesArea;
    Rect noseArea;
    Mat raw_image;
    Mat capture_image;
    vector<Mat> record_image;
    Point leftup;
    Point rightdown;
    Point eyesleftup;
    Point eyesrightdown;
    Point noseleftup;
    Point noserightdown;
    Mat face;
    bool detectFace(Mat frame, Rect &ROI);
    bool detectEyes(Mat frame, Rect &ROI);
    bool detectNose(Mat frame, Rect &ROI);
    QTime time;
public:
    int go;
    Mat match_image;
    Mat input_image;
    FaceDetector();
    void captureBegin();
    void captureCancell();
    void captureEnd(string fileName);
    void recordBegin();
    void recordCancell();
    void recordEnd(string fileName);
    void matchBegin();
    void matchEnd();
    int run();
};

#endif // FACEDETECTOR_H
