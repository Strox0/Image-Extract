#include "Helper.h"
#include <filesystem>
#include <ShObjIdl_core.h>

std::string Helper::SelectFile(const char* filter)
{
	OPENFILENAMEA ofn;
	CHAR szFile[260] = { 0 };
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	if (GetOpenFileNameA(&ofn) == TRUE)
		return ofn.lpstrFile;

	return std::string();
}

std::wstring Helper::SelectFolder(bool has_to_exist)
{
	IFileDialog* fd;
	HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);

	if (FAILED(hr)) {
		CoUninitialize();
		return std::wstring();
	}

	static bool sec_init = false;
	if (!sec_init) {
		hr = CoInitializeSecurity
		(
			NULL,
			-1,
			NULL,
			NULL,
			RPC_C_AUTHN_LEVEL_PKT_PRIVACY,
			RPC_C_IMP_LEVEL_IMPERSONATE,
			NULL,
			0,
			NULL
		);
		sec_init = true;
	}

	if (FAILED(hr)) {
		CoUninitialize();
		return std::wstring();
	}

	hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&fd));

	if (FAILED(hr)) {
		CoUninitialize();
		return std::wstring();
	}

	FILEOPENDIALOGOPTIONS fos = FOS_PICKFOLDERS;
	if (has_to_exist)
		fos |= FOS_PATHMUSTEXIST;

	hr = fd->SetOptions(fos);

	if (FAILED(hr)) {
		fd->Release();
		CoUninitialize();
		return std::wstring();
	}

	hr = fd->Show(NULL);

	if (FAILED(hr)) {
		fd->Release();
		CoUninitialize();
		return std::wstring();
	}

	IShellItem* psi;
	hr = fd->GetResult(&psi);

	if (FAILED(hr)) {
		fd->Release();
		psi->Release();
		CoUninitialize();
		return std::wstring();
	}

	wchar_t* folder;
	hr = psi->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING, &folder);

	if (FAILED(hr)) {
		fd->Release();
		psi->Release();
		CoUninitialize();
		return std::wstring();
	}

	psi->Release();
	fd->Release();
	CoUninitialize();

	return folder;
}

bool Helper::CheckExtensions(const std::string& allowed, const std::string& path)
{
	size_t extension_pos = path.find_last_of('.');

	if (extension_pos != std::string::npos) 
	{
		std::string extension = path.substr(extension_pos);

		size_t find = allowed.find(extension);

		if (find != std::string::npos) 
			return true;
		else 
			return false;
	}

	return false;
}

void Helper::CheckSize(const cv::Mat& img, cv::Rect& cropping_rect)
{
	if (cropping_rect.x < 0)
		cropping_rect.x = 0;

	if (cropping_rect.y < 0)
		cropping_rect.y = 0;

	if ((cropping_rect.x + cropping_rect.width) > img.size().width)
		cropping_rect.width = img.size().width;

	if ((cropping_rect.y + cropping_rect.height) > img.size().height)
		cropping_rect.height = img.size().height;
}

std::string Helper::WStrToStr(const std::wstring& wstr)
{
	std::string str(wstr.length(), ' ');
	std::copy(wstr.begin(), wstr.end(), str.begin());

	return str;
}
