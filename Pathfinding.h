#pragma once

#include <vector>
#include <queue>
#include <algorithm>
#include "NodeBase.h"

class Pathfinding {
public:
    static inline std::vector<NodeBase*> FindPath(NodeBase* startNode, NodeBase* targetNode) {
        // Lambda comparator: lowest F first, tie-break on lower H
        auto compare = [](NodeBase* a, NodeBase* b) {
            if (a->GetF() == b->GetF())
                return a->GetH() > b->GetH();
            return a->GetF() > b->GetF();
            };

        std::priority_queue<NodeBase*, std::vector<NodeBase*>, decltype(compare)> openSet(compare);
        std::vector<NodeBase*> closed;
        std::vector<NodeBase*> discovered;

        startNode->SetG(0);
        startNode->SetH(startNode->GetDistance(targetNode));
        openSet.push(startNode);
        discovered.push_back(startNode);

        while (!openSet.empty()) {
            auto current = openSet.top();
            openSet.pop();

            // Skip stale entries (node was re-pushed with a better G)
            if (std::find(closed.begin(), closed.end(), current) != closed.end())
                continue;

            closed.push_back(current);

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
                    std::find(closed.begin(), closed.end(), neighbor) != closed.end()) {
                    continue;
                }

                double costToNeighbor = current->GetG() + current->GetDistance(neighbor);
                bool isDiscovered = std::find(discovered.begin(), discovered.end(), neighbor) != discovered.end();

                if (!isDiscovered || costToNeighbor < neighbor->GetG()) {
                    neighbor->SetG(costToNeighbor);
                    neighbor->SetConnection(current);

                    if (!isDiscovered) {
                        neighbor->SetH(neighbor->GetDistance(targetNode));
                        discovered.push_back(neighbor);
                    }

                    // Push with updated priority (old entry becomes stale)
                    openSet.push(neighbor);
                }
            }
        }

        return {};
    }
};