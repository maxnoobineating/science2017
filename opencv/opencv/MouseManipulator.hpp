#ifndef MOUSEMANIPULATOR_H
#define MOUSEMANIPULATOR_H
#include "opencv2/opencv.hpp"
#define CV_EVENT_MOUSEMOVE			0
#define CV_EVENT_LBUTTONDOWN	1
#define CV_EVENT_RBUTTONDOWN	2
#define CV_EVENT_MBUTTONDOWN	3
#define CV_EVENT_LBUTTONUP			4
#define CV_EVENT_RBUTTONUP			5
#define CV_EVENT_MBUTTONUP			6
#define CV_EVENT_LBUTTONDBLCLK	7
#define CV_EVENT_RBUTTONDBLCLK	8
#define CV_EVENT_MBUTTONDBLCLK	9
#define CV_EVENT_FLAG_LBUTTON		1
#define CV_EVENT_FLAG_RBUTTON		2
#define CV_EVENT_FLAG_MBUTTON	4
#define CV_EVENT_FLAG_CTRLKEY		8
#define CV_EVENT_FLAG_SHIFTKEY		16
#define CV_EVENT_FLAG_ALTKEY			32

struct MouseHandle
{
public:
	MouseHandle();
	~MouseHandle();
	cv::Rect selecRect;
	cv::Point2f point;
	bool selectObject;
	bool processing;
};

class MouseManipulator
{
public:
	MouseManipulator();
	~MouseManipulator();
	void initialize(const std::string &windowName);

	bool hasSelection();
	cv::Rect getSelectRect();
	void clear();

	static void onMouse(int event, int x, int y, int, void *ptr);

private:
	MouseHandle *mouseHandler;
};

#endif