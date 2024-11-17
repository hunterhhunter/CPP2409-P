#include "NewbieSpriteRenderer.h"
#include "NewbieGameObject.h"
#include "NewbieTransform.h"

namespace newbie
{
	SpriteRenderer::SpriteRenderer()
		: mImage(nullptr)
		, mWidth(0)
		, mHeight(0)
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
		// 위치정보 불러오기
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		// Gdiplus Graphics
		Gdiplus::Graphics graphics(hdc);
		graphics.DrawImage(mImage, Gdiplus::Rect(pos.x, pos.y, mWidth, mHeight));
	}

	void SpriteRenderer::ImageLoad(const std::wstring& path)
	{
		mImage = Gdiplus::Image::FromFile(path.c_str());
		mWidth = mImage->GetWidth();
		mHeight = mImage->GetHeight();
	}
}
