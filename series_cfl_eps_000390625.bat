echo off
title GlioMath Simulations
echo Running...
call .\bin\GliomaModel.exe -CFL .\_input\cfl_000390625_1.data .\_input\vS_1d_2.data .\_output\cfl_eps_000390625.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_000390625_2.data .\_input\vS_1d_2.data .\_output\cfl_eps_000390625.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_000390625_3.data .\_input\vS_1d_2.data .\_output\cfl_eps_000390625.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_000390625_4.data .\_input\vS_1d_2.data .\_output\cfl_eps_000390625.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_000390625_5.data .\_input\vS_1d_2.data .\_output\cfl_eps_000390625.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_000390625_6.data .\_input\vS_1d_2.data .\_output\cfl_eps_000390625.data
call .\bin\GliomaModel.exe -CFL .\_input\cfl_000390625_7.data .\_input\vS_1d_2.data .\_output\cfl_eps_000390625.data