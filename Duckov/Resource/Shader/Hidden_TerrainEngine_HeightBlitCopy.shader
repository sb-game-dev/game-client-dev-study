//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/TerrainEngine/HeightBlitCopy" {
    Properties {
        _MainTex ("Texture", any) = "" { }
    }
    SubShader {
        Pass {
            Cull Off
            GpuProgramID 4839
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