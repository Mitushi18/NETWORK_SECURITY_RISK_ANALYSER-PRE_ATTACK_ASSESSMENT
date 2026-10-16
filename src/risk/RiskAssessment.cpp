
#include "risk/RiskAssessment.h"

#include <algorithm>

RiskReport RiskAssessment::assessHost(
    const std::string& hostIp,
    const std::vector<Vulnerability>& vulnerabilities
) const
{
    double highestScore = 0.0;
    double additionalScore = 0.0;
    bool highestSkipped = false;

    for (const Vulnerability& vulnerability : vulnerabilities)
    {
        double score = vulnerability.getRiskScore();

        // Clamp score to the range 0–10.
        score = std::max(0.0, std::min(10.0, score));

        highestScore = std::max(highestScore, score);
    }

    for (const Vulnerability& vulnerability : vulnerabilities)
    {
        double score = vulnerability.getRiskScore();
        score = std::max(0.0, std::min(10.0, score));

        if (!highestSkipped && score == highestScore)
        {
            highestSkipped = true;
            continue;
        }

        additionalScore += score * 0.10;
    }

    double totalScore = std::min(
        10.0, highestScore + additionalScore
    );

    RiskReport report;
    report.hostIp = hostIp;
    report.riskScore = totalScore;
    report.riskLevel = determineRiskLevel(totalScore);
    report.vulnerabilityCount =
        static_cast<int>(vulnerabilities.size());

    return report;
}

std::string RiskAssessment::determineRiskLevel(double score) const
{
    if (score >= 9.0)
        return "Critical";

    if (score >= 7.0)
        return "High";

    if (score >= 4.0)
        return "Medium";

    if (score > 0.0)
        return "Low";

    return "Informational";
}