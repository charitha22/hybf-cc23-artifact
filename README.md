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


## Analyzing Each Technique

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

For example, running on a AArch64 machine procues the following output:
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
