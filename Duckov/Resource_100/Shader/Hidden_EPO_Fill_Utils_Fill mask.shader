//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/EPO/Fill/Utils/Fill mask" {
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
                Pass Replace
                Fail Keep
                ZFail Keep
            }
            GpuProgramID 1000
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
}