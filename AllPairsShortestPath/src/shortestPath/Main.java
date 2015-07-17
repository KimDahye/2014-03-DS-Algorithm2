package shortestPath;

import java.util.ArrayList;
import java.util.HashMap;

import core.*;

public class Main {
	static final int INT_MAX = 1000000;
	static final int NIL = -1;  // predecessor matrix 에서 -1이 NIL값, vertex 는 0부터 indexing하므로

	public static void main(String[] args) {
		Graph graph = GraphFactory.getSampleGraph();
		SquareMatrix slowDynamicResult = slowDynamicAllPairs(graph);
		SquareMatrix fastDynamicResult = fastDynamicAllPairs(graph);
		SquareMatrix floydWarshallResult = floydWarshall(graph);
		
		System.out.println("slow dynamic: ");
		slowDynamicResult.printMatrix();
		
		System.out.println("fast dynamic: ");
		fastDynamicResult.printMatrix();
		
		System.out.println("floyd warshall: ");
		floydWarshallResult.printMatrix();
		
		System.out.println("predecessor matrix: ");
		graph.predecessorMatrix.printMatrix();
		
		
	}
	
	static SquareMatrix slowDynamicAllPairs(Graph graph) {
		if(graph == null) return null;
		int size = graph.vertexSet.size();
		ArrayList<SquareMatrix> shortestPathMatrix = new ArrayList<SquareMatrix>();
		shortestPathMatrix.add(0, null); //에러 방지용
		shortestPathMatrix.add(1, graph.weight);
		for(int i = 2; i < size; i++){
			shortestPathMatrix.add(i, extendShortestPaths(shortestPathMatrix.get(i-1), graph.weight));
		}
		return shortestPathMatrix.get(size-1);
	}
	
	static SquareMatrix fastDynamicAllPairs(Graph graph) {
		if(graph == null) return null;
		int size = graph.vertexSet.size();
		HashMap<Integer, SquareMatrix> shortestPathMatrix = new HashMap<Integer, SquareMatrix>();
		shortestPathMatrix.put(1, graph.weight);
		int i = 1;
		while(i < size -1){
			shortestPathMatrix.put(2*i, extendShortestPaths(shortestPathMatrix.get(i), shortestPathMatrix.get(i)));
			i = 2*i;
		}
		return shortestPathMatrix.get(i);		
	}
	
	static SquareMatrix floydWarshall(Graph graph) {
		if(graph == null) return null;
		int size = graph.vertexSet.size();
		SquareMatrix currentMatrix = graph.weight;
		
		//predecessor 초기화
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++) {
				if(i == j) {
					graph.predecessorMatrix.element[i][j] = NIL; 
 					continue;
				}
				if(currentMatrix.element[i][j] == INT_MAX){
					graph.predecessorMatrix.element[i][j] = NIL; 
					continue;
				}
				graph.predecessorMatrix.element[i][j] = i;
			}
		}
				
		for(int k = 0; k < size; k++){
			for(int i = 0; i < size; i++){
				for(int j = 0; j < size; j ++){
					//outOfBound 에러 체크 
					if(isOutOfBound(currentMatrix.element[i][k], currentMatrix.element[k][j])){
						continue;
					}
					
					if(currentMatrix.element[i][j] > currentMatrix.element[i][k] + currentMatrix.element[k][j]){
						currentMatrix.element[i][j] = currentMatrix.element[i][k] + currentMatrix.element[k][j];
						
						//predecessor 지정 
						graph.predecessorMatrix.element[i][j] = graph.predecessorMatrix.element[k][j];
					}
				}
			}
		}
		return currentMatrix;
	}
	
	static SquareMatrix extendShortestPaths(SquareMatrix matrix1, SquareMatrix matrix2) {
		if(matrix1 == null || matrix2 == null) return null;
		if(matrix1.getSize() != matrix2.getSize()) return null;
		
		int size = matrix1.getSize();
		SquareMatrix newMatrix = new SquareMatrix(size);
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				int min = matrix1.element[i][j];
				for(int k = 0; k < size; k++){
					//outOfBound 에러 체크 
					if(isOutOfBound(matrix1.element[i][k], matrix2.element[k][j])){
						continue;
					}
					if(min > matrix1.element[i][k] + matrix2.element[k][j]){
						min = matrix1.element[i][k] + matrix2.element[k][j];
					}
				}
				newMatrix.element[i][j] = min;
			}
		}
		return newMatrix;
	}
	
	static boolean isOutOfBound(int a, int b) {
		if (a == INT_MAX)
			return true;
		if (b == INT_MAX)
			return true;
		if (a > INT_MAX - b)
			return true;
		return false;
	}
}
