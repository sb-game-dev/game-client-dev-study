#pragma once
#include "Engine_Defines.h"
#include "Component.h"

NS_BEGIN(Engine)
class ENGINE_DLL CModel : public CComponent
{
private:
	CModel(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	CModel(const CModel& rhs);
public:
	~CModel() = default; 

public:
	uint32_t Get_NumMeshes() const {return m_iNumMeshes;}

public:
	HRESULT			Initialize_Prototype(MODEL eType, const char_t* pModelFilePath, fmatrix_t PreTransformMatrix);
	HRESULT			Initialize(void* pArg)override;

public:
	HRESULT			Render(uint32_t iMeshIndex);
	HRESULT			Render_Instanced(uint32_t iMeshIndex, ID3D11Buffer* pInstanceVB, uint32_t iInstanceStride, uint32_t iNumInstances);
	HRESULT			Bind_Material(uint32_t iMeshIndex, aiTextureType eType, uint32_t iIndex, uint32_t iSlot);
	HRESULT			Bind_BoneMatrix(uint32_t iMeshIndex, uint32_t iSlot);

	void			SetUseCulling(bool_t bUse) { m_bUseCulling = bUse; }
	bool_t			IsUseCulling() { return m_bUseCulling; }

	int32_t			Get_BoneIndex(const char_t* pBoneName);

	BoundingBox		GetBoundinBox() { return m_tLocalBox; }

	const float4x4_t* Get_CombinedTransformMatrix(const char_t* pBoneName);

	void			PlayAnimation(f32_t fDeltaTime);
	void			SetAnimPlaySpeed(f32_t fAnimPlaySpeed, bool_t isUpper = false);
	void			Reset_BoneTransformMatrix();
	void			Set_LowerAnimationIndex(uint32_t iAnimIndex, f32_t fBlendDuration = 0.2f);
	void			Set_UpperAnimationIndex(uint32_t iAnimIndex, bool_t bActive, f32_t fBlendDuration = 0.2f);
	void			Set_UpperAnimationInActive(f32_t fBlendDuration = 0.2f);
	void			Set_Animation_Loop(uint32_t iAnimationIndex);
	bool_t			Is_Animation_Finished(bool_t bUpper = false);
private:
	const	aiScene*	m_pAiScene = { nullptr };
	Assimp::Importer	m_pImporter = {};

private:
	MODEL									m_eType = { MODEL::END };

	vector<shared_ptr <class CMesh>>		m_Meshes;
	uint32_t								m_iNumMeshes = {};
	float4x4_t								m_PreTransformMatrix = {};

	vector<shared_ptr<class CMaterial>>		m_Materials;
	uint32_t								m_iNumMaterials = {};

	vector<shared_ptr<class CBone>>			m_Bones;

	vector<shared_ptr<class CAnimation>>	m_Animations;
	vector<bool_t>							m_IsUpperBone;
	uint32_t								m_iNumAnimaition = {};

	struct ANIM_LAYER
	{
		uint32_t			iAnimIndex = {};
		bool_t				isActive = { false };
		f32_t				fAnimPlaySpeed = {1.f};

		bool_t				isBlending = { false };
		f32_t				fBlendTime = {};
		f32_t				fBlendDuration = { 0.3f };
		vector<BONE_SRT>	PreBoneSRT;
	};
	ANIM_LAYER								m_tLowerLayer = { 0, true };
	ANIM_LAYER								m_tUpperLayer = { 0, false };

	BoundingBox								m_tLocalBox = {};
	bool_t									m_bUseCulling = { false };


private:

	HRESULT	Ready_Meshes(MODEL eType, fmatrix_t PreTransformMatrix);
	HRESULT	Ready_Materials(const char_t* pModelFilePath);
	HRESULT	Ready_Bones(const aiNode* pAINode, int32_t iParentIndex);
	HRESULT	Ready_Bones(const aiNode* pAINode, int32_t iParentIndex, bool_t isUpper);
	HRESULT	Ready_Animation();

	HRESULT	Load_Binary(const char_t* pModelFilePath, fmatrix_t PreTransformMatrix);
	HRESULT	Read_Header(FILE* pFile, const char_t* pModelFilePath, fmatrix_t PreTransformMatrix);

	HRESULT	Read_Bone(FILE* pFile);
	HRESULT Read_Meshes(FILE* pFile, fmatrix_t PreTranformMatrix);
	HRESULT Read_AnimMeshes(FILE* pFile, fmatrix_t PreTranformMatrix);
	HRESULT Read_Materials(FILE* pFile, const char_t* pModelFilePath);
	HRESULT	Read_Animation(FILE* pFile);

	f32_t	Update_BlendRatio(ANIM_LAYER& tLayer, f32_t fDeltaTime);

public:
	static shared_ptr<CModel> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, MODEL eType, const char_t* pModelFilePath, fmatrix_t PreTransformMatrix = XMMatrixIdentity());
	shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END