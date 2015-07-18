#include "tracker/Tracker.hh"
#include "cli/CliSolver.hh"

using tracker::solver::CLASSIFIER;
using tracker::solver::FILENAME;
using tracker::solver::EXPECTED;
using tracker::solver::CliSolver;
using tracker::Tracker;

#include <opencv2/opencv.hpp>

using cv::Rect_;
using cv::Size;
using cv::imread;
using cv::Mat;

#include <fstream>
#include <cmath>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>


struct Point {
	double x;
	double y;

	float distance(const Point& p) const
	{
		return std::sqrt((x-p.x)*(x-p.x) + (y-p.y)*(y-p.y));
	}
};
std::ostream& operator<<(std::ostream& o, const Point& p)
{
	o << p.x << " " << p.y;
	return o;
}

std::vector<Point> expected_points;
std::vector<Point> actual_points;
std::vector<Rect_<int>> rects;

/**
 * Given expected rect centers, image source and
 * classifier, tweaks some parameters to try to
 * minimize the distance to the expected.
 *
 * scale_factor		:	[1.0:2.0:0.1]
 * min_neighbors	:	[0:10:1]
 */
int main(const int argc, char *argv[])
{
	CliSolver cli;
	cli.parse(argc, argv);

	double x, y;
	std::string image_path;
	Tracker tracker (cli.args[CLASSIFIER].front());
	Mat image = imread(cli.args[FILENAME].front());
	std::ifstream expected (cli.args[EXPECTED].front());

	if (!expected.good()) {
		std::cerr << "Error trying to read " << cli.args[EXPECTED].front()
							<< std::endl;
		exit(EXIT_FAILURE);
	}

	while (expected >> x, expected >> y) {
		expected_points.push_back(Point {x, y});
		std::cout << expected_points.back() << std::endl;
	}

	for (double scale_factor = 1.01; scale_factor <= 2.0; scale_factor += 0.2) {
		for (int min_neighbors = 1; min_neighbors <= 10; min_neighbors += 1) {
			float sum_dist = 0.0;
			unsigned num_detected;

			tracker.scale_factor = scale_factor;
			tracker.min_neighbors = min_neighbors;
			tracker.detect(image, rects);
			num_detected = rects.size();

			for (const auto& rect : rects) {
				Point p {
						std::floor(rect.x + rect.width/2),
						std::floor(rect.y + rect.height/2)
				};

				std::sort(expected_points.begin(), expected_points.end(),
									[&p](const Point& p1, const Point&p2) -> bool {
					return p1.distance(p) < p2.distance(p);
				});

				sum_dist += p.distance(expected_points.front());
			}

			rects.clear();
			std::cout << min_neighbors << " : " << scale_factor << " = " << sum_dist
				<< " | num: " << num_detected << std::endl;
		}
	}

	return 0;
}
