# Implementation of Ukkonen's Algorithm

A C++23 implementation of suffix tree construction using Ukkonen's online algorithm without suffix trees.
The tree is built left to right, one character at a time, with a `$` terminator appended so every suffix ends at a leaf.

## Credit
This algorithm is entirely credited to [On-Line construction of suffix trees](https://www.cs.helsinki.fi/u/ukkonen/SuffixT1withFigs.pdf) by Esko Ukkonen

## Features

- **Online construction** following Ukkonen's three extension rules.
- **Shared leaf end** — every leaf points at the same end index, so all leaves grow automatically each step (rule 1).
- **Active point and remainder** tracking of pending suffixes, with early termination on rule 3.
- **Skip/count walk-down**, which moves along edges by comparing edge lengths only.
- **Edge labels stored as index pairs** into the word rather than copied substrings.

## Complexity

This version does **not** use suffix links.
After each insertion it returns to the root and walks back down, so construction is **O(n²)** in the worst case rather than Ukkonen's linear time.
The resulting tree is the same either way.

## Requirements

- A C++23 compiler 
- CMake 4.3 or newer

## Building and Running Tests

```sh
cmake -B build
cmake --build build
./build/Ukkonen
```

Runs off my own custom testing library, entirely designed for suffix tree json tests.  Json deserialisation is entirely credited to [nlohmann/json](https://github.com/nlohmann/json) library. 

The `Ukkonen` executable runs every case in `tests/tests.json` and prints a pass or fail result for each, followed by a summary.

### Data Structures 

| Type | Field | Meaning |
|---|---|---|
| `Ind` | `a`, `b` | Half-open range `[a, b)` into the word plus `$`. Leaves share one `b`. |
| `Node` | `Indices` | Label of the node's incoming edge. Null for the root. |
| `Node` | `Children` | Child nodes keyed by the first character of their edge. |
| `Active_Point` | `Parent`, `Edge`, `Length` | The active node, the active edge below it, and how far along that edge the active point is. |

## How to Add My Own Tests?

Each case in `tests/tests.json` gives a word and the expected tree:

```json
"Test_Name": {
    "word": "a",
    "exp": {
        "0": { "Edge": null,   "Children": [1, 2] },
        "1": { "Edge": [1, 2], "Children": [] },
        "2": { "Edge": [0, 2], "Children": [] }
    }
}
```

- `word` is the input to the suffix tree construction algorithm.
- `exp` contains all expected nodes, order does not matter.
- Node `"0"` is the root.
- `Edge` is the node's `[a, b)` range, or `null` for the root.
- `Children` lists node IDs, which are numbered level by level with children sorted by first character.
- The test cases are run in a simple BFS comparison where each individual node is compared by indices and number of child nodes.

## Limitations

- `$` is reserved as the terminator, so input words must not contain it.
- There is no searching functionality, it's simply running test cases only.

## Further reading

`commentary/Correctness_Commentary.pdf` — *On the Correctness of Suffix Tree Construction with Ukkonen's Algorithm: A Practical Commentary*.
`notes.txt` - Documenting of my thought process and ideas as I build the algorithm from scratch.
