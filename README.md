# NetShield: Pre-Attack Network Risk Analyzer

A C++ tool that finds the riskiest devices in a network before an attacker does.

## What it does

Most security tools check one device at a time. Attackers don't work that way. They hop from one machine to the next. NetShield treats the network as a graph, with devices as nodes and connections as edges, so it can see how a weak spot in one place opens the door to others. It then ranks devices by risk so admins know what to fix first.

## How it works

1. Reads a text file describing the devices and their connections.
2. Creates a Host object for each device.
3. Builds the graph, with each host keeping a neighbor list (an adjacency list).
4. Uses BFS and DFS to see which devices can be reached from which.
5. Gives each device a risk score based on how vulnerable it is, how much access it has, and how important it is.
6. Uses a priority queue so the riskiest devices come out first.
7. Labels each device low, medium, or high risk.
8. Suggests actions like patching, limiting access, and monitoring critical systems (still being finished).

## Project structure

- **Host:** stores a device's information
- **Edge:** a connection between two devices
- **Graph:** holds all hosts and connections
- **Traversal:** BFS and DFS
- **Risk analysis:** the scoring logic
- **Priority queue:** orders hosts by risk
- **Reporting:** in progress

## Where we are

**Done:** the Host, Edge, and Graph classes, neighbor lists, BFS/DFS, risk scoring, priority queue ranking, and text file input.

**Still to do:** hash map for faster lookups, a BST for organizing risk data, better reports, performance testing, and more tests.

## Testing

We plan to test building hosts and graphs, bad or incomplete input, BFS/DFS results, score calculations, queue order, risk labels, and disconnected or larger networks. We'll only mark a test as passed once we've actually run it.

## A note on scope

NetShield is for defensive and educational use. Its scores help decide what to look at first. They don't prove a device is safe or hacked, and the results are only as good as the input data.
