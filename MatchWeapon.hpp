#pragma once
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include "framework.h"
#include "ScreenShot.hpp"
using namespace cv;
class MatchWeapon {
	
	Mat Mk47_Mutant;
	Mat AKM;
	Mat Groza;
	Mat Beryl_M762;
	Mat ACE32;
	Mat M16A4;
	Mat QBZ;
	Mat SCAR_L;
	Mat AUG;
	Mat G36C;
	Mat K2;
	Mat M416;
	Mat FAMAS;
	Mat DP_28;
	Mat M249;
	Mat Mk14;
	Mat SLR;
	Mat SKS;
	Mat Mk12;
	Mat Mini14;
	Mat QBU;
	Mat VSS;
	Mat Lynx_AMR;
	Mat AWM;
	Mat Kar98k;
	Mat Mosin_Nagant;
	Mat M24;
	Mat Win94;
	Mat UMP45;
	Mat Tommy_Gun;
	Mat PP_19_Bizon;
	Mat P90;
	Mat MP5K;
	Mat MP9;
	Mat Vector;
	Mat Micro_UZI;
	Mat DBS;
	Mat S1897;
	Mat S686;
	Mat S12K;
	Mat Sawed_Off;
	Mat O1R452;
	Mat R1895;
	Mat Deagle;
	Mat P1911;
	Mat P92;
	Mat P18C;
	Mat Skorpion;
	Mat MG3_660_RPM;
	Mat MG3_990_RPM;

	tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
	Screenshot screenShot;
public:

	MatchWeapon() {
		api->Init(NULL, "eng");
	}


	int Match(Mat img, Mat templ) {
		Mat result;
		Mat img_display;
		img.copyTo(img_display);
		int result_cols = img.cols - templ.cols + 1;
		int result_rows = img.rows - templ.rows + 1;
		result.create(result_rows, result_cols, CV_32FC1);
		matchTemplate(img, templ, result, TM_CCOEFF_NORMED);
		normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());
		double minVal; double maxVal; Point minLoc; Point maxLoc;
		//Point matchLoc;

		minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
		//matchLoc = maxLoc;

		return maxVal;
	}

	std::string MatchFirstWeapon() {
		Mat img = screenShot.getScreenshot(1815, 120,285,50);
		Mat grey;
		cvtColor(img, grey, COLOR_RGBA2GRAY);
		return OCR(&grey);
	}

	std::string MatchSecondWeapon() {
		Mat img = screenShot.getScreenshot(1815, 395, 285, 50);
		Mat grey;
		cvtColor(img, grey, COLOR_RGBA2GRAY);
		return OCR(&grey);
	}

	/*PIX* cvtMat2PIX(Mat imgGray)
	{
		int cols = imgGray.cols;
		int rows = imgGray.rows;

		PIX* pixS = pixCreate(cols, rows, 8);

		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				pixSetPixel(pixS, j, i, (l_uint32)imgGray.at<uchar>(i, j));
		return pixS;
	}*/

	std::string OCR(Mat* im) {
		std::string ret;

		api->SetImage(im->data, im->cols, im->rows, 1, im->step);
		ret = api->GetUTF8Text();
		//pixDestroy(&image);

		return ret;
	}
private:
};