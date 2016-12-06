#include "facedetector.h"

FaceDetector::FaceDetector()
{
    QFile face(":/haar_support/haar_support/haarcascade_frontalface_alt.xml");
    QFile nose(":/haar_support/haar_support/haarcascade_mcs_nose.xml");
    QFile eyes(":/haar_support/haar_support/haarcascade_mcs_eyepair_small.xml");

    code = QTextCodec::codecForName("gb18030");

    QDir path;
    //已经不需要从本地读取了，而是直接从exe中拷贝出来，再进行读取
    //"D:/OpenCV support/haarcascade/haarcascade_frontalface_alt.xml";
    QString face_cascade_name_Temp = path.currentPath()+"/haarcascade_frontalface_alt.xml";
    face_cascade_name = code->fromUnicode(face_cascade_name_Temp).data();
    QString face_cascade_name_Q = QString::fromStdString(face_cascade_name);

    //D:/OpenCV support/haarcascade/haarcascade_mcs_nose.xml";
    QString nose_cascade_name_Temp = path.currentPath()+"/haarcascade_mcs_nose.xml";
    nose_cascade_name = code->fromUnicode(nose_cascade_name_Temp).data();
    QString nose_cascade_name_Q = QString::fromStdString(nose_cascade_name);

    //D:/OpenCV support/haarcascade/haarcascade_mcs_eyepair_small.xml";
    QString eyes_cascade_name_Temp = path.currentPath()+"/haarcascade_mcs_eyepair_small.xml";
    eyes_cascade_name = code->fromUnicode(eyes_cascade_name_Temp).data();
    QString eyes_cascade_name_Q = QString::fromStdString(eyes_cascade_name);

    if(QFile::exists(face_cascade_name_Q))
    {
        QFile::remove(face_cascade_name_Q);
    }
    face.copy(face_cascade_name_Q);

    if(QFile::exists(nose_cascade_name_Q))
    {
        QFile::remove(nose_cascade_name_Q);
    }
    nose.copy(nose_cascade_name_Q);

    if(QFile::exists(eyes_cascade_name_Q))
    {
        QFile::remove(eyes_cascade_name_Q);
    }
    eyes.copy(eyes_cascade_name_Q);

    time.start();
    capture_name = "";
    record_name = "";
    recording = false;
    match = false;
    record = false;
    ready = false;
    go = 0;
    face_cascade.load(face_cascade_name);
    nose_cascade.load(nose_cascade_name);
    eyes_cascade.load(eyes_cascade_name);
    OK = cam.open(0);
}

int FaceDetector::run()
{
    if(OK)
    {
        bool haveEyes = false;
        bool haveNose = false;
        cam >> raw_image;//用于截屏
        cam >> input_image;//用于识别和处理
        flip(raw_image, raw_image, 1);//水平翻转
        flip(input_image, input_image, 1);//水平翻转
//        cuttingArea = Rect((input_image.cols - PIC_WIDTH) / 2, (input_image.rows - PIC_WIDTH) / 2, PIC_WIDTH, PIC_WIDTH);//截图区域
//        cuttingAreaEX = Rect((input_image.cols - PIC_WIDTHEX) / 2, (input_image.rows - PIC_HEIGHTEX) / 2, PIC_WIDTHEX, PIC_HEIGHTEX);//截图区域
//        rectangle(input_image, cuttingArea, Scalar(0, 0, 255));
//        rectangle(input_image, cuttingAreaEX, Scalar(0, 0, 255));

        if (detectFace(input_image, faceArea))
        {
            leftup = Point(faceArea.x, faceArea.y);
            rightdown = Point(faceArea.x + faceArea.width, faceArea.y + faceArea.height);
            face = input_image(faceArea);
            rectangle(input_image, leftup, rightdown, Scalar(0, 255, 0));//脸的方框
            circle(input_image, (leftup + rightdown) / 2, 5, Scalar(0, 255, 255), -1);//脸中心的黄点

            if (detectEyes(face, eyesArea))
            {
                eyesleftup = Point(eyesArea.x, eyesArea.y);
                eyesrightdown = Point(eyesArea.x + eyesArea.width, eyesArea.y + eyesArea.height);
                rectangle(input_image, leftup + eyesleftup, leftup + eyesrightdown, Scalar(255, 0, 0));
                //脸中心到眼中心的线
                line(input_image, leftup + (eyesleftup + eyesrightdown) / 2, (leftup + rightdown) / 2, Scalar(0, 255, 255));
                haveEyes = true;
            }
            if (detectNose(face, noseArea))
            {
                noseleftup = Point(noseArea.x, noseArea.y);
                noserightdown = Point(noseArea.x + noseArea.width, noseArea.y + noseArea.height);
                rectangle(input_image, leftup + noseleftup, leftup + noserightdown, Scalar(255, 0, 255));
                //脸中心到鼻子中心的线
                line(input_image, leftup + (noseleftup + noserightdown) / 2, (leftup + rightdown) / 2, Scalar(0, 255, 255));
                haveNose = true;
            }
            if (haveEyes && haveNose
                    && abs(noseArea.x + 0.5*noseArea.width - 0.5*faceArea.width) <= NOSE_CENTER_BIAS//鼻子中心距脸中心的水平位置不得超出一定值
                    && noseArea.y + 0.5*noseArea.height - 0.5*faceArea.height >= 0//鼻子的中心在脸的中心以下
                    && abs(noseArea.y - (eyesArea.y + eyesArea.height)) <= NOSE_EYES_BIAS)//鼻子的上界距眼的下界不得超出一定值
            {
                ready = true;
                circle(input_image, Point(input_image.cols - 20, 20), 10, Scalar(0, 255, 0), -1);
            }
            else
            {
                ready = false;
            }

        }
        else
        {
            ready = false;
        }

        if (go>0)
        {
            circle(input_image, Point(input_image.cols - 50, 20), 10, Scalar(0, 0, 255), -1);
            if (ready&&time.elapsed()>=1000)
            {
                capture_image = raw_image(faceArea).clone();
                cv::resize(capture_image(Rect(0.1*capture_image.cols,0,0.8*capture_image.cols,capture_image.rows)),
                           capture_image,
                           Size(PIC_WIDTH,PIC_WIDTH));
                time.restart();
                go--;
                emit capture_done();
                if(go<=0)
                {
                    emit capture_allDone();
                }
            }
        }

        if(match)
        {
            circle(input_image, Point(input_image.cols - 80, 20), 10, Scalar(255, 0, 0), -1);
            if (ready)
            {
                match_image = raw_image(faceArea).clone();
                cv::resize(match_image(Rect(0.1*match_image.cols,0,0.8*match_image.cols,match_image.rows)),
                           match_image,
                           Size(PIC_WIDTH,PIC_WIDTH));
                emit match_done();
            }
        }

        if (record)
        {
            record_image.push_back(raw_image.clone());
            circle(input_image, Point(20, 20), 10, Scalar(0, 0, 255), -1);
        }

        return 0;
    }
    else
    {
        return 1;
    }
}

bool FaceDetector::detectFace(Mat frame, Rect &ROI){
    std::vector<Rect> faces;
    Mat frame_gray;

    cvtColor(frame, frame_gray, CV_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, CV_HAAR_SCALE_IMAGE | CV_HAAR_FIND_BIGGEST_OBJECT, Size(50, 50));

    if (faces.size() > 0)
    {
        ROI = faces.at(0);
    }
    else
    {
        return false;
    }

    return true;
}

bool FaceDetector::detectEyes(Mat frame, Rect &ROI){
    std::vector<Rect> eyes;
    Mat frame_gray;

    cvtColor(frame, frame_gray, CV_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    eyes_cascade.detectMultiScale(frame_gray, eyes, 1.1, 2, CV_HAAR_SCALE_IMAGE | CV_HAAR_FIND_BIGGEST_OBJECT, Size(40, 20));

    if (eyes.size() > 0)
    {
        ROI = eyes.at(0);
    }
    else
    {
        return false;
    }

    return true;
}

bool FaceDetector::detectNose(Mat frame, Rect &ROI){
    std::vector<Rect> nose;
    Mat frame_gray;

    cvtColor(frame, frame_gray, CV_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    nose_cascade.detectMultiScale(frame_gray, nose, 1.1, 2, CV_HAAR_SCALE_IMAGE | CV_HAAR_FIND_BIGGEST_OBJECT, Size(20, 20));

    if (nose.size() > 0)
    {
        ROI = nose.at(0);
    }
    else
    {
        return false;
    }

    return true;
}

void FaceDetector::captureBegin()
{
    capture_name = "";
    go = 10;
}

void FaceDetector::captureCancell()
{
    go = 0;
}

void FaceDetector::captureEnd(string fileName)
{
    capture_name = fileName;
    if(!capture_name.empty())
    {
        imwrite(capture_name, capture_image);
    }
}

void FaceDetector::recordBegin()
{
    record_image.clear();
    record_name = "";
    record = true;
}

void FaceDetector::recordCancell()
{
    record_name = "";
    record = false;
}

void FaceDetector::recordEnd(string fileName)
{
    record = false;
    record_name = fileName;
    if(!record_image.empty())
    {
        Size s = record_image.front().size();
        writer = VideoWriter(record_name, CV_FOURCC('M', 'J', 'P', 'G'), 25, s);
        if (writer.isOpened())
        {
            for(unsigned int i = 0;i<record_image.size();i++)
            {
                writer << record_image.at(i);
            }
        }
        writer.release();
    }
}

void FaceDetector::matchBegin()
{
    match = true;
}

void FaceDetector::matchEnd()
{
    match = false;
}
