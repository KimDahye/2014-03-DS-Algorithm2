package heap;

import java.util.ArrayList;

import core.Vertex;

public class MinHeap {
	int size;
	ArrayList<Vertex> element;

	MinHeap(int size, ArrayList<Vertex> element) {
		this.size = size;
		this.element = element;
		buildMinHeap();
	}

	private void minHeapify(int index) {
		int left = 2*index;
		int right = 2*index + 1;
		int smallest = index;
		if(left <= size && element.get(left).distance < element.get(index).distance) smallest = left;
		if(right <= size && element.get(right).distance < element.get(smallest).distance) smallest = right;
		if(smallest != index){
			exchangeElement(index, smallest);
			minHeapify(smallest);
		}
	}

	private void buildMinHeap() {
		for (int i = size / 2; i > 0; i--) {
			minHeapify(i);
		}
	}
	
	public void decreaseKey(Vertex vertex) {
		if(vertex == null) return;
		int index = element.indexOf(vertex);
		while (index > 1 && element.get(index/2).distance > element.get(index).distance ){
			exchangeElement(index/2, index);
			index = index/2;
		}
	}
	
	private void exchangeElement(int i, int j) {
		Vertex temp = element.get(i);
		element.set(i, element.get(j));
		element.set(j, temp);
	}
	
	public Vertex extractMin(){
		if (size < 1) {
			System.out.println("underflow");
			return null;
		}
		Vertex min = element.get(1);
		element.set(1, element.get(size));
		size--;
		minHeapify(1);
		return min;
	}
	
	public boolean isEmpty(){
		if(size < 1) {
			return true;
		}
		return false;
	}

}
