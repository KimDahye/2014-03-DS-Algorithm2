package core;

import java.util.ArrayList;

public class GraphFactory {
	static final int INT_MAX = 1000000;

	public static Graph getSampleGraph() {
		//교과서에 나온 Dynamic Programming algorithm 예제
		ArrayList<Integer> vertexSet = new ArrayList<Integer>();
		SquareMatrix weight = new SquareMatrix(5);
		
		for (int i = 0; i < 5; i++) {
			vertexSet.add(i, i);
		}
		
		for(int i = 0; i <5; i++){
			weight.element[i][i] = 0;
		}
		
		weight.element[0][1] = 3;
		weight.element[0][2] = 8;
		weight.element[0][3] = INT_MAX;
		weight.element[0][4] = -4;
		weight.element[1][0] = INT_MAX;
		weight.element[1][2] = INT_MAX;
		weight.element[1][3] = 1;
		weight.element[1][4] = 7;
		weight.element[2][0] = INT_MAX;
		weight.element[2][1] = 4;
		weight.element[2][3] = INT_MAX;
		weight.element[2][4] = INT_MAX;
		weight.element[3][0] = 2;
		weight.element[3][1] = INT_MAX;
		weight.element[3][2] = -5;
		weight.element[3][4] = INT_MAX;
		weight.element[4][0] = INT_MAX;
		weight.element[4][1] = INT_MAX;
		weight.element[4][2] = INT_MAX;
		weight.element[4][3] = 6;
			
		return new Graph(vertexSet, weight);
	}
}
