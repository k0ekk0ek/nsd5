# tree

Prototype database for efficiently storing DNS data.

A minimal [prototype](https://github.com/NLnetLabs/nsd/tree/nametree) based
on [The Adaptive Radix Tree (ART)](https://db.in.tum.de/~leis/papers/ART.pdf)
for evaluating additional node sizes, sorting, a path buffer and efficient key
transformation as [shared](https://blog.nlnetlabs.nl/adapting-radix-trees/)
previously.

To improve performance and reduce memory usage even further, adding 2x2, 4x4,
etc nodes may help. Especially useful for glue (e.g., TLD) zones where the
name is often accompanied by one or two NS records. Something that the
[Height Optimized Trie (HOT)](https://dbis.uibk.ac.at/sites/default/files/2018-04/hot-height-optimized-author-version.pdf)
seems to focus on too, though I have not read it myself.
