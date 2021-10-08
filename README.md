# fortran-yaml-cpp

This is [YAML](http://yaml.org) parser for Fortran matching the [YAML 1.2 spec](https://yaml.org/spec/1.2.2/).

This package uses the C++ package [yaml-cpp](https://github.com/jbeder/yaml-cpp) to parse yaml documents, then stores the data in Fortran derived types created by [fortran-yaml](https://github.com/BoldingBruggeman/fortran-yaml). Hence the name `fortran-yaml-cpp`.

## Building

To build and run the example and test, use `cmake`. From the root directory of `fortran-yaml-cpp`, run the following commands:

```
mkdir build
cd build
cmake ..
make
./test
./example
```