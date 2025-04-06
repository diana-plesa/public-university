//curs 2 - ex 2

typedef struct list
{
	int val;
	list* next;
}node;

void add_node(node** start, int val); //adaugare nod in lista
void remove_node(node** start, int val); //stergere nod din lista
node* find_val(node** start, int val); //returneaza nodul in care se afla valoarea cautata
void init_list(node** start, int val); //initializeaza lista
void sort_list(node** start, int val, int (*compar)(const void*, const void*)); //sorteaza lista folosind ca comparator functia trimisa ca parametru
void insert(node** start, int val, node* next_node); //insereaza un nod cu valoarea data inaintea unui nod al listei


