//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "EggPlanetAir" {
    Properties {
        _AlphaCutoff ("Alpha Cutoff ", Range(0, 1)) = 0.5
        _EmissionColor ("Emission Color", Color) = (1,1,1,1)
        _VertexHeight ("VertexHeight", Float) = 0
        _FadeDepth ("FadeDepth", Float) = 0
        _Color ("Color", Color) = (0,0,0,0)
        _Cloud ("Cloud", 2D) = "white" { }
        _Power ("Power", Float) = 1
        _TileOffset ("Tile&Offset", Vector) = (1,1,0,0)
        _QueueOffset ("_QueueOffset", Float) = 0
        _QueueControl ("_QueueControl", Float) = -1
        unity_Lightmaps ("unity_Lightmaps", 2DArray) = "" { }
        unity_LightmapsInd ("unity_LightmapsInd", 2DArray) = "" { }
        unity_ShadowMasks ("unity_ShadowMasks", 2DArray) = "" { }
        [ToggleOff] _ReceiveShadows ("Receive Shadows", Float) = 1
    }
    SubShader {
        Tags { "QUEUE" = "Transparent" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Transparent" "UniversalMaterialType" = "Unlit" }
        Pass {
            Name "Forward"
            Tags { "LIGHTMODE" = "UniversalForwardOnly" "QUEUE" = "Transparent" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Transparent" "UniversalMaterialType" = "Unlit" }
            Blend SrcAlpha OneMinusSrcAlpha, One OneMinusSrcAlpha
            ZWrite Off
            GpuProgramID 5904
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_RECEIVE_SHADOWS_OFF" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_RECEIVE_SHADOWS_OFF" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_RECEIVE_SHADOWS_OFF" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_RECEIVE_SHADOWS_OFF" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_RECEIVE_SHADOWS_OFF" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_RECEIVE_SHADOWS_OFF" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_RECEIVE_SHADOWS_OFF" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_RECEIVE_SHADOWS_OFF" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DBUFFER_MRT3" "_RECEIVE_SHADOWS_OFF" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "_DBUFFER_MRT3" "_RECEIVE_SHADOWS_OFF" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "_DBUFFER_MRT3" "_RECEIVE_SHADOWS_OFF" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "_DBUFFER_MRT3" "_RECEIVE_SHADOWS_OFF" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_RECEIVE_SHADOWS_OFF" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "LOD_FADE_CROSSFADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "LOD_FADE_CROSSFADE" "_RECEIVE_SHADOWS_OFF" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "LOD_FADE_CROSSFADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "LOD_FADE_CROSSFADE" "_RECEIVE_SHADOWS_OFF" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "LOD_FADE_CROSSFADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "LOD_FADE_CROSSFADE" "_RECEIVE_SHADOWS_OFF" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_RECEIVE_SHADOWS_OFF" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_RECEIVE_SHADOWS_OFF" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_RECEIVE_SHADOWS_OFF" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" "LOD_FADE_CROSSFADE" "_DBUFFER_MRT3" "_RECEIVE_SHADOWS_OFF" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "ShadowCaster"
            Tags { "LIGHTMODE" = "SHADOWCASTER" "QUEUE" = "Transparent" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Transparent" "UniversalMaterialType" = "Unlit" }
            ColorMask 0 0
            GpuProgramID 122289
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
                    Keywords { "LOD_FADE_CROSSFADE" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "DepthOnly"
            Tags { "LIGHTMODE" = "DepthOnly" "QUEUE" = "Transparent" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Transparent" "UniversalMaterialType" = "Unlit" }
            ColorMask B 0
            GpuProgramID 175726
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "DepthNormals"
            Tags { "LIGHTMODE" = "DepthNormalsOnly" "QUEUE" = "Transparent" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Transparent" "UniversalMaterialType" = "Unlit" }
            GpuProgramID 389521
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LOD_FADE_CROSSFADE" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
Fallback "Hidden/Shader Graph/FallbackError"
CustomEditor "UnityEditor.ShaderGraphUnlitGUI"
}