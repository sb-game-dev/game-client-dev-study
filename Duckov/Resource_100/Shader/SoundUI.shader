//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "SoundUI" {
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
        _NoiseTile ("NoiseTile", Float) = 1
        _StrengthNoiseTile ("StrengthNoiseTile", Float) = 1
        _Noise ("Noise", 2D) = "white" { }
        _StrengthNoise ("StrengthNoise", 2D) = "white" { }
        _NoiseSpeed2 ("NoiseSpeed2", Vector) = (0,0,0,0)
        _NoiseOffsetMin ("NoiseOffsetMin", Range(0, 1)) = 0
        _NoiseOffsetMax ("NoiseOffsetMax", Range(0, 1)) = 0
        _Mask ("Mask", 2D) = "white" { }
        _NoiseSpeed ("NoiseSpeed", Float) = 10
        _GlowColor ("GlowColor", Color) = (0,0,0,0)
        [RemapSliders] _GlowClamp ("GlowClamp", Vector) = (0,1,0,0)
        _GlowPower ("GlowPower", Float) = 3
        _GlowStrength ("GlowStrength", Range(0, 1)) = 0.05
        _DotColor ("DotColor", Color) = (0,0,0,0)
        _TotalAlpha ("TotalAlpha", Range(0, 1)) = 0
        _texcoord ("", 2D) = "white" { }
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
            GpuProgramID 59112
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