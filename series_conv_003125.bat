echo off
title GlioMath Simulations
echo Running...
call .\bin\GliomaModel.exe -GM .\_input\conv_003125_0.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_003125_0.data
call .\bin\GliomaModel.exe -GM .\_input\conv_003125_1.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_003125_1.data
call .\bin\GliomaModel.exe -GM .\_input\conv_003125_2.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_003125_2.data
call .\bin\GliomaModel.exe -GM .\_input\conv_003125_3.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_003125_3.data
call .\bin\GliomaModel.exe -GM .\_input\conv_003125_4.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_003125_4.data
call .\bin\GliomaModel.exe -GM .\_input\conv_003125_5.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_003125_5.data
call .\bin\GliomaModel.exe -GM .\_input\conv_003125_6.data .\_input\vS_1d_2.data .\_output\1d_v2_conv_003125_6.data