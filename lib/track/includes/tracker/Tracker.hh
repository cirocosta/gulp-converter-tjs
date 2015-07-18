#ifndef TRACKER__TRACKER_HH
#define TRACKER__TRACKER_HH

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <string>
#include <algorithm>
#include <vector>


namespace tracker {

class Tracker
{
	cv::CascadeClassifier m_classifier;
	const std::string m_classifier_path;
public:
	double scale_factor;
	int min_neighbors;
	int flags;
	cv::Size size;
public:
	Tracker (const std::string classifier_path);
	Tracker (const std::string cp, const double sf, const int mn, const int f,
					 const cv::Size s);
	~Tracker();

	void draw_objs (const cv::Mat& image,
									const std::vector<cv::Rect_<int>>& objs) const;
	void detect (const cv::Mat& image, std::vector<cv::Rect_<int>>& objs);
};

}; // !ns tracker

#endif

