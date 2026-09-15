//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/Internal-ODSWorldTexture" {
    Properties {
        _MainTex ("", 2D) = "white" { }
        _Cutoff ("", Float) = 0.5
        _Color ("", Color) = (1,1,1,1)
    }
    SubShader {
        Tags { "RenderType" = "Opaque" }
        Pass {
            Tags { "RenderType" = "Opaque" }
            GpuProgramID 56114
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
        Tags { "RenderType" = "TransparentCutout" }
        Pass {
            Tags { "RenderType" = "TransparentCutout" }
            GpuProgramID 98807
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
        Tags { "RenderType" = "TreeBark" }
        Pass {
            Tags { "RenderType" = "TreeBark" }
            GpuProgramID 193123
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
        Tags { "RenderType" = "TreeLeaf" }
        Pass {
            Tags { "RenderType" = "TreeLeaf" }
            GpuProgramID 199807
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
        Tags { "DisableBatching" = "true" "RenderType" = "TreeOpaque" }
        Pass {
            Tags { "DisableBatching" = "true" "RenderType" = "TreeOpaque" }
            GpuProgramID 275277
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
        Tags { "DisableBatching" = "true" "RenderType" = "TreeTransparentCutout" }
        Pass {
            Tags { "DisableBatching" = "true" "RenderType" = "TreeTransparentCutout" }
            GpuProgramID 344272
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
            Tags { "DisableBatching" = "true" "RenderType" = "TreeTransparentCutout" }
            Cull Front
            GpuProgramID 458084
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
        Tags { "RenderType" = "TreeBillboard" }
        Pass {
            Tags { "RenderType" = "TreeBillboard" }
            Cull Off
            GpuProgramID 460861
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
        Tags { "RenderType" = "GrassBillboard" }
        Pass {
            Tags { "RenderType" = "GrassBillboard" }
            Cull Off
            GpuProgramID 540578
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
        Tags { "RenderType" = "Grass" }
        Pass {
            Tags { "RenderType" = "Grass" }
            Cull Off
            GpuProgramID 610072
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