echo off
title GlioMath Simulations
echo Running...
call .\bin\GliomaModel.exe -CFL .\_input\cfl_1_1.data .\_input\vS_1d_2.data .\_output\cfl_eps_1.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_1_2.data .\_input\vS_1d_2.data .\_output\cfl_eps_1.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_1_3.data .\_input\vS_1d_2.data .\_output\cfl_eps_1.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_1_4.data .\_input\vS_1d_2.data .\_output\cfl_eps_1.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_1_5.data .\_input\vS_1d_2.data .\_output\cfl_eps_1.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_1_6.data .\_input\vS_1d_2.data .\_output\cfl_eps_1.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_1_7.data .\_input\vS_1d_2.data .\_output\cfl_eps_1.data