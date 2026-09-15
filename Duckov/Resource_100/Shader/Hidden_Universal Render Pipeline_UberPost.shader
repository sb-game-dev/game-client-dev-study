//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/Universal Render Pipeline/UberPost" {
    Properties {
    }
    SubShader {
        LOD 100
        Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
        Pass {
            Name "UberPost"
            LOD 100
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ZTest Always
            ZWrite Off
            Cull Off
            GpuProgramID 65005
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DITHERING" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DITHERING" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DITHERING" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DITHERING" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DITHERING" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DITHERING" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DITHERING" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DITHERING" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DITHERING" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DITHERING" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DITHERING" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DITHERING" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DITHERING" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DITHERING" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DITHERING" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DITHERING" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DITHERING" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DITHERING" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DITHERING" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DITHERING" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DITHERING" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DITHERING" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DITHERING" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DITHERING" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DITHERING" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DITHERING" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DITHERING" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DITHERING" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DITHERING" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DITHERING" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DITHERING" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DITHERING" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DITHERING" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DITHERING" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DITHERING" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DITHERING" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DITHERING" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DITHERING" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DITHERING" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DISTORTION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DITHERING" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DITHERING" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DITHERING" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DITHERING" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_CHROMATIC_ABERRATION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_DITHERING" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_DITHERING" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_DITHERING" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_DITHERING" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_DITHERING" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_DITHERING" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_DITHERING" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_DITHERING" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_CHROMATIC_ABERRATION" "_DISTORTION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_DITHERING" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_DITHERING" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_DITHERING" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_DITHERING" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_DITHERING" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_DITHERING" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_DITHERING" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_DITHERING" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_DITHERING" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_DITHERING" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_DITHERING" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_DITHERING" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_DITHERING" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_DITHERING" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_DITHERING" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_DITHERING" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_LQ_DIRT" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_DITHERING" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_DITHERING" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_FILM_GRAIN" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_DITHERING" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_LINEAR_TO_SRGB_CONVERSION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_GAMMA_20" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_CHROMATIC_ABERRATION" "_DISTORTION" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_DITHERING" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_DITHERING" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_ACES" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_DITHERING" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_DITHERING" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_DITHERING" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_GAMMA_20" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_BLOOM_HQ_DIRT" "_DISTORTION" "_DITHERING" "_FILM_GRAIN" "_LINEAR_TO_SRGB_CONVERSION" "_TONEMAP_NEUTRAL" "_USE_FAST_SRGB_LINEAR_CONVERSION" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
    }
}