#! /bin/bash

cvs -d :pserver:anoncvs@www.che.wisc.edu:/cvs login 
cvs -d :pserver:anoncvs@www.che.wisc.edu:/cvs -z 9 checkout octave 
cvs -d :pserver:anoncvs@www.che.wisc.edu:/cvs logout
