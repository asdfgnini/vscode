#include <iostream>
//避免函数名重合，都采用cv空间的函数
#include<iomanip>
using std::cout;
using std::endl;

#include "opencv2/core.hpp"
using namespace cv;


int main()
{
    //创建一个8Mb大小的大矩阵
    Mat A(1000,1000,CV_64F);
    Mat B = A;//为同一个矩阵创建另一个标题,这是一个即时操作，不论矩阵的大小。
    Mat C = B.row(3);// 为A的第三行创建另一个标题；不复制任何数据

    Mat D = B.clone();// 现在创建矩阵的一个独立副本,数据拷贝了一份     

    B.row(5).copyTo(C);//将B的第5行复制到C，即复制A的第5行

    A = D;//现在让A和D共享数据，即A指向D的数据区域；之后是修改后的版本,A仍然被B和C引用

    B.release();//现在将B设置为空矩阵（不引用任何内存缓冲区）,但是A的修改版本仍然会被C引用

    C = C.clone();//最后，对C进行完全复制。结果是，大的修改,矩阵将被释放，因为没有任何人引用它

    //你会发现，使用Mat和其他基本结构是简单的。但是对于高级类或者甚至是没有考虑自动内存管理的用户数据类型，
    //OpenCV提供了cv::Ptr模板类，它类似于C++11中的std::shared_ptr。因此，不再使用普通指针：

    //Ptr<T> ptr(new T(...));
    //Ptr<T> ptr = makePtr<T>(...);

    Mat M(2,2,CV_8UC3,Scalar(0,0,255));
    cout << "M= " << endl << " " << M << endl <<endl;

    Mat R = Mat(5, 5, CV_8UC3);
    randu(R,Scalar::all(0),Scalar::all(255));
    cout << "R= " << endl << " " << R << endl <<endl;

    cout <<  R.isContinuous() << endl;
    cout << "row: = " <<  R.rows << endl;


    const uchar* previous = R.ptr<uchar>(0);
    const uchar* current  = R.ptr<uchar>(1);
    const uchar* next     = R.ptr<uchar>(2);

    printf("%d\r\n",*(previous));
    printf("%d\r\n",*current);
    printf("%d\r\n",*next);
    printf("%d\r\n",*(current - 2));
    
    return 0;
}