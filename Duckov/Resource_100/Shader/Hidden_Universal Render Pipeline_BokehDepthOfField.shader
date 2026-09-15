//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/Universal Render Pipeline/BokehDepthOfField" {
    Properties {
    }
    SubShader {
        LOD 100
        Tags { "RenderPipeline" = "UniversalPipeline" }
        Pass {
            Name "Bokeh Depth Of Field CoC"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 48727
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "Bokeh Depth Of Field Prefilter"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 119468
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "Bokeh Depth Of Field Blur"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 194613
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "Bokeh Depth Of Field Post Blur"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 243511
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "Bokeh Depth Of Field Composite"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 296382
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
    SubShader {
        LOD 100
        Tags { "RenderPipeline" = "UniversalPipeline" }
        Pass {
            Name "Bokeh Depth Of Field CoC"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 347028
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "Bokeh Depth Of Field Prefilter"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 453181
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "Bokeh Depth Of Field Blur"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 462478
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "Bokeh Depth Of Field Post Blur"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 536737
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "Bokeh Depth Of Field Composite"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 626059
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
}