# PBL_SEM3_T131
 Network Security Risk Analyzer
Trying to Catch Risky Devices Before They Become a Real Problem — Built with DSA & OOP in C++

So this is a C++ project I've been working on. The basic idea is pretty simple — instead of waiting for something to go wrong on a network, why not scan it ahead of time and figure out which devices are actually risky? That's what this does.
 What It Actually Does

* 🔹 I'm treating the whole network like a **Graph**

  * Each device is just a **Node**
  * Every connection between devices is an **Edge**

* 🔹 Every device gets a **Risk Score**, and that's based on:

  * How vulnerable it is
  * What kind of access it has
  * How important it is to the rest of the network

* 🔹 I'm using **BFS and DFS** to actually explore the network:

  * See how devices are connected
  * Figure out what's reachable from where
  * Basically get a real sense of the network's layout instead of guessing

* 🔹 There's a **Priority Queue** doing the ranking:

  * It sorts devices by how risky they are
  * So the dangerous ones don't just get lost in a long list — they actually surface first

* 🔹 I'm also planning to add **Hashing and Binary Search Trees**, mainly so:

  * Looking up a specific device is faster
  * All the risk data stays organized instead of turning into a mess as the network gets bigger

---

## 🧠 How I Structured the Code

I built this using **OOP in C++**, and I split things into separate classes rather than cramming everything together:

* `Device`
* `NetworkGraph`
* `RiskAnalyzer`
* `PriorityManager`
* `ReportGenerator`

Honestly this just made my life easier — if I need to change or add something later, I'm not digging through one giant file trying not to break everything else.---
 How Risk Gets Categorized

At the end of it all, every device lands in one of three categories:

*  **Low Risk**
*  **Medium Risk**
*  **High Risk**

And along with that, it gives a few practical suggestions — nothing fancy, just useful stuff like:

* Apply security updates
* Cut back on access that isn't really needed
* Keep a closer eye on the devices that matter most
 Tech Stack

* **Language:** C++
* **Core Concepts:** DSA, OOP, Graph Algorithms
* **Tools:** VS Code, Git & GitHub

 Why I'm Actually Doing This

If I'm being honest, this project started because I wanted to see if all the stuff I'd learned — Graphs, BFS, DFS, Priority Queues, Hashing, BST, OOP — that usually just feels like exam material, could actually be used for something real. Turns out network security is a pretty good place to test that out, since catching a risky device early is a lot better than dealing with the aftermath of an attack.

**Status:**  Still building this out — right now it's just Phase 1.
