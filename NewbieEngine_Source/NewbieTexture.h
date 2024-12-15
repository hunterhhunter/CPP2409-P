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

			static Texture* Create(const std::wstring& name, UINT width, UINT height);

			Texture();
			~Texture();

			virtual HRESULT Load(const std::wstring& path) override;

			UINT GetWidth() { return mWidth; }
			void SetWidth(UINT width) { mWidth = width; }
			UINT GetHeight() { return mHeight; }
			void SetHeight(UINT height) { mHeight = height; }
			HDC GetHdc() { return mHdc; }
			eTextureType GetTextureType() { return mType; }
			// png파일의 경우 이미지 로드
			Gdiplus::Image* GetImage() { return mImage; }
			bool IsAlpha() { return mbAlpha; }


		private:
			bool mbAlpha;
			eTextureType mType;		// 텍스쳐 타입
			Gdiplus::Image* mImage; // 이미지 포인터
			HBITMAP mBitmap;		// bmp 비트맵 핸들러
			HDC mHdc;				// 텍스쳐가 로드된 Device Context(창)

			UINT mWidth;
			UINT mHeight;
		};
	}
}

