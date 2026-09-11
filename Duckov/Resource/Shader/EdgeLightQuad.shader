//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "EdgeLightQuad" {
    Properties {
        _AlphaCutoff ("Alpha Cutoff ", Range(0, 1)) = 0.5
        _EmissionColor ("Emission Color", Color) = (1,1,1,1)
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
            Blend DstColor Zero, DstColor Zero
            ColorMask RGB 0
            ZTest Always
            ZWrite Off
            Stencil {
                Ref 2
                ReadMask 2
                Comp NotEqual
                Pass Replace
                Fail Keep
                ZFail Keep
            }
            GpuProgramID 9956
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
        Pass {
            Name "DepthNormals"
            Tags { "LIGHTMODE" = "DepthNormalsOnly" "QUEUE" = "Transparent" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Transparent" "UniversalMaterialType" = "Unlit" }
            Stencil {
                Ref 2
                ReadMask 2
                Comp NotEqual
                Pass Replace
                Fail Keep
                ZFail Keep
            }
            GpuProgramID 123151
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
Fallback "Hidden/Shader Graph/FallbackError"
CustomEditor "UnityEditor.ShaderGraphUnlitGUI"
}