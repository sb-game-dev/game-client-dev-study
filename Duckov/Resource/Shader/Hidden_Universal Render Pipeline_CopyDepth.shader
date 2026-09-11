//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/Universal Render Pipeline/CopyDepth" {
    Properties {
    }
    SubShader {
        Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
        Pass {
            Name "CopyDepth"
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ColorMask B 0
            ZTest Always
            Cull Off
            GpuProgramID 14200
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_OUTPUT_DEPTH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DEPTH_MSAA_2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DEPTH_MSAA_2" "_OUTPUT_DEPTH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DEPTH_MSAA_4" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DEPTH_MSAA_4" "_OUTPUT_DEPTH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DEPTH_MSAA_8" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DEPTH_MSAA_8" "_OUTPUT_DEPTH" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_OUTPUT_DEPTH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DEPTH_MSAA_2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DEPTH_MSAA_2" "_OUTPUT_DEPTH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DEPTH_MSAA_4" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DEPTH_MSAA_4" "_OUTPUT_DEPTH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DEPTH_MSAA_8" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DEPTH_MSAA_8" "_OUTPUT_DEPTH" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
}