#include <iostream> 
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>

#include <stdexcept>

#include <vector>
#include <algorithm>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <ctype.h>
#include <windows.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define CVUI_IMPLEMENTATION
#include "cvui.h"
#include < locale.h >

#ifdef _DEBUG
#define CV_EXT "d.lib"
#else
#define CV_EXT ".lib"
#endif
#pragma comment(lib, "opencv_world320" CV_EXT) // OpenCV3.3.0ÇÃèÍçáÇÕÅA"opencv_core330"Ç…

using namespace cv;
using namespace std;

#define WINDOW_NAME	"CVUI Test"

std::vector<std::string> get_file_path_in_dir(const std::string& dir_name, const std::string& extension);

int main(int argc, char* argv[]){
	cv::Mat frame = cv::Mat(300, 600, CV_8UC3);
	bool checked = false;
	bool checked2 = true;
	int count = 0;
	double countFloat = 0.0;
	double trackbarValue = 0.0;

	// Init cvui and tell it to create a OpenCV window, i.e. cv::namedWindow(WINDOW_NAME).
	cvui::init(WINDOW_NAME);


	vector<string> cht_files = get_file_path_in_dir("cht", "cht");
	cout << cht_files.size() << endl;
	while (true) {
		frame = cv::Scalar(49, 52, 49);
		
		
		cvui::text(frame, 10, 10, "Setting");

		if (cvui::button(frame, frame.cols-100, 10, "Load")) {
			std::cout << "Button clicked" << std::endl;
		}

		else if (cvui::button(frame, frame.cols - 100, 40, "Start")) {
			std::cout << "Button clicked" << std::endl;
		}

		cvui::counter(frame, 10, 30, &count);

		if (count >= cht_files.size()) count = 0;
		cvui::text(frame, 150, 35, cht_files[count]);


		cvui::checkbox(frame, 10, 60, "Checkbox1", &checked);
		cvui::checkbox(frame, 10, 90, "Checkbox2", &checked2);


		cvui::update();
		cv::imshow(WINDOW_NAME, frame);
		if (cv::waitKey(1) == 27) {
			break;
		}
	}

	return 0;
}


std::vector<std::string> get_file_path_in_dir(const std::string& dir_name, const std::string& extension){

	HANDLE hFind;
	WIN32_FIND_DATA win32fd;//defined at Windwos.h
	std::vector<std::string> file_names;

	//ägí£éqÇÃê›íË
	std::string search_name = dir_name + "\\*." + extension;

	hFind = FindFirstFile((search_name.c_str()), &win32fd);

	if (hFind == INVALID_HANDLE_VALUE) {
		throw std::runtime_error("file not found");
	}

	do {
		if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
		}
		else {
			file_names.push_back(win32fd.cFileName);
			printf("%s\n", file_names.back().c_str());

		}
	} while (FindNextFile(hFind, &win32fd));

	FindClose(hFind);

	return file_names;
}
