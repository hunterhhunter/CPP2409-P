#include "NewbieSpriteRenderer.h"
#include "NewbieGameObject.h"
#include "NewbieTransform.h"
#include "NewbieTexture.h"
#include "NewbieRenderer.h"

namespace newbie
{
	SpriteRenderer::SpriteRenderer()
		: Component(enums::eComponentType::SpriteRenderer)
		, mTexture(nullptr)
		, mSize(Vector2::One)
	{
	}

	SpriteRenderer::~SpriteRenderer()
	{
	}

	void SpriteRenderer::Initialize()
	{
	}

	void SpriteRenderer::Update()
	{
	}

	void SpriteRenderer::LateUpdate()
	{
	}

	void SpriteRenderer::Render(HDC hdc)
	{
		if (mTexture == nullptr)
			assert(false);
		
		// 위치정보 불러오기
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		pos = renderer::mainCamera->CaluatePosition(pos);

		// Bmp 파일 처리
		if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Bmp)
		{
			TransparentBlt(hdc, pos.x, pos.y,
				mTexture->GetWidth() * mSize.x, mTexture->GetHeight() * mSize.y,
				mTexture->GetHdc(), 0, 0,
				mTexture->GetWidth(), mTexture->GetHeight(), RGB(255, 0, 255));
		}
		// 이미지 파일인 경우
		else if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Png)
		{
			Gdiplus::Graphics graphics(hdc);
			graphics.DrawImage(mTexture->GetImage(),
				Gdiplus::Rect(
					pos.x, pos.y,
					mTexture->GetWidth() * mSize.x, 
					mTexture->GetHeight()*mSize.y
				)
			);
		}
	}
}
