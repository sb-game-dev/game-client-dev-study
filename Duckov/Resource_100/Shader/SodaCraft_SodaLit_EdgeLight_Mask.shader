//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "SodaCraft/SodaLit_EdgeLight_Mask" {
    Properties {
        _AlphaCutoff ("Alpha Cutoff ", Range(0, 1)) = 0.5
        _MainTex ("MainTex", 2D) = "white" { }
        _Tint ("Tint", Color) = (1,1,1,1)
        _NormalMap ("NormalMap", 2D) = "bump" { }
        _NormalScale ("NormalScale", Float) = 1
        _MetallicSmoothness ("MetallicSmoothness", 2D) = "white" { }
        _Metallic ("Metallic", Range(0, 1)) = 0
        _Smoothness ("Smoothness", Range(0, 1)) = 0
        _EmissionMap ("EmissionMap", 2D) = "white" { }
        _EmissionColor ("EmissionColor", Color) = (0,0,0,0)
        _EdgeLightPower ("EdgeLightPower", Range(0.1, 10)) = 0.1
        _EdgeLightColor ("EdgeLightColor", Color) = (0,0,0,0)
        _EdgeLightShadow ("EdgeLightShadow", Range(0, 1)) = 0
        _Noise ("Noise", 2D) = "gray" { }
        _WindNoiseTileAndSpeed ("WindNoiseTileAndSpeed", Vector) = (1,1,0,0)
        _WindNoiseStrength ("WindNoiseStrength", Float) = 0
        _IgnoreVertexColor ("IgnoreVertexColor", Range(0, 1)) = 0
        _IgnoreMask ("IgnoreMask", Range(0, 1)) = 0
        _texcoord ("", 2D) = "white" { }
        _QueueOffset ("_QueueOffset", Float) = 0
        _QueueControl ("_QueueControl", Float) = -1
        unity_Lightmaps ("unity_Lightmaps", 2DArray) = "" { }
        unity_LightmapsInd ("unity_LightmapsInd", 2DArray) = "" { }
        unity_ShadowMasks ("unity_ShadowMasks", 2DArray) = "" { }
    }
    SubShader {
        Tags { "QUEUE" = "AlphaTest" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
        Pass {
            Name "ShadowCaster"
            Tags { "LIGHTMODE" = "SHADOWCASTER" "QUEUE" = "AlphaTest" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ColorMask 0 0
            Cull Off
            GpuProgramID 51826
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CASTING_PUNCTUAL_LIGHT_SHADOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_CASTING_PUNCTUAL_LIGHT_SHADOW" }
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
                    Keywords { "LOD_FADE_CROSSFADE" "_CASTING_PUNCTUAL_LIGHT_SHADOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_CASTING_PUNCTUAL_LIGHT_SHADOW" }
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
                    Keywords { "_CASTING_PUNCTUAL_LIGHT_SHADOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_CASTING_PUNCTUAL_LIGHT_SHADOW" }
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
                    Keywords { "LOD_FADE_CROSSFADE" "_CASTING_PUNCTUAL_LIGHT_SHADOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_CASTING_PUNCTUAL_LIGHT_SHADOW" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "DepthOnly"
            Tags { "LIGHTMODE" = "DepthOnly" "QUEUE" = "AlphaTest" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ColorMask 0 0
            Cull Off
            GpuProgramID 92118
            PlayerProgram "vp" {
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
            Name "DepthNormals"
            Tags { "LIGHTMODE" = "DepthNormals" "QUEUE" = "AlphaTest" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            Cull Off
            GpuProgramID 184404
            PlayerProgram "vp" {
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
            Name "GBuffer"
            Tags { "LIGHTMODE" = "UniversalGBuffer" "QUEUE" = "AlphaTest" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            Cull Off
            GpuProgramID 224367
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
Fallback "Hidden/InternalErrorShader"
CustomEditor "UnityEditor.ShaderGraphLitGUI"
}