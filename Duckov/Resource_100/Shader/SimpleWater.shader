//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "SimpleWater" {
    Properties {
        _EmissionColor ("Emission Color", Color) = (1,1,1,1)
        _AlphaCutoff ("Alpha Cutoff ", Range(0, 1)) = 0.5
        _ColorShallow ("ColorShallow", Color) = (0,0,0,0)
        _ColorDeep ("ColorDeep", Color) = (0,0,0,0)
        _EdgeColor ("EdgeColor", Color) = (0,0,0,0)
        _Smoothness ("Smoothness", Range(0, 1)) = 0
        _FadeDistance ("FadeDistance", Float) = 1
        _ColorBlendDistance ("ColorBlendDistance", Range(0, 5)) = 0.01
        _EdgeWidth ("EdgeWidth", Range(0, 0.5)) = 0.01
        _Noise ("Noise", 2D) = "white" { }
        _Wave1Normal ("Wave1Normal", 2D) = "bump" { }
        _Wave1Normal1 ("Wave1Normal", 2D) = "bump" { }
        _NoiseTileAndSpeed ("NoiseTileAndSpeed", Vector) = (0,0,0,0)
        _Wave1TileAndSpeed ("Wave1TileAndSpeed", Vector) = (0,0,0,0)
        _Wave2TileAndSpeed ("Wave2TileAndSpeed", Vector) = (0,0,0,0)
        _NoiseAffactDepthFade ("NoiseAffactDepthFade", Float) = 0
        _NoiseAffactWave1 ("NoiseAffactWave1", Float) = 0
        _NoiseAffactWave2 ("NoiseAffactWave2", Float) = 0
        _Normal1Strength ("Normal1Strength", Range(0, 1)) = 0.873248
        _Normal2Strength ("Normal2Strength", Range(0, 1)) = 0.873248
        _FadePower ("FadePower", Range(0.1, 10)) = 1
        _QueueOffset ("_QueueOffset", Float) = 0
        _QueueControl ("_QueueControl", Float) = -1
        unity_Lightmaps ("unity_Lightmaps", 2DArray) = "" { }
        unity_LightmapsInd ("unity_LightmapsInd", 2DArray) = "" { }
        unity_ShadowMasks ("unity_ShadowMasks", 2DArray) = "" { }
    }
    SubShader {
        Tags { "QUEUE" = "Transparent" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Transparent" }
        Pass {
            Name "Forward"
            Tags { "LIGHTMODE" = "UniversalForward" "QUEUE" = "Transparent" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Transparent" }
            Blend SrcAlpha OneMinusSrcAlpha, One OneMinusSrcAlpha
            ZWrite Off
            GpuProgramID 54303
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
Fallback "Hidden/InternalErrorShader"
CustomEditor "UnityEditor.ShaderGraphLitGUI"
}