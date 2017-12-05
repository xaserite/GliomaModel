echo off
title GlioMath Simulations
echo Running...
call .\bin\GliomaModel.exe -GM .\_input\conv_05_0.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_05_0.data
call .\bin\GliomaModel.exe -GM .\_input\conv_05_1.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_05_1.data
call .\bin\GliomaModel.exe -GM .\_input\conv_05_2.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_05_2.data
call .\bin\GliomaModel.exe -GM .\_input\conv_05_3.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_05_3.data
call .\bin\GliomaModel.exe -GM .\_input\conv_05_4.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_05_4.data
call .\bin\GliomaModel.exe -GM .\_input\conv_05_5.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_05_5.data
call .\bin\GliomaModel.exe -GM .\_input\conv_05_6.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_05_6.data
call .\bin\GliomaModel.exe -GM .\_input\conv_05_7.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_05_7.data