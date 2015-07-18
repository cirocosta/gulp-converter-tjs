#include "Tracker.hh"

namespace tracker {

Tracker::Tracker (const std::string classifier_path)
	: m_classifier(cv::CascadeClassifier(classifier_path)),
		m_classifier_path(classifier_path)
{
	scale_factor = 1.20;
	min_neighbors = 4;
	flags = 0|cv::CASCADE_SCALE_IMAGE;
	size = cv::Size(30,30);
}

Tracker::Tracker (const std::string cp, const double sf, const int mn, const int f,
					const cv::Size s)
	: m_classifier(cv::CascadeClassifier(cp)),
		m_classifier_path(cp)
{
	scale_factor = sf;
	min_neighbors = mn;
	flags = f;
	size = s;
}

Tracker::~Tracker() {}

/**
 * Performs the main step. Paralellizable by
 * TBB if set when building from source.
 */
void Tracker::detect (const cv::Mat& image, std::vector<cv::Rect_<int>>& faces)
{
	m_classifier.detectMultiScale(image, faces, scale_factor, min_neighbors,
																flags, size);
}

void Tracker::draw_objs (const cv::Mat& image,
												 const std::vector<cv::Rect_<int>>& objs) const
{
	cv::Mat img = image.clone();

	for (const auto& obj : objs)
		cv::rectangle(img, obj, cv::Scalar(0, 255, 0), 1, 8, 0);
	cv::imshow("Result", img);

	while (1) cv::waitKey();
}

}; // !ns tracker

