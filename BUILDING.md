 If building for vanilla USD:
 - Open command prompt x64 Native Tools Command Prompt for VS 2019

 If building for Houdini:
 - Open command prompt x64 Native Tools Command Prompt for VS 2022

Then:
 - Make build dir if it doesn't exist. cd to build. 
 - Cmake currently has hardcoded HOUDINI_ROOT and USD_ROOT
 - `cmake -DCMAKE_BUILD_TYPE=Release -G Ninja ..` and to build for Houdini add `-DTARGET_DCC=Houdini`
 - `ninja`
 - Copy plugInfo.json to bin
 - set PXR_PLUGINPATH_NAME env var to the hdRaiden/bin dir