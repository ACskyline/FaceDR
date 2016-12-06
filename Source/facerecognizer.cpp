#include "facerecognizer.h"
#include <QMessageBox>

FaceRecognizer::FaceRecognizer()
{
    trainCount = 0;
    trainLoaded = false;
    trainSize = Size(1,1);
}

void FaceRecognizer::clearTrain()
{
    trainCount = 0;
    trainSize = Size(1, 1);
    trainLoaded = false;
    trainPics.clear();
    trainPicsNames.clear();
}

void FaceRecognizer::clearMatch()
{
    matchPics.clear();
    matchPicsNames.clear();
}

int FaceRecognizer::reloadPicsToTrainFromNames(const vector<string>& _names)
{
    clearTrain();
    for (unsigned int i = 0; i < _names.size();i++){
        Mat temp = imread(_names.at(i), 0);
        if (temp.data == 0)
        {
            continue;
        }
        if (trainCount == 0)
        {
            trainSize = Size(temp.cols, temp.rows);
        }
        if (trainSize.width != temp.cols || trainSize.height != temp.rows)
        {
            resize(temp, temp, trainSize);
        }
        trainPics.push_back(temp);
        trainPicsNames.push_back(_names.at(i));
        trainCount++;
    }
    trainLoaded = true;
    return 0;
}

int FaceRecognizer::loadPicsToTrainFromNames(const vector<string>& _names)
{
    for (unsigned int i = 0; i < _names.size();i++){
        Mat temp = imread(_names.at(i), 0);
        if (temp.data == 0)
        {
            continue;
        }
        if (trainCount == 0)
        {
            trainSize = Size(temp.cols, temp.rows);
        }
        if (trainSize.width != temp.cols || trainSize.height != temp.rows)
        {
            resize(temp, temp, trainSize);
        }
        trainPics.push_back(temp);
        trainPicsNames.push_back(_names.at(i));
        trainCount++;
    }
    trainLoaded = true;
    return 0;
}

int FaceRecognizer::reloadPicsToTrainFromTxt(const string& filename)
{
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        return 1;
    }
    clearTrain();
    string line;
    while (getline(file, line)) {
        Mat temp = imread(line, 0);
        if (temp.data == 0)
        {
            continue;
        }
        if (trainCount == 0)
        {
            trainSize = Size(temp.cols, temp.rows);
        }
        if (trainSize.width != temp.cols || trainSize.height != temp.rows)
        {
            resize(temp, temp, trainSize);
        }
        trainPics.push_back(temp);
        trainPicsNames.push_back(line);
        trainCount++;
    }
    trainLoaded = true;
    return 0;
}

int FaceRecognizer::reloadPicsToMatchFromNames(const vector<string>& _names)
{
    clearMatch();
    for (unsigned int i = 0; i < _names.size(); i++){
        Mat temp = imread(_names.at(i), 0);
        if (temp.data == 0)
        {
            continue;
        }
        if (trainSize.width != temp.cols || trainSize.height != temp.rows)
        {
            resize(temp, temp, trainSize);
        }
        matchPics.push_back(temp);
        matchPicsNames.push_back(_names.at(i));
    }
    return 0;
}

int FaceRecognizer::reloadPicsToMatchFromMat(Mat _mat)
{
    clearMatch();
        Mat temp = _mat.clone();
        if (temp.data == 0)
        {
            return 1;
        }
        if (trainSize.width != temp.cols || trainSize.height != temp.rows)
        {
            resize(temp, temp, trainSize);
        }
        stringstream ss;
        ss << "current_" << 0;
        matchPics.push_back(temp);
        matchPicsNames.push_back(ss.str());

    return 0;
}

int FaceRecognizer::reloadPicsToMatchFromMats(const vector<Mat>& _mats)
{
    clearMatch();
    for (unsigned int i = 0; i < _mats.size(); i++){
        Mat temp = _mats.at(i).clone();
        if (temp.data == 0)
        {
            continue;
        }
        if (trainSize.width != temp.cols || trainSize.height != temp.rows)
        {
            resize(temp, temp, trainSize);
        }
        stringstream ss;
        ss << "current_" << i;
        matchPics.push_back(temp);
        matchPicsNames.push_back(ss.str());
    }
    return 0;
}

int FaceRecognizer::reloadPicsToMatchFromTxt(const string& filename)
{
    clearMatch();
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        return 1;
    }

    string line;
    while (getline(file, line)) {
        Mat temp = imread(line, 0);
        if (temp.data == 0)
        {
            continue;
        }

        if (trainSize.width != temp.cols || trainSize.height != temp.rows)
        {
            resize(temp, temp, trainSize);
        }
        matchPics.push_back(temp);
        matchPicsNames.push_back(line);
    }
    return 0;
}

Mat FaceRecognizer::toGrayscale(InputArray _src) {
    Mat src = _src.getMat();
    // only allow one channel
    if (src.channels() != 1) {
        CV_Error(Error::StsBadArg, "Only Matrices with one channel are supported");
    }
    // create and return normalized image
    Mat dst;
    cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
    return dst;
}

Mat FaceRecognizer::formatImagesForPCA(const vector<Mat> &images)
{
    Mat data(static_cast<int>(images.size()), images[0].rows*images[0].cols, CV_32F);
    for (unsigned int i = 0; i < images.size(); i++)
    {
        Mat image_row = images[i].clone().reshape(1, 1);
        image_row.convertTo(data.row(i), CV_32F);
    }
    return data;
}

Mat FaceRecognizer::formatImageForPCA(Mat image)
{
    Mat data(1, image.rows*image.cols, CV_32F);
    Mat image_row = image.clone();
    image_row.reshape(1, 1);
    image_row.convertTo(data.row(0), CV_32F);
    return data;
}

int FaceRecognizer::reloadAndTrainPCAFromTxt(const string& _trainPicsAddr)
{
    if (reloadPicsToTrainFromTxt(_trainPicsAddr) != 0)
    {
        return 1;
    }

    if (trainPics.size() <= 1)
    {
        return 2;
    }

    // Reshape and stack images into a rowMatrix
    Mat data = formatImagesForPCA(trainPics);

    // perform PCA
    pca = PCA(data, cv::Mat(), PCA::DATA_AS_ROW, 0.95); // trackbar is initially set here, also this is a common value for retainedVariance

    dataTrainPics = formatImagesForPCA(trainPics);
    encodedTrainPics = Mat(dataTrainPics.rows, pca.eigenvectors.rows, CV_32F);
    for (int i = 0; i < dataTrainPics.rows; i++)
    {
        pca.project(dataTrainPics.row(i), encodedTrainPics.row(i));
        //encodedTrainPics.row(i) = pca.project(dataTrainPics.row(i));//不能用这个！！
    }

    return 0;
}

int FaceRecognizer::reloadAndTrainPCAFromNames(const vector<string>& _name)
{
    if (reloadPicsToTrainFromNames(_name) != 0)
    {
        return 1;
    }

    if (trainPics.size() <= 1)
    {
        return 2;
    }

    // Reshape and stack images into a rowMatrix
    Mat data = formatImagesForPCA(trainPics);

    // perform PCA
    pca = PCA(data, cv::Mat(), PCA::DATA_AS_ROW, 0.95); // trackbar is initially set here, also this is a common value for retainedVariance

    dataTrainPics = formatImagesForPCA(trainPics);
    encodedTrainPics = Mat(dataTrainPics.rows, pca.eigenvectors.rows, CV_32F);
    for (int i = 0; i < dataTrainPics.rows; i++)
    {
        pca.project(dataTrainPics.row(i), encodedTrainPics.row(i));
        //encodedTrainPics.row(i) = pca.project(dataTrainPics.row(i));//不能用这个！！
    }

    return 0;
}

int FaceRecognizer::loadAndTrainPCAFromNames(const vector<string>& _name)
{
    if (loadPicsToTrainFromNames(_name) != 0)
    {
        return 1;
    }

    if (trainPics.size() <= 1)
    {
        return 2;
    }

    // Reshape and stack images into a rowMatrix
    Mat data = formatImagesForPCA(trainPics);

    // perform PCA
    pca = PCA(data, cv::Mat(), PCA::DATA_AS_ROW, 0.95); // trackbar is initially set here, also this is a common value for retainedVariance

    dataTrainPics = formatImagesForPCA(trainPics);
    encodedTrainPics = Mat(dataTrainPics.rows, pca.eigenvectors.rows, CV_32F);
    for (int i = 0; i < dataTrainPics.rows; i++)
    {
        pca.project(dataTrainPics.row(i), encodedTrainPics.row(i));
        //encodedTrainPics.row(i) = pca.project(dataTrainPics.row(i));//不能用这个！！
    }

    return 0;
}

int FaceRecognizer::trainPCAFromCurrentMats()
{
    if (trainPics.size() <= 1)
    {
        return 2;
    }

    // Reshape and stack images into a rowMatrix
    Mat data = formatImagesForPCA(trainPics);

    // perform PCA
    pca = PCA(data, cv::Mat(), PCA::DATA_AS_ROW, 0.95); // trackbar is initially set here, also this is a common value for retainedVariance

    dataTrainPics = formatImagesForPCA(trainPics);
    encodedTrainPics = Mat(dataTrainPics.rows, pca.eigenvectors.rows, CV_32F);
    for (int i = 0; i < dataTrainPics.rows; i++)
    {
        pca.project(dataTrainPics.row(i), encodedTrainPics.row(i));
        //encodedTrainPics.row(i) = pca.project(dataTrainPics.row(i));//不能用这个！！
    }

    return 0;
}

int FaceRecognizer::reloadAndMatchPCAFromTxt(const string& _matchPicsAddr, const string& _resultAddr)
{
    if (reloadPicsToMatchFromTxt(_matchPicsAddr) != 0)
    {
        return 1;
    }

    dataMatchPics = formatImagesForPCA(matchPics);
    encodedMatchPics = Mat(dataMatchPics.rows, pca.eigenvectors.rows, CV_32F);
    for (int i = 0; i < dataMatchPics.rows; i++)
    {
        pca.project(dataMatchPics.row(i), encodedMatchPics.row(i));
        //encodedMatchPics.row(i) = pca.project(dataMatchPics.row(i));//不能用这个！！
    }

    std::ofstream file(_resultAddr.c_str(), ifstream::out);

    for (int k = 0; k < encodedMatchPics.rows; k++)
    {
        //将近似结果和原数据进行比较
        bool first = true;
        float min_sum = -1;
        int min_index = -1;
        for (int i = 0; i < dataTrainPics.rows; i++)
        {
            float sum = 0;
            for (int j = 0; j < pca.eigenvectors.rows; j++)
            {
                float fs = encodedTrainPics.at<float>(i, j);
                float fi = encodedMatchPics.at<float>(k, j);
                sum += ((fs - fi)*(fs - fi));
            }
            if (first)
            {
                min_sum = sum;
                min_index = i;
                first = false;
            }
            else if (sum < min_sum){
                min_sum = sum;
                min_index = i;
            }
        }

        // display the target image
        file << matchPicsNames.at(k) << "\n<<<resembles>>>\n" << trainPicsNames.at(min_index) << "\nmin_sum = " << min_sum << "\n----------" << endl;
    }

    return 0;
}

int FaceRecognizer::reloadAndMatchPCAFromNames(const vector<string>& _names, string& _result)
{
    if (reloadPicsToMatchFromNames(_names) != 0)
    {
        return 1;
    }

    dataMatchPics = formatImagesForPCA(matchPics);
    encodedMatchPics = Mat(dataMatchPics.rows, pca.eigenvectors.rows, CV_32F);
    for (int i = 0; i < dataMatchPics.rows; i++)
    {
        pca.project(dataMatchPics.row(i), encodedMatchPics.row(i));
        //encodedMatchPics.row(i) = pca.project(dataMatchPics.row(i));//不能用这个！！
    }

    stringstream ss;
    for (int k = 0; k < encodedMatchPics.rows; k++)
    {
        //将近似结果和原数据进行比较
        bool first = true;
        float min_sum = -1;
        int min_index = -1;
        for (int i = 0; i < dataTrainPics.rows; i++)
        {
            float sum = 0;
            for (int j = 0; j < pca.eigenvectors.rows; j++)
            {
                float fs = encodedTrainPics.at<float>(i, j);
                float fi = encodedMatchPics.at<float>(k, j);
                sum += ((fs - fi)*(fs - fi));
            }
            if (first)
            {
                min_sum = sum;
                min_index = i;
                first = false;
            }
            else if (sum < min_sum){
                min_sum = sum;
                min_index = i;
            }
        }

        ss << matchPicsNames.at(k) << "\n<<<resembles>>>\n" << trainPicsNames.at(min_index) << "\nmin_sum = " << min_sum << "\n----------" << endl;
    }
    _result = ss.str();
    return 0;
}

int FaceRecognizer::reloadAndMatchPCAFromMats(const vector<Mat>& _mats, string& _result)
{
    if (reloadPicsToMatchFromMats(_mats) != 0)
    {
        return 1;
    }

    dataMatchPics = formatImagesForPCA(matchPics);
    encodedMatchPics = Mat(dataMatchPics.rows, pca.eigenvectors.rows, CV_32F);
    for (int i = 0; i < dataMatchPics.rows; i++)
    {
        pca.project(dataMatchPics.row(i), encodedMatchPics.row(i));
        //encodedMatchPics.row(i) = pca.project(dataMatchPics.row(i));//不能用这个！！
    }

    stringstream ss;
    for (int k = 0; k < encodedMatchPics.rows; k++)
    {
        //将近似结果和原数据进行比较
        bool first = true;
        float min_sum = -1;
        int min_index = -1;
        for (int i = 0; i < dataTrainPics.rows; i++)
        {
            float sum = 0;
            for (int j = 0; j < pca.eigenvectors.rows; j++)
            {
                float fs = encodedTrainPics.at<float>(i, j);
                float fi = encodedMatchPics.at<float>(k, j);
                sum += ((fs - fi)*(fs - fi));
            }
            if (first)
            {
                min_sum = sum;
                min_index = i;
                first = false;
            }
            else if (sum < min_sum){
                min_sum = sum;
                min_index = i;
            }
        }

        ss << matchPicsNames.at(k) << "\n<<<resembles>>>\n" << trainPicsNames.at(min_index) << "\nmin_sum = " << min_sum << "\n----------" << endl;
    }
    _result = ss.str();
    return 0;
}

int FaceRecognizer::matchPCAFromCurrentMats(string& _result)
{
    dataMatchPics = formatImagesForPCA(matchPics);
    encodedMatchPics = Mat(dataMatchPics.rows, pca.eigenvectors.rows, CV_32F);
    for (int i = 0; i < dataMatchPics.rows; i++)
    {
        pca.project(dataMatchPics.row(i), encodedMatchPics.row(i));
        //encodedMatchPics.row(i) = pca.project(dataMatchPics.row(i));//不能用这个！！
    }

    stringstream ss;
    for (int k = 0; k < encodedMatchPics.rows; k++)
    {
        //将近似结果和原数据进行比较
        bool first = true;
        float min_sum = -1;
        int min_index = -1;
        for (int i = 0; i < dataTrainPics.rows; i++)
        {
            float sum = 0;
            for (int j = 0; j < pca.eigenvectors.rows; j++)
            {
                float fs = encodedTrainPics.at<float>(i, j);
                float fi = encodedMatchPics.at<float>(k, j);
                sum += ((fs - fi)*(fs - fi));
            }
            if (first)
            {
                min_sum = sum;
                min_index = i;
                first = false;
            }
            else if (sum < min_sum){
                min_sum = sum;
                min_index = i;
            }
        }
        ss << matchPicsNames.at(k) << "\n<<<resembles>>>\n" << trainPicsNames.at(min_index) << "\nmin_sum = " << min_sum << "\n----------" << endl;
    }
    _result = ss.str();
    return 0;
}

int FaceRecognizer::matchPCAFromMat(Mat _mat, string& _result)
{
    if (reloadPicsToMatchFromMat(_mat) != 0)
    {
        return 1;
    }

    dataMatchPics = formatImagesForPCA(matchPics);
    encodedMatchPics = Mat(dataMatchPics.rows, pca.eigenvectors.rows, CV_32F);
    for (int i = 0; i < dataMatchPics.rows; i++)
    {
        pca.project(dataMatchPics.row(i), encodedMatchPics.row(i));
        //encodedMatchPics.row(i) = pca.project(dataMatchPics.row(i));//不能用这个！！
    }

    stringstream ss;
    for (int k = 0; k < encodedMatchPics.rows; k++)
    {
        //将近似结果和原数据进行比较
        bool first = true;
        float min_sum = -1;
        int min_index = -1;
        for (int i = 0; i < dataTrainPics.rows; i++)
        {
            float sum = 0;
            for (int j = 0; j < pca.eigenvectors.rows; j++)
            {
                float fs = encodedTrainPics.at<float>(i, j);
                float fi = encodedMatchPics.at<float>(k, j);
                sum += ((fs - fi)*(fs - fi));
            }
            if (first)
            {
                min_sum = sum;
                min_index = i;
                first = false;
            }
            else if (sum < min_sum){
                min_sum = sum;
                min_index = i;
            }
        }

        ss << matchPicsNames.at(k) << "\n<<<resembles>>>\n" << trainPicsNames.at(min_index) << "\nmin_sum = " << min_sum << "\n----------" << endl;
    }
    _result = ss.str();
    return 0;

//    if(trainSize.width != _mat.cols || trainSize.height != _mat.rows)
//    {
//        resize(_mat,_mat,trainSize);
//    }
//    Mat dataMatchPic = formatImageForPCA(_mat).clone();
//    Mat encodedMatchPic(dataMatchPic.rows, pca.eigenvectors.rows,CV_32F);
//    pca.project(dataMatchPic.row(0), encodedMatchPic.row(0));

//    //stringstream ss;
//    //将近似结果和原数据进行比较
//    bool first = true;
//    float min_sum = -1;
//    int min_index = -1;
//    for (int i = 0; i < dataTrainPics.rows; i++)
//    {
//        float sum = 0;
//        for (int j = 0; j < pca.eigenvectors.rows; j++)
//        {
//            float fs = encodedTrainPics.at<float>(i, j);
//            float fi = encodedMatchPic.at<float>(0, j);
//            sum += ((fs - fi)*(fs - fi));
//        }
//        if (first)
//        {
//            min_sum = sum;
//            min_index = i;
//            first = false;
//        }
//        else if (sum < min_sum){
//            min_sum = sum;
//            min_index = i;
//        }
//    }
//    //ss << "Current Picture" << "\n<<<resembles>>>\n" << trainPicsNames.at(min_index) << "\nmin_sum = " << min_sum << "\n----------" << endl;
//    //_result = ss.str();
//    _result = trainPicsNames.at(min_index);
//    return 0;
}
