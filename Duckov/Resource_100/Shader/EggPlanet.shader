//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "EggPlanet" {
    Properties {
        _EmissionColor ("Emission Color", Color) = (1,1,1,1)
        _AlphaCutoff ("Alpha Cutoff ", Range(0, 1)) = 0.5
        _Noise1 ("Noise1", 2D) = "white" { }
        _Noise2 ("Noise2", 2D) = "white" { }
        _Normal1 ("Normal1", 2D) = "bump" { }
        _Normal2 ("Normal2", 2D) = "bump" { }
        _NoiseNormalStrength ("NoiseNormalStrength", Float) = 1
        _TilingOffset1 ("Tiling&Offset1", Vector) = (1,1,0,0)
        _TilingOffset2 ("Tiling&Offset1", Vector) = (1,1,0,0)
        _Strength1 ("Strength1", Range(0, 1)) = 0
        _Strength2 ("Strength2", Range(0, 1)) = 0
        _WaterColor ("WaterColor", Color) = (0,0,0,0)
        _BaseColor ("BaseColor", Color) = (0,0,0,0)
        _LevelFade ("LevelFade", Range(0, 0.1)) = 0
        _WaterLevel ("WaterLevel", Range(0, 1)) = 0
        _VertexHeight ("VertexHeight", Float) = 0
        _WaterSmooth ("WaterSmooth", Range(0, 1)) = 0.4891304
        _GroundSmooth ("GroundSmooth", Range(0, 1)) = 0.4891304
        _GroundTexture ("GroundTexture", 2D) = "white" { }
        _texcoord ("", 2D) = "white" { }
        _QueueOffset ("_QueueOffset", Float) = 0
        _QueueControl ("_QueueControl", Float) = -1
        unity_Lightmaps ("unity_Lightmaps", 2DArray) = "" { }
        unity_LightmapsInd ("unity_LightmapsInd", 2DArray) = "" { }
        unity_ShadowMasks ("unity_ShadowMasks", 2DArray) = "" { }
    }
    SubShader {
        Tags { "QUEUE" = "Geometry" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
        Pass {
            Name "ShadowCaster"
            Tags { "LIGHTMODE" = "SHADOWCASTER" "QUEUE" = "Geometry" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ColorMask 0 0
            GpuProgramID 10093
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CASTING_PUNCTUAL_LIGHT_SHADOW" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CASTING_PUNCTUAL_LIGHT_SHADOW" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "DepthOnly"
            Tags { "LIGHTMODE" = "DepthOnly" "QUEUE" = "Geometry" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ColorMask 0 0
            GpuProgramID 120835
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "DepthNormals"
            Tags { "LIGHTMODE" = "DepthNormals" "QUEUE" = "Geometry" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            GpuProgramID 174943
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "GBuffer"
            Tags { "LIGHTMODE" = "UniversalGBuffer" "QUEUE" = "Geometry" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            GpuProgramID 218310
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_CASCADE" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_MAIN_LIGHT_SHADOWS_SCREEN" "_REFLECTION_PROBE_BLENDING" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
Fallback "Hidden/InternalErrorShader"
CustomEditor "UnityEditor.ShaderGraphLitGUI"
}