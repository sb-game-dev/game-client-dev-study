//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/TrueShadow/Cutout" {
    Properties {
        _MainTex ("Texture", 2D) = "white" { }
        _Offset ("Offset", Vector) = (0,0,0,0)
    }
    SubShader {
        Pass {
            Blend Zero OneMinusSrcAlpha, Zero OneMinusSrcAlpha
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 13897
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