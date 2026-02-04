# choonxiangg.github.io
## 4/2/2026
Watched Pathfinding - Understanding A*: https://www.youtube.com/watch?v=i0x5fj4PqP4<sup>[1]</sup>

The A* algorithm code in this video:
```
public class NodeBase {
    public NodeBase Connection { get; private set; }
    public float G { get; private set; }
    public float H { get; private set; }
    public float F => G + H;
    
    public void SetConnection(NodeBase nodeBase) => Connection = nodeBase;
    
    public void SetG(float g) => G = g;
    
    public void SetH(float h) => H = h;
}
```
This code is in C#. I will convert it into C++.

## Reference
[1] Tarodev (2021). Pathfinding - Understanding A* (A star). YouTube. Available at: https://www.youtube.com/watch?v=i0x5fj4PqP4.
