//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/Universal/CoreBlitColorAndDepth" {
    Properties {
    }
    SubShader {
        Tags { "RenderPipeline" = "UniversalPipeline" }
        Pass {
            Tags { "RenderPipeline" = "UniversalPipeline" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 664
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DISABLE_TEXTURE2D_X_ARRAY" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DISABLE_TEXTURE2D_X_ARRAY" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Tags { "RenderPipeline" = "UniversalPipeline" }
            ZTest Always
            Cull Off
            GpuProgramID 89633
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DISABLE_TEXTURE2D_X_ARRAY" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DISABLE_TEXTURE2D_X_ARRAY" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
}