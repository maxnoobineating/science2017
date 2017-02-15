/*
#define ONLY
#include "MouseManipulator.hpp"
#include < iostream >

int main(int argc, char ** argv)
{
	cv::VideoCapture cap;
	cap.open(0);

	cv::namedWindow("Demo", 1);
	MouseManipulator mouseHandler;
	mouseHandler.initialize("Demo");

	cv::Mat image;

	for (;;) {
		cv::Mat frame;
		cap >> frame;
		if (frame.empty())
			break;

		frame.copyTo(image);

		if (mouseHandler.hasSelection()) {
			cv::Rect rect = mouseHandler.getSelectRect();
			std::cout << "x = " << rect.x << ", y = " << rect.y << ", width = " << rect.width << ", height = " << rect.height << std::endl;
			mouseHandler.clear();
		}
		else {
			cv::Rect rect = mouseHandler.getSelectRect();
			cv::Mat roi(image, rect);
			cv::bitwise_not(roi, roi);
		}

		cv::imshow("Demo", image);
		cv::waitKey(30);
	}
	return 0;
}
*/