# Wish Shell

This is **Wish**, a simple Unix-style shell implemented as a university project for University of Nicosia COMP-354 course, based on the [processes-shell OSTEP project](https://github.com/remzi-arpacidusseau/ostep-projects/tree/master/processes-shell).

## Documentation

A full API reference is generated with Doxygen. 

open:

```
docs/html/index.html
```

in your browser to browse the generated documentation.

## Building & Running

Use the provided Makefile. First, display available commands:

```bash
make help
```

You should see output similar to:

```
help:            Show this help message
build:           builds the code
run-tests:       run e2e tests
run-interactive: runs wish in interactive mode
run-file:        runs wish in file mode for test.txt
```

### Commands

- **make build**  
  Compile all sources and produce the `wish` executable:

  ```bash
  make build
  ```

- **make run-interactive**  
  Start the shell in interactive mode:

  ```bash
  make run-interactive
  ```

- **make run-file**  
  Run the shell in batch mode on `test.txt`:

  ```bash
  make run-file
  ```

- **make run-tests**  
  Execute the end-to-end test script:

  ```bash
  make run-tests
  ```
