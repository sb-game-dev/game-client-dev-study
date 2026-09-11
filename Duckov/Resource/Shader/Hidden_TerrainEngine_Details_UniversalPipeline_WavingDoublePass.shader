//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/TerrainEngine/Details/UniversalPipeline/WavingDoublePass" {
    Properties {
        _WavingTint ("Fade Color", Color) = (0.7,0.6,0.5,0)
        _MainTex ("Base (RGB) Alpha (A)", 2D) = "white" { }
        _WaveAndDistance ("Wave and distance", Vector) = (12,3.6,1,1)
        _Cutoff ("Cutoff", Float) = 0.5
    }
    SubShader {
        LOD 200
        Tags { "IGNOREPROJECTOR" = "true" "QUEUE" = "Geometry+200" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Grass" "UniversalMaterialType" = "SimpleLit" }
        Pass {
            LOD 200
            Tags { "IGNOREPROJECTOR" = "true" "QUEUE" = "Geometry+200" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Grass" "UniversalMaterialType" = "SimpleLit" }
            AlphaToMask On
            Cull Off
            GpuProgramID 37060
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_MAIN_LIGHT_SHADOWS_CASCADE" }
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
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
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
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
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
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHTS" "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "DepthOnly"
            LOD 200
            Tags { "IGNOREPROJECTOR" = "true" "LIGHTMODE" = "DepthOnly" "QUEUE" = "Geometry+200" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Grass" "UniversalMaterialType" = "SimpleLit" }
            ColorMask B 0
            Cull Off
            GpuProgramID 79481
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
            Name "DepthNormalsOnly"
            LOD 200
            Tags { "IGNOREPROJECTOR" = "true" "LIGHTMODE" = "DepthNormalsOnly" "QUEUE" = "Geometry+200" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Grass" "UniversalMaterialType" = "SimpleLit" }
            Cull Off
            GpuProgramID 132422
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
    }
}