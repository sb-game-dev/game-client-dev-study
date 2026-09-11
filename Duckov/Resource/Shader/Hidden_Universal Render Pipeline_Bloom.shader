//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/Universal Render Pipeline/Bloom" {
    Properties {
    }
    SubShader {
        LOD 100
        Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
        Pass {
            Name "Bloom Prefilter"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 27064
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_USE_RGBM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_USE_RGBM" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_USE_RGBM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_USE_RGBM" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "Bloom Blur Horizontal"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 90264
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_USE_RGBM" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_USE_RGBM" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "Bloom Blur Vertical"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 142778
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_USE_RGBM" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_USE_RGBM" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "Bloom Upsample"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 255948
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_USE_RGBM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_USE_RGBM" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_USE_RGBM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_USE_RGBM" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
}