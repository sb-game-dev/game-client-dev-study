//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Universal Render Pipeline/Unlit" {
    Properties {
        _BaseMap ("Texture", 2D) = "white" { }
        _BaseColor ("Color", Color) = (1,1,1,1)
        _Cutoff ("AlphaCutout", Range(0, 1)) = 0.5
        _Surface ("__surface", Float) = 0
        _Blend ("__mode", Float) = 0
        _Cull ("__cull", Float) = 2
        [ToggleUI] _AlphaClip ("__clip", Float) = 0
        _BlendOp ("__blendop", Float) = 0
        _SrcBlend ("__src", Float) = 1
        _DstBlend ("__dst", Float) = 0
        _SrcBlendAlpha ("__srcA", Float) = 1
        _DstBlendAlpha ("__dstA", Float) = 0
        _ZWrite ("__zw", Float) = 1
        _AlphaToMask ("__alphaToMask", Float) = 0
        _QueueOffset ("Queue offset", Float) = 0
        _MainTex ("BaseMap", 2D) = "white" { }
        _Color ("Base Color", Color) = (0.5,0.5,0.5,1)
        _SampleGI ("SampleGI", Float) = 0
    }
    SubShader {
        LOD 100
        Tags { "IGNOREPROJECTOR" = "true" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" "UniversalMaterialType" = "Unlit" }
        Pass {
            Name "Unlit"
            LOD 100
            Tags { "IGNOREPROJECTOR" = "true" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" "UniversalMaterialType" = "Unlit" }
            Blend Zero Zero, Zero Zero
            ZWrite Off
            Cull Off
            GpuProgramID 15958
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "LOD_FADE_CROSSFADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "LOD_FADE_CROSSFADE" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "LOD_FADE_CROSSFADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "LOD_FADE_CROSSFADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "LOD_FADE_CROSSFADE" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "LOD_FADE_CROSSFADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "LOD_FADE_CROSSFADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "LOD_FADE_CROSSFADE" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "LOD_FADE_CROSSFADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_DBUFFER_MRT3" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_DBUFFER_MRT3" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_DBUFFER_MRT3" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_DBUFFER_MRT3" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_DBUFFER_MRT3" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_DBUFFER_MRT3" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_DBUFFER_MRT3" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "GBuffer"
            LOD 100
            Tags { "IGNOREPROJECTOR" = "true" "LIGHTMODE" = "UniversalGBuffer" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" "UniversalMaterialType" = "Unlit" }
            Blend Zero Zero, Zero Zero
            ZWrite Off
            Cull Off
            GpuProgramID 102882
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
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "DepthOnly"
            LOD 100
            Tags { "IGNOREPROJECTOR" = "true" "LIGHTMODE" = "DepthOnly" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" "UniversalMaterialType" = "Unlit" }
            Blend Zero Zero, Zero Zero
            ColorMask B 0
            Cull Off
            GpuProgramID 169475
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
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "DepthNormalsOnly"
            LOD 100
            Tags { "IGNOREPROJECTOR" = "true" "LIGHTMODE" = "DepthNormalsOnly" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" "UniversalMaterialType" = "Unlit" }
            Blend Zero Zero, Zero Zero
            Cull Off
            GpuProgramID 234658
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
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
Fallback "Hidden/Universal Render Pipeline/FallbackError"
CustomEditor "UnityEditor.Rendering.Universal.ShaderGUI.UnlitShader"
}