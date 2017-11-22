echo off
title GlioMath Simulations
echo Running...
call .\bin\GliomaModel.exe -GM .\_input\conv_1_1.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_1_1.data
call .\bin\GliomaModel.exe -GM .\_input\conv_1_2.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_1_2.data
call .\bin\GliomaModel.exe -GM .\_input\conv_1_3.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_1_3.data
call .\bin\GliomaModel.exe -GM .\_input\conv_1_4.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_1_4.data
call .\bin\GliomaModel.exe -GM .\_input\conv_1_5.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_1_5.data
call .\bin\GliomaModel.exe -GM .\_input\conv_1_6.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_1_6.data
call .\bin\GliomaModel.exe -GM .\_input\conv_1_7.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_1_7.data
call .\bin\GliomaModel.exe -GM .\_input\conv_1_8.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_1_8.data