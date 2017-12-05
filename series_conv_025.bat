echo off
title GlioMath Simulations
echo Running...
call .\bin\GliomaModel.exe -GM .\_input\conv_025_0.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_025_0.data
call .\bin\GliomaModel.exe -GM .\_input\conv_025_1.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_025_1.data
call .\bin\GliomaModel.exe -GM .\_input\conv_025_2.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_025_2.data
call .\bin\GliomaModel.exe -GM .\_input\conv_025_3.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_025_3.data
call .\bin\GliomaModel.exe -GM .\_input\conv_025_4.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_025_4.data
call .\bin\GliomaModel.exe -GM .\_input\conv_025_5.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_025_5.data
call .\bin\GliomaModel.exe -GM .\_input\conv_025_6.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_025_6.data
call .\bin\GliomaModel.exe -GM .\_input\conv_025_7.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_025_7.data