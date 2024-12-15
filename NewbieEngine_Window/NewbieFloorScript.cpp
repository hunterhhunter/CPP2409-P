#include "NewbieFloorScript.h"

#include "NewbieCatScript.h"
#include "NewbieInput.h"
#include "NewbieTransform.h"
#include "NewbieTime.h"
#include "NewbieGameObject.h"
#include "NewbieAnimator.h"
#include "NewbieObject.h"
#include "NewbieRigidbody.h"

namespace newbie
{
	FloorScript::FloorScript()
	{
	}
	FloorScript::~FloorScript()
	{
	}
	void FloorScript::Initialize()
	{
	}
	void FloorScript::Update()
	{

	}
	void FloorScript::LateUpdate()
	{
	}
	void FloorScript::Render(HDC hdc)
	{
	}
	void FloorScript::OnCollisionEnter(Collider* other)
	{
		// 플레이어 정보 불러오기
		Rigidbody* playerRb = other->GetOwner()->GetComponent<Rigidbody>();
		Transform* playerTr = other->GetOwner()->GetComponent<Transform>();
		Collider* playerCol = other;
		
		// 바닥 정보 불러오기 
		Rigidbody* floorRb = this->GetOwner()->GetComponent<Rigidbody>();
		Transform* floorTr = this->GetOwner()->GetComponent<Transform>();
		Collider* floorCol = this->GetOwner()->GetComponent<Collider>();

		// 바닥과 플레이어의 y의 차(절댓값) 계산
		float yLen = fabs(playerTr->GetPosition().y - floorTr->GetPosition().y);
		// 영역(절댓값) 계산
		float yScale = fabs(playerCol->GetSize().y * 100 / 2.0f - floorCol->GetSize().y * 100 / 2.0f);


		if (yLen < yScale)
		{
			Vector2 playerPos = playerTr->GetPosition();
			// 영역 - 객체위치 - 1해서 지면 위에 뜨도록
			playerPos.y -= (yScale - yLen) - 1.0f;
			playerTr->SetPosition(playerPos);

		}
		playerRb->SetGround(true);

		//// 영역 충돌했을 때
		//if (len < scale)
		//{
		//	Vector2 playerPos = playerTr->GetPosition();
		//	// 영역 - 객체위치 - 1해서 지면 위에 뜨도록
		//	playerPos.y  -= scale - len - 1.0f;
		//	playerTr->SetPosition(playerPos);
		//}
		//playerRb->SetGround(true);
	}
	void FloorScript::OnCollisionStay(Collider* other)
	{
	}
	void FloorScript::OnCollisionExit(Collider* other)
	{
		Rigidbody* playerRb = other->GetOwner()->GetComponent<Rigidbody>();
		playerRb->SetGround(false);
	}
}
