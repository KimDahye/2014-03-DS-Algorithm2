package core;

import java.util.ArrayList;

public class Graph {
	public ArrayList<Integer> vertexSet = new ArrayList<Integer>();
	public SquareMatrix predecessorMatrix;
	public SquareMatrix weight;
	

	public Graph (ArrayList<Integer> vertexSet, SquareMatrix weight){
		this.vertexSet = vertexSet;
		this.weight = weight;
		this.predecessorMatrix = new SquareMatrix(vertexSet.size());
	}
	
}
