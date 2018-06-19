cd ${APPVEYOR_BUILD_FOLDER}
mkdir -p build
cd build
export PATH="/mingw64/bin:/usr/local/bin:/usr/bin:/bin:/c/WINDOWS/system32:/c/WINDOWS:/c/WINDOWS/System32/Wbem:/c/WINDOWS/System32/WindowsPowerShell/v1.0:/usr/bin/site_perl:/usr/bin/vendor_perl:/usr/bin/core_perl"
exec sh -c "cmake -G\"MSYS Makefiles\" -DCMAKE_INSTALL_PREFIX=/mingw64 -DBUILD_TESTING=1 .. && make && make test"
