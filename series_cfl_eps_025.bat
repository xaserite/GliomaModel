echo off
title GlioMath Simulations
echo Running...
call .\bin\GliomaModel.exe -CFL .\_input\cfl_025_1.data .\_input\vS_1d_2.data .\_output\cfl_eps_025.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_025_2.data .\_input\vS_1d_2.data .\_output\cfl_eps_025.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_025_3.data .\_input\vS_1d_2.data .\_output\cfl_eps_025.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_025_4.data .\_input\vS_1d_2.data .\_output\cfl_eps_025.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_025_5.data .\_input\vS_1d_2.data .\_output\cfl_eps_025.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_025_6.data .\_input\vS_1d_2.data .\_output\cfl_eps_025.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_025_7.data .\_input\vS_1d_2.data .\_output\cfl_eps_025.data