# compiler-rt-builtins
based on https://github.com/embeddedartistry/compiler-rt</br>
this is a replacement for libgcc

Note: currently only aarch64 and x86_64 are tested

## Usage
* Include this project with ``dependency('compiler_rt_builtins')`` in your meson project
* To use custom includes, use ``compiler_rt_builtins_src`` instead and compile the code yourself with apropriate ``include_directories`` or just pass ``custom_includes`` option
* More configurable options are available in ``meson_options.txt``