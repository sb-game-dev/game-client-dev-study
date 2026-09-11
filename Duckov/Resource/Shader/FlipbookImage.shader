//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "FlipbookImage" {
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
        _TotalTime ("TotalTime", Float) = 1
        _FlipbookTexture ("FlipbookTexture", 2D) = "white" { }
        [IntRange] _TotalCount ("TotalCount", Range(4, 64)) = 6
        [IntRange] _Row ("Row", Range(2, 8)) = 4
        [IntRange] _Column ("Column", Range(2, 8)) = 4
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
            GpuProgramID 26520
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