echo off
title GlioMath Simulations
echo Running...
call .\bin\GliomaModel.exe -CFL .\_input\cfl_00009765625_1.data .\_input\vS_1d_2.data .\_output\cfl_eps_00009765625.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_00009765625_2.data .\_input\vS_1d_2.data .\_output\cfl_eps_00009765625.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_00009765625_3.data .\_input\vS_1d_2.data .\_output\cfl_eps_00009765625.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_00009765625_4.data .\_input\vS_1d_2.data .\_output\cfl_eps_00009765625.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_00009765625_5.data .\_input\vS_1d_2.data .\_output\cfl_eps_00009765625.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_00009765625_6.data .\_input\vS_1d_2.data .\_output\cfl_eps_00009765625.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_00009765625_7.data .\_input\vS_1d_2.data .\_output\cfl_eps_00009765625.data