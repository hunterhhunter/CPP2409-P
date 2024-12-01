#include "NewbieTexture.h"
#include "NewbieApplication.h"
#include "NewbieResources.h"

// 해당 전역변수가 존재함을 알리는 extern 키워드
extern newbie::Application application;

namespace newbie
{
	namespace graphics
	{
		Texture* Texture::Create(const std::wstring& name, UINT width, UINT height)
		{
			Texture* image = Resources::Find<Texture>(name);
			if (image)
				return image;

			image = new Texture();
			image->SetName(name);
			image->SetHeight(height);
			image->SetWidth(width);

			HDC hdc = application.GetHdc();
			HWND hwnd = application.GetHwnd();

			image->mBitmap = CreateCompatibleBitmap(hdc, width, height);
			image->mHdc = CreateCompatibleDC(hdc);

			HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
			HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);
			Rectangle(image->mHdc, -1, -1, image->GetWidth() + 1, image->GetHeight() + 1);
			SelectObject(hdc, oldBrush);

			HBITMAP oldBitmap = (HBITMAP)SelectObject(image->mHdc, image->mBitmap);
			DeleteObject(oldBitmap);

			Resources::Insert(name + L"Image", image);

			return image;
		}

		Texture::Texture()
			:Resource(enums::eResourceType::Texture)
			, mbAlpha(false)
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

				if (info.bmBitsPixel == 32)
					mbAlpha = true;
				else if (info.bmBitsPixel == 24)
					mbAlpha = false;

				// bmp 보여줄 창 가져오기 (현재 application의 메인 화면)
				HDC mainDC = application.GetHdc();
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