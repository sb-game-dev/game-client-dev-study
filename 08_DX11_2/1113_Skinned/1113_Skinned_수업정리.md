# 1113_Skinned 총정리 — 스키닝 파이프라인 완성 (뼈 행렬 → GPU → 정점)

> 1110_Anim1 → 1113_Skinned 비교. Engine과 Client가 모두 바뀌었다.

| 구분 | 파일 |
|---|---|
| Engine 수정 | `Bone.h/.cpp`, `Mesh.h/.cpp`, `Model.h/.cpp` |
| Client 수정 | `VS_Mesh.hlsl`, `Loader.cpp`, `Monster.cpp` |
| SDK 복사 | `EngineSDK/Inc/Bone.h`(처음 생김), `Engine_Enum.h`, `Engine_Struct.h`, `Mesh.h`, `Model.h` |

1110에서 뼈와 정점 데이터를 **준비**했다면, 이번 수업은 그 데이터를 **GPU까지 보내서 정점을 뼈에 붙여 그리는** 단계다.
- 정점을 뼈 기준으로 옮기는 **OffsetMatrix**를 저장한다.
- 뼈의 **누적 행렬(Combined)** 을 매 프레임 계산한다.
- `Offset × Combined`를 상수버퍼(b2)로 보내고, 정점 셰이더가 가중치로 섞어서 곱한다.
- 키프레임 재생(`Play_Animation`의 1단계)은 아직 비어 있다. 그래서 **모델이 기본 자세로 정상 출력되면 성공**이다.

> `VTXANIMMESH`, `MODEL` enum은 1110의 `Engine/Public`에 이미 있었다. 1113에서는 빌드할 때 SDK로 복사만 됐다.

---

## 1. 오늘의 공식

```
최종 정점 = 원본 정점 × OffsetMatrix × CombinedMatrix × World × View × Proj
            └─ 바인드 포즈 → 뼈 로컬 ─┘ └─ 뼈 로컬 → 현재 포즈 ─┘
```

| 행렬 | 의미 | 언제 구하나 | 어디에 |
|---|---|---|---|
| OffsetMatrix | 바인드 포즈 뼈 행렬의 **역행렬**. 정점을 뼈 기준 좌표로 옮김 | 로드할 때 1회 (고정) | `CMesh::m_OffsetMatrices` |
| TransformationMatrix | 부모 기준 로컬 행렬. **애니메이션이 바꾸는 값** | 매 프레임 (다음 수업) | `CBone` |
| CombinedMatrix | 루트부터 나까지 누적한 행렬 | 매 프레임 | `CBone` |
| BoneMatrix | `Offset × Combined`. 정점에 바로 곱하는 최종 행렬 | 메시 렌더 직전 | `CMesh::m_BoneMatrices` → b2 |

### 전체 흐름
```
[로드 시]
Ready_Bones  → aiNode 트리를 일렬로 펼침 (부모가 항상 자식보다 앞)
Ready_Meshes → 메시마다: (전체 뼈 번호, OffsetMatrix) 목록
                        + 정점마다 (메시 로컬 뼈 번호, 가중치) × 4

[매 프레임 Update]
Play_Animation → ① 로컬 행렬 갱신 (비어 있음)
               → ② Combined = Transformation × 부모 Combined

[매 메시 Render]
Bind_BoneMatrices → BoneMatrices[i] = Offset[i] × Combined[m_BoneIndices[i]] → b2
VS main_anim      → 4개 뼈 행렬을 가중치로 섞음 → W·V·P
```

---

## 2. 수업 진행 순서대로 코드 따라가기

### STEP 1. OffsetMatrix 저장 ★

**왜 필요한가**: 정점은 바인드 포즈(T포즈) 기준 좌표로 저장돼 있다. 뼈가 움직일 때 정점이 따라가려면 먼저 **뼈 기준 좌표**로 바꿔야 한다.

예시:
- 바인드 포즈에서 팔꿈치 뼈가 (0, 10, 0), 팔뚝 정점이 (1, 10, 0)에 있다.
- 팔꿈치 기준으로 바꾸면 (1, 0, 0), 즉 "팔꿈치에서 오른쪽으로 1"이다. ← **Offset이 하는 일**
- 팔꿈치가 90도 돌면 이 (1, 0, 0)에 팔꿈치의 **현재** 행렬을 곱한다. ← **Combined가 하는 일**

`Mesh.h`
```cpp
vector<uint32_t>    m_BoneIndices;     // (1110) 이 메시의 i번째 뼈 = 모델 전체 뼈 중 몇 번
vector<float4x4_t>  m_OffsetMatrices;  // (추가) 이 메시의 i번째 뼈의 오프셋
```
두 벡터는 **같은 i로 짝지어** 쓴다.

`Mesh.cpp` — `Ready_Meshes_For_Anim`의 뼈 루프
```cpp
int32_t iBoneIndex = pModel->Get_BoneIndex(pAIMesh->mBones[i]->mName.C_Str());
if (-1 == iBoneIndex)
    return E_FAIL;

float4x4_t OffsetMatrix = {};
memcpy(&OffsetMatrix, &pAIMesh->mBones[i]->mOffsetMatrix, sizeof(float4x4_t));
XMStoreFloat4x4(&OffsetMatrix, XMMatrixTranspose(XMLoadFloat4x4(&OffsetMatrix)));

m_OffsetMatrices.push_back(OffsetMatrix);
m_BoneIndices.push_back(iBoneIndex);
```
- `aiBone`은 계층 정보 없이 이름만 있다. 그래서 **이름으로** 모델의 `CBone`을 찾는다.
- `aiMatrix4x4`와 `XMFLOAT4X4`는 float 16개로 메모리 배치가 같아서 memcpy로 복사한다.
- **전치하는 이유**: Assimp는 열벡터 규칙(`M × v`, 이동값이 4번째 열)이고 DirectX는 행벡터 규칙(`v × M`, 이동값이 4번째 행)이다. → **Assimp 행렬은 들여올 때 항상 전치한다.** (`CBone::Initialize`의 `mTransformation`도 같은 이유)

---

### STEP 2. 정점에 가중치 채우기

Assimp는 데이터를 **뼈 기준**으로 준다(`aiBone → mWeights[j] = {정점 번호, 가중치}`). 우리는 **정점 기준**이 필요하니 뒤집어서 넣는다.

```cpp
for (uint32_t j = 0; j < pAIMesh->mBones[i]->mNumWeights; ++j)
{
    if (0.f == pVertices[...mVertexId].vBlendWeight.x)
    {
        pVertices[...].vBlendIndex.x  = i;
        pVertices[...].vBlendWeight.x = pAIMesh->mBones[i]->mWeights[j].mWeight;
    }
    else if (0.f == ...vBlendWeight.y) { .y 에 i, weight }
    else if (0.f == ...vBlendWeight.z) { .z 에 i, weight }
    else                               { .w 에 i, weight }
}
```
- 가중치가 0인 첫 칸(x → y → z → w)을 "빈 칸"으로 보고 채운다.
- **1110의 버그**: 인덱스만 넣고 가중치를 안 넣었다. 그래서 weight.x가 계속 0이라 매번 x칸만 덮어썼다.
- **넣는 값은 `iBoneIndex`가 아니라 `i`(메시 로컬 번호)다.** 셰이더는 메시별 행렬 배열을 이 번호로 찾아간다.

```
정점 vBlendIndex = (3, 7, 0, 0)                     ← 메시 로컬 번호
 → m_BoneIndices[3] = 42, m_BoneIndices[7] = 45     ← 모델 전체 번호
 → m_Bones[42], m_Bones[45]
```

---

### STEP 3. 뼈가 없는 메시 처리

애니메이션 모델 안에도 스키닝되지 않은 메시(무기, 장식 등)가 있다. 이런 메시는 `mNumBones == 0`이라 그대로 두면 뼈 행렬이 없다. 수업에서는 **메시와 같은 이름의 노드**에 통째로 붙였다.

```cpp
char_t m_szName[MAX_PATH] = {};
strcpy_s(m_szName, pAIMesh->mName.C_Str());     // Initialize_Prototype 시작에서
...
if (0 == m_iNumBones)
{
    m_iNumBones = 1;
    m_BoneIndices.push_back(pModel->Get_BoneIndex(m_szName));

    float4x4_t OffsetMatrix = {};
    XMStoreFloat4x4(&OffsetMatrix, XMMatrixIdentity());
    m_OffsetMatrices.push_back(OffsetMatrix);
}
```
- "가짜 뼈 1개" = 같은 이름의 노드. 오프셋은 단위행렬이다(정점이 이미 그 노드 기준이니까).
- 이 메시의 정점은 인덱스·가중치가 전부 0이다. 셰이더의 `fWeightW = 1 - (0+0+0) = 1` 때문에 **0번 행렬이 100% 적용**된다. 셰이더를 고치지 않아도 자동으로 처리되는 구조다.
- ⚠️ **"메시 이름 = 노드 이름"이 항상 맞지는 않는다.** (5장 트러블슈팅 참고)

---

### STEP 4. 뼈의 누적 행렬 (CombinedTransformationMatrix) ★

```
Combined(손) = T(손) × T(아래팔) × T(위팔) × ... × T(루트)
            = T(손) × Combined(아래팔)
```
행벡터 규칙이라 **내 것을 왼쪽, 부모 것을 오른쪽**에 곱한다.

`Bone.h`
```cpp
const float4x4_t* Get_CombinedTransformationMatrix() const { return &m_CombinedTransformationMatrix; }
void Update_CombinedTransformationMatrix(const vector<shared_ptr<CBone>>& Bones, fmatrix_t PreTransformMatrix);
```
- 부모를 포인터가 아니라 **인덱스**(`m_iParentIndex`)로 기억하기 때문에 전체 뼈 벡터를 받는다.

`Bone.cpp`
```cpp
if (-1 == m_iParentIndex)          // 루트
{
    Combined = Transformation * PreTransformMatrix;
    return;
}
Combined = Transformation * Bones[m_iParentIndex]->Combined;
```
- **루트에 PreTransform을 곱하는 이유**: NONANIM은 PreTransform을 정점에 구워 넣었다. ANIM은 OffsetMatrix가 원본 정점 기준이라 정점을 건드리면 안 된다. 대신 루트에 곱하면 모든 자식 뼈와 정점이 따라 돈다.

**전제조건**: 부모의 Combined가 먼저 계산돼 있어야 한다. `Ready_Bones`가 전위 순회(나 먼저 push_back → 자식 재귀)라서 `m_Bones`에서 **부모가 항상 자식보다 앞**에 있다. 그래서 앞에서부터 돌기만 하면 된다.

---

### STEP 5. CModel — PreTransform 저장 + `Play_Animation` 뼈대

`Model.h`
```cpp
float4x4_t m_PreTransformMatrix = {};
void Play_Animation(f32_t fTimeDelta);
```
`Model.cpp`
```cpp
XMStoreFloat4x4(&m_PreTransformMatrix, PreTransformMatrix);   // Initialize_Prototype에서

void CModel::Play_Animation(f32_t fTimeDelta)
{
    /* 1. 뼈들의 TransformationMatrix를 현재 애니메이션에 맞게 셋팅한다. */  // ← 다음 수업

    /* 2. TransformationMatrix × 부모 Combined = 나의 Combined */
    for (auto& pBone : m_Bones)
        pBone->Update_CombinedTransformationMatrix(m_Bones, XMLoadFloat4x4(&m_PreTransformMatrix));
}
```
- `fmatrix_t`(XMMATRIX)는 SIMD 타입이라 멤버로 들고 있기 부적합하다(정렬 문제). `float4x4_t`로 Store해서 보관한다.
- **애니메이션의 본질은 1번**이다. 키프레임 보간으로 각 뼈의 **로컬 행렬만** 바꾼다. 2번은 항상 똑같이 실행된다.
- 지금은 1번이 비어 있어서 로컬 행렬이 FBX 기본값이다. → **기본 자세로 서 있으면 정상**이다.

---

### STEP 6. 최종 행렬 계산 + 상수버퍼로 GPU 전달

`Mesh.h`
```cpp
#include "ConstantBuffer.h"
float4x4_t                  m_BoneMatrices[512] = {};
shared_ptr<CConstantBuffer> m_pCB = { nullptr };
HRESULT Bind_BoneMatrices(vector<shared_ptr<class CBone>>& Bones, uint32_t iSlot);
```
- 512 × 64B = 32KB. D3D11 상수버퍼 한도는 64KB(float4 4096개) → 최대 1024개까지 가능하다.
- 셰이더의 `g_BoneMatrices[512]`와 크기가 **정확히 같아야** 한다.

`Mesh.cpp`
```cpp
// Initialize_Prototype 끝
m_pCB = CConstantBuffer::Create(m_pDevice, m_pContext, m_BoneMatrices, sizeof(float4x4_t) * 512);

HRESULT CMesh::Bind_BoneMatrices(vector<shared_ptr<CBone>>& Bones, uint32_t iSlot)
{
    for (uint32_t i = 0; i < m_iNumBones; i++)
        m_BoneMatrices[i] = m_OffsetMatrices[i] * Bones[m_BoneIndices[i]]->Combined;

    return m_pCB->Bind_Vertex_ShaderResource(iSlot, m_BoneMatrices);
}
```
- 메시 로컬 번호 i로 배열을 채운다. 정점의 BlendIndex와 같은 번호 체계다.
- `Bind_Vertex_ShaderResource` 내부: `Map(WRITE_DISCARD)` → 32KB memcpy → `Unmap` → `VSSetConstantBuffers(iSlot)`.

`Model.cpp`
```cpp
HRESULT CModel::Bind_BoneMatrices(uint32_t iMeshIndex, uint32_t iSlot)
{
    return m_Meshes[iMeshIndex]->Bind_BoneMatrices(m_Bones, iSlot);
}
```
- 클라이언트는 모델만 안다. 모델이 메시에 뼈 목록을 넘겨 중계한다(`Bind_Material`과 같은 패턴).

---

### STEP 7. 정점 셰이더 `main_anim`

```hlsl
cbuffer BoneMatrices : register(b2)
{
    row_major matrix g_BoneMatrices[512];
};
```
- 슬롯: **b0 = 월드, b1 = 카메라, b2 = 뼈**.
- `row_major`: C++ 행렬을 전치 없이 memcpy해서 보내니까 행 우선으로 읽게 한다.

```hlsl
struct VS_IN_ANIM
{
    float3 vPosition    : POSITION;
    float3 vNormal      : NORMAL;
    float3 vTangent     : TANGENT;
    float3 vBinormal    : BINORMAL;
    float2 vTexcoord    : TEXCOORD0;
    uint4  vBlendIndex  : BLENDINDEX;    // R32G32B32A32_UINT → 반드시 uint4
    float4 vBlendWeight : BLENDWEIGHT;
};
```

```hlsl
float fWeightW = 1.f - (In.vBlendWeight.x + In.vBlendWeight.y + In.vBlendWeight.z);

float4x4 BoneMatrix =
      g_BoneMatrices[In.vBlendIndex.x] * In.vBlendWeight.x
    + g_BoneMatrices[In.vBlendIndex.y] * In.vBlendWeight.y
    + g_BoneMatrices[In.vBlendIndex.z] * In.vBlendWeight.z
    + g_BoneMatrices[In.vBlendIndex.w] * fWeightW;

float4 vPosition = mul(float4(In.vPosition, 1.f), BoneMatrix);   // w=1: 이동 포함
float4 vNormal   = mul(float4(In.vNormal,   0.f), BoneMatrix);   // w=0: 회전만

vPosition = mul(vPosition, g_WorldMatrix);
vPosition = mul(vPosition, g_ViewMatrix);
vPosition = mul(vPosition, g_ProjMatrix);
```
- **선형 블렌드 스키닝(LBS)**: 뼈 4개 행렬을 가중치만큼 섞어서 정점 전용 행렬을 만든다.
- w 가중치를 `1 - 나머지 합`으로 계산 → 합이 항상 1이 되도록 보정하고, 뼈 없는 메시(가중치 전부 0)도 자동 처리된다.
- 출력은 기존 `VS_OUT`을 그대로 써서 픽셀 셰이더를 공유한다.
- ⚠️ 수업 코드의 `Out.vWorldPos = mul(float4(In.vPosition,1), g_WorldMatrix)`는 **스키닝 전** 위치다. 포즈가 바뀌면 조명이 어긋난다. 탄젠트·바이노멀도 아직 스키닝되지 않는다.

---

### STEP 8. 클라이언트 연결

`Loader.cpp`
```cpp
CModel::Create(..., MODEL::ANIM,    ".../Fiona/Fiona.fbx", PreTransformMatrix)
CModel::Create(..., MODEL::NONANIM, ".../ForkLift/ForkLift.fbx", PreTransformMatrix)

/* For.Prototype_Component_VS_AnimMesh */
CVertexShader::Create(..., TEXT("../Bin/ShaderFiles/VS_Mesh.hlsl"),
    VTXANIMMESH::ElementDesc, VTXANIMMESH::iNumElments, "main_anim")
```
- 같은 hlsl 파일을 진입점만 바꿔 한 번 더 컴파일한다. InputLayout은 `VTXANIMMESH` 기준(stride 88).

`Monster.cpp`
```cpp
void CMonster::Update(f32_t fTimeDelta)
{
    __super::Update(fTimeDelta);
    m_pModelCom->Play_Animation(fTimeDelta);        // 렌더 전에 뼈 갱신
}

for (uint32_t i = 0; i < iNumMeshes; i++)           // Render
{
    m_pModelCom->Bind_BoneMatrices(i, 2);           // 메시마다 그 메시용 뼈 배열을 b2에
    m_pModelCom->Bind_Material(i, aiTextureType_DIFFUSE, 0, 0);
    m_pModelCom->Render(i);
}

// Ready_Components: VS를 Prototype_Component_VS_AnimMesh로 교체
```
- VS를 안 바꾸면 InputLayout(stride 56)과 정점 버퍼(stride 88)가 맞지 않아 모델이 깨진다.

---

### STEP 9. 빌드·실행하면서 고친 것들

1110은 컴파일이 안 되는 상태로 끝났다. 처음 빌드하면서 함께 고친 것들이다.

| 문제 | 수정 |
|---|---|
| 람다 인자 타입 불일치 | `[&](CBone* p)` → `[&](shared_ptr<CBone> p)` |
| `size_t` → `int32_t` 축소 변환 에러 | `static_cast<int32_t>(m_Bones.size()) - 1` |
| 메시가 모델을 모름 | `CMesh::Create(..., dynamic_pointer_cast<CModel>(shared_from_this()), ...)` |
| `Get_BoneIndex`가 항상 -1 | **`Ready_Bones`를 `Ready_Meshes`보다 먼저** 호출 |
| 클론의 뼈·PreTransform이 비어 있음 | 복사 생성자에 `m_Bones{Prototype.m_Bones}`, `m_PreTransformMatrix{Prototype.m_PreTransformMatrix}` |

- `shared_from_this()`는 `Create` 안에서 이미 `shared_ptr`로 감싼 뒤에 호출되니까 안전하다(생성자 안에서는 불가).
- ⚠️ `m_Bones` 복사는 `shared_ptr` **얕은 복사**다. 모든 클론이 같은 뼈를 공유하므로, 개체마다 다른 애니메이션을 재생하려면 나중에 깊은 복사가 필요하다.

---

## 3. 핵심 포인트 모음

- **Assimp 행렬은 들여올 때 전치** (`mTransformation`, `mOffsetMatrix` 모두)
- **곱셈 순서**: `Offset × Combined`, `Transformation × 부모 Combined` (행벡터 규칙이라 "나 → 부모" 순으로 오른쪽에 곱함)
- **번호 체계 두 개**: 정점 BlendIndex·`m_BoneMatrices` = 메시 로컬 번호 / `m_BoneIndices[i]`·`m_Bones` = 모델 전체 번호
- **PreTransform**: NONANIM은 정점에, ANIM은 루트 뼈에
- **순서 보장**: `m_Bones`는 부모가 자식보다 앞 (전위 순회)
- **초기화 순서**: `Ready_Bones` → `Ready_Meshes` → `Ready_Materials`
- **Clone**: 새로 추가한 멤버는 복사 생성자에도 반드시 추가

---

## 4. 알려진 한계 / 다음에 손볼 곳

| 항목 | 내용 |
|---|---|
| `vWorldPos` | 스키닝 전 위치를 씀 → 뼈 행렬 적용 후 위치에 World를 곱해야 함 |
| 탄젠트·바이노멀 | 스키닝 안 됨 → 노멀맵을 켜면 문제 |
| 뼈 영향 5개 이상 | `TargetRealtime_Fast`에는 `aiProcess_LimitBoneWeights`가 없음. w칸이 덮어써짐 |
| NONANIM 메시의 상수버퍼 | 안 쓰는데 32KB씩 생성됨 |
| 뼈 공유 | 클론끼리 `m_Bones` 공유 → 개체별 애니메이션 불가 |
| `Get_BoneIndex(m_szName)` -1 | `uint32_t`에 들어가면 42억 → 크래시 (아래 5장) |

---

## 5. 내 프로젝트(Duckov)에 적용하면서 겪은 문제

### 5-1. `vector subscript out of range` (Debug Assertion)
- **위치**: `CMesh::Bind_BoneMatrix`의 `Bones[m_BoneIndices[i]]`
- **원인**: `CModel` 복사 생성자에 `m_Bones`가 없어서, Player가 Clone한 모델의 뼈 벡터가 비어 있었음. 메시(`m_BoneIndices`)는 공유되니까 "인덱스는 있는데 뼈 배열은 빈" 상태.
- **해결**: 복사 생성자에 `m_Bones{rhs.m_Bones}` 추가.

### 5-2. FBX 경로에서 상수버퍼가 안 만들어짐
- `m_pCB` 생성 코드가 `.bin` 로드 함수에만 있었음 → aiMesh 경로의 `Initialize_Prototype`에도 추가.
- `Bind_Pixel_ShaderResource`로 바인딩하던 것을 `Bind_Vertex_ShaderResource`로 수정 (뼈 행렬은 VS에서 읽음).

### 5-3. 메시 이름 ≠ 노드 이름 (Quad / FakeAO)
- Boss_Wu FBX 안에서 **노드 이름은 `FakeAO`, 메시(Geometry) 이름은 `Quad`**(Unity 기본 Quad를 붙인 가짜 그림자 판).
- Assimp는 `aiMesh::mName`을 Geometry 이름에서, `aiNode::mName`을 Model 이름에서 가져옴 → `Get_BoneIndex("Quad")` = -1.
- **근본 해결(방법 A)**: 이름 대신 **`aiNode::mMeshes`(노드가 가진 메시 번호)** 로 연결한다.
  1. `CModel`에 `vector<int32_t> m_MeshOwnerBones` 추가
  2. `Ready_Bones` 호출 전에 `m_MeshOwnerBones.assign(m_pAiScene->mNumMeshes, -1)`
  3. `Ready_Bones`에서 push_back 직후 `pAINode->mMeshes[k]`마다 `m_MeshOwnerBones[메시번호] = 내 뼈 인덱스` (처음 것만)
  4. `CMesh::Create`에 `m_MeshOwnerBones[i]`를 넘기고, 뼈 없는 메시 블록에서 이름 검색 대신 사용
  5. 그래도 -1이면 0(루트)으로 대체하거나 `E_FAIL`
- **임시 방법**: 뼈 없는 메시는 렌더 루프에서 `continue`로 건너뜀. (블록만 주석 처리하면 `m_BoneMatrices`가 0 행렬이라 점으로 찌그러져 "우연히" 안 보이는 것일 뿐, 드로우 콜은 그대로 나감)

### 5-4. 모델이 아예 안 보임
- **원인**: 복사 생성자 오타 `m_PreTransformMatrix{m_PreTransformMatrix}` — `rhs.`가 빠져 **자기 자신으로 초기화** → 쓰레기값(Debug 힙 `0xCD` 패턴). 루트 Combined가 망가지고 모든 뼈가 그 값을 물려받아 정점이 날아감.
- 멤버 선언의 `= {}` 기본값은 초기화 목록에 그 멤버가 있으면 **무시된다**.
- **해결**: `m_PreTransformMatrix{rhs.m_PreTransformMatrix}`.

### 5-5. 그 외
- `XMMatrixRotationY(180.f)`는 **라디안**이다 → `XMConvertToRadians(180.f)`.
- 셰이더에서 뼈 적용 결과를 `mul(float4(In.vPosition,1), g_matWorld)`로 덮어쓰던 실수 → `mul(vPosW, g_matWorld)`.
- `mul(float3, float4x4)`는 크기 불일치 → `(float3x3)BoneMatrix`로 캐스팅.

---

## 6. 다음 수업 예상

`aiAnimation` → 채널(`aiNodeAnim`, 뼈별 키프레임) → 현재 시간에 맞는 위치·회전·스케일을 보간 → `m_TransformationMatrix` 덮어쓰기. 즉 `Play_Animation`의 **1번 주석 자리**를 채우는 내용.

---

## 7. 한 줄 정리

**정점 × Offset(뼈 기준으로) × Combined(현재 포즈로)** 를 메시별 상수버퍼(b2)로 보내고, 정점 셰이더가 최대 4개 뼈 행렬을 가중치로 섞어 곱한다. 오늘은 로컬 행렬이 기본값이라 **기본 자세가 정상 출력되면 성공**.
