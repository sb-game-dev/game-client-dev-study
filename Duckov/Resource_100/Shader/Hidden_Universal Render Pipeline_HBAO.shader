//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/Universal Render Pipeline/HBAO" {
    Properties {
        _MainTex ("", any) = "" { }
        _HBAOTex ("", any) = "" { }
        _TempTex ("", any) = "" { }
        _NoiseTex ("", 2D) = "" { }
        _DepthTex ("", any) = "" { }
        _NormalsTex ("", any) = "" { }
    }
    SubShader {
        LOD 100
        Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
        Pass {
            Name "HBAO - AO"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 41844
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT2" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT2" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT2" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT2" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT2" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT4" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT4" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT4" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT4" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT4" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT2" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT2" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT2" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT2" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT2" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT4" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT4" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT4" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT4" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT4" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "ORTHOGRAPHIC_PROJECTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "ORTHOGRAPHIC_PROJECTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT2" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT2" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT2" "ORTHOGRAPHIC_PROJECTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT2" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT2" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "ORTHOGRAPHIC_PROJECTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT4" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT4" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT4" "ORTHOGRAPHIC_PROJECTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT4" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT4" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "ORTHOGRAPHIC_PROJECTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "ORTHOGRAPHIC_PROJECTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "ORTHOGRAPHIC_PROJECTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT2" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT2" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT2" "ORTHOGRAPHIC_PROJECTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT2" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT2" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "ORTHOGRAPHIC_PROJECTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT4" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT4" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT4" "ORTHOGRAPHIC_PROJECTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT4" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT4" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "ORTHOGRAPHIC_PROJECTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT2" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "INTERLEAVED_GRADIENT_NOISE" "NORMALS_RECONSTRUCT4" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "HBAO - AO Deinterleaved"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 129772
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "OFFSCREEN_SAMPLES_CONTRIBUTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "ORTHOGRAPHIC_PROJECTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "ORTHOGRAPHIC_PROJECTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOWEST" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_LOW" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_MEDIUM" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGH" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "OFFSCREEN_SAMPLES_CONTRIBUTION" "ORTHOGRAPHIC_PROJECTION" "QUALITY_HIGHEST" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "HBAO - Deinterleave Depth"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 137921
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
            Name "HBAO - Deinterleave Normals"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 245257
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT4" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "ORTHOGRAPHIC_PROJECTION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT2" "ORTHOGRAPHIC_PROJECTION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT4" "ORTHOGRAPHIC_PROJECTION" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "HBAO - Atlas Deinterleaved AO"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 325026
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
            Name "HBAO - Reinterleave AO"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 379052
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
            Name "HBAO - Blur"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 411385
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "BLUR_RADIUS_2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BLUR_RADIUS_3" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BLUR_RADIUS_4" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BLUR_RADIUS_5" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BLUR_RADIUS_2" "COLOR_BLEEDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BLUR_RADIUS_3" "COLOR_BLEEDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BLUR_RADIUS_4" "COLOR_BLEEDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BLUR_RADIUS_5" "COLOR_BLEEDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BLUR_RADIUS_2" "ORTHOGRAPHIC_PROJECTION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BLUR_RADIUS_3" "ORTHOGRAPHIC_PROJECTION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BLUR_RADIUS_4" "ORTHOGRAPHIC_PROJECTION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BLUR_RADIUS_5" "ORTHOGRAPHIC_PROJECTION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BLUR_RADIUS_2" "COLOR_BLEEDING" "ORTHOGRAPHIC_PROJECTION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BLUR_RADIUS_3" "COLOR_BLEEDING" "ORTHOGRAPHIC_PROJECTION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BLUR_RADIUS_4" "COLOR_BLEEDING" "ORTHOGRAPHIC_PROJECTION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "BLUR_RADIUS_5" "COLOR_BLEEDING" "ORTHOGRAPHIC_PROJECTION" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "HBAO - Temporal Filter"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 509656
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "VARIANCE_CLIPPING_4TAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "VARIANCE_CLIPPING_8TAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "VARIANCE_CLIPPING_4TAP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "VARIANCE_CLIPPING_8TAP" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "HBAO - Copy"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 552749
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
            Name "HBAO - Composite"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ColorMask RGB 0
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 633620
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DEBUG_AO" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DEBUG_COLORBLEEDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DEBUG_NOAO_AO" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DEBUG_AO_AOONLY" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DEBUG_NOAO_AOONLY" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "MULTIBOUNCE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DEBUG_AO" "MULTIBOUNCE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DEBUG_COLORBLEEDING" "MULTIBOUNCE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DEBUG_NOAO_AO" "MULTIBOUNCE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DEBUG_AO_AOONLY" "MULTIBOUNCE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DEBUG_NOAO_AOONLY" "MULTIBOUNCE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "DEBUG_AO" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "DEBUG_COLORBLEEDING" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "DEBUG_NOAO_AO" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "DEBUG_AO_AOONLY" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "DEBUG_NOAO_AOONLY" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "MULTIBOUNCE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "DEBUG_AO" "MULTIBOUNCE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "DEBUG_COLORBLEEDING" "MULTIBOUNCE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "DEBUG_NOAO_AO" "MULTIBOUNCE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "DEBUG_AO_AOONLY" "MULTIBOUNCE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "DEBUG_NOAO_AOONLY" "MULTIBOUNCE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LIT_AO" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DEBUG_AO" "LIT_AO" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DEBUG_COLORBLEEDING" "LIT_AO" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DEBUG_NOAO_AO" "LIT_AO" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DEBUG_AO_AOONLY" "LIT_AO" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DEBUG_NOAO_AOONLY" "LIT_AO" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "LIT_AO" "MULTIBOUNCE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DEBUG_AO" "LIT_AO" "MULTIBOUNCE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DEBUG_COLORBLEEDING" "LIT_AO" "MULTIBOUNCE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DEBUG_NOAO_AO" "LIT_AO" "MULTIBOUNCE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DEBUG_AO_AOONLY" "LIT_AO" "MULTIBOUNCE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "DEBUG_NOAO_AOONLY" "LIT_AO" "MULTIBOUNCE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "LIT_AO" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "DEBUG_AO" "LIT_AO" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "DEBUG_COLORBLEEDING" "LIT_AO" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "DEBUG_NOAO_AO" "LIT_AO" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "DEBUG_AO_AOONLY" "LIT_AO" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "DEBUG_NOAO_AOONLY" "LIT_AO" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "LIT_AO" "MULTIBOUNCE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "DEBUG_AO" "LIT_AO" "MULTIBOUNCE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "DEBUG_COLORBLEEDING" "LIT_AO" "MULTIBOUNCE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "DEBUG_NOAO_AO" "LIT_AO" "MULTIBOUNCE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "DEBUG_AO_AOONLY" "LIT_AO" "MULTIBOUNCE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "COLOR_BLEEDING" "DEBUG_NOAO_AOONLY" "LIT_AO" "MULTIBOUNCE" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "HBAO - Debug ViewNormals"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ColorMask RGB 0
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 708616
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT2" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT4" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "ORTHOGRAPHIC_PROJECTION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT2" "ORTHOGRAPHIC_PROJECTION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "NORMALS_RECONSTRUCT4" "ORTHOGRAPHIC_PROJECTION" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
}