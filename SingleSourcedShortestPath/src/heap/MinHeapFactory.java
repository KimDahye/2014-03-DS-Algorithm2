package heap;

import java.util.ArrayList;
import core.*;

public class MinHeapFactory {

	public static MinHeap buildMinHeapFromGraph(Graph graph) {
		ArrayList<Vertex> element = new ArrayList<Vertex>();
		element.add(0, null);
		for (int i = 1; i <= graph.vertexSet.size(); i++) {
			element.add(i, graph.vertexSet.get(i-1));
		}
		return new MinHeap(graph.vertexSet.size(), element);
	}
}
