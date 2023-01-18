# CC'23 Artifact: "_HyBF: A Hybrid Branch Fusion Strategy for Code Size Reduction_"

The artifact is publicly available at https://github.com/charitha22/hybf-cc23-artifact.
We provide scripts that automate the installation and use of this artifact.
You can clone the artifact repository using the command below:
```
git clone https://github.com/charitha22/hybf-cc23-artifact.git
```

## Dependencies

The default apt packages should be enough for Ubuntu >= 19.10. Default packages plus a pre-built cmake should work for Ubuntu >= 18.04. For older systems, you might have to satisfy the dependencies manually. 

### Building LLVM: 
* cmake (>= 3.13.4)

    If your system's cmake is older than that, source ./scripts/install-cmake.sh to install a recent pre-built binary and add it to the path

* build-essential

    This will pull the rest of the dependencies

For more information about LLVM dependencies check the [LLVM project page](https://llvm.org/docs/GettingStarted.html#software).

### Collecting statistics and plotting the results:   
* python3 (>= 3.6)
* python3-numpy (>= 1.13)  
* python3-matplotlib (>= 2.1)
* xdot

### Running the MiBench benchmark suite:  
* zlib1g-dev

### Running 403.gcc in spec06
* gcc-multilib
* g++-multilib

## Building Clang/LLVM

In order to run HyBF and the different branch fusion techniques, we first
need to build the LLVM compiler toolchain. We provide three helper scripts.

The first script is optional, in case your system version of CMake is older
than the minimum required version.
This script downloads a recent pre-bulit CMake
```
source scripts/install-cmake.sh
```

The second script runs CMake with the appropriate flags.
```
bash scripts/run-cmake.sh
```

The third script builds the LLVM compiler toolchain, including `clang`.
```
bash scripts/build-install.sh
```
After running the above command, the folder `install/bin` should contain
`clang` and `opt` that can be used for compiling C/C++ code using HyBF.

## Reproducing the Main Results

### MiBench

Inside the folder `benchmarks/mibench`, run the command:
```
bash run-code-size.sh
```
This will build all programs listed in the file `BenchNames` using the various
branch fusion techniques. If any compilation error occur, you can look at the
log information in the `.txt` files produced for each individual program
and branch fusion technique. However, no errors should be expected if all
dependencies are installed and the LLVM toolchain has been built correctly.

The command above will produce a `results.csv` file containing the text size
of the object file produced for each benchmark program and for each branch
fusion technique.

This command will also produce the files named `absolute-reduction.pdf`
and `percentage-reduction.pdf`.
The first contains the plot with the absolute reduction, in bytes, achieved
by each technique, while the second contains the relative reduction with
respect to the baseline version without any branch fusion optimization.
These plots represent the Figure 10(a) of the paper.

### SPEC 2006 and 2017

Inside `benchmarks`, the folders `spec06` and `spec17` contain similar
build scripts to those found in the `mibench` folder.
Because both SPEC 2006 and SPEC 2017 require private access, we only
provide the build scripts as part of this artifact.
However, one only need to copy the `src` folder of each program in
the benchmark suites to their corresponding folder in our evaluation
environment.
The `Makefile.config` in the folder of each program contains a list
of the source files expected.

**NOTE** : to automate the benchmark copying we provide the script `copy-bench.sh` inside each of the 
`spec06` and `spec17` directories. To use this script update the `SPEC06_LOC` and `SPEC17_LOC`
variables in the corresponding script with the absolute path of the downloaded 
`spec06` or `spec17` directories.

Once the source files of each program have been copied to their
corresponding folder, we can follow the same steps as described for
MiBench.
We also provide a `run-code-size.sh` script inside the `spec06` and `spec17`
folders, which produces the `results.csv` file with the code size numbers
and the log information in the `.txt` files.
This script will also produce the files named `absolute-reduction.pdf`
and `percentage-reduction.pdf`.
For the `spec17`, these plots represent the Figure 10(b) of the paper.

### Comparison with Function Merging

Inside the folder for each benchmark suite in the `bechmarks` folder,
we have the `run-code-size-lto.sh` script.
This script builds the benchmark programs with link-time optimizations (LTO)
enabled, including the state-of-the-art function merging technique.
This allows us to analyze the impact of our branch fusion technique on top
of another state-of-the-art code size optimization.
This script can be executed with the command below:
```
bash run-code-size-lto.sh
```

After running the `run-code-size-lto.sh` script, e.g., inside the `mibench`
folder, this script will also produce a `results.csv` file 
as well as the files named `absolute-reduction.pdf`
and `percentage-reduction.pdf`.
However, these plots now represent 
Figure 12 from the paper, where all versions were built in LTO mode
with function merging enabled.

### AnghaBench

Inside the folder `benchmarks/anghabench`, run the command:
```
bash run-code-size.sh
```
This will build a subset of the 1 million functions from AnghaBench, which
is listed in the file `BenchNames`, using the various
branch fusion techniques.
The command above will produce a `results.csv` file containing the number of
LLVM instructions for each function in the benchmark suite and for each branch
fusion technique.

This command will also produce a file named `percentage-reduction.pdf`, which
contains a plot with two curves showing the percentage reduction of
CFM-CS (blue curve) and HyBF (red curve) relative to the baseline
version without any branch fusion optimization.
This plot represent the Figure 11 of the paper.

## Customization and Reusability 

This section is intended for researchers interested 
in doing any future work that either uses or extends our optimization pass.

### Experiment Customization

To demonstrate how _HyBF_ and its accompanying branch fusion techniques works
we provide an experiment with two simplified real world code examples.
In the folder `benchmarks/kernels`, we have example of functions highlighting
the strengths of each technique. 

The file `seme-fusion-better.c` contains a function where SEME-Fusion outperforms CFM-CS. 
Run the following command to apply all different techniques (HyBF, CFM-CS, SEME-Fusion and baseline)
to this example.
```
bash run-seme-fusion-example.sh
```
This command outputs the text size of the object file produced by each
technique. It also produces a dot file with control-flow graph produced by each
technique, including the baseline CFG. The generated dot files can be viewed using
either `xdot` on Linux or an online graph viewer such as [GraphvizOnline](https://dreampuf.github.io/GraphvizOnline/).
For example, `seme-fusion-better.c.baseline.dot` contains the CFG for the baseline CFG, without any branch fusion, 
`seme-fusion-better.c.seme-fusion.dot` contains the CFG after applying SEME-Fusion transformation.
By comparing the control-flow graphs produced, one can identify the
differences that result from branch fusion.

For example, running on an X86 machine this script produces the following output:
```
BASELINE
   text    data     bss     dec     hex filename
    922       0      16     938     3aa seme-fusion-better.c.baseline.o
SEME-FUSION
   text    data     bss     dec     hex filename
    821       0      16     837     345 seme-fusion-better.c.seme-fusion.o
CFM-CS
   text    data     bss     dec     hex filename
    922       0      16     938     3aa seme-fusion-better.c.cfm.o
HYBF
   text    data     bss     dec     hex filename
    821       0      16     837     345 seme-fusion-better.c.hybf.o
```
The output above shows that both SEME-Fusion and HyBF produce an
object file with a text size of 821 bytes, while the other techniques produce
a text size of 922 bytes. A reduction of 10.95%. Note that HyBF applies the best version 
of the two techniques, therefore in this case HyBF end up applying SEME-Fusion
obtaining the same reduction in size.

The file `cfm-better.c` contains a function where CFM-CS outperforms SEME-Fusion.
Run the following command to apply the transformations to this example.
```
bash run-cfm-exmaple.sh
```
On an X86 machine, the command above produces the following output:
```
BASELINE
   text    data     bss     dec     hex filename
    446       0       0     446     1be cfm-better.c.baseline.o
SEME-FUSION
   text    data     bss     dec     hex filename
    446       0       0     446     1be cfm-better.c.seme-fusion.o
CFM-CS
   text    data     bss     dec     hex filename
    349       0       0     349     15d cfm-better.c.cfm.o
HYBF
   text    data     bss     dec     hex filename
    349       0       0     349     15d cfm-better.c.hybf.o
```
This shows a size reduction of 21.75% in text section of the binary for CFM-CS
 over baseline or SEME-Fusion. Similar to above, you can view the generated .dot files to 
 see how CFM-CS changes the CFG of the function.

### Modifying/Extending HyBF

_HyBF_ is implemented as an transformation pass at the `LLVM IR` level.
It can easily be extended to add new features or new branch fusion techniques.
In this section, we give a brief overview of the source code structure of 
_HyBF_ along with details on what is implemented on each source file.

_HyBF_ is implemented as a `LLVM` module pass in `llvm/lib/Transforms/Scalar/HybridBranchFusion.cpp`.
The `run` method of this module pass iterates over all functions of the module
and, for each conditional branch location inside the function, applies the best
branch fusion technique (out of CFM-CS and SEME-Fusion).
HyBF is implemented as a transformation on the function level and its
implementation can be found in the `runImpl` method. 
This method iterates over all conditional branches of the functions and
applies both SEME-Fusion and CFM-CS to cloned versions of the same function.
If any of the techniques is profitable, the best approach is applied for the original function.
The `EstimateFunctionSize` method offers an estimate of the final binary size of a given function
at the LLVM IR level. 
Similar to SEME-Fusion and CFM-CS, any novel branch fusion technique can be easily integrated into the `runImpl` method.


_SEME-Fusion_ technique is implemented in `llvm/lib/Transforms/Scalar/BranchFusion.cpp` and
_CFM-CS_ technique is implemented inside `llvm/lib/Transforms/CFMelder/` directory.

