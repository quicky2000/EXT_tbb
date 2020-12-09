# EXT_tbb

Continuous integration with [Travis-Ci](https://travis-ci.org/quicky2000/EXT_tbb) : ![Build Status](https://travis-ci.org/quicky2000/EXT_tbb.svg?branch=master)

Quicky tools wrapper for TBB library.

License
-------
Please see [LICENSE](LICENSE) for info on the license.

CMake module has been obtained thanks to Contributors to the [OpenVDB Project](https://github.com/AcademySoftwareFoundation/openvdb/blob/master/cmake/FindTBB.cmake) under the [LICENSE](cmake/Modules/LICENSE)

TBB library
-----------

Official documentation can be found here:
https://software.intel.com/content/www/us/en/develop/tools/oneapi/components/onetbb.html

To install it on Debian based distributions:
```bash
sudo apt-get install libtbb-dev
```

Build
-----
Build process is the same used in [Travis file](.travis.yml)

Reference build can be found [here](https://travis-ci.org/quicky2000/EXT_tbb)


