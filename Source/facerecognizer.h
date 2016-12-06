#ifndef FACERECOGNIZER_H
#define FACERECOGNIZER_H

#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class FaceRecognizer
{
private:
    //是否已读取训练图片
    bool trainLoaded;

    //训练图像的数量
    int trainCount;

    //训练图像的尺寸
    Size trainSize;

    //未PCA投影的训练用的图片集
    Mat dataTrainPics;

    //未PCA投影的待识别的图片集
    Mat dataMatchPics;

    //经过PCA投影后的训练用的图片集
    Mat encodedTrainPics;

    //经过PCA投影后的待识别的图片集
    Mat encodedMatchPics;

    //opencv的PCA类
    PCA pca;

    //降维以备PCA使用
    Mat formatImageForPCA(Mat images);

    //降维以备PCA使用
    Mat formatImagesForPCA(const vector<Mat> &images);

    //转换为灰度图
    Mat toGrayscale(InputArray _src);

    //从Txt中的地址读取训练图片集及对应名字（包含绝对地址）
    int reloadPicsToTrainFromTxt(const string& filename);

    //从string向量中读取训练图片集及对应名字（包含绝对地址）
    int reloadPicsToTrainFromNames(const vector<string>& _names);

    //从string向量中读取训练图片集及对应名字（包含绝对地址）
    int loadPicsToTrainFromNames(const vector<string>& _names);

    //从Txt中的地址读取待匹配图片集及对应名字（包含绝对地址）
    int reloadPicsToMatchFromTxt(const string& filename);

    //从string向量中读取待匹配图片集及对应名字（包含绝对地址）
    int reloadPicsToMatchFromNames(const vector<string>& _names);

    //从string向量中读取待匹配图片集及对应名字（包含绝对地址）
    int reloadPicsToMatchFromMats(const vector<Mat>& _mats);

    //从string向量中读取待匹配图片集及对应名字（包含绝对地址）
    int reloadPicsToMatchFromMat(Mat _mat);
public:
    FaceRecognizer();

    //清空训练图片集
    void clearTrain();

    //清空待匹配图片集
    void clearMatch();

    //训练用的图片集
    vector<Mat> trainPics;

    //待识别的图片集
    vector<Mat> matchPics;

    //训练用的图片集中图片的文件名（包含绝对地址）
    vector<string> trainPicsNames;

    //待识别的图片集中图片的文件名（包含绝对地址）
    vector<string> matchPicsNames;

    //用txt指定的图片进行训练
    int reloadAndTrainPCAFromTxt(const string& _trainPicsAddr);

    //用string向量中指定的图片进行训练
    int reloadAndTrainPCAFromNames(const vector<string>& _names);

    //用string向量中指定的图片进行训练
    int loadAndTrainPCAFromNames(const vector<string>& _names);

    //直接用当前trainPics训练
    int trainPCAFromCurrentMats();

    //从txt指定的路径进行匹配并返回最匹配的训练文件的下标
    int reloadAndMatchPCAFromTxt(const string& _matchPicsAddr, const string& _resultAddr);

    //从string向量指定的路径进行匹配并返回最匹配的训练文件的下标
    int reloadAndMatchPCAFromNames(const vector<string>& _names, string& _resultNames);

    //从Mat向量指定的图片进行匹配并反回最匹配的训练文件的下标
    int reloadAndMatchPCAFromMats(const vector<Mat>& _names, string& _resultNames);

    //直接从当前matchPics匹配
    int matchPCAFromCurrentMats(string& _resultNames);

    //直接从Mat匹配
    int matchPCAFromMat(Mat _mat, string& _resultNames);
};

#endif // FACERECOGNIZER_H
