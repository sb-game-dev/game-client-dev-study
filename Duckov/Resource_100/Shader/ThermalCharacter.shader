//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "ThermalCharacter" {
    Properties {
        _AlphaCutoff ("Alpha Cutoff ", Range(0, 1)) = 0.5
        _EmissionColor ("Emission Color", Color) = (1,1,1,1)
        _HurtValue ("_HurtValue", Range(0, 1)) = 1
        _MetallicSmoothness ("MetallicSmoothness", 2D) = "white" { }
        _Metallic ("Metallic", Range(0, 1)) = 0
        _TempratureLerp ("TempratureLerp", Range(0, 1)) = 1
        _BaseMap ("BaseMap", 2D) = "white" { }
        _MainTex ("MainTex", 2D) = "white" { }
        _HideInThermal ("HideInThermal", Float) = 0
        _texcoord ("", 2D) = "white" { }
        _QueueOffset ("_QueueOffset", Float) = 0
        _QueueControl ("_QueueControl", Float) = -1
        unity_Lightmaps ("unity_Lightmaps", 2DArray) = "" { }
        unity_LightmapsInd ("unity_LightmapsInd", 2DArray) = "" { }
        unity_ShadowMasks ("unity_ShadowMasks", 2DArray) = "" { }
        [ToggleOff] _ReceiveShadows ("Receive Shadows", Float) = 1
    }
    SubShader {
        Tags { "QUEUE" = "Transparent" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Transparent" "UniversalMaterialType" = "Unlit" }
        Pass {
            Name "Forward"
            Tags { "LIGHTMODE" = "UniversalForward" "QUEUE" = "Transparent" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Transparent" "UniversalMaterialType" = "Unlit" }
            Blend SrcAlpha OneMinusSrcAlpha, One OneMinusSrcAlpha
            ZWrite Off
            GpuProgramID 22732
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    Keywords { "_ALPHATEST_ON" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "_ALPHATEST_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ALPHATEST_ON" "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
Fallback "Hidden/Shader Graph/FallbackError"
CustomEditor "UnityEditor.ShaderGraphUnlitGUI"
}