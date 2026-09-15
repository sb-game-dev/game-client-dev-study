//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "SmokeFireFX" {
    Properties {
        _AlphaCutoff ("Alpha Cutoff ", Range(0, 1)) = 0.5
        _MainTex ("MainTex", 2D) = "white" { }
        [RemapSliders] _EmiClampValue ("EmiClampValue", Vector) = (0,1,0,0)
        _EmissionColor ("EmissionColor", Color) = (0,0,0,1)
        _SoftDistance ("SoftDistance", Float) = 0
        _AlphaTint ("AlphaTint", Color) = (0,0,0,0)
        _Alpha ("Alpha", Range(0, 1)) = 0.4215889
        _ThermalColor ("ThermalColor", Color) = (0,0,0,1)
        [RemapSliders] _AlphaRemap ("AlphaRemap", Vector) = (0,1,0,0)
        _texcoord ("", 2D) = "white" { }
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
            GpuProgramID 20146
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_CLUSTERED_RENDERING" "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
Fallback "Hidden/InternalErrorShader"
CustomEditor "UnityEditor.ShaderGraphLitGUI"
}