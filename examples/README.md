# LibMcuLl playgrounds
Just a hodgepodge of all kinds of little projects where I try new things out with libMcuLL and see how they work, most of my development is here.
# Compiling
Instead of duplicating the build system per example we use one general Makefile. To compile each project issue the following command:
```
make PROJECT=project name CONFIG=configuration
```
"project name" is the name of the project, see the directory names for each project name and the configuration can either be debug or release. By default debug is built.
# Running
