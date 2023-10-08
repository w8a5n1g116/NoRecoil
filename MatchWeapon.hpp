#pragma once
#include "framework.h"
#include "ScreenShot.hpp"
#include "CWeapon.h"
using namespace cv;
class MatchWeapon {
	

	tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
	Screenshot screenShot;
public:

	MatchWeapon() {
		api->Init(NULL, "eng");
	}


	Point Match(Mat img, Mat templ,Mat mask) {

		cvtColor(img, img, COLOR_RGBA2RGB);

		Mat result;
		int result_cols = img.cols - templ.cols + 1;
		int result_rows = img.rows - templ.rows + 1;
		result.create(result_rows, result_cols, CV_8UC3);
		matchTemplate(img, templ, result, TM_CCORR_NORMED,mask);
		normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());
		double minVal; double maxVal; Point minLoc; Point maxLoc;
		//Point matchLoc;

		minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
		//matchLoc = maxLoc;

		return maxLoc;
	}

	Point MatchNoMask(Mat img, Mat templ) {

		cvtColor(img, img, COLOR_RGBA2RGB);

		Mat result;
		int result_cols = img.cols - templ.cols + 1;
		int result_rows = img.rows - templ.rows + 1;
		result.create(result_rows, result_cols, CV_8UC3);
		matchTemplate(img, templ, result, TM_SQDIFF_NORMED);
		normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());
		double minVal; double maxVal; Point minLoc; Point maxLoc;
		//Point matchLoc;

		minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
		//matchLoc = maxLoc;

		return maxLoc;
	}

	std::vector<std::string> MatchWeaponName() {
		Mat screenshot = screenShot.getScreenshot();
		Mat img1 = screenshot(cv::Rect(1815, 120, 140, 50));
		Mat img2 = screenshot(cv::Rect(1815, 395, 140, 50));

		Mat grey;
		Mat binary;
		cvtColor(img1, grey, COLOR_RGBA2GRAY);
		threshold(grey, binary, 128, 255, THRESH_BINARY);
		std::string name1 = OCR(&grey);
		cvtColor(img2, grey, COLOR_RGBA2GRAY);
		threshold(grey, binary, 128, 255, THRESH_BINARY);
		std::string name2= OCR(&grey);



		return {name1, name2};
	}

	bool MatchWeaponNameImage(Mat src,Mat temp,Mat mask) {
		if (temp.empty() || mask.empty()) {
			return false;
		}
		Point ret = Match(src, temp, mask);
		if ( ret.x >= 40 && ret.x <= 46  && ret.y >= 0 && ret.y <=4) {
			return true;
		}
		else {
			return false;
		}
	}

	int MatchAttachmentImage(Mat src, Mat temp, Mat mask) {
		if (temp.empty() || mask.empty()) {
			return false;
		}
		Point ret = Match(src, temp,mask);
		if (ret.x >= 0 && ret.x <= 6 && ret.y >= 182 && ret.y <= 190) {
			return 1;
		}
		else if (ret.x >= 132 && ret.x <= 140 && ret.y >= 182 && ret.y <= 190) {
			return 2;
		}
		else if (ret.x >= 562 && ret.x <= 572 && ret.y >= 182 && ret.y <= 190) {
			return 3;
		}
		else if (ret.x >= 362 && ret.x <= 372 && ret.y >= 28 && ret.y <= 42) {
			return 4;
		}
		else {
			return 0;
		}
	}

	Mat GetScreenShot() {
		return screenShot.getScreenshot();
	}

	void SaveScreenShot(CWeapon* weapon1, CWeapon* weapon2) {
		Mat screenshot = screenShot.getScreenshot();
		Mat img = screenshot(Rect(1772, 125, 648, 250));
		/*Mat weapon1Name = screenshot(Rect(1815, 120, 140, 50));
		imwrite("image/template/" + weapon1->weaponName + ".png", weapon1Name);
		Mat weapon2Name = screenshot(Rect(1815, 395, 140, 50));
		imwrite("image/template/" + weapon2->weaponName + ".png", weapon2Name);*/

		Mat weapon1Scope = img(Rect(368, 32, 57, 35));
		imwrite("image/template/" + weapon1->cscope->name + ".png", weapon1Scope);
		Mat weapon1Muzzle = img(Rect(3, 181, 60, 60));
		imwrite("image/template/" + weapon1->muzzle->name + ".png", weapon1Muzzle);
		Mat weapon1Grip = img(Rect(138, 181, 60, 60));
		imwrite("image/template/" + weapon1->grip->name + ".png", weapon1Grip);
		Mat weapon1Stock = img(Rect(568, 181, 60, 60));
		imwrite("image/template/" + weapon1->stock->name + ".png", weapon1Stock);
	}

	void SaveMask(string name) {
		Mat grey = imread("image/template/" + name + ".png", IMREAD_GRAYSCALE);
		Mat binary;
		threshold(grey, binary, 80, 255, THRESH_BINARY_INV);
		imwrite("image/mask/" + name + ".png", binary);
	}

	std::string OCR(Mat* im) {
		std::string ret;

		api->SetImage(im->data, im->cols, im->rows, 1, im->step);
		ret = api->GetUTF8Text();
		//pixDestroy(&image);

		return ret;
	}
private:
};