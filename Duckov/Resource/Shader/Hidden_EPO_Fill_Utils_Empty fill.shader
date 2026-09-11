//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/EPO/Fill/Utils/Empty fill" {
    Properties {
    }
    SubShader {
        Pass {
            ColorMask 0 0
            ZTest Off
            ZWrite Off
            Cull Off
            Stencil {
                Comp Always
                Pass Zero
                Fail Keep
                ZFail Keep
            }
            GpuProgramID 25505
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
}