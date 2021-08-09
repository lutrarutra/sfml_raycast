# How to build?
#### You need visual studio 2019 (probably works with earlier versions)
#### Compile it for x64 Debug or Release, x86 is not supported

# Not working?
#### Check all additional dependencies in project properties:
1. `Configuration -> C/C++ -> Additional Include Directories` should point to include directory in SFML library (included with the project but you can change it to your library).
2. `Configuration -> Linker -> General-> Additional Library Directories` should point to lib directory in SFML library.
3. `Configuration -> Linker -> Input -> Additional Dependencies` should contain `sfml-system.lib`, `sfml-window.lib`, `sfml-graphics.lib` for Release configuration and `sfml-system-d.lib`, `sfml-window.lib-d`, `sfml-graphics-d.lib` for Debug configuration.

#### Note that platform should be set to x64 when setting up properties.

# Additional info
- Original project creator: lutrarutra https://github.com/lutrarutra
- This fork creator: nesickc
