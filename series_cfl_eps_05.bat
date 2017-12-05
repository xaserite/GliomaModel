echo off
title GlioMath Simulations
echo Running...
call .\bin\GliomaModel.exe -CFL .\_input\cfl_05_1.data .\_input\vS_1d_2.data .\_output\cfl_eps_05.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_05_2.data .\_input\vS_1d_2.data .\_output\cfl_eps_05.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_05_3.data .\_input\vS_1d_2.data .\_output\cfl_eps_05.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_05_4.data .\_input\vS_1d_2.data .\_output\cfl_eps_05.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_05_5.data .\_input\vS_1d_2.data .\_output\cfl_eps_05.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_05_6.data .\_input\vS_1d_2.data .\_output\cfl_eps_05.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_05_7.data .\_input\vS_1d_2.data .\_output\cfl_eps_05.data