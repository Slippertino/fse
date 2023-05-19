# File Search Engine
=====================

## Description
-------------

File Search Engine(fse) is the console application with the purpose to search for local files by key words.
The application is compatible with JSON-supported files.
First is the config file(config.json by default), which is used for setup. 
It can contain some meta information(name, version) and 
a list of paths to files, which is indexed for further search queries.
Second is the file with a list of queries(requests.json by default). 
All results are also written in JSON-file(answers.json by default).

List of used technologies: C++17(JSON, GTest as 3d party), CMake.

## Building
-----------

```cmake

mkdir build & cd build
cmake ..
cmake --build . --config=<your build type>

```

## Running
----------

```

fse <path to config> <path to output>

```

Then you should enter the path to a file with requests.