//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/Universal Render Pipeline/ScreenSpaceAmbientOcclusion" {
    Properties {
    }
    SubShader {
        Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
        Pass {
            Name "SSAO_Occlusion"
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 32489
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "_INTERLEAVED_GRADIENT" "_SAMPLE_COUNT_HIGH" "_SOURCE_DEPTH_NORMALS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_INTERLEAVED_GRADIENT" "_ORTHOGRAPHIC" "_SAMPLE_COUNT_HIGH" "_SOURCE_DEPTH_NORMALS" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "SSAO_Bilateral_HorizontalBlur"
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 100028
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
            Name "SSAO_Bilateral_VerticalBlur"
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 131279
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
            Name "SSAO_Bilateral_FinalBlur"
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 253624
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
            Name "SSAO_Bilateral_FinalBlur_AfterOpaque"
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            Blend One SrcAlpha, Zero One
            ZTest NotEqual
            ZWrite Off
            Cull Off
            GpuProgramID 290120
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
            Name "SSAO_Gaussian_HorizontalBlur"
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 356475
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
            Name "SSAO_Gaussian_VerticalBlur"
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 405281
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
            Name "SSAO_Gaussian_VerticalBlur_AfterOpaque"
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            Blend One SrcAlpha, Zero One
            ZTest NotEqual
            ZWrite Off
            Cull Off
            GpuProgramID 500373
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
            Name "SSAO_Kawase"
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 562838
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
            Name "SSAO_Kawase_AfterOpaque"
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            Blend One SrcAlpha, Zero One
            ZTest NotEqual
            ZWrite Off
            Cull Off
            GpuProgramID 627409
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