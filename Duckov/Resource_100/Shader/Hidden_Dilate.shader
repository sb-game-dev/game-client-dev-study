//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/Dilate" {
    Properties {
    }
    SubShader {
        Pass {
            ZTest Always
            ZWrite Off
            Cull Front
            Stencil {
                Comp Disabled
                Pass IncrWrap
                Fail Keep
                ZFail Keep
            }
            GpuProgramID 55464
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    Keywords { "BASE_QUALITY_DILATE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BASE_QUALITY_DILATE" "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BASE_QUALITY_DILATE" "INFO_BUFFER_STAGE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BASE_QUALITY_DILATE" "INFO_BUFFER_STAGE" "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HIGH_QUALITY_DILATE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HIGH_QUALITY_DILATE" "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HIGH_QUALITY_DILATE" "INFO_BUFFER_STAGE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HIGH_QUALITY_DILATE" "INFO_BUFFER_STAGE" "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "ULTRA_QUALITY_DILATE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "ULTRA_QUALITY_DILATE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INFO_BUFFER_STAGE" "ULTRA_QUALITY_DILATE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INFO_BUFFER_STAGE" "INSTANCING_ON" "ULTRA_QUALITY_DILATE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BASE_QUALITY_DILATE" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BASE_QUALITY_DILATE" "INSTANCING_ON" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BASE_QUALITY_DILATE" "INFO_BUFFER_STAGE" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BASE_QUALITY_DILATE" "INFO_BUFFER_STAGE" "INSTANCING_ON" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HIGH_QUALITY_DILATE" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HIGH_QUALITY_DILATE" "INSTANCING_ON" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HIGH_QUALITY_DILATE" "INFO_BUFFER_STAGE" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HIGH_QUALITY_DILATE" "INFO_BUFFER_STAGE" "INSTANCING_ON" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "ULTRA_QUALITY_DILATE" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "ULTRA_QUALITY_DILATE" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INFO_BUFFER_STAGE" "ULTRA_QUALITY_DILATE" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INFO_BUFFER_STAGE" "INSTANCING_ON" "ULTRA_QUALITY_DILATE" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "BASE_QUALITY_DILATE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BASE_QUALITY_DILATE" "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BASE_QUALITY_DILATE" "INFO_BUFFER_STAGE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BASE_QUALITY_DILATE" "INFO_BUFFER_STAGE" "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HIGH_QUALITY_DILATE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HIGH_QUALITY_DILATE" "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HIGH_QUALITY_DILATE" "INFO_BUFFER_STAGE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HIGH_QUALITY_DILATE" "INFO_BUFFER_STAGE" "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "ULTRA_QUALITY_DILATE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "ULTRA_QUALITY_DILATE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INFO_BUFFER_STAGE" "ULTRA_QUALITY_DILATE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INFO_BUFFER_STAGE" "INSTANCING_ON" "ULTRA_QUALITY_DILATE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BASE_QUALITY_DILATE" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BASE_QUALITY_DILATE" "INSTANCING_ON" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BASE_QUALITY_DILATE" "INFO_BUFFER_STAGE" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BASE_QUALITY_DILATE" "INFO_BUFFER_STAGE" "INSTANCING_ON" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HIGH_QUALITY_DILATE" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HIGH_QUALITY_DILATE" "INSTANCING_ON" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HIGH_QUALITY_DILATE" "INFO_BUFFER_STAGE" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "HIGH_QUALITY_DILATE" "INFO_BUFFER_STAGE" "INSTANCING_ON" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "ULTRA_QUALITY_DILATE" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "ULTRA_QUALITY_DILATE" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INFO_BUFFER_STAGE" "ULTRA_QUALITY_DILATE" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INFO_BUFFER_STAGE" "INSTANCING_ON" "ULTRA_QUALITY_DILATE" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
}