Prerequisites
=============

**Hardware**

A relatively recent Nvidia GPU is mandatory for the GPU code.
Nothing special is needed for the CPU code.

**Operating Systems and Compilers**

In order to compile the GPU code, the most recent
`PGI compiler <https://www.pgroup.com/products/community.htm>`_
is preferred for the OpenACC directives. Due to its limitations,
the GPU code is unavailable on macOS.

For Linux, we need:

- GNU or Intel Fortran compiler.
- Recent C++ compiler that supports C++11 syntax.
- (GPU code only) PGI compiler for OpenACC and nvcc for CUDA.
- If Nvidia driver has been installed correctly, *nvidia-smi* should be
  available.

The PGI compilers have recently been rebranded as
`NVIDIA HPC SDK <https://developer.nvidia.com/hpc-sdk>`_
and we successfully built Tinker9 on Windows WSL2 Ubuntu with
CUDA 11.0 and NVHPC 20.9. Please proceed to
`this webpage <https://docs.nvidia.com/cuda/wsl-user-guide/index.html>`_
for more details.

**FFTW Libraries**

Two prebuilt FFTW libraries: *libfftw3* and *libfftw3_threads* are used by
Tinker. Two more FFTW libraries, *libfftw3f*, *libfftw3f_threads* are
needed by the single precision CPU code.

**More About Using PGI Compiler on the Clusters**

I recently (in Jan. 2020) worked on a cluster that was still running
Red Hat with gcc 4.8.5 by default without root privilege. Although several
more recent gcc and PGI versions were available via the *module* program,
the most recent PGI compiler (2019) was still configured with gcc 4.8.5
by default, which had a very bad support for C++11.
Since I didn't have root privilege on the cluster, I had to use
a custom *localrc* file by running the following command to
reconfigure PGI compiler with gcc 7.4.0:

.. code-block:: bash

   makelocalrc $PGI/linux86-64-llvm/2019 \
   -gcc /usr/local/gcc-7.4.0/bin/gcc \
   -gpp /usr/local/gcc-7.4.0/bin/g++ \
   -g77 /usr/local/gcc-7.4.0/bin/gfortran \
   -o -net > /path/to/new_config

then added *export PGI_LOCALRC=/path/to/new_config* to my bash resource file.

**Other Nonmandatory Utilities**

- `ClangFormat <https://clang.llvm.org/docs/ClangFormat.html>`_:
  to format the source code.

- `Sphinx <https://www.sphinx-doc.org>`_: to generate user manual.

   - PDF version also depends on `TeX <https://www.tug.org/begin.html>`_.

   - HTML theme from *pip*.

- `Doxygen <https://www.doxygen.nl>`_: to generate developer guides.

.. code-block:: bash

   pip install -U Sphinx
   pip install 'sphinxcontrib-bibtex==1.0.0'
   pip install pydata-sphinx-theme
