//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Shader Graphs/Decal" {
    Properties {
        Base_Map ("Base Map", 2D) = "white" { }
        Normal_Map ("Normal Map", 2D) = "bump" { }
        Normal_Blend ("Normal Blend", Float) = 0.5
        _DrawOrder ("Draw Order", Range(-50, 50)) = 0
        [Enum(Depth Bias, 0, View Bias, 1)] _DecalMeshBiasType ("DecalMesh BiasType", Float) = 0
        _DecalMeshDepthBias ("DecalMesh DepthBias", Float) = 0
        _DecalMeshViewBias ("DecalMesh ViewBias", Float) = 0
        unity_Lightmaps ("unity_Lightmaps", 2DArray) = "" { }
        unity_LightmapsInd ("unity_LightmapsInd", 2DArray) = "" { }
        unity_ShadowMasks ("unity_ShadowMasks", 2DArray) = "" { }
    }
    SubShader {
        Tags { "DisableBatching" = "False" "PreviewType" = "Plane" "RenderPipeline" = "UniversalPipeline" "ShaderGraphShader" = "true" "ShaderGraphTargetId" = "UniversalDecalSubTarget" }
        Pass {
            Name "DBufferProjector"
            Tags { "DisableBatching" = "False" "LIGHTMODE" = "DBufferProjector" "PreviewType" = "Plane" "RenderPipeline" = "UniversalPipeline" "ShaderGraphShader" = "true" "ShaderGraphTargetId" = "UniversalDecalSubTarget" }
            Blend 0 SrcAlpha OneMinusSrcAlpha, Zero OneMinusSrcAlpha
            Blend 1 SrcAlpha OneMinusSrcAlpha, Zero OneMinusSrcAlpha
            Blend 2 SrcAlpha OneMinusSrcAlpha, Zero OneMinusSrcAlpha
            ColorMask 0 2
            ZTest Greater
            ZWrite Off
            Cull Front
            GpuProgramID 50690
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "DBufferMesh"
            Tags { "DisableBatching" = "False" "LIGHTMODE" = "DBufferMesh" "PreviewType" = "Plane" "RenderPipeline" = "UniversalPipeline" "ShaderGraphShader" = "true" "ShaderGraphTargetId" = "UniversalDecalSubTarget" }
            Blend 0 SrcAlpha OneMinusSrcAlpha, Zero OneMinusSrcAlpha
            Blend 1 SrcAlpha OneMinusSrcAlpha, Zero OneMinusSrcAlpha
            Blend 2 SrcAlpha OneMinusSrcAlpha, Zero OneMinusSrcAlpha
            ColorMask 0 2
            ZWrite Off
            GpuProgramID 200709
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
Fallback "Hidden/Shader Graph/FallbackError"
CustomEditor "UnityEditor.ShaderGraph.GenericShaderGraphMaterialGUI"
}