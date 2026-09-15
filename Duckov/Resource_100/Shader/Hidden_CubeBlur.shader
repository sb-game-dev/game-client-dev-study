//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/CubeBlur" {
    Properties {
        _MainTex ("Main", Cube) = "" { }
        _Texel ("Texel", Float) = 0.0078125
        _Level ("Level", Float) = 0
        _Scale ("Scale", Float) = 1
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
            GpuProgramID 21152
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
            GpuProgramID 122835
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