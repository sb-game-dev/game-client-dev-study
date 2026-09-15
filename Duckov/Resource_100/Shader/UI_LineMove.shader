//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "UI_LineMove" {
    Properties {
        _MainTex ("Sprite Texture", 2D) = "white" { }
        _Color ("Tint", Color) = (1,1,1,1)
        _StencilComp ("Stencil Comparison", Float) = 8
        _Stencil ("Stencil ID", Float) = 0
        _StencilOp ("Stencil Operation", Float) = 0
        _StencilWriteMask ("Stencil Write Mask", Float) = 255
        _StencilReadMask ("Stencil Read Mask", Float) = 255
        _ColorMask ("Color Mask", Float) = 15
        [Toggle(UNITY_UI_ALPHACLIP)] _UseUIAlphaClip ("Use Alpha Clip", Float) = 0
        _Noise ("Noise", 2D) = "white" { }
        _NoiseTileAndSpeed ("NoiseTileAndSpeed", Vector) = (1,1,0.5,0.5)
        _NoiseAffactAlpha ("NoiseAffactAlpha", Range(0, 1)) = 0
        _GlowColor ("GlowColor", Color) = (0,0,0,0)
        _Clamp ("Clamp", Range(0, 1)) = 1
    }
    SubShader {
        Tags { "CanUseSpriteAtlas" = "true" "IGNOREPROJECTOR" = "true" "PreviewType" = "Plane" "QUEUE" = "Transparent" "RenderType" = "Transparent" }
        Pass {
            Name "Default"
            Tags { "CanUseSpriteAtlas" = "true" "IGNOREPROJECTOR" = "true" "PreviewType" = "Plane" "QUEUE" = "Transparent" "RenderType" = "Transparent" }
            Blend SrcAlpha OneMinusSrcAlpha, SrcAlpha OneMinusSrcAlpha
            ColorMask 0 0
            ZTest Off
            ZWrite Off
            Cull Off
            Stencil {
                ReadMask 0
                WriteMask 0
                Comp Disabled
                Pass Keep
                Fail Keep
                ZFail Keep
            }
            GpuProgramID 60067
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "UNITY_UI_ALPHACLIP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "UNITY_UI_CLIP_RECT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "UNITY_UI_ALPHACLIP" "UNITY_UI_CLIP_RECT" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "UNITY_UI_ALPHACLIP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "UNITY_UI_CLIP_RECT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "UNITY_UI_ALPHACLIP" "UNITY_UI_CLIP_RECT" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
CustomEditor "ASEMaterialInspector"
}