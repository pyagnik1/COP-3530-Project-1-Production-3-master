#include <bits/stdc++.h>
using namespace std;
#define COUNT 10

class gatorInfo
{
public:
	int gatorID;
	string gatorName;
	gatorInfo *left;
	gatorInfo *right;
	int height;
};

int height(gatorInfo *root)
{
	if (root == NULL)
	{
		return 0;
	}
	return root->height;
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

gatorInfo *newGatorInfo(string gatorName, int gatorID)
{
	gatorInfo *root = new gatorInfo();
	root->gatorID = gatorID;
	root->left = NULL;
	root->right = NULL;
	root->gatorName = gatorName;
	root->height = 1;
	return (root);
}

gatorInfo *rightRotate(gatorInfo *root)
{
	gatorInfo *newParent = root->left;
	gatorInfo *garndChild = newParent->right;
	/*
			Pre rotation-->
			root->val = 3, newParent->val = 2, grandChild = NULL
								root->	3
										/
			newParent	->	2	
									/		\					
								1			NULL	<- grandChild			
		*/
	newParent->right = root;
	root->left = garndChild;
	/*
				Post rotation
				newParent->val = 2, newParent->right->val = 3
							newParent->	2
												/		\
											1				3 <-root
														/
													NULL <-grandChild
			*/
	root->height = max(height(root->left), height(root->right)) + 1;
	newParent->height = max(height(newParent->left), height(newParent->right)) + 1;

	return newParent;
}

gatorInfo *leftRotate(gatorInfo *root)
{
	gatorInfo *newParent = root->right;
	gatorInfo *garndChild = newParent->left;
	/*
			Pre rotation
							root->	1
												\
							newParent->	2			
												/		\					
			grandChild->		NULL	   3				
		*/

	newParent->left = root;
	root->right = garndChild;

	root->height = max(height(root->left), height(root->right)) + 1;
	newParent->height = max(height(newParent->left), height(newParent->right)) + 1;

	/*
		Post rotation
		newParent->		2
								/		\
			root->	1				3
								\
								NULL <- grandChild
		*/
	return newParent;
}

int getBalance(gatorInfo *root)
{
	if (root == NULL)
	{
		return 0;
	}
	return height(root->left) - height(root->right);
}

gatorInfo *balanceTree(gatorInfo *root, int gatorID, int balance)
{
	// Left Left Case
	/*
		-->Left Left case
		--> fix: Rotate right
				-->root->left->val = 2
						3 <-balance =2
					/
				2	<-balance =1			-->				2 <- balance = 1- 1 = 0
			/															/		\
		1															1				3
		*/
	if (balance > 1 && gatorID < root->left->gatorID){
		return rightRotate(root);
	}
	// Right Right Case
	/*
		--> Right Right case
		--> fix: Rotate 1 to left
		1 <- balance = -2
			\
				2	<- balance = -1			-->			2 <- balance = 1 - 1 = 0
					\													/		\
						3											1				3
		*/
	if (balance < -1 && gatorID > root->right->gatorID){
		return leftRotate(root);
	}

	// Left Right Case
	/*
		-->Left Right case
		--> fix: 1.Rotate left
				-->root->val = 1, root->left->val = 2 
		
			3	<- balance = 2								3 <- balance = 2
		/																/
		1	<- balance = -1		--> 			2 <- balance = 1
		\														/
			2												1
		-->2. rotate righ
			-->root->val = 2
						3 <- balance = 2
					/
				2	<- balance = 1		-->			2 <- balance = 1 - 1 = 0
			/														/		\
		1														1				3
		
		*/
	if (balance > 1 && gatorID > root->left->gatorID)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	// Right Left Case
	/*
		-->Right Left case
			--> fix: 1. Rotae right
			-->root->right->val = 3
		
			1	<- balance = -2								1 <- balance = -2
				\																\
					3 <- balance = 1		--> 				2	<- balance = -1
				/																		\				
			2																				3
			-->2. Rotate left	
			-->root->val = 2, root->right->val = 3
			1	<-balance = -2
				\
					2		<- balance = -1			--> 				2 <- balance = 1 - 1 = 0
						\																/		\
							3														1				3
		*/
	if (balance < -1 && gatorID < root->right->gatorID)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	return root;
}

gatorInfo *insertGatorInfo(gatorInfo *root, string gatorName, int gatorID)
{

	if (root == NULL)
	{
		cout << "successful\n";
		return (newGatorInfo(gatorName, gatorID));
	}
	if (gatorID == root->gatorID)
	{
		// Equal gatorIDs are not allowed in BST
		cout << "unsuccessful\n";
		return root;
	}
	/*
		insert 1

							10
						/			\
					9					11
				/		\
			3			8

		*/

	if (gatorID < root->gatorID)
	{
		root->left = insertGatorInfo(root->left, gatorName, gatorID);
	}
	/*
		insert 12

							10
						/			\
					9					11
				/		\
			1			8



		*/
	if (gatorID > root->gatorID)
	{
		root->right = insertGatorInfo(root->right, gatorName, gatorID);
	}

	root->height = 1 + max(height(root->left), height(root->right));

	int balance = getBalance(root);

	root = balanceTree(root, gatorID, balance);

	return root;
}

void print2DUtil(gatorInfo *root, int space)
{

	if (root == NULL)
		return;

	space += COUNT;

	print2DUtil(root->right, space);

	cout << endl;
	for (int i = COUNT; i < space; i++)
		cout << " ";
	cout << root->gatorName << "\n";

	print2DUtil(root->left, space);
}

void print2D(gatorInfo *root)
{

	print2DUtil(root, 0);
}

int searchGatorName(gatorInfo *root, const string &gatorName)
{
	if (root == NULL)
	{
		return 0;
	}
	/*
	Find Poojan

						Parth
					/				\
			Poojan			Poojan	

	*/

	/*
		To find the duplicate name with 2
		diffrent gatorID I need to first
		traverse the left subtree, if such 
		name exists then print it, after 
		traverse the right subtree and
		print if the name was found
	*/
	searchGatorName(root->left, gatorName);
	if (gatorName == root->gatorName)
	{

		cout << root->gatorID << "\n";
	}
	searchGatorName(root->right, gatorName);

	return 1;
}

gatorInfo *findMin(gatorInfo *node)
{
	gatorInfo *temp = node;

	while (temp && temp->left != NULL){
		temp = temp->left;
	}

	return temp;
}

gatorInfo *deleteGatorID(gatorInfo *root, int gatorID)
{
	if (root == NULL)
		return root;

	//Deleting gatorID is first requires searching 
	//for the gatorID in the same way as bst searching
	if (gatorID < root->gatorID)
	{
			/*
			delet 4

															8
														/		\
													7				10
												/		\			
		Find this node->		4		5				

		*/
		root->left = deleteGatorID(root->left, gatorID);
	}

	
	if (gatorID > root->gatorID)
	{
		 /*
			delet 10

															8
														/		\
													7				10 <- delet this
												/		\			
												4		5				

		*/
		root->right = deleteGatorID(root->right, gatorID);
	}

	/*

			found the node

															8
														/		\
													7				10 <- found
												/		\		/		\
												4		5	NULL	NULL


		*/
	if(gatorID == root->gatorID)
	{
		// node has no child
		if (root->left == NULL and root->right == NULL)
		{
				/*

			pre return

															8
														/		\
													7				10 <- root
												/		\		/		\
												4		5	NULL	NULL


		*/
			return NULL;
				/*

			post return

															8
														/		\
													7			NULL<- root
												/		\		
												4		5	


		*/

		}

		// node with only one child or no child
		else if (root->left == NULL)
		{
			/*
				pre return

															8
														/		\
													7				10<- root
												/		\		 /	\
												4		5		NULL	2<-temp

			*/
			gatorInfo *temp = root->right;
			free(root);
			return temp;
			/*
				post return

															8
														/		\
													7				2<- temp
												/		\		 
												4		5			

			*/
		}
		else if (root->right == NULL)
		{
			/*
				pre return

															8
														/		\
										root->7				10
												/		\		 
									temp->4		NULL	

			*/
			gatorInfo *temp = root->left;
			free(root);
			return temp;
			/*
				pre return

															8
														/		\
										temp->4				10
												

			*/
		}

			/*
						pre return

																	8
																/		\
											root->	7				2
														/		\		 
													4				5	
																/		\
		temp =	return of findMin->3			8		


			while (temp && temp->left != NULL){
					temp = temp->left;
				}
			*/
		
		gatorInfo *temp = findMin(root->right);

		/*
						pre return

																	8
																/		\
											root->	3				2
														/		\		 
													1				5	
																/		\
															3				8		


			while (temp && temp->left != NULL){
					temp = temp->left;
				}
		*/
		root->gatorID = temp->gatorID;
		root->gatorName = temp->gatorName;

		
		root->right = deleteGatorID(root->right, temp->gatorID);
		/*
						post return

																	8
																/		\
											root->	3				2
														/		\		 
													1				5	
																/		\
				delete(root->right)->	3				8		


			
		*/
	}
	cout << "successful\n";
	return root;
}

void searchGatorID(gatorInfo *root, int gatorID, gatorInfo *parent)
{

	if (root == NULL)
	{
		cout << "unsuccessful\n";
		return;
	}

	if (root->gatorID == gatorID)
	{
		cout << root->gatorName << "\n";
		return;
	}
	/*
			find 10

															8
														/		\
					find this->			7				10 
												/		\			
												4		5				

		*/
	if (gatorID < root->gatorID)
	{
		return searchGatorID(root->left, gatorID, root);
	}
	/*
			find 10

															8
														/		\
													7				10 <- find this
												/		\			
												4		5				

		*/
	return searchGatorID(root->right, gatorID, root);
}

void printInorder(gatorInfo *root)
{
	if(root != NULL)
    {
        if(root->left) 
        {
            printInorder(root->left);
            cout << ", "; 
        }

        cout << root->gatorName;

        if(root->right)
        {
            cout << ", "; 
            printInorder(root->right);
        }
   }	
}

void printPreorder(gatorInfo *root)
{
	if (root != NULL)
	{
		cout << root->gatorName;
		if (root->left != NULL || root->right != NULL)
		{
			cout << ", ";
		}
		printPreorder(root->left);
		if (root->left && root->right)
		{
			cout << ", ";
		}
		printPreorder(root->right);
	}
}

bool printPostorder(gatorInfo *root)
{

	if (!root)
	{
		return false;
	}
	if (printPostorder(root->left)){
		cout << ", ";
	}
	if (printPostorder(root->right)){
		cout << ", ";
	}
	cout << root->gatorName;
	return true;
}

int findLevel(gatorInfo *root)
{
	if (root->left == NULL && root->right == NULL)
	{

		/*

					1
				/		\
			NULL		NULL

		*/
		return 1;
	}

	int left = 0;
	if (root->left != NULL)
	{
		//This will traverse the left subtree and find the level
		left = findLevel(root->left);
	}

	int right = 0;
	if (root->right != NULL)
	{
		//This will traverse the right subtree and find the level
		right = findLevel(root->right);
	}

	//Since the level of left or right might be the highest, I need to find the max of the two
	return (max(left, right) + 1);
}

gatorInfo *removeNthInorder(gatorInfo *root, int n, gatorInfo *temp)
{
	static int count = 0;
	if (root == NULL)
		return root;

	if (count <= n)
	{

		count++;

		if (count == n)
		{
			//cout << temp->gatorName << "<--\n";

			root = deleteGatorID(root, temp->gatorID);

			return root;

		}

		//To find the Nth node in the tree, I first traverse the left subtree and then travel the right subtree

		removeNthInorder(root, n, temp->right);

		removeNthInorder(root, n, temp->left);

	}

	return root;

}

bool isNumber(const string &str)
{
	for (char const &c : str)
	{

		if (std::isdigit(c) == 0)
		{
			return false;
		}
	}
	return true;
}

int main()
{

	gatorInfo *root = NULL;

	int iter = 0;

	cin >> iter;

	for (int i = 0; i < iter; i++)
	{

		string comand;

		cin >> comand;

		if (comand == "insert")
		{
			int gatorID = 0;
			string gatorName;


			cin >> gatorName;

			

			cin >> gatorID;
			gatorName.erase(remove(gatorName.begin(), gatorName.end(), '\"'), gatorName.end());

			root = insertGatorInfo(root, gatorName, gatorID);
		}
		if (comand == "remove")
		{
			int gatorID;
			cin >> gatorID;

			root = deleteGatorID(root, gatorID);
		}

		if (comand == "search")
		{
			string searchThis;
			cin >> searchThis;

			searchThis.erase(remove(searchThis.begin(), searchThis.end(), '\"'), searchThis.end());

			if (isNumber(searchThis))
			{

				stringstream convertToInt(searchThis);

				int x = 0;
				convertToInt >> x;
				searchGatorID(root, x, NULL);
			}

			if (!isNumber(searchThis))
			{
				int val = 0;

				val = searchGatorName(root, searchThis);

				if (val == 0)
				{
					cout << "unsuccessful\n";
				}
			}
		}

		if (comand == "printLevelCount")
		{
			int level = findLevel(root);

			cout << level << "\n";
		}

		if (comand == "removeInorder")
		{
			int num = 0;
			cin >> num;
			gatorInfo *temp = new class gatorInfo;
			temp = root;
			root = removeNthInorder(root, num, temp);
		}
		if (comand == "printInorder")
		{
			
			printInorder(root);
			cout << "\n";
		}
		if (comand == "printPreorder")
		{
			printPreorder(root);
			cout << "\n";
		}
		if (comand == "printPostorder")
		{
			bool res;
			res = printPostorder(root);
			cout << "\n";
		}
		if (comand == "print2D")
		{
			print2D(root);
		}
	}
	return 0;
}