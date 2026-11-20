#pragma once

namespace Client
{
	/* =========================================================
	*  원형(Prototype) 태그 : Add_Prototype / Add_Component / Add_GameObject의 원형 인자
	* ========================================================= */
	namespace Proto
	{
		// ---------- Texture ----------
		inline constexpr const wchar_t* Texture_BackGround = L"Prototype_Component_Texture_BackGround";
		inline constexpr const wchar_t* Texture_Mouse = L"Prototype_Component_Texture_Mouse";
		inline constexpr const wchar_t* Texture_ItemIcons = L"Prototype_Component_Texture_ItemIcons";
		inline constexpr const wchar_t* Texture_HUDIcons = L"Prototype_Component_Texture_HUDIcons";
		inline constexpr const wchar_t* Texture_Cube = L"Prototype_Component_Texture_Cube";
		inline constexpr const wchar_t* Texture_Hill = L"Prototype_Component_Texture_Hill";
		inline constexpr const wchar_t* Texture_Wave = L"Prototype_Component_Texture_Wave";
		inline constexpr const wchar_t* Texture_Tree = L"Prototype_Component_Texture_Tree";
		inline constexpr const wchar_t* Texture_SkyBox = L"Prototype_Component_Texture_SkyBox";
		inline constexpr const wchar_t* Texture_Mirror = L"Prototype_Component_Texture_Mirror";
		inline constexpr const wchar_t* Texture_Terrain_Blend = L"Prototype_Component_Texture_Terrain_Blend";
		inline constexpr const wchar_t* Texture_Terrain_Layer = L"Prototype_Component_Texture_Terrain_Layer";

		// ---------- VIBuffer ----------
		inline constexpr const wchar_t* VIBuffer_Rect = L"Prototype_Component_VIBuffer_Rect";
		inline constexpr const wchar_t* VIBuffer_Cube = L"Prototype_Component_VIBuffer_Cube";
		inline constexpr const wchar_t* VIBuffer_SkyBox = L"Prototype_Component_VIBuffer_SkyBox";
		inline constexpr const wchar_t* VIBuffer_Pyramid = L"Prototype_Component_VIBuffer_Pyramid";
		inline constexpr const wchar_t* VIBuffer_Terrain = L"Prototype_Component_VIBuffer_Terrain";

		// ---------- Shader : VtxTex ----------
		inline constexpr const wchar_t* VS_VTXTEX = L"Prototype_Component_VS_VTXTEX";
		inline constexpr const wchar_t* VS_VTXTEX_UI = L"Prototype_Component_VS_VTXTEX_UI";
		inline constexpr const wchar_t* VS_VTXTEX_INSTANCE = L"Prototype_Component_VS_VTXTEX_INSTANCE";
		inline constexpr const wchar_t* VS_VTXTEX_INSTANCE_UI = L"Prototype_Component_VS_VTXTEX_INSTANCE_UI";
		inline constexpr const wchar_t* PS_VTXTEX = L"Prototype_Component_PS_VTXTEX";
		inline constexpr const wchar_t* PS_VTXTEX_NOLIGHT = L"Prototype_Component_PS_VTXTEX_NOLIGHT";
		inline constexpr const wchar_t* PS_VTXTEX_SHADOW = L"Prototype_Component_PS_VTXTEX_SHADOW";
		inline constexpr const wchar_t* PS_VTXTEX_SKYBOX = L"Prototype_Component_PS_VTXTEX_SKYBOX";

		// ---------- Shader : VtxCol ----------
		inline constexpr const wchar_t* VS_VTXCOL = L"Prototype_Component_VS_VTXCOL";
		inline constexpr const wchar_t* VS_VTXCOL_UI = L"Prototype_Component_VS_VTXCOL_UI";
		inline constexpr const wchar_t* PS_VTXCOL = L"Prototype_Component_PS_VTXCOL";
		inline constexpr const wchar_t* PS_VTXCOL_SCOPE = L"Prototype_Component_PS_VTXCOL_SCOPE";
		inline constexpr const wchar_t* PS_VTXCOL_SHADOW = L"Prototype_Component_PS_VTXCOL_SHADOW";
		inline constexpr const wchar_t* PS_VTXCOL_OCCLUDED = L"Prototype_Component_PS_VTXCOL_OCCLUDEDPLAYER";

		// ---------- Shader : Terrain / UI ----------
		inline constexpr const wchar_t* VS_TERRAIN = L"Prototype_Component_VS_TERRAIN";
		inline constexpr const wchar_t* PS_TERRAIN = L"Prototype_Component_PS_TERRAIN";
		inline constexpr const wchar_t* VS_UI = L"Prototype_Component_VS_UI";
		inline constexpr const wchar_t* PS_UI = L"Prototype_Component_PS_UI";
		inline constexpr const wchar_t* VS_UI_CIRCLE = L"Prototype_Component_VS_UI_CIRCLE";
		inline constexpr const wchar_t* PS_UI_CIRCLE = L"Prototype_Component_PS_UI_CIRCLE";

		// ---------- Shader : Model ----------
		inline constexpr const wchar_t* VS_MODEL = L"Prototype_Component_VS_MODEL";
		inline constexpr const wchar_t* VS_ANIM_MODEL = L"Prototype_Component_VS_ANIM_MODEL";
		inline constexpr const wchar_t* VS_MODEL_INSTANCE = L"Prototype_Component_VS_MODEL_INSTANCE";
		inline constexpr const wchar_t* PS_MODEL = L"Prototype_Component_PS_MODEL";
		inline constexpr const wchar_t* PS_CHARACTER = L"Prototype_Component_PS_CHARACTER";

		// ---------- Model ----------
		// 값은 Normalize_AssetPath()를 거친 경로(소문자, Resource 루트 제외) 그대로 둔다.
		// StaticProp::Change_Model / 맵툴 콤보(Get_ModelTags) / 씬 파일이 이 경로로 원형을 찾기 때문.
		inline constexpr const wchar_t* Model_Duck = L"characters/s12_duckv2_2/s12_duckv2_2.fbx";
		inline constexpr const wchar_t* Model_Boss_Wu = L"characters/0_charactermodel_boss_wu/0_charactermodel_boss_wu.bin";
		inline constexpr const wchar_t* Model_Tree_01 = L"mesh/tree/pfb_tree_01_1.bin";
		inline constexpr const wchar_t* Model_Container_Back = L"mesh/sm_container/sm_container_back.bin";
		inline constexpr const wchar_t* Model_Container_Ceiling = L"mesh/sm_container/sm_container_ceiling.bin";
		inline constexpr const wchar_t* Model_Container_Ground = L"mesh/sm_container/sm_container_ground.bin";
		inline constexpr const wchar_t* Model_Container_L = L"mesh/sm_container/sm_container_l.bin";
		inline constexpr const wchar_t* Model_Container_R = L"mesh/sm_container/sm_container_r.bin";
		inline constexpr const wchar_t* Model_Weapon_AK47 = L"mesh/weapons/guns/ig_gun_ak47.bin";
		inline constexpr const wchar_t* Model_Weapon_M700 = L"mesh/weapons/guns/ig_gun_m700.bin";
		inline constexpr const wchar_t* Model_Weapon_PM = L"mesh/weapons/guns/ig_gun_pm.bin";
		inline constexpr const wchar_t* Model_Weapon_Axe = L"mesh/weapons/melee_handheld/meleeweaponagent_axe.bin";
		inline constexpr const wchar_t* Model_Helmet_LV2 = L"mesh/equipment/helmet/ig_helmat_lv2.bin";
		inline constexpr const wchar_t* Model_Helmet_LV3 = L"mesh/equipment/helmet/ig_helmat_lv3.bin";
		inline constexpr const wchar_t* Model_Armor_LV2 = L"mesh/equipment/armor/ig_armor_lv2.bin";
		inline constexpr const wchar_t* Model_Armor_LV3 = L"mesh/equipment/armor/ig_armor_lv3.bin";
		inline constexpr const wchar_t* Model_BackPack_LV2 = L"mesh/equipment/backpack/ig_backpack_lv2.bin";
		inline constexpr const wchar_t* Model_BackPack_LV3 = L"mesh/equipment/backpack/ig_backpack_lv3.bin";
		inline constexpr const wchar_t* Model_Headset_LV0 = L"mesh/equipment/headset/ig_headset_lv0.bin";
		inline constexpr const wchar_t* Model_Headset_LV1 = L"mesh/equipment/headset/ig_headset_lv1v2.bin";
		inline constexpr const wchar_t* Model_FaceMask_FlyMask = L"mesh/equipment/facemask/ig_fackmask_flymask.bin";
		inline constexpr const wchar_t* Model_FaceMask_GasMask = L"mesh/equipment/facemask/ig_fackmask_gasmask_01.bin";
		inline constexpr const wchar_t* Model_FaceMask_NightVision = L"mesh/equipment/facemask/ig_fackmask_nightvision.bin";


		// ---------- GameObject 원형 ----------
		inline constexpr const wchar_t* Obj_BackGround = L"Prototype_GameObject_BackGround";
		inline constexpr const wchar_t* Obj_Player = L"Prototype_GameObject_Player";
		inline constexpr const wchar_t* Obj_Player_Body = L"Prototype_GameObject_Player_Body";
		inline constexpr const wchar_t* Obj_Weapon = L"Prototype_GameObject_Weapon";
		inline constexpr const wchar_t* Obj_Helmet = L"Prototype_GameObject_Helmet";
		inline constexpr const wchar_t* Obj_Armor = L"Prototype_GameObject_Armor";
		inline constexpr const wchar_t* Obj_BackPack = L"Prototype_GameObject_BackPack";
		inline constexpr const wchar_t* Obj_Headset = L"Prototype_GameObject_Headset";
		inline constexpr const wchar_t* Obj_FaceMask = L"Prototype_GameObject_FaceMask";
		inline constexpr const wchar_t* Obj_Cube = L"Prototype_GameObject_Cube";
		inline constexpr const wchar_t* Obj_Cube_Instance = L"Prototype_GameObject_Cube_Instance";
		inline constexpr const wchar_t* Obj_SkyBox = L"Prototype_GameObject_SkyBox";
		inline constexpr const wchar_t* Obj_Hill = L"Prototype_GameObject_Hill";
		inline constexpr const wchar_t* Obj_Wave = L"Prototype_GameObject_Wave";
		inline constexpr const wchar_t* Obj_Fog = L"Prototype_GameObject_Fog";
		inline constexpr const wchar_t* Obj_Mirror = L"Prototype_GameObject_Mirror";
		inline constexpr const wchar_t* Obj_Tree = L"Prototype_GameObject_Tree";
		inline constexpr const wchar_t* Obj_Client_Mouse = L"Prototype_GameObject_Client_Mouse";
		inline constexpr const wchar_t* Obj_Scope = L"Prototype_GameObject_Scope";
		inline constexpr const wchar_t* Obj_Inven = L"Prototype_GameObject_Inven";
		inline constexpr const wchar_t* Obj_HUD = L"Prototype_GameObject_HUD";
		inline constexpr const wchar_t* Obj_QuaterViewCam = L"Prototype_GameObject_QuaterViewCam";
		inline constexpr const wchar_t* Obj_FreeCam = L"Prototype_GameObject_FreeCam";
		inline constexpr const wchar_t* Obj_MapToolCam = L"Prototype_GameObject_MapToolCam";
		inline constexpr const wchar_t* Obj_StaticProp = L"Prototype_GameObject_StaticProp";
		inline constexpr const wchar_t* Obj_Tree_Instance = L"Prototype_GameObject_Tree_Instance";

	}

	/* =========================================================
	*  사본(GameObject) 태그 : Add_GameObject의 마지막 인자 / Find_GameObject
	* ========================================================= */
	namespace GO
	{
		inline constexpr const wchar_t* BackGround = L"GameObject_BackGround";
		inline constexpr const wchar_t* Player = L"GameObject_Player";
		inline constexpr const wchar_t* Cube = L"GameObject_Cube";          // 뒤에 번호 붙여서 사용
		inline constexpr const wchar_t* Cube_Instance = L"GameObject_Cube_Instance";
		inline constexpr const wchar_t* SkyBox = L"GameObject_SkyBox";
		inline constexpr const wchar_t* Hill = L"GameObject_Hill";
		inline constexpr const wchar_t* Wave = L"GameObject_Wave";
		inline constexpr const wchar_t* Fog = L"GameObject_Fog";
		inline constexpr const wchar_t* Mirror = L"GameObject_Mirror";
		inline constexpr const wchar_t* Tree = L"GameObject_Tree";
		inline constexpr const wchar_t* Client_Mouse = L"GameObject_Client_Mouse";
		inline constexpr const wchar_t* Scope = L"GameObject_Scope";
		inline constexpr const wchar_t* Inven = L"GameObject_Inven";
		inline constexpr const wchar_t* HUD = L"GameObject_HUD";
		inline constexpr const wchar_t* QuaterViewCam = L"GameObject_QuaterViewCam";
		inline constexpr const wchar_t* FreeCam = L"GameObject_FreeCam";
		inline constexpr const wchar_t* MapToolCam = L"GameObject_MapToolCam";
		inline constexpr const wchar_t* StaticProp = L"GameObject_StaticProp";
		inline constexpr const wchar_t* Tree_Instance = L"GameObject_Tree_Instance";
	}

	/* =========================================================
	*  레이어 태그
	* ========================================================= */
	namespace Layer
	{
		inline constexpr const wchar_t* BackGround = L"Layer_BackGround";
		inline constexpr const wchar_t* GameObject = L"Layer_GameObject";
	}

	/* =========================================================
	*  컴포넌트 슬롯 태그 (Com_Transform은 엔진의 g_strTransformComTag 사용)
	* ========================================================= */
	namespace Com
	{
		inline constexpr const wchar_t* Texture = L"Com_Texture";
		inline constexpr const wchar_t* Blend = L"Com_Blend";
		inline constexpr const wchar_t* Diffuse = L"Com_Diffuse";
		inline constexpr const wchar_t* IconTex = L"Com_IconTex";
		inline constexpr const wchar_t* Buffer = L"Com_Buffer";
		inline constexpr const wchar_t* VS = L"Com_VS";
		inline constexpr const wchar_t* PS = L"Com_PS";
		inline constexpr const wchar_t* PS_Shadow = L"Com_PS_SHADOW";
		inline constexpr const wchar_t* PS_Occluded = L"Com_PS_OCCLUDEDPLAYER";
	}
}