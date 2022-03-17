
@echo off
set PATH_TO_MSBUILD=
rem path to msbuild if u are not using visual studio cuz its too heavy for
rem your pc to run, like mine, while using a browser and/or music player
@echo on
%PATH_TO_MSBUILD% s-files.vcxproj -property:Configuration=Debug