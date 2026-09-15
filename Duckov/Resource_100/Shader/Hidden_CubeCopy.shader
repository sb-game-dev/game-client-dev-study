//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/CubeCopy" {
    Properties {
        _MainTex ("Main", Cube) = "" { }
        _Level ("Level", Float) = 0
    }
    SubShader {
        LOD 200
        Tags { "RenderType" = "Opaque" }
        Pass {
            LOD 200
            Tags { "RenderType" = "Opaque" }
            ZTest Always
            ZWrite Off
            Cull Off
            Fog {
                Mode Off
            }
            GpuProgramID 40103
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
    SubShader {
        LOD 200
        Tags { "RenderType" = "Opaque" }
        Pass {
            LOD 200
            Tags { "RenderType" = "Opaque" }
            ZTest Always
            ZWrite Off
            Cull Off
            Fog {
                Mode Off
            }
            GpuProgramID 107876
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