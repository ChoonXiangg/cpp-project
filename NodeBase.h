#pragma once
#include <vector>

class NodeBase {
public:
    NodeBase() : connection_(nullptr), g_(0.0), h_(0.0), walkable_(true) {}

    NodeBase* GetConnection() const { return connection_; }
    double GetG() const { return g_; }
    double GetH() const { return h_; }
    double GetF() const { return g_ + h_; }
    const std::vector<NodeBase*>& GetNeighbors() const { return neighbors_; }
    bool IsWalkable() const { return walkable_; }
    void SetConnection(NodeBase* node_base) { connection_ = node_base; }
    void SetG(double g) { g_ = g; }
    void SetH(double h) { h_ = h; }
    void SetNeighbors(const std::vector<NodeBase*>& neighbors) { neighbors_ = neighbors; }
    void SetWalkable(bool walkable) { walkable_ = walkable; }
    virtual double GetDistance(NodeBase* other) = 0;
    virtual ~NodeBase() = default;

private:
    NodeBase* connection_;
    double g_;
    double h_;
    std::vector<NodeBase*> neighbors_;
    bool walkable_;
};