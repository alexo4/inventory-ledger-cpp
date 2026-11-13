# Inventory ledger (C++)

A command-line inventory and transport tracker for a fruit-selling business. Every event (ordering stock, shipping it, receiving it, selling it) is stored as a block in a hash-linked list, so a change to any earlier block can be detected.

Written in C++14 for a university module, to practise object-oriented design: an abstract base class, a small class hierarchy, polymorphism and a hand-built linked list.

This is a "blockchain-style" ledger, not a real blockchain. There is no network or consensus, only blocks chained together by SHA-256 hashes.

## What it does

| Menu option | What it does |
|-------------|--------------|
| Display blockchain | Prints every block with its number, hash, previous hash, timestamp and contents |
| Display orders | Groups blocks by order ID: request, then transport, then receipt |
| Display stock levels | Per good: in stock, in transit and ordered |
| Display sales | Sales per good, with a total |
| Add to blockchain | Append a Request, Transport, Receive or Sale block |
| Insert into blockchain | Insert a new block after any existing one |
| Move block | Move a block to a new position |

Stock levels are computed from the chain, not stored. Receiving an order moves its quantity from "in transit" to "in stock", and a sale reduces stock. You can only add a Transport or Receive block to an order that exists and is not yet received, and you cannot sell more than is in stock.

## Example (stock levels from the built-in sample data)

```
|Good name   |In Stock    |In Transit  |Ordered     |
|apple       |     60     |      0     |     150    |
|pear        |     100    |      0     |      0     |
|orange      |      0     |     250    |     50     |
|durian      |      0     |      0     |     250    |
```

## Design

```
Information (abstract: quantity, toString())
├── Order (abstract: orderID)
│   ├── Request    supplier, location, good
│   ├── Transport  carrier, type, origin, destination, estimated days
│   └── Receive    amount paid, payment type
└── Sale           good, revenue, payment type

Block       one node in the list: number, hash, previous hash, timestamp, Information*
BlockChain  owns the list: add / insert / move, hash check and repair, order grouping, stock levels
```

- Each block's hash is SHA-256 of its contents plus the previous block's hash.
- `checkBlockChain` walks the list and returns the position of the first block whose hash does not match the next block's stored previous hash.
- After an insert or move, the hashes and block numbers after that point are recalculated.
- Blocks are told apart with `dynamic_cast` on the `Information` object they hold.

## Build and run

Needs a C++14 compiler.

```bash
g++ -std=c++14 src/*.cpp library/sha256.cpp -o inventory-ledger
./inventory-ledger
```

or with CMake (3.27 or newer):

```bash
cmake -S . -B build && cmake --build build
./build/COMP2034CW_C__
```

At start-up it asks "would you like to load blocks". The sample data (a few orders and sales for apples, pears, oranges and durians) is loaded whatever you answer.

## Limitations

- Nothing is saved to disk; the chain is rebuilt from the sample data on each run.
- Text inputs are read with `cin >>`, so names cannot contain spaces.
- The repair step recalculates hashes after an insert or move. So detecting tampering only helps if you check before repairing, because repairing accepts the altered data.
- Memory is not freed on exit and the sample blocks leak.
- The sample data always loads, even if you answer no at the prompt.

## Third-party code

`library/sha256.cpp` and `library/sha256.h` are not my work. They are a C++ SHA-256 implementation from [zedwood.com](http://www.zedwood.com/article/cpp-sha256-function), based on Olivier Gay's FIPS 180-2 implementation, used under its modified BSD licence. The full copyright notice and licence text are at the top of each file.

## Layout

```
src/        class implementations and main.cpp (menu)
headers/    class declarations
library/    third-party SHA-256 (BSD licence, notice in the files)
```
