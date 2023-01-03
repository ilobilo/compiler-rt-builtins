# compiler-rt-builtins
based on https://github.com/embeddedartistry/compiler-rt</br>
this is a replacement for libgcc

Note: currently only aarch64 and x86_64 are tested

## Usage
* Include this project with ``dependency('compiler_rt_builtins')`` in your meson project
* To use custom ``assert.h`` for ``builtins/cpu_model.c`` instead of ``include/assert.h``, use ``compiler_rt_builtins_src`` and compile the code yourself with apropriate ``include_directories``
* Configurable options are available in ``meson_options.txt``