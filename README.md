# PBL_SEM3_T131
# Network Security Risk Analyzer
### Trying to Catch Risky Devices Before They Become a Real Problem — Built with DSA & OOPS in C++

So this is a C++ and Data Structures project we've been working on. The basic idea is pretty simple — instead of waiting for something to go wrong on a network, why not scan it ahead of time and figure out which devices are actually risky? That's what this does.

## What It Actually Does

* 🔹 We're treating the whole network like a **Graph**
  * Each device is just a **Node**
  * Every connection between devices is an **Edge**
* 🔹 Every device gets a **Risk Score**, and that's based on:
  * How vulnerable it is
  * What kind of access it has
  * How important it is to the rest of the network
* 🔹 We're using **BFS and DFS** to actually explore the network:
  * See how devices are connected
  * Figure out what's reachable from where
  * Basically get a real sense of the network's layout instead of guessing
* 🔹 There's a **Priority Queue** doing the ranking:
  * It sorts devices by how risky they are
  * So the dangerous ones don't just get lost in a long list — they actually surface first
* 🔹 We're also planning to add **Hashing and Binary Search Trees**, mainly so:
  * Looking up a specific device is faster
  * All the risk data stays organized instead of turning into a mess as the network gets bigger

---

## How We Structured the Code

We built this using **C++ and Data Structures with an OOPS approach**, and we split things into separate classes rather than cramming everything together:

* `Device`
* `NetworkGraph`
* `RiskAnalyzer`
* `PriorityManager`
* `ReportGenerator`

Honestly this just made our lives easier — if we need to change or add something later, we're not digging through one giant file trying not to break everything else.

---

## How Risk Gets Categorized

At the end of it all, every device lands in one of three categories:

* **Low Risk**
* **Medium Risk**
* **High Risk**

And along with that, it gives a few practical suggestions — nothing fancy, just useful stuff like:

* Apply security updates
* Cut back on access that isn't really needed
* Keep a closer eye on the devices that matter most

## Tech Stack

* **Language:** C++
* **Core Concepts:** DSA (Data Structures & Algorithms), OOP, Graph Algorithms
* **Tools:** VS Code, Git & GitHub

## Why We're Actually Doing This

If we're being honest, this project started because we wanted to see if all the stuff we'd learned — Graphs, BFS, DFS, Priority Queues, Hashing, BST, OOP — that usually just feels like exam material, could actually be used for something real. Turns out network security is a pretty good place to test that out, since catching a risky device early is a lot better than dealing with the aftermath of an attack.

**Status:** Still building this out — right now it's just Phase 1.
