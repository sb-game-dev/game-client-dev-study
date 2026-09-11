//////////////////////////////////////////
//
// NOTE: This is *not* a valid shader file
//
///////////////////////////////////////////
Shader "Hidden/Universal Render Pipeline/ObjectMotionVectors" {
    Properties {
    }
    SubShader {
        Pass {
            Name "Object Motion Vectors"
            Tags { "LIGHTMODE" = "MOTIONVECTORS" }
            GpuProgramID 63731
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