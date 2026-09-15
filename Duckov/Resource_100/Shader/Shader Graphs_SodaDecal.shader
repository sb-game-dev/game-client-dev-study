//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Shader Graphs/SodaDecal" {
    Properties {
        _MainTex ("MainTex", 2D) = "white" { }
        _Tint ("Tint", Color) = (1,1,1,1)
        _Metallic ("Metallic", Range(0, 1)) = 0
        _Smoothness ("Smoothness", Range(0, 1)) = 0
        _MAOSAlpha ("_MAOSAlpha", Range(0, 1)) = 0
        _BlendNormal ("BlendNormal", Range(0, 1)) = 0
        _Normal ("Normal", 2D) = "bump" { }
        _MetallicSmoothness ("_MetallicSmoothness", 2D) = "white" { }
        _Emission ("Emission", Color) = (0,0,0,0)
        _DrawOrder ("Draw Order", Range(-50, 50)) = 0
        [Enum(Depth Bias, 0, View Bias, 1)] _DecalMeshBiasType ("DecalMesh BiasType", Float) = 0
        _DecalMeshDepthBias ("DecalMesh DepthBias", Float) = 0
        _DecalMeshViewBias ("DecalMesh ViewBias", Float) = 0
        _DecalAngleFadeSupported ("Decal Angle Fade Supported", Float) = 1
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
            ZTest Greater
            ZWrite Off
            Cull Front
            GpuProgramID 42338
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "DecalProjectorForwardEmissive"
            Tags { "DisableBatching" = "False" "LIGHTMODE" = "DecalProjectorForwardEmissive" "PreviewType" = "Plane" "RenderPipeline" = "UniversalPipeline" "ShaderGraphShader" = "true" "ShaderGraphTargetId" = "UniversalDecalSubTarget" }
            Blend 0 SrcAlpha One, SrcAlpha One
            ZTest Greater
            ZWrite Off
            Cull Front
            GpuProgramID 100528
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" }
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
            ZWrite Off
            GpuProgramID 265256
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "DecalMeshForwardEmissive"
            Tags { "DisableBatching" = "False" "LIGHTMODE" = "DecalMeshForwardEmissive" "PreviewType" = "Plane" "RenderPipeline" = "UniversalPipeline" "ShaderGraphShader" = "true" "ShaderGraphTargetId" = "UniversalDecalSubTarget" }
            Blend 0 SrcAlpha One, SrcAlpha One
            ZWrite Off
            GpuProgramID 372182
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
Fallback "Hidden/Shader Graph/FallbackError"
CustomEditor "UnityEditor.ShaderGraph.GenericShaderGraphMaterialGUI"
}