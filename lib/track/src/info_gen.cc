#include "opencv2/opencv.hpp"

#include <vector>
#include <iostream>

using cv::WINDOW_NORMAL;
using cv::imread;
using cv::waitKey;
using cv::setMouseCallback;
using cv::imshow;
using cv::Rect;
using cv::Point;
using cv::Scalar;
using cv::rectangle;
using cv::Mat;

Mat src;
Mat img;

// Current rectangle and start&end points
Rect rect (0, 0, 0, 0);
Point P1 (0, 0);
Point P2 (0, 0);

// Rectangles to be outputted
std::vector<Rect> rects;

static const char* WINDOW_NAME = "Tracking Info Generator";
static bool clicked = false;


void fixBoundaries(){
	if (rect.width > img.cols - rect.x)
	  rect.width = img.cols - rect.x;

	if (rect.height > img.rows - rect.y)
		rect.height = img.rows - rect.y;

	if (rect.x < 0)
		rect.x = 0;

	if (rect.y < 0)
		rect.height = 0;
}

void draw(){
	img = src.clone();
	fixBoundaries();

	for (const auto& r : rects)
		rectangle(img, r, Scalar(0,255,0), 1, 8, 0 );
	rectangle(img, rect, Scalar(0,255,0), 1, 8, 0 );

	imshow(WINDOW_NAME, img);
}


void onMouse(int event, int x, int y, int f, void*){
	switch(event){
		case CV_EVENT_LBUTTONDOWN:
			clicked = true;
			P1.x = x;
			P1.y = y;
			P2.x = x;
			P2.y = y;
			break;

		case  CV_EVENT_LBUTTONUP:
			clicked = false;
			P2.x = x;
			P2.y = y;
			break;

		case CV_EVENT_MOUSEMOVE:
			if (clicked) {
				P2.x=x;
				P2.y=y;
			}
			break;

		default:
			break;
	}

	if (P1.x > P2.x) {
		rect.x = P2.x;
		rect.width = P1.x - P2.x;
	} else {
		rect.x=P1.x;
		rect.width = P2.x - P1.x;
	}

	if (P1.y > P2.y) {
		rect.y = P2.y;
		rect.height = P1.y - P2.y;
	} else {
		rect.y = P1.y;
		rect.height = P2.y - P1.y;
	}

	draw();
}

int main()
{
    src = imread("../assets/face/faces.png", 1);

    namedWindow(WINDOW_NAME, WINDOW_NORMAL);
    setMouseCallback(WINDOW_NAME, onMouse, NULL );
    imshow(WINDOW_NAME, src);

    while (1) {
			char c = waitKey();

			switch (c) {
				case 's':
					if (rects.empty()) {
						std::cerr << "No rect added." << std::endl
											<< "Select an area and press 'a' to add!" << std::endl;
						continue;
					}

					for (const auto& r : rects) {
						std::cout << r.x + r.width/2 << " "
											<< r.y + r.height/2 << std::endl;
					}
					break;
				case 'a':
					rects.push_back(rect);
					rect = Rect(0, 0, 0, 0);
					break;
			}
    }

    return 0;
}

