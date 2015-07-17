package core;

import java.util.ArrayList;
import java.util.HashMap;

public class Graph {
	public ArrayList<Vertex> vertexSet = new ArrayList<Vertex>();
	public HashMap<Edge, Integer> weight = new HashMap<Edge, Integer>();

	public Graph (ArrayList<Vertex> vertexSet, HashMap<Edge, Integer> weight){
		this.vertexSet = vertexSet;
		this.weight = weight;
	}
	
	public void printDistances() {
		System.out.print("Distances: ");
		for (Vertex vertex : vertexSet) {
			System.out.print("("+ vertex.name +", "+ vertex.distance + ") ");
		}
		System.out.println();
	}
}
