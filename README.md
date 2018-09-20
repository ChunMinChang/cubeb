[![Build Status](https://travis-ci.org/kinetiknz/cubeb.svg?branch=master)](https://travis-ci.org/kinetiknz/cubeb)
[![Build status](https://ci.appveyor.com/api/projects/status/osv2r0m1j1nt9csr/branch/master?svg=true)](https://ci.appveyor.com/project/kinetiknz/cubeb/branch/master)

See INSTALL.md for build instructions.

Licensed under an ISC-style license.  See LICENSE for details.

## Build CoreAudio Rust Backend
1. The *cubeb-coreaudio-rs* project will be cloned under *src* after running ```git submodule update --init --recursive```.
2. Go to *cubeb-coreaudio-rs* and switch branch to *build-config-in-cubeb*
3. Follow the same steps as usual to build cubeb project by *cmake*. It should work!
