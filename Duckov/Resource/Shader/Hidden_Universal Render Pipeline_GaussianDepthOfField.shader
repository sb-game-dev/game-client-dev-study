//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/Universal Render Pipeline/GaussianDepthOfField" {
    Properties {
    }
    SubShader {
        LOD 100
        Tags { "RenderPipeline" = "UniversalPipeline" }
        Pass {
            Name "Gaussian Depth Of Field CoC"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 18364
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
            Name "Gaussian Depth Of Field Prefilter"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 75117
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_HIGH_QUALITY_SAMPLING" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_HIGH_QUALITY_SAMPLING" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "Gaussian Depth Of Field Blur Horizontal"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 173802
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
            Name "Gaussian Depth Of Field Blur Vertical"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 234127
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
            Name "Gaussian Depth Of Field Composite"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 271688
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_HIGH_QUALITY_SAMPLING" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_HIGH_QUALITY_SAMPLING" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
}