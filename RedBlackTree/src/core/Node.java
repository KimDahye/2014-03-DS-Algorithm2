package core;

public class Node{
	public enum Color {
		RED, BLACK
	}
	
	public Node parent;
	public Node left;
	public Node right;
	public int value;
	public Color color;
	
	Node() { }
	
	public Node (int value) {
		this.value = value;
	}

	boolean leftRotate(RedBlackTree tree) {
		if (tree == null || this == null || this.right instanceof Nil)
			return false;

		Node y = this.right;
		this.right = y.left;
		if (!(y.left instanceof Nil))
			y.left.parent = this;
		y.parent = this.parent;
		if (this.parent instanceof Nil)
			tree.root = y;
		if (this.parent.left == this)
			this.parent.left = y;
		if (this.parent.right == this)
			this.parent.right = y;
		y.left = this;
		this.parent = y;
		return true;
	}

	boolean rightRotate(RedBlackTree tree) {
		if (tree == null || this == null || this.left instanceof Nil)
			return false;
		Node x = this.left;
		this.left = x.right;
		if (!(x.right instanceof Nil))
			x.right.parent = this;
		x.parent = this.parent;
		if (this.parent instanceof Nil)
			tree.root = x;
		if (this.parent.left == this)
			this.parent.left = x;
		if (this.parent.right == this)
			this.parent.right = x;
		x.right = this;
		this.parent = x;
		return true;
	}
}
