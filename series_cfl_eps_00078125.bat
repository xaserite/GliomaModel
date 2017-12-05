echo off
title GlioMath Simulations
echo Running...
call .\bin\GliomaModel.exe -CFL .\_input\cfl_00078125_1.data .\_input\vS_1d_2.data .\_output\cfl_eps_00078125.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_00078125_2.data .\_input\vS_1d_2.data .\_output\cfl_eps_00078125.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_00078125_3.data .\_input\vS_1d_2.data .\_output\cfl_eps_00078125.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_00078125_4.data .\_input\vS_1d_2.data .\_output\cfl_eps_00078125.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_00078125_5.data .\_input\vS_1d_2.data .\_output\cfl_eps_00078125.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_00078125_6.data .\_input\vS_1d_2.data .\_output\cfl_eps_00078125.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_00078125_7.data .\_input\vS_1d_2.data .\_output\cfl_eps_00078125.data