//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/TerrainEngine/Splatmap/Standard-BaseGen" {
    Properties {
        _DstBlend ("DstBlend", Float) = 0
    }
    SubShader {
        Pass {
            Tags { "Format" = "RGBA32" "Name" = "_MainTex" "Size" = "1" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 57051
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
            Tags { "Format" = "A2R10G10B10" "Name" = "_NormalMap" "Size" = "1" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 105198
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
            Tags { "Format" = "R8" "Name" = "_MetallicTex" "Size" = "1/4" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 150356
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