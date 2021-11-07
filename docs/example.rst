.. _example:

Simple API usage example
========================

The following example demonstrates almost zero-effort method of parsing format
string.

.. literalinclude:: example.c
  :language: c
  :linenos:

CMake integration
~~~~~~~~~~~~~~~~~
Integrating into CMake projects is possible, of course. Here is an example which uses external toolchain:

.. literalinclude:: example.cmake
  :language: cmake
  :linenos:
