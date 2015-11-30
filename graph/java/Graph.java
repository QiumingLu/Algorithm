import java.util.ArrayList;
import java.util.LinkedList;

public class Graph {
  private ArrayList vertexList; 
  private int[][] edges;
  private int numOfEdges;

  public Graph(int n) {
    edges = new int[n][n];
    vertexList = new ArrayList(n);
    numOfEdges = 0;
  }

  // 得到节点的个数
  public int getNumOfVertex() {
    return vertexList.size();
  }

  // 得到边的数目
  public int getNumOfEdges() {
    return numOfEdges;
  }

  // 得到节点 i 的数据
  public Object getValueByIndex(int i) {
    return vertexList.get(i);
  }

  // 插入节点
  public void insertVertex(Object vertex) {
    vertexList.add(vertexList.size(), vertex);
  }

  // 插入节点
  public void insertEdge(int v1, int v2, int weight) {
    edges[v1][v2] = weight;
    ++numOfEdges;
  }

  // 删除节点
  public void deleteEdge(int v1, int v2) {
    edges[v1][v2] = 0;
    --numOfEdges;
  }

  // 得到第一个邻接节点的下标
  public int getFirstNeighbor(int index) {
    for (int i = 0; i < vertexList.size(); ++i) {
      if (edges[index][i] > 0) {
        return i;
      }
    } 
    return -1;
  }

  public int getNextNeighbor(int v1, int v2) {
    for (int j = v2+1; j < vertexList.size(); ++j) {
      if (edges[v1][j] > 0) {
        return j;
      }
    }
    return -1;
  }

  private void depthFirstSearch(boolean[] isVisited, int i) {
    System.out.print(getValueByIndex(i) + " ");
    isVisited[i] = true;
    int w = getFirstNeighbor(i);
    while (w != -1) {
      if(!isVisited[w]) {
        depthFirstSearch(isVisited, w);
      }
      w = getNextNeighbor(i, w);
    }
  }

  public void depthFirstSearch() {
    boolean[] isVisited = new boolean[getNumOfVertex()];
    for (int i = 0; i < getNumOfVertex(); ++i) {
      isVisited[i] = false;
    }
    for (int i = 0; i < getNumOfVertex(); ++i) {
      if (!isVisited[i]) {
        depthFirstSearch(isVisited, i);
      }
    }
  }

  private void broadFirstSearch(boolean[] isVisited, int i) {
    int u, w;
    LinkedList<Integer> queue = new LinkedList();
    System.out.print(getValueByIndex(i) + " ");
    isVisited[i] = true;
    queue.addLast(i);
    while (!queue.isEmpty()) {
      u = queue.removeFirst();
      w = getFirstNeighbor(u);
      while (w != -1) {
        if (!isVisited[w]) {
          System.out.print(getValueByIndex(w) + " ");
          isVisited[w] = true;
          queue.addLast(w);
        }
        w = getNextNeighbor(u, w);
      }
    }
  }

  public void broadFirstSearch() {
    boolean[] isVisited = new boolean[getNumOfVertex()];
    for (int i = 0; i < getNumOfVertex(); ++i) {
      isVisited[i] = false;
    }
    for (int i = 0; i < getNumOfVertex(); ++i) {
      if (!isVisited[i]) {
        broadFirstSearch(isVisited, i);
      }
    }
  }
}
