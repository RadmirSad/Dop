#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
using namespace std;

typedef struct Item
{
	int key;
	int balance;
	struct Item* left, * right, * parent;
}Item;

void get_string(char** info);
int get_int(int* key);
void add_elem(Item** root, int* count, int key, bool* flag);
void delete_elem(Item** root, int* count);
Item* find_elem(Item* root, int key, int flag); // 0 - add, 1 - find, 2 - delete
void put_tree(Item* root, int dop);
void del_tree(Item* root);
void timing();
void left_rotate(Item* leaf, Item** root);
void right_rotate(Item* leaf, Item** root);
int node_correction_for_addition(Item* new_node, Item** root);
void tree_correction_for_addition(Item* node, Item** root);
int tree_correction_for_deletion(Item** node, Item** root);
void change_pointers(Item** node, Item** root);
Item* find_max(Item* node);
int find_designated_nodes(Item* root, bool* flag);

int main()
{
	setlocale(LC_ALL, "Rus");
	Item* root = nullptr;
	int k = 0, flag_for_download = 0, count = 0;
	bool flag = false;
	while (!flag)
	{
		cout << "Выберите действие:\n";
		cout << "1. Ввод элемента в дерево\n";
		cout << "2. Удаление элемента из дерева\n";
		cout << "3. Поиск элемента в дереве по ключу\n";
		cout << "4. Просмотр элементов дерева\n";
		cout << "5. Удаление дерева и завершение работы\n";
		cout << "6. Таймирование программы\n";
		cout << "7. Вывод вершин, у которых высоты поддеревьев равны, а количество потомков в правом и левом поддеревьях разное\n";
		cout << "8. Вывод максимального элемента\n";
		int n = 0;
		while (n != 1)
		{
			n = get_int(&k);
			if (n != 1)
			{
				if (n == -1) cout << "Введён недопустимый символ.\n";
				cout << "Введите значение заново:\n";
			}
		}
		switch (k)
		{
		case 1:
			add_elem(&root, &count, 0, nullptr);
			break;
		case 2:
			if (count)
			{
				delete_elem(&root, &count);
				cout << "Элемент успешно удалён.\n";
			}
			else cout << "Удаление невозможно, поскольку дерево пустое.\n";
			break;
		case 3:
			if (count)
			{
				int key = 0, n = 0;
				while (n != 1)
				{
					n = get_int(&key);
					if (n != 1)
					{
						if (n == -1) cout << "Введён недопустимый символ.\n";
						cout << "Введите значение заново:\n";
					}
				}
				find_elem(root, key, 1);
			}
			else cout << "Поиск невозможен, поскольку дерево пустое.\n";
			break;
		case 4:
			if (count)
				put_tree(root, 0);
			else cout << "Дерево пустое.\n";
			break;
		case 5:
			del_tree(root);
			cout << "Дерево успешно удалено.\n";
			root = nullptr;
			count = 0;
			flag = true;
			break;
		case 6:
			timing();
			break;
		case 7:
			if (count)
			{
				bool flag = false;
				find_designated_nodes(root, &flag);
				if (!flag) cout << "Таких элементов не найдено.\n";
			}
			else
				cout << "Дерево пустое.\n";
			break;
		case 8:
			if (count)
			{
				Item* buf = nullptr;
				buf = find_max(root);
				cout << "Ключ максимального элемента: " << buf->key << endl;
			}
			else cout << "Дерево пустое.\n";
			break;
		default:
			cout << "Функции с таким номером не существует.\n";
			break;
		}
	}
	return 0;
}

int find_designated_nodes(Item* root, bool* flag)
{
	int left, right;
	if (root != nullptr)
	{
		left = find_designated_nodes(root->left, flag);
		right = find_designated_nodes(root->right, flag);
		if ((left != right) && (root->balance == 0))
		{
			cout << "[" << root->key << "]\n";
			*flag = true;
		}
		return left + right + 1;
	}
	else return 0;
}

void add_elem(Item ** root, int *count, int key,  bool * flag_for_addition)
{
	int my_key;
	if (flag_for_addition == nullptr)
	{
		int n = 0;
		cout << "Введите ключ:\n";
		while (n != 1)
		{
			n = get_int(&my_key);
			if (n != 1)
			{
				if (n == -1) cout << "Введён недопустимый символ.\n";
				cout << "Введите значение заново:\n";
			}
		}
	}
	else
	{
		my_key = key;
	}
	if (*count != 0)
	{
		Item* dop;
		dop = find_elem(*root, my_key, 0);
		if (dop != nullptr)
		{
			Item* par = dop;
			if (my_key < dop->key)
			{
				dop->left = new Item;
				dop = dop->left;
			}
			else
			{
				dop->right = new Item;
				dop = dop->right;
			}
			dop->key = my_key;
			dop->parent = par;
			dop->left = nullptr;
			dop->right = nullptr;
			dop->balance = 0;
			(*count)++;
			node_correction_for_addition(dop, root);
			if (flag_for_addition == nullptr) cout << "Элемент успешно добавлен.\n";
		}
		else
			if (flag_for_addition == nullptr)
				cout << "Элемент с таким ключём уже существует.\n";
			else 
				*flag_for_addition = false;
	}
	else
	{
		*root = new Item;
		(*root)->balance = 0;
		(*root)->key = my_key;
		(*root)->left = nullptr;
		(*root)->parent = nullptr;
		(*root)->right = nullptr;
		(*count)++;
		if (flag_for_addition == nullptr) cout << "Элемент успешно добавлен.\n";
	}
}

int node_correction_for_addition(Item * new_node, Item ** root)
{
	Item* par = new_node->parent;
	while ((par != nullptr) && (par->balance == 0))
	{
		if (new_node == par->left)
			par->balance = -1;
		else
			par->balance = 1;
		new_node = par;
		par = new_node->parent;
	}
	if (par == nullptr)
		return 1;
	if ( ( (new_node == par->left) && (par->balance == 1) ) || ( (new_node == par->right) && (par->balance == -1) ) )
	{
		par->balance = 0;
		return 1;
	}
	tree_correction_for_addition(new_node, root);
	return 1;
}

void tree_correction_for_addition(Item* node, Item** root) // Снова не рассмотрены случаи!!!
{
	Item* par = node->parent;
	if ((node == par->left) && (par->balance == -1))
	{
		if (node->balance == -1) // 1
		{
			right_rotate(par, root);
			par->balance = 0;
			node->balance = 0;
		}
		else
		{
			switch (node->right->balance)
			{
			case -1: // 2a
				node->balance = 0;
				par->balance = 1;
				break;
			case 1: // 2b
				node->balance = -1;
				par->balance = 0;
				break;
			case 0: // 2c*
				node->balance = 0;
				par->balance = 0;
				break;
			}
			node->right->balance = 0;
			left_rotate(node, root);
			right_rotate(par, root);
		}
	}
	else
	{
		if (node->balance == 1) // 3
		{
			left_rotate(par, root);
			par->balance = 0;
			node->balance = 0;
		}
		else
		{
			switch (node->left->balance)
			{
			case 1: // 4a
				node->balance = 0;
				par->balance = -1;
				break;
			case -1: // 4b
				node->balance = 1;
				par->balance = 0;
				break;
			case 0: // 4c*
				node->balance = 0;
				par->balance = 0;
				break;
			}
			node->left->balance = 0;
			right_rotate(node, root);
			left_rotate(par, root);
		}
	}
}

void left_rotate(Item* leaf, Item** root)
{
	Item* dopRight = leaf->right, * par = leaf->parent;
	leaf->right = dopRight->left;
	if (dopRight->left != nullptr)
		dopRight->left->parent = leaf;
	dopRight->parent = par;
	if (par == nullptr)
		* root = dopRight;
	else
	{
		if (par->left == leaf)
			par->left = dopRight;
		else
			par->right = dopRight;
	}
	dopRight->left = leaf;
	leaf->parent = dopRight;
}

void right_rotate(Item* leaf, Item** root)
{
	Item* dopLeft = leaf->left, * par = leaf->parent;
	leaf->left = dopLeft->right;
	if (dopLeft->right != nullptr)
		dopLeft->right->parent = leaf;
	dopLeft->parent = par;
	if (par == nullptr)
		* root = dopLeft;
	else
	{
		par->left == leaf? par->left = dopLeft:	par->right = dopLeft;
	}
	dopLeft->right = leaf;
	leaf->parent = dopLeft;
}

void delete_elem(Item** root, int* count)
{
	int my_key, n = 0;
	cout << "Введите ключ:\n";
	while (n != 1)
	{
		n = get_int(&my_key);
		if (n != 1)
		{
			if (n == -1) cout << "Введён недопустимый символ.\n";
			cout << "Введите значение заново:\n";
		}
	}
	Item* del_elem = nullptr;
	del_elem = find_elem(*root, my_key, 2);
	if (del_elem != nullptr)
	{
		Item* par = nullptr;
		if ((del_elem->left == nullptr) || (del_elem->right == nullptr))
			change_pointers(&del_elem, root);
		else
		{
			Item* buf = find_max(del_elem->left);
			del_elem->key = buf->key;
			change_pointers(&buf, root);
			del_elem = buf;
		}
		(*count)--;
		par = del_elem;
		int dh = 0, correct = 0;
		while (par != nullptr)
		{
			if (par != del_elem)
				del_elem == par->left ? par->balance++: par->balance--;
			dh = abs(par->balance);
			if (dh > 1)
			{
				par->balance > 0 ? par->balance-- : par->balance++;
				correct = tree_correction_for_deletion(&del_elem, root);
				if (correct)
					par = del_elem->parent;
				else return;
			}
			else
				if (dh == 1)
					return;
				else
				{
					del_elem = par;
					par = par->parent;
				}
		}
	}
}

int tree_correction_for_deletion(Item** node, Item** root)
{
	Item* par = nullptr;
	(*node)->parent == nullptr ? par = (*node) : par = (*node)->parent;
	if (par->balance == 1)
	{
		switch (par->right->balance)
		{
		case 1: // 1
			left_rotate(par, root);
			par->balance = 0;
			par->parent->balance = 0;
			(*node) = par->parent;
			return 1;
		case -1: // 2
			right_rotate(par->right, root);
			left_rotate(par, root);
			(*node) = par->parent;
			switch (par->parent->balance)
			{
			case 1: // 2a
				par->balance = -1;
				par->parent->right->balance = 0;
				break;
			case 0: // 2b
				par->balance = 0;
				par->parent->right->balance = 0;
				break;
			case -1: // 2c
				par->balance = 0;
				par->parent->right->balance = 1;
				break;
			}
			par->parent->balance = 0;
			return 1;
		case 0: // 3
			left_rotate(par, root);
			par->balance = 1;
			par->parent->balance = -1;
			(*node) = par->parent;
			return 0;
		default:
			cout << "Error in delete.\n";
			return 0;
		}
	}
	else // reverse
	{
		switch (par->left->balance)
		{
		case -1: // 1*
			right_rotate(par, root);
			par->balance = 0;
			par->parent->balance = 0;
			(*node) = par->parent;
			return 1;
		case 1: // 2*
			left_rotate(par->left, root);
			right_rotate(par, root);
			switch (par->parent->balance)
			{
			case -1: // 2a*
				par->balance = 1;
				par->parent->left->balance = 0;
				break;
			case 0: // 2b*
				par->balance = 0;
				par->parent->left->balance = 0;
				break;
			case 1: // 2c*
				par->balance = 0;
				par->parent->left->balance = -1;
			}
			par->parent->balance = 0;
			(*node) = par->parent;
			return 1;
		case 0: // 3*
			right_rotate(par, root);
			par->balance = -1;
			par->parent->balance = 1;
			(*node) = par->parent;
			return 0;
		default:
			cout << "Error in delete.\n";
			return 0;
		}
	}
}

void change_pointers(Item** node, Item ** root)
{
	Item* par = (*node)->parent, * dop;
	(*node)->left == nullptr ? dop = (*node)->right : dop = (*node)->left;
	if (dop != nullptr)
		dop->parent = par;
	if (par == nullptr) * root = dop;
	else
		if (par->left == (*node))
		{
			par->left = dop;
			par->balance++;
		}
		else
		{
			par->right = dop;
			par->balance--;
		}
	delete (*node);
	*node = par;
}

Item* find_max(Item* node)
{
	Item* dop = nullptr;
	while (node != nullptr)
	{
		dop = node;
		node = node->right;
	}
	return dop;
}

Item* find_elem(Item* root, int key, int flag_for_finding)
{
	Item* leaf = root;
	while (leaf != nullptr)
	{
		root = leaf;
		if (key == leaf->key)
		{
			switch (flag_for_finding)
			{
			case 0:
				return nullptr;
				break;
			case 1:
				cout << "Элемент с введённым ключом " << key << " найден." << endl;
				return nullptr;
				break;
			case 2:
				return leaf;
				break;
			}
		}
		else
		{
			if (key < leaf->key)
				leaf = leaf->left;
			else leaf = leaf->right;
		}
	}
	if (flag_for_finding > 0)
		cout << "Элемента с таким ключом не найдено.\n";
	return root;
}

void put_tree(Item *root, int dop)
{
	int i;
	if (root != nullptr)
	{
		put_tree(root->right, dop + 1);
		for (i = 0; i < dop; i++)
			cout << "\t";
		cout << "[" << root->key << "]" << endl;
		put_tree(root->left, dop + 1);
	}
}

void del_tree(Item* root)
{
	if (root != nullptr)
	{
		del_tree(root->right);
		del_tree(root->left);
		delete(root);
	}
}

void timing()
{
	Item* root = nullptr;
	int num_of_elem = 1000000, k = 10, count = 0, key, height = 0;
	clock_t first, last;
	srand(time(NULL));
	while (k-- > 0)
	{
		int i;
		bool flag;
		first = clock();
		for ( i = 0; i < num_of_elem; )
		{
			flag = true;
			key = rand() * rand();
			add_elem(&root, &count, key, &flag);
			if (flag) i++;
#ifdef DEBUG
			if (i % 1000000 == 0) cout << i << " элементов было добавлено.\n";
#endif
		}
		last = clock();
		Item* buf = root;
		while (buf != nullptr)
		{
			height++;
			buf->balance == 1 ? buf = buf->right : buf = buf->left;
		}
		del_tree(root);
		count = 0;
		root = nullptr;
		cout << "Тест №" << 10 - k << ", количество элементов = " << num_of_elem << ", высота дерева = " << height << ", время в секундах = " << (last - first) / CLK_TCK << endl;
		num_of_elem += 1000000;
	}
}

int get_int(int *key)
{
	char *str;
	get_string(&str);
	int i, flag = 0;
	while (flag == 0)
	{
		int len = strlen(str);
		for (i = 0; i < len; i++)
		{
			if ((str[i] < 48) || (str[i] > 57))
			{
				return -1;
			}
		}
		*key = atoi(str);
		free(str);
		flag = 1;
	}
	return 1;
}

void get_string(char** info)
{
	char buff[80] = "", * b;
	int len = 0;
	while (strlen(buff) == 0)
	{
		scanf("%79[^\n]", buff);
		if (strlen(buff) == 0)
		{
			cout << "Неверный формат ввода. Попробуйте снова:\n";
			scanf("%*c");
		}
	}
	len = strlen(buff) + 1;
	b = (char*)calloc(len, sizeof(char));
	strcat(b, buff);
	while (strlen(buff) == 79)
	{
		scanf("%79[^\n]", buff);
		len += strlen(buff);
		b = (char*)realloc(b, len);
		strcat(b, buff);
	}
	scanf("%*c");
	*info = b;
}