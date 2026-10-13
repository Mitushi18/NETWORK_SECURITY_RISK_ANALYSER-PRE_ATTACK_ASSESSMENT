
#include "risk/AttackGraph.h"

#include <iostream>

void AttackGraph::addNode(
    const std::string& id,
    const std::string& type,
    const std::string& label
)
{
    for (const GraphNode& node : nodes)
    {
        if (node.id == id)
            return;
    }

    nodes.push_back({id, type, label});
}

void AttackGraph::addEdge(
    const std::string& from,
    const std::string& to,
    const std::string& relationship
)
{
    bool sourceExists = false;
    bool targetExists = false;

    for (const GraphNode& node : nodes)
    {
        if (node.id == from)
            sourceExists = true;

        if (node.id == to)
            targetExists = true;
    }

    if (!sourceExists || !targetExists)
        return;

    edges.push_back({from, to, relationship});
}

const std::vector<GraphNode>& AttackGraph::getNodes() const
{
    return nodes;
}

const std::vector<GraphEdge>& AttackGraph::getEdges() const
{
    return edges;
}

void AttackGraph::print() const
{
    std::cout << "\nAttack/Risk Graph Nodes\n";
    std::cout << "-----------------------\n";

    for (const GraphNode& node : nodes)
    {
        std::cout << node.id << " ["
                  << node.type << "] "
                  << node.label << "\n";
    }

    std::cout << "\nGraph Relationships\n";
    std::cout << "-------------------\n";

    for (const GraphEdge& edge : edges)
    {
        std::cout << edge.from << " --"
                  << edge.relationship << "--> "
                  << edge.to << "\n";
    }
}