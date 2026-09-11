//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/ClearStencil" {
    Properties {
    }
    SubShader {
        Pass {
            ColorMask 0 0
            ZTest Always
            ZWrite Off
            Cull Front
            Stencil {
                Comp Always
                Pass Replace
                Fail Keep
                ZFail Keep
            }
            GpuProgramID 20641
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INSTANCING_ON" }
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
            }
        }
    }
}