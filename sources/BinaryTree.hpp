#include <iostream>
#include <stack>
using namespace std;
namespace ariel{
template<typename T>
class BinaryTree {

	class Node {
		friend class BinaryTree;
	private:
		T value;
		Node* left;
		Node* right;
		Node* root;
		Node(): left(nullptr), right(nullptr), root(nullptr),value(0){}
		Node(const T& v) : value(v), left(nullptr), right(nullptr), root(nullptr) {}
	};

	class PreorderIterator {
	private:
		Node* PreOrderNode;
	public:

        PreorderIterator(Node* root= nullptr)
		{
			PreOrderNode = root;
		}
		
		Node* getNode() 
		{
			return PreOrderNode;
		}
		T& operator*() const
		{
			return PreOrderNode->value;
		}
		T* operator->() const
		{
			return &(PreOrderNode->value);
		}
		bool operator!=(const PreorderIterator& other) const
		{
			return PreOrderNode != other.PreOrderNode;
		}
		bool operator==(const PreorderIterator& other) const
		{
			return PreOrderNode == other.PreOrderNode;
		}
		PreorderIterator operator++(int)
		{
			PreorderIterator i = *this;
			++* this;
			return i;
		}

		PreorderIterator& operator++()
		{
			if (PreOrderNode->left != NULL)
			{
				PreOrderNode = PreOrderNode->left;
			}
			else if (PreOrderNode->right != NULL)
			{
				PreOrderNode = PreOrderNode->right;
			}
			else
			{
				while (PreOrderNode->root != NULL &&
					(PreOrderNode->root)->right != NULL &&
					(PreOrderNode->root)->left != NULL &&
					(PreOrderNode->root)->right == PreOrderNode)
				{
					PreOrderNode = PreOrderNode->root;
				}
				if (PreOrderNode->root != NULL)
				{
					PreOrderNode = (PreOrderNode->root)->right;
				}
				else
				{
					PreOrderNode = NULL;
				}
			}
			return *this;
		}

		PreorderIterator& operator--()
		{
			if (PreOrderNode->root == NULL)
			{
				PreOrderNode = NULL;
				return *this;
			}
			if ((PreOrderNode->root)->left != NULL && (PreOrderNode->root)->left != PreOrderNode)
			{
				Node* tmp = (PreOrderNode->root)->left;
				while (PreOrderNode != tmp)
				{
					while (tmp->right != NULL)
					{
						tmp = tmp->right;
					}
					PreOrderNode = tmp;
					if (tmp->left != NULL)
					{
						tmp = tmp->left;
					}
				}
			}
			else
			{
				PreOrderNode = PreOrderNode->root;
			}
			return *this;
		}


	};

	class InorderIterator {
	private:
		Node* InOrderNode;
	public:
	
		InorderIterator(Node* root = nullptr)
		{
			if (!root)
			{
				InOrderNode = nullptr;
				return;
			}
			InOrderNode = root;
			while (InOrderNode->left != NULL)
			{
				InOrderNode = InOrderNode->left;
			}
		}
		
		Node* getNode() 
		{
			return InOrderNode;
		}
		T& operator*() const
		{
			return InOrderNode->value;
		}
		T* operator->() const
		{
			return &(InOrderNode->value);
		}
		bool operator!=(const InorderIterator& other) const
		{
			return InOrderNode != other.InOrderNode;
		}
		bool operator==(const InorderIterator& other) const
		{
			return InOrderNode == other.InOrderNode;
		}
		InorderIterator operator++(int)
		{
			InorderIterator i = *this;
			++* this;
			return i;
		}
		InorderIterator& operator++()
		{
			// if i have a right son
			if (InOrderNode->right != NULL)
			{
				InOrderNode = InOrderNode->right;
				while (InOrderNode->left != NULL)
				{
					InOrderNode = InOrderNode->left;
				}
			}
			else
			{
				bool nodeFound = false;
				Node* tmp = InOrderNode;

				while (!nodeFound && InOrderNode != NULL)
				{
					// if im a right son myself
					if (InOrderNode->root == NULL || (InOrderNode->root)->right == tmp)
					{
						InOrderNode = InOrderNode->root;
					}
					else
					{
						InOrderNode = tmp->root;
						nodeFound = true;
					}
				}
			}
			return *this;
		}

		InorderIterator& operator--()
		{
			// if i have a left son
			if (InOrderNode->left != NULL)
			{
				InOrderNode = InOrderNode->left;
				while (InOrderNode->right != NULL)
				{
					InOrderNode = InOrderNode->right;
				}
			}
			else
			{
				// if im a left son myself
				if (InOrderNode->root == NULL || (InOrderNode->root)->left == InOrderNode)
				{
					// go up until youre right son
					while (InOrderNode != NULL && (InOrderNode->root)->right != InOrderNode)
					{
						InOrderNode = InOrderNode->root;
					}
				}
				InOrderNode = InOrderNode->root;
			}
			return *this;
		}

	};

	class PostorderIterator {
	private:
		Node* PostOrderNode;
	public:

		PostorderIterator(Node* root = nullptr)
		{
			if (!root)
			{
				PostOrderNode = nullptr;
				return;
			}
			Node* tmp = root;
			while (PostOrderNode != tmp)
			{
				while (tmp->left != NULL)
				{
					tmp = tmp->left;
				}
				PostOrderNode = tmp;
				if (tmp->right != NULL)
				{
					tmp = tmp->right;
				}
			}
		}
		Node* getNode() 
		{
			return PostOrderNode;
		}
		T& operator*() const
		{
			return PostOrderNode->value;
		}
		T* operator->() const
		{
			return &(PostOrderNode->value);
		}
		bool operator!=(const PostorderIterator& other) const
		{
			return PostOrderNode != other.PostOrderNode;
		}
		bool operator==(const PostorderIterator& other) const
		{
			return PostOrderNode == other.PostOrderNode;
		}
		PostorderIterator operator++(int)
		{
			PostorderIterator i = *this;
			++* this;
			return i;
		}
		PostorderIterator& operator++()
		{
			if (PostOrderNode->root == NULL)
			{
				PostOrderNode = PostOrderNode->root;
				return *this;
			}

			// my right brother
			Node* rightBrother = (PostOrderNode->root)->right;

			//do i have a right brother, and thats not me
			if (rightBrother != NULL && PostOrderNode != rightBrother)
			{
				while (PostOrderNode != rightBrother)
				{
					while (rightBrother->left != NULL)
					{
						rightBrother = rightBrother->left;
					}
					PostOrderNode = rightBrother;
					if (rightBrother->right != NULL)
					{
						rightBrother = rightBrother->right;
					}
				}
			}
			else
			{
				PostOrderNode = PostOrderNode->root;
			}
			return *this;
		}

		PostorderIterator& operator--()
		{
			// do i have a right son
			if (PostOrderNode->right != NULL)
			{
				PostOrderNode = PostOrderNode->right;
			}
			// do i have a left son
			else if (PostOrderNode->left != NULL)
			{
				PostOrderNode = PostOrderNode->left;
			}
			else
			{
				bool nodeFound = false;

				while (!nodeFound && PostOrderNode != NULL)
				{
					// do i have a left brother and its not me
					if (PostOrderNode->root != NULL && (PostOrderNode->root)->left != NULL && (PostOrderNode->root)->left != PostOrderNode)
					{
						// node found
						PostOrderNode = (PostOrderNode->root)->left;
						nodeFound = true;
					}
					else
					{
						// go up 1 level
						PostOrderNode = PostOrderNode->root;
					}
				}
			}
			return *this;
		}


	};

private:
	Node* root;
public:
	BinaryTree() : root(nullptr) {}

	//BinaryTree(BinaryTree<T>*);
	
	~BinaryTree() {
		if (root != nullptr) {
			delete root;
		}
	}


	BinaryTree<T>(BinaryTree<T>& t)
	{
		if (t.root == NULL) {
			root = NULL;
		}
		else {
			copy(this->root, t.root);
		}
	}
	BinaryTree<T>(BinaryTree<T>&& t)noexcept
	{	
	root=t.root;
	}

	void copy(Node*& root, Node*& otherRoot)
	{
		if (otherRoot == NULL)
		{
			root = NULL;
		}
		else
		{
			root = new Node(otherRoot->value);
			copy(root->left, otherRoot->left);
			copy(root->right, otherRoot->right);
		}
	}
		void copy(Node*& root,  Node*const& otherRoot)
	{
		if (otherRoot == NULL)
		{
			root = NULL;
		}
		else   
		{
			root = new Node(otherRoot->value);
			copy(root->left, otherRoot->left);
			copy(root->right, otherRoot->right);
		}
	}

	BinaryTree<T>& add_root(T v)
	{
		if (root == nullptr)
		{
			root = new Node();
			root->value = v;
		}
		root->value = v;
		return *this;
	}

	BinaryTree<T>& add_left(T RootVal, T LeftVal)
	{
		if (IsParent(RootVal))
		{
			for (auto it = begin_preorder(); it != end_preorder(); ++it)
			{
				if ((*it) == RootVal)
				{
					it.getNode()->left = new Node();
					(it.getNode()->left)->root->value = LeftVal;
				}
			}
		}
		else
		{
			throw "Parent is not exist";
		}
		return *this;
	}
	BinaryTree<T>& add_right(T RootVal, T RightVal)
	{
		if (IsParent(RootVal))
		{
			for (auto it = begin_preorder(); it != end_preorder(); ++it) {
				if ((*it) == RootVal) {
					it.getNode()->right = new Node();
					it.getNode()->right->root->value = RightVal;
				}
			}
		}
		else
		{
			throw "Parent is not exist";
		}
		return *this;
	}
	
        auto begin()
        {
            return begin_inorder();
        }

        auto end()
        {
            return end_inorder();
        }

	PreorderIterator begin_preorder()
	{
		return PreorderIterator(root);
	}
	PreorderIterator end_preorder()
	{
		return PreorderIterator();
	}

	InorderIterator begin_inorder() 
	{
		return InorderIterator(root);
	}
	InorderIterator end_inorder()
	{
		return InorderIterator();
	}

	PostorderIterator begin_postorder()
	{
		return PostorderIterator(root);
	}
	PostorderIterator end_postorder()
	{
		return PostorderIterator();
	}


	bool operator==(const BinaryTree<T>& Tree)
	{
		InorderIterator thisIt = this->begin_inorder();
		InorderIterator thatIt = Tree.begin_inorder();
		while (thisIt != this->end_inorder() && thatIt != Tree.end_inorder())
		{
			if (thisIt != thatIt){
				return false;
				}
		}
		return true;
	}
	bool operator!=(const BinaryTree& Tree)
	{
		InorderIterator thisIt = this->begin_inorder();
		InorderIterator thatIt = Tree.begin_inorder();
		while (thisIt != this->end_inorder() && thatIt != Tree.end_inorder())
		{
			if (thisIt == thatIt){
				return false;
				}
		}
		return true;
	}
	
	

	friend std::ostream& operator<<(std::ostream& os, const BinaryTree& binaryTree)
	{
		os << "\nPrint the tree:\n";
		std::stack<Node*> s;
		Node* curr = binaryTree.root;

		while (curr != NULL || !s.empty()) {
			while (curr != NULL) {
				s.push(curr);
				curr = curr->left;
			}
			curr = s.top();
			s.pop();
			os << curr->value << " ";
			curr = curr->right;
		}
		os << endl;
		return os;
	}
	// NOLINTNEXTLINE(bugprone-unhandled-self-assignment)
BinaryTree<T>& operator=(const BinaryTree<T>& binaryTree)
{
Node* tmp = new Node();
this->copy(tmp, binaryTree.root);

delete this->root;
this->copy(this->root, tmp);
return *this;
}

 BinaryTree<T>& operator=(BinaryTree<T>&& binaryTree)noexcept
{
if(this!=&binaryTree)
{
this->root=binaryTree->root;
} 
}
      
	bool IsParent(T RootVal) 
	{
		for (auto it = begin_preorder(); it != end_preorder(); ++it) {
			if ((*it) == RootVal){
				return true;
				}
			}
		return false;
		}
};
}
