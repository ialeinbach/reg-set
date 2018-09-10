# reg-set

`reg-set` defines a simple register-based ISA and provides a reference
interpreter. `reg-set` is intended to be used for education and so makes many
trade-offs thusly. It is a work in progress.

Instructions can be composed into user-defined procedures.  Labels can be
injected between statements and used as targets for a goto instruction.  This
pair of features allows for both functional and imperative styles of
programming.

`_X` where `X` matches `[a-zA-Z]+` is an instruction or procedure.</br>
`#X` where `X` matches `[0-9]+` is a positive decimal integer literal.</br>
`@X` where `X` matches `[0-9]+` is a general-purpose register.</br>
`$X` where `X` matches `[0-9]+` is a special-purpose register used for parameter passing.

`reg-set` source code is structured as many procedure definitions, one of which
must be called 'main'. The 'main' procedure is used as the entry point for
program execution.
