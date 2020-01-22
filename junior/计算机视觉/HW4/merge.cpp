#include <windows.h>  // for windows systems
#include <iostream>     // cout
#include <algorithm>    // std::sort
#include <opencv2/opencv.hpp>

using std::string;
using std::vector;
using std::cout;
using std::cerr;
using std::endl;

// Returns a list of files in a directory (except the ones that begin with a dot)
int readFilenames(vector<string>& filenames, const string& directory) {
	HANDLE dir;
	WIN32_FIND_DATA file_data;

	if ((dir = FindFirstFile((directory + "\\*").c_str(), &file_data)) == INVALID_HANDLE_VALUE)
		return -1;  // no files found
	do {
		const string file_name = file_data.cFileName;
		const string full_file_name = directory + "\\" + file_name;
		const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

		if (file_name[0] == '.')
			continue;

		if (is_directory)
			continue;

		filenames.push_back(full_file_name);
	} while (FindNextFile(dir, &file_data));

	FindClose(dir);
	std::sort(filenames.begin(), filenames.end());  // optional, sort the filenames
	return(filenames.size());  // return how many we found
}  // GetFilesInDirectory

void help( char *argv[]) {
	cout << "\n\n"
		<< "\Enter a chessboard¡¯s width and height,\n"
		<< "              reading in a directory of chessboard images,\n"
		<< "              and calibrating the camera, using homography to get a bird's eye view.\n\n"
		<< "Call:\n" << argv[0] << " <1board_width> <2board_height> <3number_of_boards>"
		<< " <4ms_delay_framee_capture> <5image_scaling_factor> <6path_to_calibration_images><path/chessboard_image>\n\n"
		<< "\nExample:\n"
		<< "./example_18-01_from_disk 12 12 28 100 0.5 ../../birdseye/ ../../birdseye/IMG_0215.jpg \n\n"
		<< " * First it reads in checker boards and calibrates itself\n"
		<< " * Then it saves and reloads the calibration matricies\n"
		<< " * Then it creates an undistortion map and finaly\n"
		<< " * It displays an undistorted image\n"
		<< endl;
}

void func18_01(int board_w, int board_h, int n_boards, int delay, float image_sf, string folder)
{
	int board_n = board_w * board_h;  // number of corners
	cv::Size board_sz = cv::Size(board_w, board_h);  // width and height of the board
	cout << "Reading in directory " << folder << endl;
	vector<string> filenames;
	int num_files = readFilenames(filenames, folder);
	cout << "   ... Done. Number of files = " << num_files << "\n" << endl;

	// PROVIDE PPOINT STORAGE
	//
	vector<vector<cv::Point2f> > image_points;
	vector<vector<cv::Point3f> > object_points;

	/////////// COLLECT //////////////////////////////////////////////
	// Capture corner views: loop through all calibration images
	// collecting all corners on the boards that are found
	//
	cv::Size image_size;
	int board_count = 0;
	for (size_t i = 0; (i < filenames.size()) && (board_count < n_boards); ++i) {
		cv::Mat image, image0 = cv::imread(filenames[i]);
		board_count += 1;
		if (!image0.data) {  // protect against no file
			cerr << filenames[i] << ", file #" << i << ", is not an image" << endl;
			continue;
		}
		image_size = image0.size();
		cv::resize(image0, image, cv::Size(), image_sf, image_sf, cv::INTER_LINEAR);

		// Find the board
		//
		vector<cv::Point2f> corners;
		bool found = cv::findChessboardCorners(image, board_sz, corners);

		// Draw it
		//
		drawChessboardCorners(image, board_sz, corners, found);  // will draw only if found

																 // If we got a good board, add it to our data
																 //
		if (found) {
			image ^= cv::Scalar::all(255);
			cv::Mat mcorners(corners);

			// do not copy the data
			mcorners *= (1.0 / image_sf);

			// scale the corner coordinates
			image_points.push_back(corners);
			object_points.push_back(vector<cv::Point3f>());
			vector<cv::Point3f> &opts = object_points.back();

			opts.resize(board_n);
			for (int j = 0; j < board_n; j++) {
				opts[j] = cv::Point3f(static_cast<float>(j / board_w),
					static_cast<float>(j % board_w), 0.0f);
			}
			cout << "Collected " << static_cast<int>(image_points.size())
				<< "total boards. This one from chessboard image #"
				<< i << ", " << filenames[i] << endl;
		}
		cv::imshow("Calibration", image);

		// show in color if we did collect the image
		if ((cv::waitKey(delay) & 255) == 27) {
			return;
		}

	}

	// END COLLECTION WHILE LOOP.
	cv::destroyWindow("Calibration");
	cout << "\n\n*** CALIBRATING THE CAMERA...\n" << endl;

	/////////// CALIBRATE //////////////////////////////////////////////
	// CALIBRATE THE CAMERA!
	//
	cv::Mat intrinsic_matrix, distortion_coeffs;
	double err = cv::calibrateCamera(
		object_points, image_points, image_size, intrinsic_matrix,
		distortion_coeffs, cv::noArray(), cv::noArray(),
		cv::CALIB_ZERO_TANGENT_DIST | cv::CALIB_FIX_PRINCIPAL_POINT
	);

	// SAVE THE INTRINSICS AND DISTORTIONS
	cout << " *** DONE!\n\nReprojection error is " << err
		<< "\nStoring Intrinsics.xml and Distortions.xml files\n\n";
	cv::FileStorage fs("intrinsics.xml", cv::FileStorage::WRITE);
	fs << "image_width" << image_size.width << "image_height" << image_size.height
		<< "camera_matrix" << intrinsic_matrix << "distortion_coefficients"
		<< distortion_coeffs;
	fs.release();

	// EXAMPLE OF LOADING THESE MATRICES BACK IN:
	fs.open("intrinsics.xml", cv::FileStorage::READ);
	cout << "\nimage width: " << static_cast<int>(fs["image_width"]);
	cout << "\nimage height: " << static_cast<int>(fs["image_height"]);
	cv::Mat intrinsic_matrix_loaded, distortion_coeffs_loaded;
	fs["camera_matrix"] >> intrinsic_matrix_loaded;
	fs["distortion_coefficients"] >> distortion_coeffs_loaded;
	cout << "\nintrinsic matrix:" << intrinsic_matrix_loaded;
	cout << "\ndistortion coefficients: " << distortion_coeffs_loaded << "\n" << endl;
	cv::Mat map1, map2;
	cv::initUndistortRectifyMap(intrinsic_matrix_loaded, distortion_coeffs_loaded,
		cv::Mat(), intrinsic_matrix_loaded, image_size,
		CV_16SC2, map1, map2);

	////////// DISPLAY //////////////////////////////////////////////
	cout << "*****************\nPRESS A KEY TO SEE THE NEXT IMAGE, ESQ TO QUIT\n"
		<< "****************\n" << endl;
	board_count = 0;  // resent max boards to read
	for (size_t i = 0; (i < filenames.size()) && (board_count < n_boards); ++i) {
		cv::Mat image, image0 = cv::imread(filenames[i]);
		++board_count;
		if (!image0.data) {  // protect against no file
			cerr << folder + filenames[i] << ", file #" << i << ", is not an image" << endl;
			continue;
		}
		// Just run the camera to the screen, now showing the raw and
		// the undistorted image.
		//
		cv::remap(image0, image, map1, map2, cv::INTER_LINEAR,
			cv::BORDER_CONSTANT, cv::Scalar());
		cv::imshow("Original", image0);
		resize(image, image, cv::Size(600, 800));
		cv::imshow("Undistorted", image);
		if ((cv::waitKey(0) & 255) == 27) {
			break;
		}
	}
	return;
}


int main(int argc, char *argv[]) {
	float image_sf = 0.5f;    // image scaling factor
	int delay = 250;          // miliseconds
	if (argc != 8) {
		cout << "\nERROR: too few parameters\n";
		help(argv);
		return -1;
	}
	// Input Parameters:
	//
	int board_w = atoi(argv[1]);
	int board_h = atoi(argv[2]);
	int board_n = board_w * board_h; 
	int n_boards = atoi(argv[3]);  // how many boards max to read
	delay = atof(argv[4]);         // milisecond delay
	image_sf = atof(argv[5]);
	string folder = argv[6];
	func18_01(board_w, board_h, n_boards, delay, image_sf, folder);
	cv::Size board_sz(board_w, board_h);
	cv::FileStorage fs("intrinsics.xml", cv::FileStorage::READ);
	cv::Mat intrinsic, distortion;

	fs["camera_matrix"] >> intrinsic;
	fs["distortion_coefficients"] >> distortion;

	if (!fs.isOpened() || intrinsic.empty() || distortion.empty()) {
		cout << "Error: Couldn't load intrinsic parameters from " << argv[3]
			<< endl;
		return -1;
	}
	fs.release();

	cv::Mat gray_image, image, image0 = cv::imread(argv[7], 1);
	if (image0.empty()) {
		cout << "Error: Couldn't load image " << argv[7] << endl;
		return -1;
	}

	// UNDISTORT OUR IMAGE
	//
	cv::undistort(image0, image, intrinsic, distortion, intrinsic);
	cv::cvtColor(image, gray_image, cv::COLOR_BGRA2GRAY);

	// GET THE CHECKERBOARD ON THE PLANE
	//
	vector<cv::Point2f> corners;

	bool found = cv::findChessboardCorners( // True if found
		image,                              // Input image
		board_sz,                           // Pattern size
		corners,                            // Results
		cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FILTER_QUADS);
	if (!found) {
		cout << "Couldn't acquire checkerboard on " << argv[7] << ", only found "
			<< corners.size() << " of " << board_n << " corners\n";
		return -1;
	}

	// Get Subpixel accuracy on those corners
	//
	cv::cornerSubPix(
		gray_image,       // Input image
		corners,          // Initial guesses, also output
		cv::Size(11, 11), // Search window size
		cv::Size(-1, -1), // Zero zone (in this case, don't use)
		cv::TermCriteria(cv::TermCriteria::EPS | cv::TermCriteria::COUNT, 30,
			0.1));

	// GET THE IMAGE AND OBJECT POINTS:
	// Object points are at (r,c):
	// (0,0), (board_w-1,0), (0,board_h-1), (board_w-1,board_h-1)
	// That means corners are at: corners[r*board_w + c]
	//
	cv::Point2f objPts[4], imgPts[4];
	objPts[0].x = 0;
	objPts[0].y = 0;
	objPts[1].x = board_w - 1;
	objPts[1].y = 0;
	objPts[2].x = 0;
	objPts[2].y = board_h - 1;
	objPts[3].x = board_w - 1;
	objPts[3].y = board_h - 1;
	imgPts[0] = corners[0];
	imgPts[1] = corners[board_w - 1];
	imgPts[2] = corners[(board_h - 1) * board_w];
	imgPts[3] = corners[(board_h - 1) * board_w + board_w - 1];

	// DRAW THE POINTS in order: B,G,R,YELLOW
	//
	cv::circle(image, imgPts[0], 9, cv::Scalar(255, 0, 0), 3);
	cv::circle(image, imgPts[1], 9, cv::Scalar(0, 255, 0), 3);
	cv::circle(image, imgPts[2], 9, cv::Scalar(0, 0, 255), 3);
	cv::circle(image, imgPts[3], 9, cv::Scalar(0, 255, 255), 3);

	// DRAW THE FOUND CHECKERBOARD
	//
	cv::drawChessboardCorners(image, board_sz, corners, found);
	cv::imshow("Checkers", image);

	// FIND THE HOMOGRAPHY
	//
	cv::Mat H = cv::getPerspectiveTransform(objPts, imgPts);

	// LET THE USER ADJUST THE Z HEIGHT OF THE VIEW
	//
	cout << "\nPress 'd' for lower birdseye view, and 'u' for higher (it adjusts the apparent 'Z' height), Esc to exit" << endl;
	double Z = 15;
	cv::Mat birds_image;
	for (;;) {
		// escape key stops
		H.at<double>(2, 2) = Z;
		// USE HOMOGRAPHY TO REMAP THE VIEW
		//
		cv::warpPerspective(image,			// Source image
			birds_image, 	// Output image
			H,              // Transformation matrix
			image.size(),   // Size for output image
			cv::WARP_INVERSE_MAP | cv::INTER_LINEAR,
			cv::BORDER_CONSTANT, cv::Scalar::all(0) // Fill border with black
		);
		cv::imshow("Birds_Eye", birds_image);
		int key = cv::waitKey() & 255;
		if (key == 'u')
			Z += 0.5;
		if (key == 'd')
			Z -= 0.5;
		if (key == 27)
			break;
	}

	// SHOW ROTATION AND TRANSLATION VECTORS
	//
	vector<cv::Point2f> image_points;
	vector<cv::Point3f> object_points;
	for (int i = 0; i < 4; ++i) {
		image_points.push_back(imgPts[i]);
		object_points.push_back(cv::Point3f(objPts[i].x, objPts[i].y, 0));
	}
	cv::Mat rvec, tvec, rmat;
	cv::solvePnP(object_points, 	// 3-d points in object coordinate
		image_points,  	// 2-d points in image coordinates
		intrinsic,     	// Our camera matrix
		cv::Mat(),     	// Since we corrected distortion in the
						// beginning,now we have zero distortion
						// coefficients
		rvec, 			// Output rotation *vector*.
		tvec  			// Output translation vector.
	);
	cv::Rodrigues(rvec, rmat);

	// PRINT AND EXIT
	cout << "rotation matrix: " << rmat << endl;
	cout << "translation vector: " << tvec << endl;
	cout << "homography matrix: " << H << endl;
	cout << "inverted homography matrix: " << H.inv() << endl;

	return 1;
}
