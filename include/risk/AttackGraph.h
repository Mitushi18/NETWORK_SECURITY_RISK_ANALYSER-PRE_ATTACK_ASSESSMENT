
#ifndef ATTACK_GRAPH_H
#define ATTACK_GRAPH_H

#include <string>
#include <vector>

struct GraphNode
{
    std::string id;
    std::string type;
    std::string label;
};

struct GraphEdge
{
    std::string from;
    std::string to;
    std::string relationship;
};

class AttackGraph
{
private:
    std::vector<GraphNode> nodes;
    std::vector<GraphEdge> edges;

public:
    void addNode(
        const std::string& id,
        const std::string& type,
        const std::string& label
    );

    void addEdge(
        const std::string& from,
        const std::string& to,
        const std::string& relationship
    );

    const std::vector<GraphNode>& getNodes() const;
    const std::vector<GraphEdge>& getEdges() const;

    void print() const;
};

#endif