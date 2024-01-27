#include <iostream>
#include <vector>
#include <fstream>
using std::cout;
using std::endl;
using std::vector;
using std::ofstream;

#include "opencv2/opencv.hpp"
#include <opencv2/core/utils/logger.hpp>

#include <string>
using namespace cv;

static bool matPrint(Mat &img,String tiltle)
{
	uchar* pTemp = NULL;
	cout << endl << "/******************" << tiltle << "******************/" << endl;

	for (int i = 0; i < img.rows; i++)
	{
		for(int j = 0; j < img.cols; j++)
		{
			cout << "[";
			for (int k = 0; k < img.step[1]; k++)
			{
				pTemp = img.data + img.step[0] * i + img.step[1] * j + k;
				cout << (int)*pTemp << " ";
			}
			cout << "] ";
		}
		cout << endl;
	}

	return true;
}

static void showImgPara(Mat &img)
{
	cout << "sizeof(img) is: " << sizeof(img) << ", img size is: " << img.size << endl;
	cout << "rows x cols: (" << img.rows << " x " << img.cols << ")" << endl;
	cout << "dims: " << img.dims << endl;
	cout << "channels: " << img.channels() << endl;
	cout << "type: " << img.type() << endl;
	cout << "depth:" << img.depth() << endl;
	cout << "elemSize:" << img.elemSize() << " (Bytes per element)" << endl;
	cout << "elemSize1:" << img.elemSize1() << "(Bytes per channel)" << endl;
	cout << "step[0]: " << img.step[0] << " (Bytes per cows only when 2 dims)" << endl;
	cout <<	"step[1]: " << img.step[1] << " (Bytes per element only when 2 dims)" << endl;
	cout << "step1(0): " << img.step1(0) << ", step1(1): " << img.step1(1) << " (step / elemSize1)" << endl;
}

static bool picCreat(Mat &img, String name)
{
	for (int i = 0; i < img.rows; i++)
	{
		uchar *p = img.ptr<uchar>(i);
		for (int j = 0; j < img.cols * img.channels(); j += img.channels())
		{
			if (i > img.rows/4 && i < img.rows*3/4 && j > img.cols*img.channels()/4 && j < img.cols*img.channels()*3/4)
			{
				p[j] = 0;
				p[j + 1] = 0;
				p[j + 2] = 255;

			}
			else
			{
				p[j] = 255;
				p[j + 1] = 255;
				p[j + 2] = 255;
			}
		}
	}

	cout << endl << "/******************picCreat******************/" << endl;
	showImgPara(img);
    // matPrint(img);
	namedWindow(name);
	imshow(name, img);

	return true;
}

static bool tran2singleChannel(Mat &src, Mat &tar)
{
	vector<Mat> channels;

	split(src, channels);
	tar = channels.at(0);
	
	return true;
}
static bool pic2digit(Mat &img, String picName, String fileName)
{
	uchar*		pTemp = NULL;
	Mat			signalChannel;
	ofstream	output;

	if (img.empty())
	{
		cout << "Load picture fail!" << endl;
		return false;
	}

	cout << endl << "/******************pic2digit******************/" << endl;
	//showImgPara(img);

	//namedWindow(picName);
	//imshow(picName, img);


	tran2singleChannel(img, signalChannel);

	//namedWindow(picName + "_signalChannel");
	//imshow(picName + "_signalChannel", signalChannel);

	showImgPara(signalChannel);

	output.open(fileName);
	for (int i = 0; i < signalChannel.rows; i++)
	{
		for (int j = 0; j < signalChannel.cols; j++)
		{
			for (int k = 0; k < signalChannel.step[1]; k++)
			{
				pTemp = signalChannel.data + signalChannel.step[0] * i + signalChannel.step[1] * j + k;
				output << std::setw(2) << std::setfill('0') << (int)*pTemp << " ";
			}
		}
		output << endl;
	}

	output.close();

	imwrite(picName + "_signalChannel.jpg", signalChannel);

	return true;
}

void creatLookuptable(Mat& table,uchar quan_val)
{
    table.create(1,256,CV_8UC1);
    uchar* p = table.data;
    for (int i = 0; i < 256; i++)
    {
        p[i] = quan_val * (i / quan_val);
    }
    
}

void creatLookuptable_2(Mat& table)
{
    table.create(1,256,CV_8UC1);
    uchar* p = table.data;
    for (int i = 0; i < 256; i++)
    {
        p[i] = i;
    }
}

int main()
{
    //设置打印等级
    utils::logging::setLogLevel(utils::logging::LOG_LEVEL_ERROR);
    //创建矩阵，元素全为0
    Mat m1 = Mat::zeros(10, 10, CV_8UC3);
    //修改元素
	picCreat(m1, "White");
    // matPrint(m1,"m1");

    Mat table;
    Mat out1;
    //创建查找表，对色彩空间进行分割
    creatLookuptable(table,20);
    //进行查找表运算
    LUT(m1,table,out1);
    matPrint(table,"table");
    matPrint(out1,"out1");
    namedWindow("name_out");
    imshow("name_out",out1);

    
    // Mat pic1 = imread("C:/Users/22231/Pictures/Screenshots/123.png");
    // pic2digit(pic1, "check", "check-circle.txt");

	waitKey(0);


    return 0;
}