//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/Universal Render Pipeline/Debug/DebugReplacement" {
    Properties {
    }
    SubShader {
        Tags { "IGNOREPROJECTOR" = "true" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
        Pass {
            Name "Vertex Attributes"
            Tags { "IGNOREPROJECTOR" = "true" "LIGHTMODE" = "UniversalForward" "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            GpuProgramID 5015
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