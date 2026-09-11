//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/Internal-DebugPattern" {
    Properties {
        _MainTex ("Texture", 2D) = "white" { }
    }
    SubShader {
        Pass {
            Name "Target Color and DepthStencil"
            ZTest Always
            Stencil {
                Ref 255
                Comp Always
                Pass Replace
                Fail Keep
                ZFail Keep
            }
            GpuProgramID 24322
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
            Name "Target only Color"
            ZTest Always
            ZWrite Off
            GpuProgramID 89907
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
            Name "Target only DepthStencil"
            ZTest Always
            Stencil {
                Ref 255
                Comp Always
                Pass Replace
                Fail Keep
                ZFail Keep
            }
            GpuProgramID 195071
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