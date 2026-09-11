//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/FinalBlit" {
    Properties {
    }
    SubShader {
        Pass {
            Blend One OneMinusSrcAlpha, One OneMinusSrcAlpha
            ZTest Always
            ZWrite Off
            Cull Off
            Stencil {
                ReadMask 0
                Comp Disabled
                Pass Keep
                Fail Keep
                ZFail Keep
            }
            GpuProgramID 1017
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" "USE_INFO_BUFFER" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
}