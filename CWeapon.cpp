#include "CWeapon.h"
#include "GameStart.h"

vector<string> split(const string& s, const string& seperator);

CWeapon::CWeapon(string weaponName) :weaponName(weaponName), function(FUNCTION2) {

	string imageSuffix = "";
	if (GameStart::RESOLUTION_TYPE == 0) {
		imageSuffix = "_1440";
	}
	else if (GameStart::RESOLUTION_TYPE == 1) {
		imageSuffix = "";
	}
	else if (GameStart::RESOLUTION_TYPE == 2) {
		imageSuffix = "_1080";
	}

	templateImage = imread("image/template/" + weaponName + imageSuffix + ".png", IMREAD_COLOR);
	maskImage = imread("image/mask/" + weaponName + imageSuffix + ".png", IMREAD_GRAYSCALE);


	//
	scope = GameStart::WEAPON_LIB.FindCScope(0);
};

void CWeapon::ComputeYOffset()
{
	attachmentEffect = 0;
	if (muzzle != nullptr) {
		attachmentEffect += muzzle->y_effect;
	}
	if (grip != nullptr) {
		attachmentEffect += grip->y_effect;
	}
	if (stock != nullptr) {
		attachmentEffect += stock->y_effect;
	}
}

void CWeapon::AssembleMuzzle(CMuzzle* muzzle)
{
	this->muzzle = muzzle;
	ComputeYOffset();
}

void CWeapon::AssembleGrip(CGrip* grip)
{
	this->grip = grip;
	ComputeYOffset();
}

void CWeapon::AssembleMagazine(CMagazine* magazine)
{
	this->magazine = magazine;
	if (this->magazine != nullptr) {
		this->shotCount = this->magazine->shots;
	}
}

void CWeapon::AssembleStock(CStock* stock)
{
	this->stock = stock;
	ComputeYOffset();
}

void CWeapon::AssembleScope(CScope* scope)
{
	this->scope = scope;
}

void CWeapon::Reload()
{
	currentShot = 0;
}

void CWeapon::LoadSetting()
{
	recoilBase = GetPrivateProfileIntA(weaponName.c_str(), "recoilBase", 400, INI_FILE_PATH.c_str());
	shotInterval = GetPrivateProfileIntA(weaponName.c_str(), "shotInterval", 400, INI_FILE_PATH.c_str());
	char buffer[1024] = {0};
	GetPrivateProfileStringA(weaponName.c_str(), "recoilRates", "", buffer,1024, INI_FILE_PATH.c_str());
	string ratesString = string(buffer);
	vector<string> rateVec = split(ratesString,",");
	if (rateVec.size() > 0) {
		recoilRates.clear();
		for (auto rs : rateVec) {
			recoilRates.push_back(atof(rs.c_str()));
		}
	}
	
	shotCount = GetPrivateProfileIntA(weaponName.c_str(), "shotCount", 400, INI_FILE_PATH.c_str());
	aimRecoil = GetPrivateProfileIntA(weaponName.c_str(), "aimRecoil", 400, INI_FILE_PATH.c_str());
	crouchEffect = GetPrivateProfileIntA(weaponName.c_str(), "crouchEffect", 400, INI_FILE_PATH.c_str());
	proneEffect = GetPrivateProfileIntA(weaponName.c_str(), "proneEffect", 400, INI_FILE_PATH.c_str());
}

void CWeapon::ChangeSetting()
{
	WritePrivateProfileStringA(weaponName.c_str(), "recoilBase", std::to_string(recoilBase).c_str(), INI_FILE_PATH.c_str());
	WritePrivateProfileStringA(weaponName.c_str(), "shotInterval", std::to_string(shotInterval).c_str(), INI_FILE_PATH.c_str());
	string strData;

	for (auto data : recoilRates)
	{
		strData += to_string(data) + ",";
	}
	WritePrivateProfileStringA(weaponName.c_str(), "recoilRates", strData.c_str(), INI_FILE_PATH.c_str());
	WritePrivateProfileStringA(weaponName.c_str(), "shotCount", std::to_string(shotCount).c_str(), INI_FILE_PATH.c_str());
	WritePrivateProfileStringA(weaponName.c_str(), "aimRecoil", std::to_string(aimRecoil).c_str(), INI_FILE_PATH.c_str());
	WritePrivateProfileStringA(weaponName.c_str(), "crouchEffect", std::to_string(crouchEffect).c_str(), INI_FILE_PATH.c_str());
	WritePrivateProfileStringA(weaponName.c_str(), "proneEffect", std::to_string(proneEffect).c_str(), INI_FILE_PATH.c_str());
}


void CWeapon::Crouch(int isCrouch)
{
	if (isCrouch) {
		
	}
	else {
		
	}
	
}

void CWeapon::Prone(int isProne)
{
	if (isProne) {
		
	}
	else {
		
	}
	
}



void CWeapon::ResetWeapon()
{
	muzzle = nullptr;
	grip = nullptr;
	stock = nullptr;
}

void CWeapon::HoldBreath(bool b)
{
	if (b) {
		if (!isHoldBreath) {
			isHoldBreath = true;

		}	
	}
	else {
		if (isHoldBreath) {

			isHoldBreath = false;
		}
		
	}
	
}

void CWeapon::SetRecoilRates(vector<double> rates) {
	recoilRates = rates;
}

void CWeapon::SetRecoilBase(double base) {
	recoilBase = base;
}

void CWeapon::SetShotInterval(int intval) {
	shotInterval = intval;
}


vector<string> split(const string& s, const string& seperator) {
	vector<string> result;
	typedef string::size_type string_size;
	string_size i = 0;

	while (i != s.size()) {
		//找到字符串中首个不等于分隔符的字母；
		int flag = 0;
		while (i != s.size() && flag == 0) {
			flag = 1;
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[i] == seperator[x]) {
					++i;
					flag = 0;
					break;
				}
		}

		//找到又一个分隔符，将两个分隔符之间的字符串取出；
		flag = 0;
		string_size j = i;
		while (j != s.size() && flag == 0) {
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[j] == seperator[x]) {
					flag = 1;
					break;
				}
			if (flag == 0)
				++j;
		}
		if (i != j) {
			result.push_back(s.substr(i, j - i));
			i = j;
		}
	}
	return result;
}
