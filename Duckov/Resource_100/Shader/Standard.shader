//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Standard" {
    Properties {
        _Color ("Color", Color) = (1,1,1,1)
        _MainTex ("Albedo", 2D) = "white" { }
        _Cutoff ("Alpha Cutoff", Range(0, 1)) = 0.5
        _Glossiness ("Smoothness", Range(0, 1)) = 0.5
        _GlossMapScale ("Smoothness Scale", Range(0, 1)) = 1
        [Enum(Metallic Alpha,0,Albedo Alpha,1)] _SmoothnessTextureChannel ("Smoothness texture channel", Float) = 0
        _Metallic ("Metallic", Range(0, 1)) = 0
        _MetallicGlossMap ("Metallic", 2D) = "white" { }
        [ToggleOff] _SpecularHighlights ("Specular Highlights", Float) = 1
        [ToggleOff] _GlossyReflections ("Glossy Reflections", Float) = 1
        _BumpScale ("Scale", Float) = 1
        _BumpMap ("Normal Map", 2D) = "bump" { }
        _Parallax ("Height Scale", Range(0.005, 0.08)) = 0.02
        _ParallaxMap ("Height Map", 2D) = "black" { }
        _OcclusionStrength ("Strength", Range(0, 1)) = 1
        _OcclusionMap ("Occlusion", 2D) = "white" { }
        _EmissionColor ("Color", Color) = (0,0,0,1)
        _EmissionMap ("Emission", 2D) = "white" { }
        _DetailMask ("Detail Mask", 2D) = "white" { }
        _DetailAlbedoMap ("Detail Albedo x2", 2D) = "grey" { }
        _DetailNormalMapScale ("Scale", Float) = 1
        _DetailNormalMap ("Normal Map", 2D) = "bump" { }
        [Enum(UV0,0,UV1,1)] _UVSec ("UV Set for secondary textures", Float) = 0
        _Mode ("__mode", Float) = 0
        _SrcBlend ("__src", Float) = 1
        _DstBlend ("__dst", Float) = 0
        _ZWrite ("__zw", Float) = 1
    }
    SubShader {
        LOD 300
        Tags { "PerformanceChecks" = "False" "RenderType" = "Opaque" }
        Pass {
            Name "FORWARD"
            LOD 300
            Tags { "LIGHTMODE" = "FORWARDBASE" "PerformanceChecks" = "False" "RenderType" = "Opaque" "SHADOWSUPPORT" = "true" }
            Blend Zero Zero, Zero Zero
            ZWrite Off
            GpuProgramID 3935
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "FORWARD_DELTA"
            LOD 300
            Tags { "LIGHTMODE" = "FORWARDADD" "PerformanceChecks" = "False" "RenderType" = "Opaque" "SHADOWSUPPORT" = "true" }
            Blend Zero One, Zero One
            ZWrite Off
            GpuProgramID 83234
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    Keywords { "POINT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT_COOKIE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT_COOKIE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT_COOKIE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_DEPTH" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_DEPTH" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_DEPTH" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_DEPTH" "SHADOWS_SOFT" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_DEPTH" "SHADOWS_SOFT" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_DEPTH" "SHADOWS_SOFT" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT" "SHADOWS_CUBE" "SHADOWS_SOFT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT" "SHADOWS_CUBE" "SHADOWS_SOFT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT" "SHADOWS_CUBE" "SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT_COOKIE" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT_COOKIE" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT_COOKIE" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT_COOKIE" "SHADOWS_CUBE" "SHADOWS_SOFT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT_COOKIE" "SHADOWS_CUBE" "SHADOWS_SOFT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT_COOKIE" "SHADOWS_CUBE" "SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT_COOKIE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT_COOKIE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT_COOKIE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_LINEAR" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_LINEAR" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_LINEAR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "SHADOWS_DEPTH" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "SHADOWS_DEPTH" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "SHADOWS_DEPTH" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "SHADOWS_DEPTH" "SHADOWS_SOFT" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "SHADOWS_DEPTH" "SHADOWS_SOFT" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "SHADOWS_DEPTH" "SHADOWS_SOFT" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_LINEAR" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_LINEAR" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_LINEAR" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT" "SHADOWS_CUBE" "SHADOWS_SOFT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT" "SHADOWS_CUBE" "SHADOWS_SOFT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT" "SHADOWS_CUBE" "SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT_COOKIE" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT_COOKIE" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT_COOKIE" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT_COOKIE" "SHADOWS_CUBE" "SHADOWS_SOFT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT_COOKIE" "SHADOWS_CUBE" "SHADOWS_SOFT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT_COOKIE" "SHADOWS_CUBE" "SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT_COOKIE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT_COOKIE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT_COOKIE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "SHADOWS_DEPTH" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "SHADOWS_DEPTH" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "SHADOWS_DEPTH" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "SHADOWS_DEPTH" "SHADOWS_SOFT" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "SHADOWS_DEPTH" "SHADOWS_SOFT" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "SHADOWS_DEPTH" "SHADOWS_SOFT" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT" "SHADOWS_CUBE" "SHADOWS_SOFT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT" "SHADOWS_CUBE" "SHADOWS_SOFT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT" "SHADOWS_CUBE" "SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT_COOKIE" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT_COOKIE" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT_COOKIE" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT_COOKIE" "SHADOWS_CUBE" "SHADOWS_SOFT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT_COOKIE" "SHADOWS_CUBE" "SHADOWS_SOFT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT_COOKIE" "SHADOWS_CUBE" "SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT_COOKIE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT_COOKIE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT_COOKIE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP2" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP2" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "SHADOWS_DEPTH" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "SHADOWS_DEPTH" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "SHADOWS_DEPTH" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "SHADOWS_DEPTH" "SHADOWS_SOFT" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "SHADOWS_DEPTH" "SHADOWS_SOFT" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "SHADOWS_DEPTH" "SHADOWS_SOFT" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP2" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP2" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP2" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT" "SHADOWS_CUBE" "SHADOWS_SOFT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT" "SHADOWS_CUBE" "SHADOWS_SOFT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT" "SHADOWS_CUBE" "SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT_COOKIE" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT_COOKIE" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT_COOKIE" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT_COOKIE" "SHADOWS_CUBE" "SHADOWS_SOFT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT_COOKIE" "SHADOWS_CUBE" "SHADOWS_SOFT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT_COOKIE" "SHADOWS_CUBE" "SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "POINT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT_COOKIE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT_COOKIE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT_COOKIE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_DEPTH" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_DEPTH" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_DEPTH" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_DEPTH" "SHADOWS_SOFT" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_DEPTH" "SHADOWS_SOFT" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_DEPTH" "SHADOWS_SOFT" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT" "SHADOWS_CUBE" "SHADOWS_SOFT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT" "SHADOWS_CUBE" "SHADOWS_SOFT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT" "SHADOWS_CUBE" "SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT_COOKIE" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT_COOKIE" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT_COOKIE" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT_COOKIE" "SHADOWS_CUBE" "SHADOWS_SOFT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT_COOKIE" "SHADOWS_CUBE" "SHADOWS_SOFT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT_COOKIE" "SHADOWS_CUBE" "SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT_COOKIE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT_COOKIE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT_COOKIE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_LINEAR" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_LINEAR" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_LINEAR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "SHADOWS_DEPTH" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "SHADOWS_DEPTH" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "SHADOWS_DEPTH" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "SHADOWS_DEPTH" "SHADOWS_SOFT" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "SHADOWS_DEPTH" "SHADOWS_SOFT" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "SHADOWS_DEPTH" "SHADOWS_SOFT" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_LINEAR" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_LINEAR" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_LINEAR" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT" "SHADOWS_CUBE" "SHADOWS_SOFT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT" "SHADOWS_CUBE" "SHADOWS_SOFT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT" "SHADOWS_CUBE" "SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT_COOKIE" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT_COOKIE" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT_COOKIE" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT_COOKIE" "SHADOWS_CUBE" "SHADOWS_SOFT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT_COOKIE" "SHADOWS_CUBE" "SHADOWS_SOFT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT_COOKIE" "SHADOWS_CUBE" "SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT_COOKIE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT_COOKIE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT_COOKIE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "SHADOWS_DEPTH" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "SHADOWS_DEPTH" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "SHADOWS_DEPTH" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "SHADOWS_DEPTH" "SHADOWS_SOFT" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "SHADOWS_DEPTH" "SHADOWS_SOFT" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "SHADOWS_DEPTH" "SHADOWS_SOFT" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT" "SHADOWS_CUBE" "SHADOWS_SOFT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT" "SHADOWS_CUBE" "SHADOWS_SOFT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT" "SHADOWS_CUBE" "SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT_COOKIE" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT_COOKIE" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT_COOKIE" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT_COOKIE" "SHADOWS_CUBE" "SHADOWS_SOFT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT_COOKIE" "SHADOWS_CUBE" "SHADOWS_SOFT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT_COOKIE" "SHADOWS_CUBE" "SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT_COOKIE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT_COOKIE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT_COOKIE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP2" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP2" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "SHADOWS_DEPTH" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "SHADOWS_DEPTH" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "SHADOWS_DEPTH" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "SHADOWS_DEPTH" "SHADOWS_SOFT" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "SHADOWS_DEPTH" "SHADOWS_SOFT" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "SHADOWS_DEPTH" "SHADOWS_SOFT" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP2" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP2" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP2" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT" "SHADOWS_CUBE" "SHADOWS_SOFT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT" "SHADOWS_CUBE" "SHADOWS_SOFT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT" "SHADOWS_CUBE" "SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT_COOKIE" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT_COOKIE" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT_COOKIE" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT_COOKIE" "SHADOWS_CUBE" "SHADOWS_SOFT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT_COOKIE" "SHADOWS_CUBE" "SHADOWS_SOFT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT_COOKIE" "SHADOWS_CUBE" "SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "ShadowCaster"
            LOD 300
            Tags { "LIGHTMODE" = "SHADOWCASTER" "PerformanceChecks" = "False" "RenderType" = "Opaque" "SHADOWSUPPORT" = "true" }
            GpuProgramID 143605
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_DEPTH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_DEPTH" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_DEPTH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_DEPTH" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "DEFERRED"
            LOD 300
            Tags { "LIGHTMODE" = "DEFERRED" "PerformanceChecks" = "False" "RenderType" = "Opaque" }
            GpuProgramID 257049
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LIGHTPROBE_SH" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LIGHTPROBE_SH" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LIGHTPROBE_SH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "UNITY_HDR_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "UNITY_HDR_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "UNITY_HDR_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LIGHTPROBE_SH" "UNITY_HDR_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LIGHTPROBE_SH" "UNITY_HDR_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LIGHTPROBE_SH" "UNITY_HDR_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LIGHTPROBE_SH" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LIGHTPROBE_SH" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LIGHTPROBE_SH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "UNITY_HDR_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "UNITY_HDR_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "UNITY_HDR_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LIGHTPROBE_SH" "UNITY_HDR_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LIGHTPROBE_SH" "UNITY_HDR_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LIGHTPROBE_SH" "UNITY_HDR_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
    SubShader {
        LOD 150
        Tags { "PerformanceChecks" = "False" "RenderType" = "Opaque" }
        Pass {
            Name "FORWARD"
            LOD 150
            Tags { "LIGHTMODE" = "FORWARDBASE" "PerformanceChecks" = "False" "RenderType" = "Opaque" "SHADOWSUPPORT" = "true" }
            Blend Zero Zero, Zero Zero
            ZWrite Off
            GpuProgramID 343811
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "VERTEXLIGHT_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "LIGHTPROBE_SH" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "LIGHTPROBE_SH" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "LIGHTPROBE_SH" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "LIGHTPROBE_SH" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "FORWARD_DELTA"
            LOD 150
            Tags { "LIGHTMODE" = "FORWARDADD" "PerformanceChecks" = "False" "RenderType" = "Opaque" "SHADOWSUPPORT" = "true" }
            Blend Zero One, Zero One
            ZWrite Off
            GpuProgramID 428635
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    Keywords { "POINT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT_COOKIE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT_COOKIE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT_COOKIE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_DEPTH" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_DEPTH" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_DEPTH" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT_COOKIE" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT_COOKIE" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT_COOKIE" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT_COOKIE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT_COOKIE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT_COOKIE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_LINEAR" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_LINEAR" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_LINEAR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "SHADOWS_DEPTH" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "SHADOWS_DEPTH" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "SHADOWS_DEPTH" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_LINEAR" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_LINEAR" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_LINEAR" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT_COOKIE" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT_COOKIE" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT_COOKIE" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT_COOKIE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT_COOKIE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT_COOKIE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "SHADOWS_DEPTH" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "SHADOWS_DEPTH" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "SHADOWS_DEPTH" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT_COOKIE" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT_COOKIE" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT_COOKIE" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT_COOKIE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT_COOKIE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT_COOKIE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP2" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP2" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "SHADOWS_DEPTH" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "SHADOWS_DEPTH" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "SHADOWS_DEPTH" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP2" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP2" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP2" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT_COOKIE" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT_COOKIE" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT_COOKIE" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "POINT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT_COOKIE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT_COOKIE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT_COOKIE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_DEPTH" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_DEPTH" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_DEPTH" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT_COOKIE" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT_COOKIE" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT_COOKIE" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "POINT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT_COOKIE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT_COOKIE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT_COOKIE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_LINEAR" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_LINEAR" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_LINEAR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "SHADOWS_DEPTH" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "SHADOWS_DEPTH" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "SHADOWS_DEPTH" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_LINEAR" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_LINEAR" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_LINEAR" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_LINEAR" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT_COOKIE" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT_COOKIE" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT_COOKIE" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "POINT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT_COOKIE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT_COOKIE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT_COOKIE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "SHADOWS_DEPTH" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "SHADOWS_DEPTH" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "SHADOWS_DEPTH" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT_COOKIE" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT_COOKIE" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT_COOKIE" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "POINT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT_COOKIE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT_COOKIE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT_COOKIE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP2" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP2" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "SHADOWS_DEPTH" "SPOT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "SHADOWS_DEPTH" "SPOT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "SHADOWS_DEPTH" "SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL" "FOG_EXP2" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP2" "SHADOWS_SCREEN" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP2" "SHADOWS_SCREEN" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DIRECTIONAL_COOKIE" "FOG_EXP2" "SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT_COOKIE" "SHADOWS_CUBE" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT_COOKIE" "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT_COOKIE" "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "POINT" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "ShadowCaster"
            LOD 150
            Tags { "LIGHTMODE" = "SHADOWCASTER" "PerformanceChecks" = "False" "RenderType" = "Opaque" "SHADOWSUPPORT" = "true" }
            GpuProgramID 507809
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_DEPTH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_DEPTH" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_DEPTH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_CUBE" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_CUBE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "SHADOWS_DEPTH" "_ALPHAPREMULTIPLY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
Fallback "VertexLit"
CustomEditor "StandardShaderGUI"
}