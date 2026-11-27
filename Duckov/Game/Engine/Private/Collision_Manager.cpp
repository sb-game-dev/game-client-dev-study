#include "Collision_Manager.h"
#include "Cube_Collider.h"
#include "GameObject.h"
void CCollision_Manager::Collision(shared_ptr<class CCollider> pDstCollider, shared_ptr<class CCollider> pSrcCollider)
{
	if (pDstCollider == nullptr || pSrcCollider == nullptr)
		return;

	COLLIDER_TYPE pDstType = pDstCollider->GetColliderType();
	COLLIDER_TYPE pSrcType = pSrcCollider->GetColliderType();

	if (pDstType == COLLIDER_TYPE::CUBE && pSrcType == COLLIDER_TYPE::CUBE)
	{
		auto pDstCubeCollider = dynamic_pointer_cast<CCube_Collider>(pDstCollider);
		auto pSrcCubeCollider = dynamic_pointer_cast<CCube_Collider>(pSrcCollider);

		if (nullptr == pDstCubeCollider || nullptr == pSrcCubeCollider)
			return;
		if (pDstCubeCollider->Get_Info().Intersects(pSrcCubeCollider->Get_Info()))
		{
			if (pDstCollider->GetIsTrigger() || pSrcCollider->GetIsTrigger())
			{
				pSrcCubeCollider->Get_Owner().lock()->TriggerEnter(pDstCollider);
				pDstCubeCollider->Get_Owner().lock()->TriggerEnter(pSrcCollider);
			}
			else
			{
				pSrcCubeCollider->Get_Owner().lock()->CollisionEnter(pDstCollider);
				pDstCubeCollider->Get_Owner().lock()->CollisionEnter(pSrcCollider);
			}
		}
	}
}

unique_ptr<CCollision_Manager> CCollision_Manager::Create()
{
	return unique_ptr<CCollision_Manager>(new CCollision_Manager());
}
