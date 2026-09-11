//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "SodaTeleporter" {
    Properties {
        _AlphaCutoff ("Alpha Cutoff ", Range(0, 1)) = 0.5
        _EmissionColor ("Emission Color", Color) = (1,1,1,1)
        _Tint ("Tint", Color) = (0,0,0,0)
        _DistortionStrength ("DistortionStrength", Float) = 0
        _Noise ("Noise", 2D) = "white" { }
        _VertexNoiseStrength ("VertexNoiseStrength", Float) = 0
        _EdgeColor ("EdgeColor", Color) = (0,0,0,0)
        _EdgePower ("EdgePower", Float) = 1
        _NoiseTileAndSpeed ("NoiseTileAndSpeed", Vector) = (0,0,0,0)
        _Smoothness ("Smoothness", Range(0, 1)) = 1
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
            GpuProgramID 13360
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "ShadowCaster"
            Tags { "LIGHTMODE" = "SHADOWCASTER" "QUEUE" = "Transparent" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Transparent" }
            ColorMask 0 0
            GpuProgramID 88341
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CASTING_PUNCTUAL_LIGHT_SHADOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_CASTING_PUNCTUAL_LIGHT_SHADOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_CASTING_PUNCTUAL_LIGHT_SHADOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_CASTING_PUNCTUAL_LIGHT_SHADOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_CASTING_PUNCTUAL_LIGHT_SHADOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_CASTING_PUNCTUAL_LIGHT_SHADOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_CASTING_PUNCTUAL_LIGHT_SHADOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_CASTING_PUNCTUAL_LIGHT_SHADOW" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CASTING_PUNCTUAL_LIGHT_SHADOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_CASTING_PUNCTUAL_LIGHT_SHADOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_CASTING_PUNCTUAL_LIGHT_SHADOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_CASTING_PUNCTUAL_LIGHT_SHADOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "_CASTING_PUNCTUAL_LIGHT_SHADOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "INSTANCING_ON" "_CASTING_PUNCTUAL_LIGHT_SHADOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "INSTANCING_ON" "_CASTING_PUNCTUAL_LIGHT_SHADOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "INSTANCING_ON" "_CASTING_PUNCTUAL_LIGHT_SHADOW" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
Fallback "Hidden/InternalErrorShader"
CustomEditor "UnityEditor.ShaderGraphLitGUI"
}