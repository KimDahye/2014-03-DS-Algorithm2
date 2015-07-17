package core;

import java.util.ArrayList;

public class Vertex {
	static final int INT_MAX = 1000000;
	
	 public Vertex predecessor;
	 public int distance;
	 public ArrayList<Vertex> adjacencyList = new ArrayList<Vertex>();
	 public String name;

}
