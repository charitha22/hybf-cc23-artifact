# CC'23 Artifact: "_HyBF: A Hybrid Branch Fusion Strategy for Code Size Reduction_"

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
In order to generate the bar plot with the code size reduction, as shown in
Figure 10 of the paper, run the following command line inside the folder
`benchmarks`.
```
python3 plot-code-size.py mibench/results.csv
```
The command line above will produce the files named `absolute-reduction.pdf`
and `percentage-reduction.pdf`.
The first contains the plot with the absolute reduction, in bytes, achieved
by each technique, while the second contains the relative reduction with
respect to the baseline version without any branch fusion optimization.


## Customization and Reusability 
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

This script also produces a dot file with control-flow graph produced by each
technique, including the baseline CFG. The generated dot files can be viewed using
an online graph viewer like [GraphvizOnline](https://dreampuf.github.io/GraphvizOnline/).
For example, `seme-fusion-better.c.baseline.dot` contains the CFG for the baseline CFG (before applying any transformation), 
`seme-fusion-better.c.seme-fusion.dot` contains the CFG after applying SEME-Fusion transformation.

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

