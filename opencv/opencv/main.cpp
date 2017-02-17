#include <cstdio>
#include<iostream>
#include<vector>
#include <highgui.h>
#include <cv.h>
#include <opencv2/opencv.hpp>

#define STOPOUT() 	if (waitKey(0) == ' ') break;
#define BREAKOUT() if (waitKey(1) == ' ') break;
#define POINT(x,  y) x>=y?return Point(x, y):return Point(y, x);
#define D 9.0
#define SIGMA 300.0
#define DEVIATION 5.0
#define KIBI 16


using namespace cv;

struct Zone {
public:
	int x;
	int y;
	Zone(int a = 256, int b = 0) {
		if (a >= b) {
			x = a;
			y = b;
		}
		else {
			x = b;
			y = a;
		}
	}
	~Zone(){}
};
struct Color8 {
public:
	int blue;
	int green;
	int red;
	Color8(int b, int g, int r) {
		blue = b;
		green = g;
		red = r;
	}
	~Color8() {}
/**@做為當前pixel亮度		
Color8::average()為BGR三色平均
*/
	double average() {
		return (blue + green + red) / 3;
	}
/**@做為當前pixel色偏差
Color8::deviation()為BGR三色標準差
*/
	double deviation() {
		return (unsigned int)(blue - average()) + (unsigned int)(green - average()) + (unsigned int)(red - average()) / 3;
	}
};
struct Deviation {
public:
	std::vector <Color8> color;

	Deviation() {
	}
/**@此做為色差範圍的基準平均
Deviation::deviationAverage()為 Color8容器裡所有標準差的平均
為容許色偏差的基準
*/
	double deviationAverage() {
		double dA = 0.0;
		for (std::vector<Color8>::iterator iter = color.begin(); iter != color.end(); ++iter) {
			dA += (*iter).deviation();
		}
		return dA / (double)color.size();
	}
/**@顏色二值化之亮度基準平均
Deviation::totalAverage()為 Color8容器裡所有平均的平均
也就是所有色彩資料的平均  
因為只取灰色  此可當作亮度平均
以後如果有更多顏色需求  此段需在行更改
*/
	double totalAverage() {
		double tA = 0.0;
		for (std::vector<Color8>::iterator iter = color.begin(); iter != color.end(); ++iter) {
			tA += (*iter).average();
		}
		return tA / (double)color.size();
	}
/**@顏色二值化之亮度標準差
Deviation::averageDeviation()為Color8容器中所有平均的標準差
因為只取灰色  此可當作亮度容器Zone的範圍
以後如果有更多顏色需求  此段需在行更改
*/
	double averageDeviation() {
		double aD = 0.0;
		double tAverage = totalAverage();
		for (std::vector<Color8>::iterator iter = color.begin(); iter != color.end(); ++iter) {
			aD += (unsigned)((*iter).average() - tAverage);
		}
		return aD / color.size();
	}
}dev;

using unit = long long;
using number = unit[KIBI];

void plus(number, number);
void carry(number);
void selectPixel(int, int, int, int, void*);
void area(int, int, int, int, void *);
void skip(int, int, int, int, void *);
bool inRange(Mat&, Zone);
void test(Mat, Mat&, bool);

int set = 0;
const unit mask = (unit)0b001 << (sizeof(unit) * 8 - 2);

int main() {

	namedWindow("frame", WINDOW_NORMAL);
	namedWindow("Road", WINDOW_NORMAL);

	cv::Mat	frame;
	cv::Mat road;
	cv::VideoCapture cap("C:\\vedio.avi");
	if (!cap.isOpened()) {
		return -1;
	}

	while (true) {
		do {
			cap >> frame;
		} while (frame.empty());
		//bilateralFilter(frame, road, D, SIGMA, SIGMA);
		imshow("Road", frame);
		inRange(frame, Zone(dev.totalAverage() + dev.averageDeviation(), dev.totalAverage() - dev.averageDeviation()));
		//test(road, road, 1);
		imshow("frame", frame);
		//imshow("Road", road);
		setMouseCallback("Road", selectPixel, &frame);
	  /*	WTH!?
		*	這東西...TM竟然是同步執行的!?
		*  只要call過一次
		*  就會一直check event...
		*/

		BREAKOUT();
	}

	/*
		Mat img = imread("C:\\cat.jpg")
			, imgB
			, imgGB;
		double a = 0.0
			, b = 0.0;
		if (img.empty())
			return -1;
		namedWindow("Origin", WINDOW_NORMAL);
		namedWindow("Blur", WINDOW_NORMAL);
		namedWindow("GaussianBlur", WINDOW_NORMAL);
		blur(img, imgB, Size(3, 3));
		imshow("Origin", img);
		imshow("Blur", imgB);
		while (1) {
			GaussianBlur(img, imgGB, Size(3, 3), a, b);
			imshow("GaussianBlur", imgGB);
			switch (waitKey(0)) {
			case 119:
				b += 0.1;
				break;
			case 115:
				b -= 0.1;
				break;
			case 100:
				a += 0.1;
				break;
			case 97:
				a -= 0.1;
				break;
			case 27:
				return 0;
			}
			std::cout << a << " " << b << std::endl;
		}
		*/
	/*
	number a = { 0 }
				 , b = { 0 };
		a[0] = ((unit)0b001 << (sizeof(unit) * 8 - 1))-1;
		b[0] = (unit)0b001;
		set = 0;
		plus(a, b);
		std::cout << a[1] << a[0] << std::endl;
	*/
	/*
	namedWindow("輸入圖", WINDOW_NORMAL);
	namedWindow("頻譜", WINDOW_NORMAL);
	namedWindow("逆向求輸入圖", WINDOW_NORMAL);
	Mat padded;
	int m = getOptimalDFTSize(inputImg.rows);  //m為大於等於inputImg.rows裡的最小值，且須為2、3、5的次方相乘
	int n = getOptimalDFTSize(inputImg.cols);
	copyMakeBorder(inputImg, padded, 0, m - inputImg.rows, 0, n - inputImg.cols, BORDER_CONSTANT, Scalar::all(0)); //為了效率，所以對影像邊界拓展

	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexImg;
	merge(planes, 2, complexImg);
	dft(complexImg, complexImg);

	split(complexImg, planes);                  //分離通道，planes[0]為實數部分，planes[1]為虛數部分 
	magnitude(planes[0], planes[1], planes[0]); //planes[0] = sqrt((planes[0])^2 + (planes[1])^2
	Mat magI = planes[0];
	magI += Scalar::all(1);                     //magI = log(1+planes[0])
	log(magI, magI);

	magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));  //令邊長為偶數

															  //將區塊重排，讓原點在影像的中央
	int cx = magI.cols / 2;
	int cy = magI.rows / 2;

	Mat q0(magI, Rect(0, 0, cx, cy));
	Mat q1(magI, Rect(cx, 0, cx, cy));
	Mat q2(magI, Rect(0, cy, cx, cy));
	Mat q3(magI, Rect(cx, cy, cx, cy));

	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	normalize(magI, magI, 0, 1, CV_MINMAX);

	imshow("輸入圖", inputImg);
	imshow("頻譜", magI);

	//逆向傅立葉轉換
	Mat ifft;
	idft(complexImg, ifft, DFT_REAL_OUTPUT);
	normalize(ifft, ifft, 0, 1, CV_MINMAX);
	imshow("逆向求輸入圖", ifft);
	waitKey();
	*/
	return 0;
}

void plus(number a = { 0 }, number b = { 0 }) {
	for (int i = 0; i < KIBI; i++) {
		std::cout << i << "位數" << std::endl;
		unit temp = 0;
		while (b) {
			std::cout << "*" << std::endl;
			temp = a[set] ^ b[set];
			b[set] &= a[set];
			a[set] = temp;
			if (b[set] & mask) {
				b[set] = b[set] - mask;
				b[set] <<= 1;
				set++;
				carry(a);
				set--;
			}
			else
				b[set] <<= 1;
		}
		set++;
	}
}
void carry(number a = { 0 } ) {
	unit b = 1;
	for (int i = 0; i < KIBI; i++) {
		std::cout << i << "位數" << std::endl;
		unit temp = 0;
		while (b) {
			std::cout << "*" << std::endl;
			temp = a[set] ^ 1;
			b &= a[set];
			a[set] = temp;
			if (b & mask) {
				b = b - mask;
				b <<= 1;
				set++;
				carry(a);
				set--;
			}
			else
				b <<= 1;
		}
		set++;
	}
}
void selectPixel(int event, int x, int y, int flags, void *param) {
	if (!(event == CV_EVENT_LBUTTONDOWN))
		return;
	Mat *arr = (Mat *)param;
	int chan = arr->channels();
	uchar *ptr = arr->ptr<uchar>(y);
	dev.color.push_back(Color8((int) *(ptr + x*chan), (int) *(ptr + x*chan + 1), (int) *(ptr + x*chan + 2)));
}
void area(int event, int x, int y, int flags, void *) {

}
void skip(int event, int x, int y, int flags, void * param) {
	
}
bool inRange(Mat& src, Zone zone) {
	const int channel = src.channels();
	if (channel != 3) {
		std::cout << "There's no necessity to InRange a gray src" << std::endl;
		return false;
	}
	for (int height = 0; height != src.rows; ++height) {
		uchar *ptr = src.ptr<uchar>(height);
		for (int width = 0; width != src.cols; ++width) {
			const double &&average = ((int) *(ptr + width*channel) + (int) *(ptr + width*channel + 1) + (int) *(ptr + width*channel + 2)) / 3.0;
			if (average <= zone.x &&
				average >= zone.y &&
				((unsigned int)((int) *(ptr + width*channel) - average) + 
				(unsigned int)((int) *(ptr + width*channel + 1) - average) + 
				(unsigned int)((int) *(ptr + width*channel + 2) - average)) / 3 
				<= dev.deviationAverage()) {
				*(ptr + width*channel) = (uchar)255;
				*(ptr + width*channel + 1) = (uchar)255;
				*(ptr + width*channel + 2) = (uchar)255;
			}
			else {
				*(ptr + width*channel) = (uchar)0;
				*(ptr + width*channel + 1) = (uchar)0;
				*(ptr + width*channel + 2) = (uchar)0;
			}
		}
	}
	return true;
}
void test(Mat src, Mat &cah, bool light) {
	cah.create(src.cols, src.rows, CV_8U);
	for (int height = 0; height != src.rows; ++height) {
		uchar *pas = cah.ptr<uchar>(height);
		for (int width = 0; width != src.cols; ++width) {
			*(pas + width) += light ? 70 : -70;
		}
	}
	return;
}
