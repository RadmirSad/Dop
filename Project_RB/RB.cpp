#define _CRT_SECURE_NO_WARNINGS
#define RED 1
#define BLACK 0
#include <iostream>
#include <time.h>
using namespace std;

typedef struct Elem
{
	int key;
	int color;
	struct Elem * left, * right, * parent;
}Elem;

void lev_pov(Elem*, Elem**, Elem*);
void pr_pov(Elem*, Elem**, Elem*);
char* getstr();
int* getint();
void create_tree_rand(Elem**, Elem* const, int);
void user_create(Elem**, Elem* const);
int find_elem(Elem**, Elem* const, int);
void rb_insert_fixup(Elem*, Elem**, Elem * const);
Elem* add_node(Elem**, Elem*, int*);
void del_node_with_fixup(Elem** root, Elem* EList);
void del_elem(Elem**, Elem*, Elem**);
void delete_fixup(Elem**, Elem*, Elem*);
void see_all_tree(Elem*, Elem*, int);
int del_tree(Elem*, Elem*);
Elem* find_min(Elem*, Elem*);
int put_elems(Elem*, Elem*);
void dop_func(Elem *);

int main()
{
	setlocale(LC_ALL, "Rus");
	Elem Elist = { 0, BLACK, nullptr, nullptr, nullptr };
	Elem * root = &Elist;
	int flag = 0;
	while (!flag)
	{
		cout << "Выберите способ создания элементов:\n1. Произвольно\n2. Ввод элементов с клавиатуры\n";
		int *create = getint();
		switch (*create)
		{
		case 1:
			create_tree_rand(&root, &Elist, 0);
			flag = 1;
			break;
		case 2:
			user_create(&root, &Elist);
			flag = 1;
			break;
		default:
			cout << "Способа с таким номером нет.\n";
			break;
		}
	}
	flag = 0;
	while (!flag)
	{
		cout << "Выберите номер дальнейшего действия:\n1. Добавление элемента\n2. Поиск элемента\n3. Удаление элемента\n4. Просмотр дерева\n5. Удаление дерева\n6. Обнуление ключа минимального элемента\n7. Вывод вершин с разным количеством потомков в левом и правом поддеревьях\n";
		int *option = getint();
		switch (*option)
		{
		case 1:
		{
			Elem* node = add_node(&root, &Elist, nullptr);
			if (node != nullptr)
			{
				rb_insert_fixup(node, &root, &Elist);
				cout << "Элемент был успешно добавлен.\n";
			}
			else cout << "Элемент с таким ключом уже существовал.\n";
			break;
		}
		case 2:
		{
			Elem* dop = root;
			int *key, check = 0;
			cout << "Введите ключ:\n";
			key = getint();
			check = find_elem(&dop, &Elist, *key);
			if (check)
			{
				cout << "Ключ = " << dop->key << ", цвет = ";
				if (dop->color == RED) cout << "красный\n";
				else cout << "чёрный\n";
			}
			else cout << "Элемента с таким ключом не найдено.\n";
			break;
		}
		case 3:
			del_node_with_fixup(&root, &Elist);
			break;
		case 4:
			see_all_tree(root, &Elist, 0);
			break;
		case 5:
			del_tree(root, &Elist);
			flag = 1;
			break;
		case 6:
		{
			Elem* dop = find_min(root, &Elist);
			dop->key = 0;
			break;
		}
		case 7:
			put_elems(root, &Elist);
			cout << endl;
			break;
		default:
			cout << "Действия с таким номером нет.\n";
			break;
		}
	}
	cout << "Чтобы провести оценку времени создания дерева нажмите 1, при нажатии любой другой клавиши программа завершит свою работу. По завершению проверки программа так же завершит свою работу\n";
	int *k = nullptr;
	k = getint();
	if (*k == 1) dop_func(&Elist);
	return 0;
}

void dop_func(Elem * Elist)
{
	Elem* root = Elist;
	srand(time(NULL));
	int count = 0, key, numb = 1000000, i, height = 0;
	clock_t start, stop, summ;
	for (i = 1; i <= 10; i++)
	{
		summ = 0;
		for (int j = 0; j < i * numb; )
		{
			key = rand() * rand();
			start = clock();
			Elem * ptr = add_node(&root, Elist, &key);
			stop = clock();
			if (ptr != nullptr)
			{
				summ += stop - start;
				rb_insert_fixup(ptr, &root, Elist);
				j++;
			}
		}
		height = del_tree(root, Elist);
		root = Elist;
		cout << "Тест " << i << ", количество элементов = " << numb * i << ", высота дерева = " << height << ", время в секундах = " << summ / CLK_TCK << endl;
	}
}

int put_elems(Elem* node, Elem* Elist)
{
	int num_l = 0, num_r = 0;
	if (node != Elist)
	{
		num_l = put_elems(node->left, Elist);
		num_r = put_elems(node->right, Elist);
		if (num_l != num_r)
			cout << " "<< node->key;
		return num_l + num_r + 1;
	}
	else return 0;
}

void see_all_tree(Elem* node, Elem* Elist, int tab)
{
	if (node != Elist)
	{
		see_all_tree(node->right, Elist, tab + 1);
		for (int k = 0; k < tab; k++)
			cout << "\t";
		cout << node->key;
		if (node->color == RED) cout << " Кр\n";
		else cout << " Чер\n";
		see_all_tree(node->left, Elist, tab + 1);
	}
}

int del_tree(Elem* node, Elem* Elist)
{
	int left, right;
	if (node != Elist)
	{
		right = del_tree(node->right, Elist);
		left = del_tree(node->left, Elist);
		delete(node);
		if (left > right) return left + 1;
		else return right + 1;
	}
	return 0;
}

void del_node_with_fixup(Elem** root, Elem* Elist)
{
	int* key, flag = 0;
	while (!flag)
	{
		key = getint();
		if (key != nullptr) flag = 1;
		else cout << "Введено некорректное значение. Введите значение снова:\n";
	}
	Elem* dop = *root;
	int check = find_elem(&dop, Elist, *key);
	if (check)
		del_elem(&dop, Elist, root);
	else cout << "Элемента с таким ключом не найдено.\n";
}

void del_elem(Elem** ptr, Elem* Elist, Elem ** root)
{
	Elem* p, * y;
	if (((*ptr)->left == Elist) || ((*ptr)->right == Elist))
		y = *ptr;
	else
		y = find_min((*ptr)->right, Elist);
	if (y->left != Elist)
		p = y->left;
	else p = y->right;
	p->parent = y->parent;
	if (y->parent == Elist)
		root = &p;
	else
		if (y->parent->left == y)
			y->parent->left = p;
		else
			y->parent->right = p;
	if (y != *ptr)
		(*ptr)->key = y->key;
	if (y->color == BLACK)
		delete_fixup(root, Elist, p);
	delete(y);
	cout << "Элемент успешно удалён.\n";
}

void delete_fixup(Elem** root, Elem* Elist, Elem* x)
{
	while ((x != *root) && (x->color == BLACK))
	{
		Elem* p = x->parent, * br;
		if (x == p->left)
		{
			br = p->right;
			if (br->color == RED) // 1
			{
				br->color = BLACK;
				p->color = RED;
				lev_pov(p, root, Elist);
				br = p->right;
			}
			if ((br->left->color == BLACK) && (br->right->color == BLACK)) // 2
			{
				br->color = RED;
				x = p;
			}
			else
			{
				if (br->right->color == BLACK) // 3
				{
					br->color = RED;
					br->left->color = BLACK;
					pr_pov(br, root, Elist);
					br = p->right;
				}
				br->color = p->color; // 4
				p->color = BLACK;
				br->right->color = BLACK;
				lev_pov(p, root, Elist);
				x = *root;
			}
		}
		else
		{
			br = p->left;
			if (br->color == RED)
			{
				br->color = BLACK;
				p->color = RED;
				pr_pov(p, root, Elist);
				br = p->left;
			}
			if ((br->left->color == BLACK) && (br->right->color == BLACK))
			{
				br->color = RED;
				x = p;
			}
			else
			{
				if (br->left->color == BLACK)
				{
					br->color = RED;
					br->right->color = BLACK;
					lev_pov(br, root, Elist);
					br = p->left;
				}
				br->color = p->color;
				p->color = BLACK;
				br->left->color = BLACK;
				pr_pov(p, root, Elist);
				x = *root;
			}
		}
	}
	x->color = BLACK;
}

Elem* find_min(Elem* ptr, Elem * Elist)
{
	Elem* dop = ptr;
	while (ptr != Elist)
	{
		dop = ptr;
		ptr = ptr->left;
	}
	return dop;
}

Elem * add_node(Elem** root, Elem* Elist, int * my_key)
{
	Elem* dop = *root;
	int flag = 0, * ptr_key;
	if (my_key == nullptr)
	{
		cout << "Введите ключ элемента:\n";
		while (!flag)
		{
			ptr_key = getint();
			if ((ptr_key != nullptr) && (*ptr_key > 0)) flag = 1;
			else cout << "Введено некорректное значение. Введите значение снова:\n";
		}
	}
	else ptr_key = my_key;
	int key = *ptr_key;
	int check = find_elem(&dop, Elist, key);
	if (!check)
	{
		Elem* node = new Elem;
		if (dop == Elist) * root = node;
		else
			if (key < dop->key)
				dop->left = node;
			else
				dop->right = node;
		node->parent = dop;
		node->key = key;
		node->left = Elist;
		node->right = Elist;
		node->color = RED;
		return node;
	}
	return nullptr;
}

void create_tree_rand(Elem** root, Elem * const Elist, int count)
{
	if (!count)
	{
		int flag = 0, * num;
		cout << "Введите количество элементов:\n";
		while (!flag)
		{
			num = getint();
			if (*num > 0) flag = 1;
			else cout << "Введено некорректное значение. Введите значение снова:\n";
		}
		count = *num;
	}
	int my_key;
	srand(time(NULL));
	for (int i = 0; i < count; )
	{
		my_key = rand();
		Elem* node;
		node = add_node(root, Elist, &my_key);
		if (node != nullptr)
		{
			rb_insert_fixup(node, root, Elist);
			i++;
		}
	}
}

void user_create(Elem** root, Elem *const Elist)
{
	cout << "Введите количество элементов:\n";
	int flag = 0, *count;
	while (!flag)
	{
		count = getint();
		if (*count >= 0) flag = 1;
		else cout << "Введено некорректное значение. Введите значение снова:\n";
	}
	for (int k = 0; k < *count; )
	{
		Elem* node;
		node = add_node(root, Elist, nullptr);
		if (node != nullptr)
		{
			rb_insert_fixup(node, root, Elist);
			k++;
		}
	}
	cout << "Дерево успешно создано\n";
}

void rb_insert_fixup(Elem* node, Elem** root, Elem * const Elist)
{
	if (node->parent != Elist)
		while (node->parent->color == RED)
		{
			Elem* p1 = node->parent, * pp = p1->parent, *p2;
			if (p1 == pp->left)
			{
				p2 = pp->right;
				if (p2->color == RED) // 1
				{
					p1->color = BLACK;
					p2->color = BLACK;
					pp->color = RED;
					node = pp;
				}
				else
				{
					if (node == p1->right) // 2а
					{
						node = p1;
						lev_pov(node, root, Elist);
						p1 = node->parent;
					}
					p1->color = BLACK; // 2б
					pp->color = RED;
					pr_pov(pp, root, Elist);
				}
			}
			else // зеркальные случаи
			{
				p2 = pp->left;
				if (p2->color == RED)
				{
					p1->color = BLACK;
					p2->color = BLACK;
					pp->color = RED;
					node = pp;
				}
				else
				{
					if (node == p1->left)
					{
						node = p1;
						pr_pov(node, root, Elist);
						p1 = node->parent;
					}
					p1->color = BLACK;
					pp->color = RED;
					lev_pov(pp, root, Elist);
				}
			}
		}
	(*root)->color = BLACK;
}

int find_elem(Elem** ptr, Elem * const Elist, int key)
{
	Elem* prev = Elist;
	while (*ptr != Elist)
	{
		prev = *ptr;
		if (key < (*ptr)->key)
			(*ptr) = (*ptr)->left;
		else
			if (key == (*ptr)->key)
				return 1;
			else (*ptr) = (*ptr)->right;
	}
	*ptr = prev;
	return 0;
}

void lev_pov(Elem* node, Elem** root, Elem * Elist)
{
	Elem* rdop = node->right, * parent = node->parent;
	node->right = rdop->left;
	if (rdop->left != Elist)
		rdop->left->parent = node;
	rdop->parent = parent;
	if (parent == Elist)
		* root = rdop;
	else
		parent->left == node ? parent->left = rdop: parent->right = rdop;
	rdop->left = node;
	node->parent = rdop;
}

void pr_pov(Elem* node, Elem** root, Elem * Elist)
{
	Elem* ldop = node->left, * parent = node->parent;
	node->left = ldop->right;
	if (ldop->right != Elist)
		ldop->right->parent = node;
	ldop->parent = parent;
	if (parent == Elist)
		* root = ldop;
	else
		parent->left == node ? parent->left = ldop : parent->right = ldop;
	ldop->right = node;
	node->parent = ldop;
}

char* getstr()
{
	char* buf, * c;
	buf = (char*)malloc(10);
	c = (char*)malloc(10);
	*c = '\0';
	while (scanf("%9[^\n]", buf) == 0)
		scanf("%*c");
	strcat(c, buf);
	c[strlen(c)] = '\0';
	while (scanf("%9[^\n]", buf))
	{
		c = (char*)realloc(c, strlen(c) + 10);
		strcat(c, buf);
		c[strlen(c)] = '\0';
	}
	scanf("%*c");
	free(buf);
	return c;
}

int * getint()
{
	char* info = nullptr;
	info = getstr();
	for (int i = 0; i < strlen(info); i++)
	{
		if ((info[i] < 48) || (info[i] > 57))
			return nullptr;
	}
	int buf = atoi(info);
	return &buf;
}