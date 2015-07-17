package core;

import core.Node.Color;

public class RedBlackTree {
	public Node root;
	Nil nil;

	public RedBlackTree() {
		this.nil = new Nil();
		root = this.nil;
	}

	/* RBT인지 확인하는 함수들 */
	public int countBlackHeight(Node node) {
		if (node instanceof Nil) {
			return 0;
		}

		int leftCount = countBlackHeight(node.left);
		int rightCount = countBlackHeight(node.right);

		if (leftCount == -1 || rightCount == -1)
			return -1;

		if (node.left.color == Color.BLACK)
			leftCount++;
		if (node.right.color == Color.BLACK)
			rightCount++;

		if (leftCount != rightCount)
			return -1;
		return leftCount;
	}

	public boolean isBalanced() {
		if (countBlackHeight(root) < 0)
			return false;
		return true;
	}

	/* INSERT 관련 함수들 */
	public void insert(Node node) {
		Node parentNode = this.nil;
		Node curNode = this.root;
		while (curNode != this.nil) {
			parentNode = curNode;
			if (node.value <= curNode.value)
				curNode = curNode.left;
			else
				curNode = curNode.right;
		}
		node.parent = parentNode;

		if (parentNode == this.nil) {
			root = node;
		} else if (node.value <= parentNode.value) {
			parentNode.left = node;
		} else {
			parentNode.right = node;
		}

		node.left = this.nil;
		node.right = this.nil;
		node.color = Color.RED;
		insertFixUp(node);
	}

	private void insertFixUp(Node fixupNode) {
		while (fixupNode.parent.color == Color.RED) {
			if (fixupNode.parent == fixupNode.parent.parent.left) {
				Node uncleNode = fixupNode.parent.parent.right;
				if (uncleNode.color == Color.RED) {
					/* case 1 */
					fixupNode.parent.color = Color.BLACK;
					uncleNode.color = Color.BLACK;
					fixupNode.parent.parent.color = Color.RED;
					fixupNode = fixupNode.parent.parent; // fixupNode 재조정
				}
				else { // uncleNode.color == Color.BLACK
					if (fixupNode == fixupNode.parent.right) {
						/* case 3에서 case 2로 바꾸는 과정 */
						fixupNode = fixupNode.parent;
						fixupNode.leftRotate(this);
					}
					/* case 2 */
					fixupNode.parent.color = Color.BLACK;
					fixupNode.parent.parent.color = Color.RED;
					fixupNode.parent.parent.rightRotate(this);
				}
			} else {
				// fixupNode.parent == fixupNode.parent.parent.right
				// if then 절에서 left와 right를 바꾼 경우와 같음
				Node uncleNode = fixupNode.parent.parent.left;
				if (uncleNode.color == Color.RED) {
					/* case 1 */
					fixupNode.parent.color = Color.BLACK;
					uncleNode.color = Color.BLACK;
					fixupNode.parent.parent.color = Color.RED;
					fixupNode = fixupNode.parent.parent; // fixupNode 조정
				}
				else { // uncleNode.color == Color.BLACK
					if (fixupNode == fixupNode.parent.left) {
						/* case 3에서 case 2로 바꾸는 과정 */
						fixupNode = fixupNode.parent;
						fixupNode.rightRotate(this);
					}
					/* case 2 */
					fixupNode.parent.color = Color.BLACK;
					fixupNode.parent.parent.color = Color.RED;
					fixupNode.parent.parent.leftRotate(this);
				}
			}
		}
		root.color = Color.BLACK; 
	}

	/* DELETE 관련 함수들 */
	public void delete(Node node) {
		if (node == null || node instanceof Nil)
			return;

		Color erasedColor = node.color;
		Node fixupNode;
		if (node.left instanceof Nil) {
			// children이 없거나, right child만 있는 경우
			fixupNode = node.right;
			transplant(node, node.right);
		} else if (node.right instanceof Nil) {
			// left child만 있는 경우
			fixupNode = node.left;
			transplant(node, node.left);
		} else {
			// left child, right child 모두 있는 경우 
			Node successor = minimumNode(node.right);
			erasedColor = successor.color;
			fixupNode = successor.right;
			if (successor.parent == node) {
				fixupNode.parent = successor; //fixupNode가 Nil일 경우에 parent 지정해주는 것
			} else {
				transplant(successor, successor.right);
				successor.right = node.right;
				successor.right.parent = successor;
			}
			transplant(node, successor);
			successor.left = node.left;
			successor.left.parent = successor;
			successor.color = node.color;
		}

		if (erasedColor == Color.BLACK) {
			deleteFixUp(fixupNode);
		}
	}

	private void transplant(Node oldNode, Node plantNode) { //oldNode를 plantNode로 교체
		if(oldNode.parent instanceof Nil) {
			root = plantNode;
		}else if(oldNode == oldNode.parent.left) {
			oldNode.parent.left = plantNode;
		}else {
			oldNode.parent.right = plantNode;
		}
		
		plantNode.parent = oldNode.parent; //plantNode가 nil이어도 예외처리 없이 parent 지정
		
	}

	private Node minimumNode(Node node) {
		if (node == null || node instanceof Nil)
			return null;
		Node parentNode = node;
		Node curNode = node.left;
		while (!(curNode instanceof Nil)) {
			parentNode = curNode;
			curNode = curNode.left;
		}
		return parentNode;
	}
	
	private void deleteFixUp(Node fixupNode) {
		while(fixupNode != this.root && fixupNode.color == Color.BLACK){
			if(fixupNode == fixupNode.parent.left){
				Node sibling = fixupNode.parent.right;
				if(sibling.color == Color.RED){
					/* case 5 -> case 1,2,3 으로 바꾸는 과정 */
					sibling.color = Color.BLACK;
					fixupNode.parent.color = Color.RED;
					fixupNode.parent.leftRotate(this);
					sibling = fixupNode.parent.right;
				}
				if(sibling.left.color == Color.BLACK && sibling.right.color == Color.BLACK){
					/* case 1 */
					sibling.color = Color.RED;
					fixupNode = fixupNode.parent;
				}
				else{
					if(sibling.right.color == Color.BLACK){
						/* case 3 를 case 2로 바꾸는 과정 */
						sibling.left.color = Color.BLACK;
						sibling.color = Color.RED;
						sibling.rightRotate(this);
						sibling = fixupNode.parent.right;
					}
					sibling.color = fixupNode.parent.color;
					fixupNode.parent.color = Color.BLACK;
					sibling.right.color = Color.BLACK;
					fixupNode.parent.leftRotate(this);
					fixupNode = this.root; //이후 바로 while문 빠져나가기 위해서
				}
			}
			else { 
				//fixupNode == fixupNode.parent.right
				//line 192~ 218의 then 코드 에서 left, right를 서로 바꿔주면 됨.
				
				Node sibling = fixupNode.parent.left;
				if(sibling.color == Color.RED){
					/* case 5 -> case 1,2,3 으로 바꾸는 과정 */
					sibling.color = Color.BLACK;
					fixupNode.parent.color = Color.RED;
					fixupNode.parent.rightRotate(this);
					sibling = fixupNode.parent.left;
				}
				if(sibling.right.color == Color.BLACK && sibling.left.color == Color.BLACK){
					/* case 1 */
					sibling.color = Color.RED;
					fixupNode = fixupNode.parent;
				}
				else{
					if(sibling.left.color == Color.BLACK){
						/* case 3 를 case 2로 바꾸는 과정 */
						sibling.right.color = Color.BLACK;
						sibling.color = Color.RED;
						sibling.leftRotate(this);
						sibling = fixupNode.parent.left;
					}
					sibling.color = fixupNode.parent.color;
					fixupNode.parent.color = Color.BLACK;
					sibling.left.color = Color.BLACK;
					fixupNode.parent.rightRotate(this);
					fixupNode = this.root; //이제 바로 while문 빠져나가기 위해서
				}
			}
		}
		fixupNode.color = Color.BLACK;
	}

	/* SEARCH */
	public Node binarySearch(int value) {
		Node curNode = this.root;
		if(curNode == this.nil) return null;
		
		while (curNode != this.nil) {
			if (value < curNode.value)
				curNode = curNode.left;
			else if (value > curNode.value)
				curNode = curNode.right;
			else return curNode;
		}
		return null;
	}
}
