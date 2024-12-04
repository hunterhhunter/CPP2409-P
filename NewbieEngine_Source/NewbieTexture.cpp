#include "NewbieTexture.h"
#include "NewbieApplication.h"

// 해당 전역변수가 존재함을 알리는 extern 키워드
extern newbie::Application application;

namespace newbie
{
	namespace graphics
	{
		Texture::Texture()
			:Resource(enums::eResourceType::Texture)
		{
		}

		Texture::~Texture()
		{
		}

		HRESULT Texture::Load(const std::wstring& path)
		{
			std::wstring ext = path.substr(path.find_last_of(L".") + 1);

			//bmp일 때
			if (ext == L"bmp")
			{
				mType = eTextureType::Bmp;
				// 비트맵 로드
				mBitmap = (HBITMAP)LoadImage(nullptr, path.c_str(), IMAGE_BITMAP,
					0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				// 비트맵 로드 실패시
				if (mBitmap == nullptr)
					return S_FALSE;

				
				BITMAP info = {};
				GetObject(mBitmap, sizeof(BITMAP), &info);

				mWidth = info.bmWidth;
				mHeight = info.bmHeight;

				// bmp 보여줄 창 가져오기 (현재 application의 메인 화면)
				HDC mainDC = application.GetHDC();
				mHdc = CreateCompatibleDC(mainDC);

				// 화면에 보여주기
				HBITMAP oldBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
				// 메모리 반환
				DeleteObject(oldBitmap);
			}
			else if (ext == L"png")
			{
				mType = eTextureType::Png;
				mImage = Gdiplus::Image::FromFile(path.c_str());

				if (mImage == nullptr)
					return S_FALSE;

				mWidth = mImage->GetWidth();
				mHeight = mImage->GetHeight();
			}

			return S_OK;
		}
	}
}