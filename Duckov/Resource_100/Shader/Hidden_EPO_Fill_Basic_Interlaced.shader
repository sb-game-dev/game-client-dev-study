//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/EPO/Fill/Basic/Interlaced" {
    Properties {
        _PublicColor ("Color", Color) = (1,0,0,1)
        _PublicGapColor ("Gap color", Color) = (1,0,0,0.2)
        _PublicSize ("Size", Float) = 1
        _PublicGapSize ("Gap size", Range(-1, 1)) = 0.2
        _PublicSoftness ("Softness", Range(0, 3)) = 0.75
        _PublicSpeed ("Speed", Float) = 1
        _PublicAngle ("Angle", Range(0, 360)) = 0
    }
    SubShader {
        Pass {
            Blend SrcAlpha OneMinusSrcAlpha, SrcAlpha OneMinusSrcAlpha
            ZTest Off
            ZWrite Off
            Cull Off
            Stencil {
                Comp Equal
                Pass Zero
                Fail Keep
                ZFail Keep
            }
            GpuProgramID 32568
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "EPO_HDRP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "EPO_HDRP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" "EPO_HDRP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" "EPO_HDRP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "EPO_HDRP" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "EPO_HDRP" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" "EPO_HDRP" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" "EPO_HDRP" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "EPO_HDRP" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "EPO_HDRP" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" "EPO_HDRP" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" "EPO_HDRP" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "EPO_HDRP" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "EPO_HDRP" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" "EPO_HDRP" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" "EPO_HDRP" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "EPO_HDRP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "EPO_HDRP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" "EPO_HDRP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" "EPO_HDRP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "EPO_HDRP" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "EPO_HDRP" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" "EPO_HDRP" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" "EPO_HDRP" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "EPO_HDRP" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "EPO_HDRP" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" "EPO_HDRP" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" "EPO_HDRP" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "EPO_HDRP" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "EPO_HDRP" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" "EPO_HDRP" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" "EPO_HDRP" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_OBSTACLE_RENDERING" "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACK_MASKING_RENDERING" "BACK_RENDERING" "EPO_HDRP" "TEXARRAY_CUTOUT" "USE_CUTOUT" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
}