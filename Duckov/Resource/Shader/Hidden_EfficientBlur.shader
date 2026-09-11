//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/EfficientBlur" {
    Properties {
        _MainTex ("Texture", 2D) = "white" { }
        _BackgroundColor ("_BackgroundColor", Color) = (0,0,0,0)
    }
    SubShader {
        Pass {
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 19291
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
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 79523
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    Keywords { "BACKGROUND_FILL_NONE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACKGROUND_FILL_COLOR" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "BACKGROUND_FILL_NONE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BACKGROUND_FILL_COLOR" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
}