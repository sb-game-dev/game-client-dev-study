//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/BlitToDepth_MSAA" {
    Properties {
        _MainTex ("DepthTexture", any) = "" { }
    }
    SubShader {
        Pass {
            ColorMask 0 0
            ZTest Always
            Cull Off
            GpuProgramID 27283
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