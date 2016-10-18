Shared Server for CS3450

Please read directory READMEs before committing changes

To obtain third party libraries, first navigate to https://github.com/smanders/externpro. Go to releases, get the 16.07.1 Release. For Windows, you can simply grab the executable and install it. For Linux, grab the .tar.gz file and unpack and build yourself. Externpro contains third party libraries and allows you to link them to your project.

CMake is also necessary as we will be using it for our build system. Install version 3.6.2. When you fork the repository, create a build folder in the repository and then choose to build the binaries in the build folder. The source code is everything not located in the build folder. Use CMake to build the project files and externpro will find them. Finally, you can open the project and be able to include the boost and wx files that you'll need.

To test that you have everything configured correctly, build the project which includes example.cpp. If it builds and runs, you are good to go and can use boost and wx libraries.

