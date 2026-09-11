//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "MoveRing" {
    Properties {
        _AlphaCutoff ("Alpha Cutoff ", Range(0, 1)) = 0.5
        _EmissionColor ("Emission Color", Color) = (1,1,1,1)
        _Threshold ("Threshold", Float) = 0.9
        _Scale ("Scale", Float) = 1
        _Direction ("Direction", Vector) = (0,0,0,1)
        _LineWidth ("LineWidth", Float) = 0.1
        _Distance ("Distance", Float) = 0.1
        _DotRadius ("DotRadius", Float) = 0.2
        _Shadow ("Shadow", Range(0, 1)) = 0
        _ShadowStrength ("ShadowStrength", Range(0, 1)) = 1
        _WalkColor ("WalkColor", Color) = (1,1,1,0)
        _RunColor ("RunColor", Color) = (1,1,1,0)
        _FadeDistance ("FadeDistance", Float) = 0
        _Running ("Running", Range(0, 1)) = 0
        _QueueOffset ("_QueueOffset", Float) = 0
        _QueueControl ("_QueueControl", Float) = -1
        unity_Lightmaps ("unity_Lightmaps", 2DArray) = "" { }
        unity_LightmapsInd ("unity_LightmapsInd", 2DArray) = "" { }
        unity_ShadowMasks ("unity_ShadowMasks", 2DArray) = "" { }
        [ToggleOff] _ReceiveShadows ("Receive Shadows", Float) = 1
    }
    SubShader {
        Tags { "QUEUE" = "Transparent" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Overlay" "UniversalMaterialType" = "Unlit" }
        Pass {
            Name "Forward"
            Tags { "LIGHTMODE" = "UniversalForwardOnly" "QUEUE" = "Transparent" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Overlay" "UniversalMaterialType" = "Unlit" }
            Blend SrcAlpha OneMinusSrcAlpha, One OneMinusSrcAlpha
            ZTest Always
            ZWrite Off
            GpuProgramID 52603
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
Fallback "Hidden/InternalErrorShader"
CustomEditor "UnityEditor.ShaderGraphUnlitGUI"
}