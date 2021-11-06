.. _index:

Fmt Parser library
==================

.. toctree::
    :hidden:
    :caption: Core API

    example
    group_fmt_parser
    group_fmt_util

.. toctree::
    :hidden:
    :caption: Advanced topics

    global


A light-weight implementation of printf-like format string.

The main idea of the project is to send tasks to the analyzer and get a set of reports back.

.. rubric:: Building

The project is based on CMake, so use a typical CMake approach:

.. ref-code-block:: shell

    mkdir -p build && cd build
    cmake -GNinja ..

There is a simple ``tools/make.sh`` wrapper:

.. ref-code-block:: shell

    ./tools/make.sh

To build for Windows on Linux, you may need MinGW. Then use:

.. ref-code-block:: shell

    ./tools/make.sh --win32

To build with unit tests, add ``--test`` key.

.. rubric:: Documentation

It is possible to generate Doxygen/Sphinx documentation using the following shell command on UNIX-based operating systems:

.. ref-code-block:: shell

    ./tools/generate_doc.sh

The documentation will be located in ``build/html`` folder.
