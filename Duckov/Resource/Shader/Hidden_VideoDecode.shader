//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/VideoDecode" {
    Properties {
        _MainTex ("_MainTex (A)", 2D) = "black" { }
        _SecondTex ("_SecondTex (A)", 2D) = "black" { }
        _ThirdTex ("_ThirdTex (A)", 2D) = "black" { }
    }
    SubShader {
        Pass {
            Name "YCbCr_To_RGB1"
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 47600
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "ADJUST_TO_LINEARSPACE" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "ADJUST_TO_LINEARSPACE" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "YCbCrA_To_RGBAFull"
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 90961
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "ADJUST_TO_LINEARSPACE" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "ADJUST_TO_LINEARSPACE" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "YCbCrA_To_RGBA"
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 192437
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "ADJUST_TO_LINEARSPACE" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "ADJUST_TO_LINEARSPACE" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "Flip_RGBA_To_RGBA"
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 244574
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "ADJUST_TO_LINEARSPACE" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "ADJUST_TO_LINEARSPACE" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "Flip_RGBASplit_To_RGBA"
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 267143
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "ADJUST_TO_LINEARSPACE" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "ADJUST_TO_LINEARSPACE" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "Flip_NV12_To_RGB1"
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 366377
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "ADJUST_TO_LINEARSPACE" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "ADJUST_TO_LINEARSPACE" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "Flip_NV12_To_RGBA"
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 456580
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "ADJUST_TO_LINEARSPACE" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "ADJUST_TO_LINEARSPACE" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "Flip_P010_To_RGB1"
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 498858
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