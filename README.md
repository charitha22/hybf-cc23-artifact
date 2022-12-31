# hybf-cc23-artifact

## Dependencies

Building LLVM:   
* cmake   
* build-essential   

Collecting statistics and plotting the results:   
* python3   
* python3-numpy   
* python3-matplotlib    

Running the MiBench benchmark suite:  
* zlib1g-dev   

## Building Clang/LLVM

In order to run HyBF and the different branch fusion techniques, we first
need to build the LLVM compiler toolchain. We provide two helper scripts.

The first script runs `cmake` with the appropriate flags.
```
bash scripts/run-cmake.sh
```

The second script builds the LLVM compiler toolchain, including `clang`.
```
bash scripts/build-install.sh
```
After running the above command, the folder `install/bin` should contain
`clang` and `opt` that can be used for compiling C/C++ code using HyBF.

## Customization and Reusability 
### Experiment Customization

In the folder `benchmarks/kernels`, we have example of functions highlighting
the strengths of each technique. For example, the file `seme-fusion-better.c`
contains a function where SEME-Fusion outperforms CFM-CS. Similarly, the file
`cfm-cs-better.c` contains a function where CFM-CS outperforms SEME-Fusion.

In order to analyze each technique on these examples, we need to run
the command:
```
bash run.sh
```
This command outputs the text size of the object file produced by each
technique.
It also produces a dot file with control-flow graph produced by each
technique, including the baseline with no branch fusion.

For example, running on a AArch64 machine produces the following output:
```
BASELINE
   text	   data	    bss	    dec	    hex	filename
    813	      0	     16	    829	    33d	seme-fusion-better.c.baseline.o
SEME-FUSION
   text	   data	    bss	    dec	    hex	filename
    745	      0	     16	    761	    2f9	seme-fusion-better.c.seme-fusion.o
CFM-CS
   text	   data	    bss	    dec	    hex	filename
    813	      0	     16	    829	    33d	seme-fusion-better.c.cfm.o
HYBF
   text	   data	    bss	    dec	    hex	filename
    745	      0	     16	    761	    2f9	seme-fusion-better.c.hybf.o
```
The output above shows that both SEME-Fusion and HyBF produce an
object file with a text size of 745 bytes, while the other techniques produce
a text size of 813 bytes. A reduction of 8.36%.


### Modifying/Extending HyBF

_HyBF_ is implemented as `LLVM-IR` transformation pass, therefore it can be extended to add new features or 
new branch fusion techniques. In this section, we give a brief overview of the source code structure of 
_HyBF_ along with details on what is implemented on each source file.


_HyBF_ is implemented as a `LLVM` module pass in `<ARTIFACT_HOME>/llvm/lib/Transforms/Scalar/HybridBranchFusion.cpp`. The `run`
method of this module pass iterate over all functions of the module and apply the best branch fusion technique 
(out of CFM-CS and SEME-Fusion) to given conditional branch location.
Application of HyBF for a given function is implemented in `runImpl` method. 
This method iterates over all conditional branches of the functions and applies SEME-Fusion and CFM-CS to 
cloned versions of the same function.
If any of the techniques is profitable, the best approach is applied for the original function.
`EstimateFunctionSize` method implements the IR size calculation for a given function. 
Any other novel branch fusion technique can be also integrated into the `runImpl` method similarly.


_CFM-CS_ technique is implemented inside `<ARTIFACT_HOME>/llvm/lib/Transforms/CFMelder/` directory. 

