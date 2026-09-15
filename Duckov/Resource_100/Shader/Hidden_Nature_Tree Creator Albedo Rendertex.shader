//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/Nature/Tree Creator Albedo Rendertex" {
    Properties {
        _TranslucencyColor ("Translucency Color", Color) = (0.73,0.85,0.41,1)
        _Cutoff ("Alpha cutoff", Range(0, 1)) = 0.5
        _HalfOverCutoff ("0.5 / alpha cutoff", Range(0, 1)) = 1
        _TranslucencyViewDependency ("View dependency", Range(0, 1)) = 0.7
        _MainTex ("Base (RGB) Alpha (A)", 2D) = "white" { }
        _BumpSpecMap ("Normalmap (GA) Spec (R) Shadow Offset (B)", 2D) = "bump" { }
        _TranslucencyMap ("Trans (B) Gloss(A)", 2D) = "white" { }
    }
    SubShader {
        Pass {
            GpuProgramID 30435
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