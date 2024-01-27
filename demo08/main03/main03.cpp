#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using std::cout;
using std::endl;
using std::vector;
using std::ofstream;

#include "opencv2/opencv.hpp"
#include <opencv2/core/utils/logger.hpp>
using namespace cv;

static bool matPrint(Mat &img,String tiltle)
{
	uchar* pTemp = NULL;
	cout << endl << "/****************** " << tiltle << " ******************/" << endl;

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
			cout << "]	";
		}
		cout << endl;
	}

	return true;
}


void Sharpen(const Mat& myImage,Mat& Result)
{
    CV_Assert(myImage.depth() == CV_8U);  // accept only uchar images
    const int nChannels = myImage.channels();
    Result.create(myImage.size(),myImage.type());
    for(int j = 1 ; j < myImage.rows-1; ++j)
    {
        const uchar* previous = myImage.ptr<uchar>(j - 1);
        const uchar* current  = myImage.ptr<uchar>(j    );
        const uchar* next     = myImage.ptr<uchar>(j + 1);
	
        uchar* output = Result.ptr<uchar>(j);
        for(int i= nChannels;i < nChannels*(myImage.cols-1); ++i)
        {
            output[i] = saturate_cast<uchar>(5*current[i]
                         -current[i-nChannels] - current[i+nChannels] - previous[i] - next[i]);
        }
    }
    Result.row(0).setTo(Scalar(0));
    Result.row(Result.rows-1).setTo(Scalar(0));
    Result.col(0).setTo(Scalar(0));
    Result.col(Result.cols-1).setTo(Scalar(0));
}

int main()
{
	utils::logging::setLogLevel(utils::logging::LOG_LEVEL_ERROR);

	Mat a = Mat(10,10,CV_8UC3);
	randu(a,Scalar::all(0),Scalar::all(255));

	matPrint(a,"a");
	Mat dst1;
	double t = (double)getTickCount();

	Sharpen(a,dst1);

	t = ((double)getTickCount() - t) / getTickFrequency();
	cout << "t: = " << t << endl;
	matPrint(dst1,"dst1");
	const uchar* previous = a.ptr<uchar>(0);
	const uchar* current  = a.ptr<uchar>(1);
	const uchar* next     = a.ptr<uchar>(2);

	printf("%d\r\n",*previous);
	printf("%d\r\n",*current);
	printf("%d\r\n",*next);
	printf("\r\n");
	printf("%d\r\n",*(current + 3));
	printf("%d\r\n",*(current + 0));
	printf("%d\r\n",*(current + 6));
	printf("%d\r\n",*(previous + 3));
	printf("%d\r\n",*(next + 3));




    return 0;
}