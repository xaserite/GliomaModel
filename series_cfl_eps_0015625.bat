echo off
title GlioMath Simulations
echo Running...
call .\bin\GliomaModel.exe -CFL .\_input\cfl_0015625_1.data .\_input\vS_1d_2.data .\_output\cfl_eps_0015625.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_0015625_2.data .\_input\vS_1d_2.data .\_output\cfl_eps_0015625.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_0015625_3.data .\_input\vS_1d_2.data .\_output\cfl_eps_0015625.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_0015625_4.data .\_input\vS_1d_2.data .\_output\cfl_eps_0015625.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_0015625_5.data .\_input\vS_1d_2.data .\_output\cfl_eps_0015625.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_0015625_6.data .\_input\vS_1d_2.data .\_output\cfl_eps_0015625.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_0015625_7.data .\_input\vS_1d_2.data .\_output\cfl_eps_0015625.data