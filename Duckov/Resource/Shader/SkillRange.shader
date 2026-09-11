//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "SkillRange" {
    Properties {
        _AlphaCutoff ("Alpha Cutoff ", Range(0, 1)) = 0.5
        _EmissionColor ("Emission Color", Color) = (1,1,1,1)
        _Radius ("Radius", Float) = 1
        _lineWidth ("lineWidth", Range(0, 0.2)) = 0
        _blur ("blur", Range(0, 0.2)) = 0.2
        _depthFadeDistance ("depthFadeDistance", Float) = 1
        _RingColor ("RingColor", Color) = (1,1,1,1)
        _ProgressColor ("ProgressColor", Color) = (0.1556604,0.6167926,1,0.2784314)
        _HideColor ("HideColor", Color) = (0.1556604,0.6167926,1,0.2784314)
        _Progress ("Progress", Range(0, 1)) = 1
        _ProgressPower ("ProgressPower", Float) = 1
        _Grid ("Grid", 2D) = "white" { }
        _GridTile ("GridTile", Float) = 1
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
            Tags { "LIGHTMODE" = "UniversalForwardOnly" "QUEUE" = "Transparent" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Transparent" "UniversalMaterialType" = "Unlit" }
            Blend SrcAlpha OneMinusSrcAlpha, One OneMinusSrcAlpha
            ZTest Always
            ZWrite Off
            GpuProgramID 35479
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
Fallback "Hidden/Shader Graph/FallbackError"
CustomEditor "UnityEditor.ShaderGraphUnlitGUI"
}