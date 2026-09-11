//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/Universal/HDRDebugView" {
    Properties {
    }
    SubShader {
        Tags { "RenderPipeline" = "UniversalPipeline" }
        Pass {
            Tags { "RenderPipeline" = "UniversalPipeline" }
            ZClip Off
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 49349
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
            Tags { "RenderPipeline" = "UniversalPipeline" }
            ZClip Off
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 130443
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