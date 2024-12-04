#pragma once
#include "NewbieResource.h"

namespace newbie
{
	namespace graphics
	{
		class Texture : public Resource
		{
		public:
			enum class eTextureType
			{
				Bmp,
				Png,
				None,
			};

			Texture();
			~Texture();

			virtual HRESULT Load(const std::wstring& path) override;

			UINT GetWidth() { return mWidth; }
			UINT GetHeight() { return mHeight; }
			HDC GetHdc() { return mHdc; }
			eTextureType GetTextureType() { return mType; }
			// png파일의 경우 이미지 로드
			Gdiplus::Image* GetImage() { return mImage; }


		private:
			eTextureType mType;		// 텍스쳐 타입
			Gdiplus::Image* mImage; // 이미지 포인터
			HBITMAP mBitmap;		// bmp 비트맵 핸들러
			HDC mHdc;				// 텍스쳐가 로드된 Device Context(창)

			UINT mWidth;
			UINT mHeight;
		};
	}
}

