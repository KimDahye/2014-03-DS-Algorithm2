package core;

import java.util.ArrayList;
import java.util.HashMap;

public class GraphFactory {
	public static Graph getBellmanSampleGraph() {
		//교과서에 나온 Bellman 예제
		ArrayList<Vertex> vertexSet = new ArrayList<Vertex>();
		HashMap<Edge, Integer> weight = new HashMap<Edge, Integer>();
		for (int i = 0; i < 5; i++) {
			vertexSet.add(i, new Vertex());
		}

		vertexSet.get(0).name = "s";
		vertexSet.get(1).name = "t";
		vertexSet.get(2).name = "y";
		vertexSet.get(3).name = "x";
		vertexSet.get(4).name = "z";

		vertexSet.get(0).adjacencyList.add(vertexSet.get(1));
		vertexSet.get(0).adjacencyList.add(vertexSet.get(2));
		vertexSet.get(1).adjacencyList.add(vertexSet.get(2));
		vertexSet.get(1).adjacencyList.add(vertexSet.get(3));
		vertexSet.get(1).adjacencyList.add(vertexSet.get(4));
		vertexSet.get(2).adjacencyList.add(vertexSet.get(3));
		vertexSet.get(2).adjacencyList.add(vertexSet.get(4));
		vertexSet.get(3).adjacencyList.add(vertexSet.get(1));
		vertexSet.get(4).adjacencyList.add(vertexSet.get(0));
		vertexSet.get(4).adjacencyList.add(vertexSet.get(3));
		
		weight.put(new Edge(vertexSet.get(0), vertexSet.get(1)), 6);
		weight.put(new Edge(vertexSet.get(0), vertexSet.get(2)), 7);
		weight.put(new Edge(vertexSet.get(1), vertexSet.get(2)), 8);
		weight.put(new Edge(vertexSet.get(1), vertexSet.get(3)), 5);
		weight.put(new Edge(vertexSet.get(1), vertexSet.get(4)), -4);
		weight.put(new Edge(vertexSet.get(2), vertexSet.get(3)), -3);
		weight.put(new Edge(vertexSet.get(2), vertexSet.get(4)), 9);
		weight.put(new Edge(vertexSet.get(3), vertexSet.get(1)), -2);
		weight.put(new Edge(vertexSet.get(4), vertexSet.get(0)), 2);
		weight.put(new Edge(vertexSet.get(4), vertexSet.get(3)), 7);

		return new Graph(vertexSet, weight);
	}
	
	public Graph getBellmanRandomGraph() {
		//나중에 구현하겠습니다.
		return null;
	}
	
	public static Graph getDijkstraSampleGraph() {
		//교과서에 나온 Dijkstra 예제
		ArrayList<Vertex> vertexSet = new ArrayList<Vertex>();
		HashMap<Edge, Integer> weight = new HashMap<Edge, Integer>();
		for (int i = 0; i < 5; i++) {
			vertexSet.add(i, new Vertex());
		}

		vertexSet.get(0).name = "s";
		vertexSet.get(1).name = "t";
		vertexSet.get(2).name = "y";
		vertexSet.get(3).name = "x";
		vertexSet.get(4).name = "z";

		vertexSet.get(0).adjacencyList.add(vertexSet.get(1));
		vertexSet.get(0).adjacencyList.add(vertexSet.get(2));
		vertexSet.get(1).adjacencyList.add(vertexSet.get(2));
		vertexSet.get(1).adjacencyList.add(vertexSet.get(3));
		vertexSet.get(2).adjacencyList.add(vertexSet.get(1));
		vertexSet.get(2).adjacencyList.add(vertexSet.get(3));
		vertexSet.get(2).adjacencyList.add(vertexSet.get(4));
		vertexSet.get(3).adjacencyList.add(vertexSet.get(4));
		vertexSet.get(4).adjacencyList.add(vertexSet.get(0));
		vertexSet.get(4).adjacencyList.add(vertexSet.get(3));
		
		weight.put(new Edge(vertexSet.get(0), vertexSet.get(1)), 10);
		weight.put(new Edge(vertexSet.get(0), vertexSet.get(2)), 5);
		weight.put(new Edge(vertexSet.get(1), vertexSet.get(2)), 2);
		weight.put(new Edge(vertexSet.get(1), vertexSet.get(3)), 1);
		weight.put(new Edge(vertexSet.get(2), vertexSet.get(1)), 3);
		weight.put(new Edge(vertexSet.get(2), vertexSet.get(3)), 9);
		weight.put(new Edge(vertexSet.get(2), vertexSet.get(4)), 2);
		weight.put(new Edge(vertexSet.get(3), vertexSet.get(4)), 4);
		weight.put(new Edge(vertexSet.get(4), vertexSet.get(0)), 7);
		weight.put(new Edge(vertexSet.get(4), vertexSet.get(3)), 6);

		return new Graph(vertexSet, weight);
	}
	
	public Graph getDijkstraRandomGraph() {
		//나중에 구현하겠습니다.
		return null;
	}
}
