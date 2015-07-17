package shortestPath;

import heap.*;
import core.*;
import java.util.Map;

public class Main {
	static final int INT_MAX = 1000000;

	public static void main(String[] args) {
		test(GraphFactory.getBellmanSampleGraph(), "bellman");
		test(GraphFactory.getDijkstraSampleGraph(), "dijkstra");
	}

	static void test(Graph graph, String flag){
		Vertex source = graph.vertexSet.get(0);
		boolean check = false;
		if(flag.equals("bellman")){
			check = bellmanFord(graph, source);
		}
		
		if(flag.equals("dijkstra")){
			check = dijkstra(graph, source);
		}
		
		if(check) {
			graph.printDistances();
			for (Vertex vertex : graph.vertexSet) {
				printPath(source, vertex);
				System.out.println();
			}
			return;
		}
		
		if(flag.equals("bellman")){
			System.out.println("negative weighted cycle detected");
		}
	}

	static void printPath(Vertex source, Vertex vertex) {
		if (source == null || vertex == null)
			return;
		if (source == vertex) {
			System.out.print(vertex.name + " ");
			return;
		}
		if (vertex.predecessor == null) {
			System.out.print("there is no path from source to vertex.");
			return;
		}
		printPath(source, vertex.predecessor);
		System.out.print(vertex.name + " ");
	}

	static boolean bellmanFord(Graph graph, Vertex source) {
		if (graph == null || source == null)
			return false;
		initialize(graph, source);
		for (int i = 0; i < graph.vertexSet.size() - 1; i++) {
			for (Vertex u : graph.vertexSet) {
				for (Vertex v : u.adjacencyList) {
					relax(u, v, graph.weight);
				}
			}
		}

		for (Vertex u : graph.vertexSet) {
			for (Vertex v : u.adjacencyList) {
				Edge edge = new Edge(u, v);
				if (isBoundOutOfLimit(u.distance, graph.weight.get(edge))) {
					continue;
				}
				if (v.distance > u.distance + graph.weight.get(edge)) {
					return false;
				}
			}
		}
		return true;
	}

	static boolean dijkstra(Graph graph, Vertex source) {
		if (graph == null || source == null) return false;
		initialize(graph, source);
		MinHeap heap = MinHeapFactory.buildMinHeapFromGraph(graph);
		while (!heap.isEmpty()) {
			Vertex u = heap.extractMin();
			for (Vertex v : u.adjacencyList) {
				relax(u, v, graph.weight);
				heap.decreaseKey(v);
			}
		}
		return true;
	}

	static void relax(Vertex u, Vertex v, Map<Edge, Integer> weight) {
		Edge edge = new Edge(u, v);
		if (isBoundOutOfLimit(u.distance, weight.get(edge))) {
			return;
		}

		if (v.distance > u.distance + weight.get(edge)) {
			v.distance = u.distance + weight.get(edge);
			v.predecessor = u;
		}
	}

	static boolean isBoundOutOfLimit(int a, int b) {
		if (a == INT_MAX)
			return true;
		if (b == INT_MAX)
			return true;
		if (a > INT_MAX - b)
			return true;
		return false;
	}

	static void initialize(Graph graph, Vertex source) {
		for (Vertex v : graph.vertexSet) {
			v.distance = INT_MAX;
			v.predecessor = null;
		}
		source.distance = 0;
	}
}
