# SR 기법 정리

### 1. 오브젝트 계층구조, 트랜스폼(쿼터니언)
<details>
  <summary>1. CGameObject의 멤버로 부모/자식포인터 소유</summary>

```cpp
vector<CGameObject*>  m_vecChildren;
CGameObject*          m_pParent;
```

- 부모/자식 포인터는 CGameObject가 소유
- 부모는 하나이고 자식은 여럿일 수 있으니 부모는 포인터, 자식은 벡터로 관리
</details>

<details>
  <summary>2. Transform의 로컬 / 월드 이원화</summary>

> 로컬 / 월드 이원화
```cpp
// Get_World()를 통해 이 둘을 만듬
m_matLocalWorld // 자신만의 S,R,T만 조립한 로컬 행렬
m_matWorld      // 로컬 x 부모 월드 = 최종 월드 행렬
```
> Get_World()

- Render하기 전에 m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_World())으로 월드행렬 설정.
```cpp
_matrix* CTransform::Get_World()
{
	if (!m_bDirty)
		return &m_matWorld;

	// 1. 월드 행렬의 초기화
	D3DXMatrixIdentity(&m_matLocalWorld);

	// 2. Right, Up, Look의 초기화
	for (int i = 0; i < INFO_POS; ++i) {
		memcpy(&m_vInfo[i], &m_matLocalWorld.m[i][0], sizeof(_vec3));
	}

	// 3. 크기 적용
	for (int i = 0; i < INFO_POS; ++i) {
		m_vInfo[i] *= *(((float*)&m_vScale) + i);
	}

	// 4. 회전 적용
	_matrix matRotQ;
	D3DXMatrixRotationQuaternion(&matRotQ, &m_localQuaternion);

	for (int i = 0; i < INFO_POS; ++i) {
		D3DXVec3TransformNormal(&m_vInfo[i], &m_vInfo[i], &matRotQ);
	}

	// 4-1. 빌보드 행렬 적용(Set_Billboard()함수를 호출하지 않은 경우 빌보드 행렬은 항등행렬)
	for (int i = 0; i < INFO_POS; ++i) {
		D3DXVec3TransformNormal(&m_vInfo[i], &m_vInfo[i], &m_matBillboard);
	}

	// 5. 월드 행렬 생성
	// 이동은 컴포넌트를 수정한 GameObject에서 직접 수행됨
	// 월드 행렬에 이동 상태를 옮길 뿐
	for (int i = 0; i < INFO_END; ++i) {
		memcpy(&m_matLocalWorld.m[i][0], m_vInfo[i], sizeof(_vec3));
	}

	CGameObject* pParent = m_pOwner->Get_Parent();
	m_matWorld = m_matLocalWorld;

	if (pParent == nullptr)
	{
		m_worldQuaternion = m_localQuaternion;
		m_bDirty = false;
		return &m_matWorld;
	}

	// 6. 부모의 월드 행렬/쿼터니언 가져오기
	_matrix* parentWorld = pParent->Get_Transform()->Get_World();
	_quaternion qParent = pParent->Get_Transform()->Get_WorldQuaternion();
	m_worldQuaternion = m_localQuaternion * qParent;

	// 7. 로컬 월드 행렬 * 부모의 월드 행렬 = 실제 월드 행렬 
	m_matWorld *= (*parentWorld);

	m_bDirty = false;
	return &m_matWorld;
}
```
</details>

<details>
  <summary>3. 회전은 행렬이 아니라 쿼터니언으로 따로 누적</summary>

- 행렬만 곱하면 로컬에서의 순수 회전을 다시 뽑아내기 어려움(스케일이 섞이기 때문).
- 회전을 별도로 관리
```cpp
m_LocalQuaternion  // Rotate(), MultipleQuaternoin()이 누적하는 로컬에서의 회전
m_WorldQuaternion  // 부모의 회전을 m_LocalQuaternion에 합성한 월드에서의 회전(Get_World를 먼저 호출하여 최신화를 보장)
```
</details>

<details>
  <summary>4. Dirty플래그의 전파</summary>

- Dirty 플래그가 없으면 최상위 부모까지 행렬계산을 하게됨
- 위치가 바뀌거나 값이 바뀔 때 (ex. Set_Pos, Set_Scale, Rotate, Move_Pos,Set_Billboard) 자신 + 모든 자식을 dirty로 표시
- 값이 필요할 때(ex. Get_World, Get_Info) dirty일 때만 부모 체인을 타고 실제 월드 행렬을 계산
```cpp
void CTransform::Set_Dirty()
{
    if (!m_bDirty) {          // 이미 dirty면 즉시 종료 -> 중복 전파 차단
        m_bDirty = true;
        for (auto& child : m_pOwner->Get_Children())
            child->Get_Transform()->Set_Dirty();   // 자식에게 전파
    }
}
```
</details>

<details>
  <summary>5. 자식으로 설정 Insert_Child</summary>

```cpp
//_iIndex    : m_vecChild내 삽입 위치. -1이면 맨 뒤
// bTune     : 붙인 뒤 로컬 변환을 재계산해서 자세를 보존할지(기본 true)
// bDefault  : 재계산시 m_defaultQuaternion까지 갱신할 지(기본 false)
void CGameObject::Insert_Child(CGameObject* _pGO, int _iIndex, bool bTune, bool bDefault)
{
    if (_pGO == nullptr)
        return;

    // 자신을 자식으로 할 수 없음
    if (this == _pGO)
        return;

    // 조상이 내 자식이 될수는 없음
    CGameObject* ancestor = m_pParent;
    while (ancestor != nullptr) {
        if (_pGO == ancestor)
            return;
        ancestor = ancestor->m_pParent;
    }

    // 같은 부모 내에서 순서 재조정인가(에디터용)
    const bool bSameParent = (_pGO->m_pParent == this);

    _matrix matLocal;
    // 같은 부모가 아니면 로컬 보존을 위해 저장
    if (!bSameParent)
        matLocal = *_pGO->Get_Transform()->Get_LocalWorld();

    int iOld = -1;
    // 같은 부모면 이전 위치를 기억
    if (bSameParent)
    {
        auto it = std::find(m_vecChildren.begin(), m_vecChildren.end(), _pGO);
        if (it != m_vecChildren.end())
            iOld = (int)(it - m_vecChildren.begin());
    }

    // 부모가 있으면 부모와 연결을 끊고, 최상위였으면 최상위 목록에서 삭제
    if (_pGO->m_pParent != nullptr)
    {
        auto& vecOld = _pGO->m_pParent->m_vecChildren;
        vecOld.erase(std::remove(vecOld.begin(), vecOld.end(), _pGO), vecOld.end());
        _pGO->m_pParent = nullptr;
    }
    else
        CManagement::GetInstance()->Detach_Root(_pGO);

    // iOld가 0보다 크거나 같다는 것은 같은 부모였다는 것
    // 삭제한 위치보다 넣으려는 위치가 더 뒤면 삭제 때문에 1칸 앞당겨짐
    if (iOld >= 0 && _iIndex > iOld)
        --_iIndex;

    // clmap
    if (_iIndex < 0 || _iIndex > (int)m_vecChildren.size())
        _iIndex = (int)m_vecChildren.size();

    // 삽입
    m_vecChildren.insert(m_vecChildren.begin() + _iIndex, _pGO);
    _pGO->m_pParent = this;

    // 아까 저장한 위치로 보존
    if (!bSameParent && bTune)
    {
        _matrix* pMatParent = Get_Transform()->Get_World();
        _matrix matInvParent;
        D3DXMatrixInverse(&matInvParent, 0, pMatParent);
        matLocal *= matInvParent;
        _pGO->Get_Transform()->Set_LocalWorld(&matLocal, bDefault);
    }
}
```
</details>













