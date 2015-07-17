package test;

import java.util.Random;

import core.Nil;
import core.RedBlackTree;
import core.Node;
import core.Node.Color;

public class Main {
	static int nodeNum = 20; // rbt에 들어가는 노드 개수를 조절하면서 테스트할 수 있습니다.
	static int ratio = 2; // random number를 추출할 때 nodeNum에 비례하여 range를 잡습니다.
	
	public static void main(String[] args) {
		RedBlackTree rbt = new RedBlackTree();
		insertTest(rbt);
		deleteTest(rbt);
	}
	
	static void insertTest(RedBlackTree rbt) {
		Random rand = new Random();
		for(int i= 0; i < nodeNum; i++) {
			int value = rand.nextInt(ratio*nodeNum);
			rbt.insert(new Node(value));
			System.out.println("----- after inserting " +  value + " -----");
			print(0, rbt.root);
			System.out.println("isbalanced: " + rbt.isBalanced());
		}
	}
	
	static void deleteTest(RedBlackTree rbt) {
		Random rand = new Random();
		for(int i= 0; i < nodeNum; i++) {
			int value = rand.nextInt(ratio*nodeNum);
			System.out.println("delete test chosen number :"+value);
			Node deletedNode = rbt.binarySearch(value);
			rbt.delete(deletedNode);
			if(deletedNode != null) {
				System.out.println("----- after deleting " + deletedNode.value +" -----");
				print(0, rbt.root);
				System.out.println("=> isbalanced: " + rbt.isBalanced());
				System.out.println();
			}
		}
	}
	
	public static void print(int level, Node node){
		if(node == null || node instanceof Nil) return;
		
		print(level+1, node.left);
		for(int i = 0; i < level; i++) {
			System.out.print("		");
		}
		if(node.color == Color.RED){
			System.out.println("( " + node.value + " )");
		}
		if(node.color == Color.BLACK) {
			System.out.println("(*" + node.value + "*)");
		}
		print(level+1, node.right);
	}
}
