//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/BlitCopyHDRTonemap" {
    Properties {
        _MainTex ("Texture", any) = "" { }
        _NitsForPaperWhite ("NitsForPaperWhite", Float) = 160
        _ColorGamut ("ColorGamut", Float) = 0
        _ForceGammaToLinear ("ForceGammaToLinear", Float) = 0
        _MaxDisplayNits ("MaxDisplayNits", Float) = 160
    }
    SubShader {
        Pass {
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 17300
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