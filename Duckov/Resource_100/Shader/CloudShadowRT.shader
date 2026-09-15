//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "CloudShadowRT" {
    Properties {
        _Noise1 ("Noise1", 2D) = "white" { }
        _Noise2 ("Noise1", 2D) = "white" { }
        [IntRange] _Noise1Tile ("Noise1Tile", Range(1, 10)) = 1
        [IntRange] _Noise2Tile ("Noise2Tile", Range(1, 10)) = 1
        [RemapSliders] _CloudClamp ("CloudClamp", Vector) = (0,1,0,0)
        _Speed12 ("Speed1&2", Vector) = (0,0,0,0)
        _CloudColor ("CloudColor", Color) = (0,0,0,1)
    }
    SubShader {
        Pass {
            Name "Custom RT Update"
            GpuProgramID 57929
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
CustomEditor "ASEMaterialInspector"
}