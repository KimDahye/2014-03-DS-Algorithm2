package core;

public class SquareMatrix {
	public int [][] element;
	private int size;
	static final int INT_MAX = 1000000;
	
	public SquareMatrix(int size) {
		this.size = size;
		element = new int[size][size];
	}
	
	public int getSize(){
		return size;
	}
	
	public void printMatrix() {
		for(int i = 0; i < size; i++) {
			for(int j = 0; j < size; j++) {
				if(element[i][j] != INT_MAX)
					System.out.print(element[i][j]+" ");
				else
					System.out.print("*");
			}
			System.out.println();
		}
		System.out.println();
	}
}
