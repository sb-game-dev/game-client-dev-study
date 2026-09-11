//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/Universal Render Pipeline/StencilDeferred" {
    Properties {
        _StencilRef ("StencilRef", Float) = 0
        _StencilReadMask ("StencilReadMask", Float) = 0
        _StencilWriteMask ("StencilWriteMask", Float) = 0
        _LitPunctualStencilRef ("LitPunctualStencilWriteMask", Float) = 0
        _LitPunctualStencilReadMask ("LitPunctualStencilReadMask", Float) = 0
        _LitPunctualStencilWriteMask ("LitPunctualStencilWriteMask", Float) = 0
        _SimpleLitPunctualStencilRef ("SimpleLitPunctualStencilWriteMask", Float) = 0
        _SimpleLitPunctualStencilReadMask ("SimpleLitPunctualStencilReadMask", Float) = 0
        _SimpleLitPunctualStencilWriteMask ("SimpleLitPunctualStencilWriteMask", Float) = 0
        _LitDirStencilRef ("LitDirStencilRef", Float) = 0
        _LitDirStencilReadMask ("LitDirStencilReadMask", Float) = 0
        _LitDirStencilWriteMask ("LitDirStencilWriteMask", Float) = 0
        _SimpleLitDirStencilRef ("SimpleLitDirStencilRef", Float) = 0
        _SimpleLitDirStencilReadMask ("SimpleLitDirStencilReadMask", Float) = 0
        _SimpleLitDirStencilWriteMask ("SimpleLitDirStencilWriteMask", Float) = 0
        _ClearStencilRef ("ClearStencilRef", Float) = 0
        _ClearStencilReadMask ("ClearStencilReadMask", Float) = 0
        _ClearStencilWriteMask ("ClearStencilWriteMask", Float) = 0
    }
    SubShader {
        Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
        Pass {
            Name "Stencil Volume"
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ColorMask 0 0
            ZClip Off
            ZWrite Off
            Cull Off
            Stencil {
                ReadMask 0
                WriteMask 0
                CompFront NotEqual
                PassFront Keep
                FailFront Keep
                ZFailFront Invert
                CompBack NotEqual
                PassBack Keep
                FailBack Keep
                ZFailBack Invert
            }
            GpuProgramID 36646
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_SPOT" }
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
            Name "Deferred Punctual Light (Lit)"
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            Blend One One, Zero One
            ZClip Off
            ZTest GEqual
            ZWrite Off
            Cull Front
            Stencil {
                ReadMask 0
                WriteMask 0
                Comp Equal
                Pass Zero
                Fail Keep
                ZFail Keep
            }
            GpuProgramID 104220
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    Keywords { "_POINT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_POINT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_POINT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_POINT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_POINT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_POINT" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_SHADOWS_SOFT" "_SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_POINT" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_SHADOWS_SOFT" "_SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_POINT" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_SHADOWS_SOFT" "_SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_POINT" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_SHADOWS_SOFT" "_SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "Deferred Punctual Light (SimpleLit)"
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            Blend One One, Zero One
            ZClip Off
            ZTest GEqual
            ZWrite Off
            Cull Front
            Stencil {
                ReadMask 0
                WriteMask 0
                CompBack Equal
                PassBack Zero
                FailBack Keep
                ZFailBack Keep
            }
            GpuProgramID 188156
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    Keywords { "_POINT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_POINT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_POINT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_POINT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_POINT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_POINT" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_SHADOWS_SOFT" "_SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_POINT" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_SHADOWS_SOFT" "_SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_POINT" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_SHADOWS_SOFT" "_SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_POINT" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_SHADOWS_SOFT" "_SPOT" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "Deferred Directional Light (Lit)"
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            Blend One SrcAlpha, Zero One
            ZTest NotEqual
            ZWrite Off
            Cull Off
            Stencil {
                ReadMask 0
                WriteMask 0
                Comp Equal
                Pass Keep
                Fail Keep
                ZFail Keep
            }
            GpuProgramID 217692
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "Deferred Directional Light (SimpleLit)"
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            Blend One SrcAlpha, Zero One
            ZTest NotEqual
            ZWrite Off
            Cull Off
            Stencil {
                ReadMask 0
                WriteMask 0
                Comp Equal
                Pass Keep
                Fail Keep
                ZFail Keep
            }
            GpuProgramID 314264
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_CASCADE" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "_ADDITIONAL_LIGHT_SHADOWS" "_DEFERRED_FIRST_LIGHT" "_DEFERRED_MAIN_LIGHT" "_DEFERRED_MIXED_LIGHTING" "_LIGHT_COOKIES" "_MAIN_LIGHT_SHADOWS_SCREEN" "_SHADOWS_SOFT" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "Fog"
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            Blend OneMinusSrcAlpha SrcAlpha, Zero One
            ZTest NotEqual
            ZWrite Off
            Cull Off
            GpuProgramID 367807
            PlayerProgram "vp" {
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" }
                    "// shader disassembly not supported on DXBC"
                }
            }
            PlayerProgram "fp" {
                SubProgram "d3d11 " {
                    Keywords { "FOG_LINEAR" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP" }
                    "// shader disassembly not supported on DXBC"
                }
                SubProgram "d3d11 " {
                    Keywords { "FOG_EXP2" }
                    "// shader disassembly not supported on DXBC"
                }
            }
        }
        Pass {
            Name "ClearStencilPartial"
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            ColorMask 0 0
            ZTest NotEqual
            ZWrite Off
            Cull Off
            Stencil {
                ReadMask 0
                WriteMask 0
                Comp NotEqual
                Pass Zero
                Fail Keep
                ZFail Keep
            }
            GpuProgramID 401139
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
            Name "SSAOOnly"
            Tags { "RenderPipeline" = "UniversalPipeline" "RenderType" = "Opaque" }
            Blend One SrcAlpha, Zero One
            ZTest NotEqual
            ZWrite Off
            Cull Off
            GpuProgramID 508855
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
Fallback "Hidden/Universal Render Pipeline/FallbackError"
}