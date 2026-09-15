//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/Universal Render Pipeline/Scaling Setup" {
    Properties {
    }
    SubShader {
        LOD 100
        Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
        Pass {
            Name "ScalingSetup"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 16062
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "_FXAA" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_GAMMA_20" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_FXAA_AND_GAMMA_20" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
}