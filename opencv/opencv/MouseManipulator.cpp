#include "MouseManipulator.hpp"


MouseHandle::MouseHandle()
{
	this->selectObject = false;
	this->processing = false;
}
MouseHandle::~MouseHandle()
{

}

MouseAreaSelect::MouseAreaSelect()
{
	mouseHandler = new MouseHandle();
}

MouseAreaSelect::~MouseAreaSelect()
{
	if (mouseHandler != NULL) {
		delete mouseHandler;
	}
}

void MouseAreaSelect::initialize(const std::string &windowName)
{
	if (mouseHandler == NULL) {
		return;
	}
	cv::setMouseCallback(windowName, onMouse, mouseHandler);
}

bool MouseAreaSelect::hasSelection()
{
	if (mouseHandler->selectObject) {
		return true;
	}
	else {
		return false;
	}
}

cv::Rect MouseAreaSelect::getSelectRect()
{
	return mouseHandler->selecRect;
}

void MouseAreaSelect::clear()
{
	mouseHandler->processing = false;
	mouseHandler->selecRect = cv::Rect();
	mouseHandler->selectObject = false;

}

void MouseAreaSelect::onMouse(int event, int x, int y, int, void *ptr)
{
	MouseHandle *mouseHandler = (MouseHandle*)ptr;
	if (mouseHandler->processing) {
		mouseHandler->selecRect.x = MIN(x, mouseHandler->point.x);
		mouseHandler->selecRect.y = MIN(y, mouseHandler->point.y);
		mouseHandler->selecRect.width = std::abs(x - mouseHandler->point.x);
		mouseHandler->selecRect.height = std::abs(y - mouseHandler->point.y);
	}
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN:
		mouseHandler->point = cv::Point(x, y);
		mouseHandler->selecRect = cv::Rect(x, y, 0, 0);
		mouseHandler->processing = true;
		mouseHandler->selectObject = false;
		break;
	case CV_EVENT_LBUTTONUP:
		mouseHandler->processing = false;
		if (mouseHandler->selecRect.width > 0 &&
			mouseHandler->selecRect.height > 0) {
			mouseHandler->selectObject = true;
		}
		break;
	}
}