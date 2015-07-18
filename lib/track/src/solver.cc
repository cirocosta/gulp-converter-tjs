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

	while (expected >> x, expected >> y) {
		expected_points.push_back(Point {x, y});
		std::cout << expected_points.back() << std::endl;
	}

	tracker.detect(image, rects);

	for (const auto& rect : rects) {
		Point p {
				std::floor(rect.x + rect.width/2),
				std::floor(rect.y + rect.height/2)
		};

		std::sort(expected_points.begin(), expected_points.end(),
							[&p](const Point& p1, const Point&p2) -> bool {
			return p1.distance(p) < p2.distance(p);
		});

		std::cout <<  p.distance(expected_points.front()) << " : "
			<< p << " compared to " << expected_points.front() << std::endl;
	}


	return 0;
}
