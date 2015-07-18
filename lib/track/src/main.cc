#include "tracker/Tracker.hh"
#include "cli/CliTracker.hh"

#include <iostream>
#include <cstdio>

using tracker::tracker::CliTracker;
using tracker::Tracker;
using tracker::tracker::FILENAMES;
using tracker::tracker::CLASSIFIER;
using tracker::tracker::SHOW;


int main(const int argc, char **argv)
{
	CliTracker cli;
	cli.parse(argc, argv);

	cv::Mat image;
	Tracker tracker (cli.args[CLASSIFIER].front());
	std::vector<cv::Rect_<int>> faces;
	bool show = cli.args[SHOW].size() > 0;

	for (const auto& fname : cli.args[FILENAMES]) {
		image = cv::imread(fname, 1);

		if (!image.data) {
			std::cerr << "Error:\n"
								<< "\t" << fname << " not found." << std::endl;
			exit(EXIT_FAILURE);
		}

		tracker.detect(image, faces);

		for (const auto& face : faces) {
			std::cout << face.x + face.width/2 << " "
								<< face.y + face.height/2 << std::endl;
		}

		if (show)
			tracker.draw_objs(image, faces);
	}

	return EXIT_SUCCESS;
}

