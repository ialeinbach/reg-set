# reg-set

`reg-set` is a simple register machine designed to aid teaching in the area of
abstraction and models of computation.

It is still a work in progress.

## Overview

`reg-set` exposes only very basic operations on 3 registers. It presents a
simple ISA that is trivial to explain in its entirety.  Moreover, the details of
the model of computation employed by `reg-set` are designed to be unobtrusive at
the cost of practicality.

An `.rg` file has the capacity to do only two things. When evaluated by some
`reg-set` implementation, instructions listed at the top level are enacted in
top-down order. The only other statements allowed at the top level are procedure
definitions, which are compositions of instructions that are collectively given
a name and can be invoked from anywhere.

The three registers are aliased `@0`, `@1`, `@2`. The value stored in `@0` is
printed upon halting.

