//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/TerrainEngine/CrossBlendNeighbors" {
    Properties {
        _TopTex ("Top Texture", any) = "black" { }
        _BottomTex ("Bottom Texture", any) = "black" { }
        _LeftTex ("Left Texture", any) = "black" { }
        _RightTex ("Right Texture", any) = "black" { }
    }
    SubShader {
        Pass {
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 62096
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