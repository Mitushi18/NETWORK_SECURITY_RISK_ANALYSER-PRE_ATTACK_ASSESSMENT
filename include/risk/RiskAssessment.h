#include "vulnerability/Vulnerability.h"
#ifndef RISK_ASSESSMENT_H
#define RISK_ASSESSMENT_H

#include <string>
#include <vector>

#include "vulnerability/Vulnerability.h"

struct RiskReport
{
    std::string hostIp;
    double riskScore;
    std::string riskLevel;
    int vulnerabilityCount;
};

class RiskAssessment
{
public:
    RiskReport assessHost(
        const std::string& hostIp,
        const std::vector<Vulnerability>& vulnerabilities
    ) const;

private:
    std::string determineRiskLevel(double score) const;
};

#endif