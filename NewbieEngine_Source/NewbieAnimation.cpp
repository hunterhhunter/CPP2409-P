#include "NewbieAnimation.h"
#include "NewbieTime.h"
#include "NewbieTransform.h"
#include "NewbieGameObject.h"
#include "NewbieAnimator.h"
#include "NewbieRenderer.h"
#include "NewbieCamera.h"
#

namespace newbie
{
	Animation::Animation()
		: Resource(enums::eResourceType::Animation)
		, mAnimator(nullptr)
		, mTexture(nullptr)
		, mAnimationSheet{}
		, mIndex(-1)
		, mTime(0.0f)
		, mbComplete(false)
	{

	}

	Animation::~Animation()
	{

	}

	HRESULT Animation::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	void Animation::Update()
	{
		// if animation finished, return
		if (mbComplete)
			return;

		mTime += Time::DeltaTime();
		
		// When mTime is bigger then duration of mAnimationSheet[mIndex], 
		// reset Time
		if (mAnimationSheet[mIndex].duration < mTime)
		{
			mTime = 0.0f;
			// if mIndex overflow, finish Animation
			if (mIndex < mAnimationSheet.size() - 1)
				mIndex++;
			else
				mbComplete = true;
		}
	}

	void Animation::Render(HDC hdc)
	{
		// 알파블렌드를 쓰는 조건: 해당 이미지 알파채널이 있어야함
		if (mTexture == nullptr)
			return;

		GameObject* gameObj = mAnimator->GetOwner();
		Transform* tr = gameObj->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		float rot = tr->GetRotation();
		Vector2 scale = tr->GetScale();

		if (renderer::mainCamera)
			pos = renderer::mainCamera->CaluatePosition(pos);

		Sprite sprite = mAnimationSheet[mIndex];
		graphics::Texture::eTextureType type = mTexture->GetTextureType();

		if (type == graphics::Texture::eTextureType::Bmp)
		{
			//BLENDFUNCTION func = {};
			//func.BlendOp = AC_SRC_OVER;
			//func.BlendFlags = 0;
			//func.AlphaFormat = AC_SRC_ALPHA;
			//func.SourceConstantAlpha = 225; // 0(transparent) ~ 255(Opaque)

			HDC imgHdc = mTexture->GetHdc();

			/*AlphaBlend(hdc
				, pos.x - (sprite.size.x / 2.0f)
				, pos.y - (sprite.size.y / 2.0f)
				, sprite.size.x * scale.x
				, sprite.size.y * scale.y
				, imgHdc
				, sprite.leftTop.x
				, sprite.leftTop.y
				, sprite.size.x
				, sprite.size.y
				, func);*/

			// 알파 채널이 없을 때 마지막 인자의 색과 동일한 색을 투명처리
			TransparentBlt(hdc
				, pos.x - (sprite.size.x / 2.0f)
				, pos.y - (sprite.size.y / 2.0f)
				, sprite.size.x * scale.x
				, sprite.size.y * scale.y
				, imgHdc
				, sprite.leftTop.x
				, sprite.leftTop.y
				, sprite.size.x
				, sprite.size.y
				, RGB(255, 0, 255));
		}
		else if (type == graphics::Texture::eTextureType::Png)
		{
			// make Pexel Color of what i want transparent
			Gdiplus::ImageAttributes imgAtt = {};

			// Color range of Pexel to be made transparent
			imgAtt.SetColorKey(Gdiplus::Color(230, 230, 230), Gdiplus::Color(255, 255, 255));

			Gdiplus::Graphics graphics(hdc);
			
			graphics.TranslateTransform(pos.x, pos.y);
			graphics.RotateTransform(rot);
			graphics.TranslateTransform(-pos.x, -pos.y);

			graphics.DrawImage(mTexture->GetImage()
				, Gdiplus::Rect
				(
					  pos.x - (sprite.size.x / 2.0f)
					, pos.y - (sprite.size.y / 2.0f)
					, sprite.size.x * scale.x
					, sprite.size.y * scale.y
				)
				, sprite.leftTop.x
				, sprite.leftTop.y
				, sprite.size.x
				, sprite.size.y
				, Gdiplus::UnitPixel
				, &imgAtt
			);
		}
	}

	void Animation::CreateAnimation(const std::wstring& name, 
		graphics::Texture* spriteSheet,
		Vector2 leftTop, Vector2 size, Vector2 offset,
		UINT spriteLegth, float duration)
	{
		mTexture = spriteSheet;

		for (size_t i = 0; i < spriteLegth; i++)
		{
			Sprite sprite = {};
			sprite.leftTop.x = leftTop.x + (size.x * i);
			sprite.leftTop.y = leftTop.y;
			sprite.size = size;
			sprite.offset = offset;
			sprite.duration = duration;

			mAnimationSheet.push_back(sprite);
		}
	}

	void Animation::Reset()
	{
		mTime = 0.0f;
		mIndex = 0;
		mbComplete = false;
	}
}