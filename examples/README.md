# LibMcuLl example directory
Contains bare minimum frames of projects, they have a rudimentary board definition in their project trees. The build system is one level higher to prevent any duplication of code as many projects will share this these prebuilt files.
# Compiling
Instead of duplicating the build system per example we use one general Makefile. To compile each project issue the following command:
```
make PROJECT=project name CONFIG=configuration
```
"project name" is the name of the project, see the directory names for each project name and the configuration can either be debug or release. By default debug is built.
# Running
