
#include <cassert>
#include <iostream>
#include <vector>

#include "risk/RiskAssessment.h"
#include "risk/AttackGraph.h"
#include "vulnerability/Vulnerability.h"

int main()
{
    std::cout << "Member 3 Risk Assessment Test\n";
    std::cout << "-----------------------------\n";

    RiskAssessment assessor;

    std::vector<Vulnerability> findings;

    findings.emplace_back(
        "TEST-001",
        "SMB",
        "Demonstration finding",
        "Critical",
        9.8
    );

    findings.emplace_back(
        "TEST-002",
        "HTTP",
        "Demonstration finding",
        "Medium",
        5.0
    );

    RiskReport report = assessor.assessHost(
        "192.0.2.10",
        findings
    );

    assert(report.hostIp == "192.0.2.10");
    assert(report.vulnerabilityCount == 2);
    assert(report.riskScore >= 0.0);
    assert(report.riskScore <= 10.0);
    assert(report.riskLevel == "Critical");

    std::cout << "Host: " << report.hostIp << "\n";
    std::cout << "Risk score: " << report.riskScore << "/10\n";
    std::cout << "Risk level: " << report.riskLevel << "\n";
    std::cout << "Findings: " << report.vulnerabilityCount << "\n";

    AttackGraph graph;

    graph.addNode("host-1", "Host", "192.0.2.10");
    graph.addNode("service-1", "Service", "SMB");
    graph.addNode("finding-1", "Vulnerability", "TEST-001");

    graph.addEdge("host-1", "service-1", "exposes");
    graph.addEdge(
        "service-1",
        "finding-1",
        "potentially-affected-by"
    );

    assert(graph.getNodes().size() == 3);
    assert(graph.getEdges().size() == 2);

    graph.print();

    std::cout << "\nAll Member 3 tests passed.\n";

    return 0;
}