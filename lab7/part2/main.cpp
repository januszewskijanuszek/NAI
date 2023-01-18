#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;


int main(int argc, char** argv){
//    using namespace cv;
//    VideoCapture vc(0);
//    if (!vc.isOpened() ) return 1;
//    cv::Mat frame;
//    cv::Mat video;
//
//    cv::namedWindow("Window", WINDOW_AUTOSIZE); // Create a window for display.
//    while (waitKey(10) != 27) {
//        vc >> frame;
//        std::cout << "frame info: " << frame.rows << " " << frame.cols << std::endl;
//        cv::flip(frame, video, 1);
//        cv::imshow("Video", video);
//    }
//    return 0;
    cv::VideoCapture cap(0);
    if(!cap.isOpened())
        return -1;
    cv::Mat frame;
    namedWindow("Flipped", cv::WINDOW_AUTOSIZE);
    while(cv::waitKey(10) != 27){
        cap >> frame;
        cv::flip(frame, frame, 1);
        cv::imshow("Flipped", frame);
    }
    return 0;
}
