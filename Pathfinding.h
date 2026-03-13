#pragma once

#include <vector>
#include <algorithm>
#include "NodeBase.h"

class Pathfinding {
public:
    static inline std::vector<NodeBase*> FindPath(NodeBase* startNode, NodeBase* targetNode) {
        std::vector<NodeBase*> toSearch = { startNode };
        std::vector<NodeBase*> processed;

        while (!toSearch.empty()) {
            auto current = toSearch[0];
            for (auto t : toSearch) {
                if (t->GetF() < current->GetF() ||
                    (t->GetF() == current->GetF() && t->GetH() < current->GetH())) {
                    current = t;
                }
            }

            processed.push_back(current);
            toSearch.erase(std::remove(toSearch.begin(), toSearch.end(), current), toSearch.end());

            if (current == targetNode) {
                auto currentPathTile = targetNode;
                std::vector<NodeBase*> path;
                while (currentPathTile != startNode) {
                    path.push_back(currentPathTile);
                    currentPathTile = currentPathTile->GetConnection();
                }
                return path;
            }

            for (auto neighbor : current->GetNeighbors()) {
                if (!neighbor->IsWalkable() ||
                    std::find(processed.begin(), processed.end(), neighbor) != processed.end()) {
                    continue;
                }

                bool inSearch = std::find(toSearch.begin(), toSearch.end(), neighbor) != toSearch.end();

                double costToNeighbor = current->GetG() + current->GetDistance(neighbor);

                if (!inSearch || costToNeighbor < neighbor->GetG()) {
                    neighbor->SetG(costToNeighbor);
                    neighbor->SetConnection(current);

                    if (!inSearch) {
                        neighbor->SetH(neighbor->GetDistance(targetNode));
                        toSearch.push_back(neighbor);
                    }
                }
            }
        }

        return {};
    }
};