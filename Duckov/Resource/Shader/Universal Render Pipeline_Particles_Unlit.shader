//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Universal Render Pipeline/Particles/Unlit" {
    Properties {
        _BaseMap ("Base Map", 2D) = "white" { }
        _BaseColor ("Base Color", Color) = (1,1,1,1)
        _Cutoff ("Alpha Cutoff", Range(0, 1)) = 0.5
        _BumpMap ("Normal Map", 2D) = "bump" { }
        _EmissionColor ("Color", Color) = (0,0,0,1)
        _EmissionMap ("Emission", 2D) = "white" { }
        _SoftParticlesNearFadeDistance ("Soft Particles Near Fade", Float) = 0
        _SoftParticlesFarFadeDistance ("Soft Particles Far Fade", Float) = 1
        _CameraNearFadeDistance ("Camera Near Fade", Float) = 1
        _CameraFarFadeDistance ("Camera Far Fade", Float) = 2
        _DistortionBlend ("Distortion Blend", Range(0, 1)) = 0.5
        _DistortionStrength ("Distortion Strength", Float) = 1
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
        _ColorMode ("_ColorMode", Float) = 0
        _BaseColorAddSubDiff ("_ColorMode", Vector) = (0,0,0,0)
        [ToggleOff] _FlipbookBlending ("__flipbookblending", Float) = 0
        [ToggleUI] _SoftParticlesEnabled ("__softparticlesenabled", Float) = 0
        [ToggleUI] _CameraFadingEnabled ("__camerafadingenabled", Float) = 0
        [ToggleUI] _DistortionEnabled ("__distortionenabled", Float) = 0
        _SoftParticleFadeParams ("__softparticlefadeparams", Vector) = (0,0,0,0)
        _CameraFadeParams ("__camerafadeparams", Vector) = (0,0,0,0)
        _DistortionStrengthScaled ("Distortion Strength Scaled", Float) = 0.1
        _QueueOffset ("Queue offset", Float) = 0
        _FlipbookMode ("flipbook", Float) = 0
        _Mode ("mode", Float) = 0
        _Color ("color", Color) = (1,1,1,1)
    }
    SubShader {
        Tags { "IGNOREPROJECTOR" = "true" "PerformanceChecks" = "False" "PreviewType" = "Plane" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
        Pass {
            Name "ForwardLit"
            Tags { "IGNOREPROJECTOR" = "true" "PerformanceChecks" = "False" "PreviewType" = "Plane" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            Blend Zero Zero, Zero Zero
            ZWrite Off
            Cull Off
            GpuProgramID 54169
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_FLIPBOOKBLENDING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_FADING_ON" "_SOFTPARTICLES_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_FADING_ON" "_FLIPBOOKBLENDING_ON" "_SOFTPARTICLES_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" "_FLIPBOOKBLENDING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" "_FADING_ON" "_SOFTPARTICLES_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" "_FADING_ON" "_FLIPBOOKBLENDING_ON" "_SOFTPARTICLES_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_FLIPBOOKBLENDING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_FADING_ON" "_SOFTPARTICLES_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_FADING_ON" "_FLIPBOOKBLENDING_ON" "_SOFTPARTICLES_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "PROCEDURAL_INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "PROCEDURAL_INSTANCING_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "PROCEDURAL_INSTANCING_ON" "_FLIPBOOKBLENDING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "PROCEDURAL_INSTANCING_ON" "_FADING_ON" "_SOFTPARTICLES_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "PROCEDURAL_INSTANCING_ON" "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "PROCEDURAL_INSTANCING_ON" "_FADING_ON" "_FLIPBOOKBLENDING_ON" "_SOFTPARTICLES_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_FLIPBOOKBLENDING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_FADING_ON" "_SOFTPARTICLES_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_FADING_ON" "_FLIPBOOKBLENDING_ON" "_SOFTPARTICLES_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "PROCEDURAL_INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "PROCEDURAL_INSTANCING_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "PROCEDURAL_INSTANCING_ON" "_FLIPBOOKBLENDING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "PROCEDURAL_INSTANCING_ON" "_FADING_ON" "_SOFTPARTICLES_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "PROCEDURAL_INSTANCING_ON" "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "PROCEDURAL_INSTANCING_ON" "_FADING_ON" "_FLIPBOOKBLENDING_ON" "_SOFTPARTICLES_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_FLIPBOOKBLENDING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_FADING_ON" "_SOFTPARTICLES_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_FADING_ON" "_FLIPBOOKBLENDING_ON" "_SOFTPARTICLES_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "PROCEDURAL_INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "PROCEDURAL_INSTANCING_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "PROCEDURAL_INSTANCING_ON" "_FLIPBOOKBLENDING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "PROCEDURAL_INSTANCING_ON" "_FADING_ON" "_SOFTPARTICLES_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "PROCEDURAL_INSTANCING_ON" "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "PROCEDURAL_INSTANCING_ON" "_FADING_ON" "_FLIPBOOKBLENDING_ON" "_SOFTPARTICLES_ON" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_EMISSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ALPHATEST_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_NORMALMAP" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_FADING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_FADING_ON" "_FLIPBOOKBLENDING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_EMISSION" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_EMISSION" "_FLIPBOOKBLENDING_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_EMISSION" "_FADING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_EMISSION" "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_EMISSION" "_FADING_ON" "_FLIPBOOKBLENDING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ALPHATEST_ON" "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ALPHAPREMULTIPLY_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ALPHAPREMULTIPLY_ON" "_NORMALMAP" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ALPHAPREMULTIPLY_ON" "_FADING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_COLOROVERLAY_ON" "_EMISSION" "_FLIPBOOKBLENDING_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" "_EMISSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" "_ALPHATEST_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" "_NORMALMAP" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" "_FADING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" "_FADING_ON" "_FLIPBOOKBLENDING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" "_EMISSION" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" "_EMISSION" "_FLIPBOOKBLENDING_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" "_EMISSION" "_FADING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" "_EMISSION" "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" "_EMISSION" "_FADING_ON" "_FLIPBOOKBLENDING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" "_ALPHATEST_ON" "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" "_ALPHAPREMULTIPLY_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" "_ALPHAPREMULTIPLY_ON" "_NORMALMAP" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" "_ALPHAPREMULTIPLY_ON" "_FADING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" "_COLOROVERLAY_ON" "_EMISSION" "_FLIPBOOKBLENDING_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_EMISSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ALPHATEST_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_NORMALMAP" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_FADING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_FADING_ON" "_FLIPBOOKBLENDING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_EMISSION" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_EMISSION" "_FLIPBOOKBLENDING_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_EMISSION" "_FADING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_EMISSION" "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_EMISSION" "_FADING_ON" "_FLIPBOOKBLENDING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ALPHATEST_ON" "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ALPHAPREMULTIPLY_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ALPHAPREMULTIPLY_ON" "_NORMALMAP" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ALPHAPREMULTIPLY_ON" "_FADING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_COLOROVERLAY_ON" "_EMISSION" "_FLIPBOOKBLENDING_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "PROCEDURAL_INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "PROCEDURAL_INSTANCING_ON" "_EMISSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "PROCEDURAL_INSTANCING_ON" "_ALPHATEST_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "PROCEDURAL_INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "PROCEDURAL_INSTANCING_ON" "_NORMALMAP" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "PROCEDURAL_INSTANCING_ON" "_FADING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "PROCEDURAL_INSTANCING_ON" "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "PROCEDURAL_INSTANCING_ON" "_FADING_ON" "_FLIPBOOKBLENDING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "PROCEDURAL_INSTANCING_ON" "_EMISSION" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "PROCEDURAL_INSTANCING_ON" "_EMISSION" "_FLIPBOOKBLENDING_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "PROCEDURAL_INSTANCING_ON" "_EMISSION" "_FADING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "PROCEDURAL_INSTANCING_ON" "_EMISSION" "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "PROCEDURAL_INSTANCING_ON" "_EMISSION" "_FADING_ON" "_FLIPBOOKBLENDING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "PROCEDURAL_INSTANCING_ON" "_ALPHATEST_ON" "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "PROCEDURAL_INSTANCING_ON" "_ALPHAPREMULTIPLY_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "PROCEDURAL_INSTANCING_ON" "_ALPHAPREMULTIPLY_ON" "_NORMALMAP" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "PROCEDURAL_INSTANCING_ON" "_ALPHAPREMULTIPLY_ON" "_FADING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "PROCEDURAL_INSTANCING_ON" "_COLOROVERLAY_ON" "_EMISSION" "_FLIPBOOKBLENDING_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_EMISSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ALPHATEST_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_NORMALMAP" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_FADING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_FADING_ON" "_FLIPBOOKBLENDING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_EMISSION" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_EMISSION" "_FLIPBOOKBLENDING_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_EMISSION" "_FADING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_EMISSION" "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_EMISSION" "_FADING_ON" "_FLIPBOOKBLENDING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ALPHATEST_ON" "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ALPHAPREMULTIPLY_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ALPHAPREMULTIPLY_ON" "_NORMALMAP" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ALPHAPREMULTIPLY_ON" "_FADING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_COLOROVERLAY_ON" "_EMISSION" "_FLIPBOOKBLENDING_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "PROCEDURAL_INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "PROCEDURAL_INSTANCING_ON" "_EMISSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "PROCEDURAL_INSTANCING_ON" "_ALPHATEST_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "PROCEDURAL_INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "PROCEDURAL_INSTANCING_ON" "_NORMALMAP" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "PROCEDURAL_INSTANCING_ON" "_FADING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "PROCEDURAL_INSTANCING_ON" "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "PROCEDURAL_INSTANCING_ON" "_FADING_ON" "_FLIPBOOKBLENDING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "PROCEDURAL_INSTANCING_ON" "_EMISSION" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "PROCEDURAL_INSTANCING_ON" "_EMISSION" "_FLIPBOOKBLENDING_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "PROCEDURAL_INSTANCING_ON" "_EMISSION" "_FADING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "PROCEDURAL_INSTANCING_ON" "_EMISSION" "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "PROCEDURAL_INSTANCING_ON" "_EMISSION" "_FADING_ON" "_FLIPBOOKBLENDING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "PROCEDURAL_INSTANCING_ON" "_ALPHATEST_ON" "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "PROCEDURAL_INSTANCING_ON" "_ALPHAPREMULTIPLY_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "PROCEDURAL_INSTANCING_ON" "_ALPHAPREMULTIPLY_ON" "_NORMALMAP" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "PROCEDURAL_INSTANCING_ON" "_ALPHAPREMULTIPLY_ON" "_FADING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "PROCEDURAL_INSTANCING_ON" "_COLOROVERLAY_ON" "_EMISSION" "_FLIPBOOKBLENDING_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_EMISSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ALPHATEST_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_NORMALMAP" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_FADING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_FADING_ON" "_FLIPBOOKBLENDING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_EMISSION" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_EMISSION" "_FLIPBOOKBLENDING_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_EMISSION" "_FADING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_EMISSION" "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_EMISSION" "_FADING_ON" "_FLIPBOOKBLENDING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ALPHATEST_ON" "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ALPHAPREMULTIPLY_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ALPHAPREMULTIPLY_ON" "_NORMALMAP" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ALPHAPREMULTIPLY_ON" "_FADING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_COLOROVERLAY_ON" "_EMISSION" "_FLIPBOOKBLENDING_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "PROCEDURAL_INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "PROCEDURAL_INSTANCING_ON" "_EMISSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "PROCEDURAL_INSTANCING_ON" "_ALPHATEST_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "PROCEDURAL_INSTANCING_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "PROCEDURAL_INSTANCING_ON" "_NORMALMAP" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "PROCEDURAL_INSTANCING_ON" "_FADING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "PROCEDURAL_INSTANCING_ON" "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "PROCEDURAL_INSTANCING_ON" "_FADING_ON" "_FLIPBOOKBLENDING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "PROCEDURAL_INSTANCING_ON" "_EMISSION" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "PROCEDURAL_INSTANCING_ON" "_EMISSION" "_FLIPBOOKBLENDING_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "PROCEDURAL_INSTANCING_ON" "_EMISSION" "_FADING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "PROCEDURAL_INSTANCING_ON" "_EMISSION" "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "PROCEDURAL_INSTANCING_ON" "_EMISSION" "_FADING_ON" "_FLIPBOOKBLENDING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "PROCEDURAL_INSTANCING_ON" "_ALPHATEST_ON" "_FADING_ON" "_NORMALMAP" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "PROCEDURAL_INSTANCING_ON" "_ALPHAPREMULTIPLY_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "PROCEDURAL_INSTANCING_ON" "_ALPHAPREMULTIPLY_ON" "_NORMALMAP" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "PROCEDURAL_INSTANCING_ON" "_ALPHAPREMULTIPLY_ON" "_FADING_ON" "_SOFTPARTICLES_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "PROCEDURAL_INSTANCING_ON" "_COLOROVERLAY_ON" "_EMISSION" "_FLIPBOOKBLENDING_ON" "_SURFACE_TYPE_TRANSPARENT" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "DepthOnly"
            Tags { "IGNOREPROJECTOR" = "true" "LIGHTMODE" = "DepthOnly" "PerformanceChecks" = "False" "PreviewType" = "Plane" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ColorMask B 0
            Cull Off
            GpuProgramID 104203
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_FLIPBOOKBLENDING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ALPHATEST_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" "_FLIPBOOKBLENDING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" "_ALPHATEST_ON" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_FLIPBOOKBLENDING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ALPHATEST_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_COLOROVERLAY_ON" "_FLIPBOOKBLENDING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" "_FLIPBOOKBLENDING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" "_ALPHATEST_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "PROCEDURAL_INSTANCING_ON" "_COLOROVERLAY_ON" "_FLIPBOOKBLENDING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "DepthNormalsOnly"
            Tags { "IGNOREPROJECTOR" = "true" "LIGHTMODE" = "DepthNormalsOnly" "PerformanceChecks" = "False" "PreviewType" = "Plane" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            Cull Off
            GpuProgramID 162173
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ALPHATEST_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ALPHATEST_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ALPHATEST_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ALPHATEST_ON" "_NORMALMAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_COLOROVERLAY_ON" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
Fallback "Hidden/Universal Render Pipeline/FallbackError"
CustomEditor "UnityEditor.Rendering.Universal.ShaderGUI.ParticlesUnlitShader"
}