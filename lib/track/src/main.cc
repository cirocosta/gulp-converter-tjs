#include "Tracker.hh"
#include "Cli.hh"

#include <iostream>
#include <cstdio>


int main(const int argc, char **argv)
{
	tracker::parse(argc, argv);
	tracker::Tracker tracker ("../assets/face/haarcascade_frontalface_alt.xml");
	cv::Mat image = cv::imread("../assets/face/faces.png", 1);
	std::vector<cv::Rect_<int>> faces;

	if (!image.data) {
		printf("No image data\n");
		exit(EXIT_FAILURE);
	}

	tracker.detect(image, faces);

	for (const auto& face : faces) {
		std::cout << "face:" << std::endl
							<< "\t" << face.x     << ":" << face.y      << std::endl
						  << "\t" << face.width << ":" << face.height << std::endl;
	}

	return EXIT_SUCCESS;
}

