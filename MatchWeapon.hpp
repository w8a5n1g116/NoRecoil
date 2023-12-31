#pragma once
#include "framework.h"
#include "ScreenShot.hpp"
#include "CWeapon.h"
using namespace cv;
class MatchWeapon {
	

	//tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
	Screenshot screenShot;
public:

	MatchWeapon() {
		//api->Init(NULL, "eng");
	}


	Point Match(Mat* img, Mat* templ,Mat* mask) {

		Mat result;
		int result_cols = img->cols - templ->cols + 1;
		int result_rows = img->rows - templ->rows + 1;
		result.create(result_rows, result_cols, CV_8UC3);
		matchTemplate(*img, *templ, result, TM_CCORR_NORMED,*mask);
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


	bool MatchWeaponNameImage(Mat* src,Mat* temp,Mat* mask,Rect weaponNameRect) {
		if (temp->empty() || mask->empty()) {
			return false;
		}
		Point ret = Match(src, temp, mask);
		if ( ret.x >= weaponNameRect.x && ret.x <= weaponNameRect.y && ret.y >= weaponNameRect.width && ret.y <= weaponNameRect.height) {
			return true;
		}
		else {
			return false;
		}
	}

	int MatchAttachmentImage(Mat* src, Mat* temp, Mat* mask,Rect muzzleRect,Rect gripRect,Rect stockRect,Rect scopeRect) {
		if (temp->empty() || mask->empty()) {
			return false;
		}
		Point ret = Match(src, temp,mask);
		if (ret.x >= muzzleRect.x && ret.x <= muzzleRect.y && ret.y >= muzzleRect.width && ret.y <= muzzleRect.height) {
			return 1;
		}
		else if (ret.x >= gripRect.x && ret.x <= gripRect.y && ret.y >= gripRect.width && ret.y <= gripRect.height) {
			return 2;
		}
		else if (ret.x >= stockRect.x && ret.x <= stockRect.y && ret.y >= stockRect.width && ret.y <= stockRect.height) {
			return 3;
		}
		else if (ret.x >= scopeRect.x && ret.x <= scopeRect.y && ret.y >= scopeRect.width && ret.y <= scopeRect.height) {
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
		Mat img = screenshot(Rect(1769, 117,657 , 255));
		/*Mat weapon1Name = img(Rect(52, 3, 140, 46));
		imwrite("image/template/" + weapon1->weaponName + ".png", weapon1Name);*/

		/*Mat weapon1Scope = img(Rect(369, 38, 59, 35));
		imwrite("image/template/" + weapon1->cscope->name + "_1440.png", weapon1Scope);
		Mat weapon1Muzzle = img(Rect(6 ,189, 59, 59));
		imwrite("image/template/" + weapon1->muzzle->name + "_1440.png", weapon1Muzzle);
		Mat weapon1Grip = img(Rect(142 ,189 ,59 ,59));
		imwrite("image/template/" + weapon1->grip->name + "_1440.png", weapon1Grip);
		Mat weapon1Stock = img(Rect(572, 189 ,59 ,59));
		imwrite("image/template/" + weapon1->stock->name + "_1440.png", weapon1Stock);*/
	}

	void SaveMask(string name) {
		Mat grey = imread("image/template/" + name + "_1440.png", IMREAD_GRAYSCALE);
		Mat binary;
		threshold(grey, binary, 80, 255, THRESH_BINARY_INV);
		imwrite("image/mask/" + name + "_1440.png", binary);
	}

	std::string OCR(Mat* im) {
		//std::string ret;

		//api->SetImage(im->data, im->cols, im->rows, 1, im->step);
		//ret = api->GetUTF8Text();
		////pixDestroy(&image);

		return "ret";
	}
private:
};