//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/Universal Render Pipeline/SubpixelMorphologicalAntialiasing" {
    Properties {
        _StencilRef ("_StencilRef", Float) = 64
        _StencilMask ("_StencilMask", Float) = 64
    }
    SubShader {
        Pass {
            ZTest Always
            ZWrite Off
            Cull Off
            Stencil {
                WriteMask 0
                Comp Always
                Pass Replace
                Fail Keep
                ZFail Keep
            }
            GpuProgramID 47249
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    Keywords { "_SMAA_PRESET_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_SMAA_PRESET_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_SMAA_PRESET_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "_SMAA_PRESET_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_SMAA_PRESET_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_SMAA_PRESET_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            ZTest Always
            ZWrite Off
            Cull Off
            Stencil {
                ReadMask 0
                WriteMask 0
                Comp Equal
                Pass Replace
                Fail Keep
                ZFail Keep
            }
            GpuProgramID 117177
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    Keywords { "_SMAA_PRESET_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_SMAA_PRESET_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_SMAA_PRESET_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "_SMAA_PRESET_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_SMAA_PRESET_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_SMAA_PRESET_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 136238
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    Keywords { "_SMAA_PRESET_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_SMAA_PRESET_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_SMAA_PRESET_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "_SMAA_PRESET_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_SMAA_PRESET_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_SMAA_PRESET_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
}