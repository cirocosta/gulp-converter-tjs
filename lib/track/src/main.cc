#include "Tracker.hh"

#include <iostream>
#include <cstdio>

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("displaying\n");
	}

	Tracker tracker ("../assets/face/haarcascade_frontalface_alt.xml");
	cv::Mat image = cv::imread("../assets/face/faces.png", 1);
	std::vector<cv::Rect_<int>> faces;

	if (!image.data) {
		printf("No image data\n");
		return -1;
	}

	tracker.detect(image, faces);

	for (const auto& face : faces) {
		std::cout << "face:" << std::endl
							<< "\t" << face.x     << ":" << face.y      << std::endl
						  << "\t" << face.width << ":" << face.height << std::endl;
	}

	cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
	cv::imshow("Display Image", image);
	cv::waitKey(0);

	return EXIT_SUCCESS;
}

