@ echo off

::Title of shell/cmd window
title build Euler solution

@ echo on

::Remove solution
::@ rmdir -R ./out

::Generate VS2019 solution
cmake -G "Visual Studio 16 2019" -S ./ -B ./out

::Build
::cmake --build ./out

::Print end msg
@ echo Build script finished!

::Wait for input before closing
@ pause

