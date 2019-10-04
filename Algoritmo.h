// Lista Encadeada - Linked List

void add_Struct(struct *&estrutura, char info[]) 
{
    struct* p = estrutura;

    while(p!=NULL)
    {
        p = p->prox;
    }

    struct* novo = (struct*)malloc(sizeof(struct ));

    strcpy(novo->info,info);

    novo->prox = estrutura;
}

void clear_Struct(struct *&estrutura) 
{
    struct *ptr, no;
    if(estrutura != NULL)
    {   
        ptr = estrutura->prox;
        while(ptr != NULL)
        {
            no = ptr->prox;
            free(ptr);
            ptr = no;
        }
        ptr = estrutura;
        free(ptr);
    }
    estrutura = NULL;
}

void del_Struct(struct *&estrutura, char info[]) 
{
    struct* p = estrutura;   
    struct* aux = NULL;

    while(p!= NULL && strcmp(p->info, info)!=0)
    {
        aux = p;
        p = p->prox;
    }

    if(p == NULL)
    {
        return estrutura;
    }

    if(aux == NULL)
    {
        estrutura = estrutura->prox;
    }
    else
    {
        aux->prox = p->prox;
    }
    free(p);
}

void swp_Struct(struct *&estrutura, char info[], char info2[]) 
{
    char aux[256];
    struct* valor1, valor2;
    struct* p = playlist;

    while(p!=NULL)
    {
        if(strcmp(p->info, info) == 0)
        {
            valor1 = p;
            break;
        }
        p = p->prox;      
    }

    p = playlist;

    while(p!=NULL)
    {
        if(strcmp(p->info, info2) == 0)
        {
            valor2 = p;
            break;
        }
        p = p->prox; 
    }


    strcpy(aux, valor1->info);
    strcpy(valor1->info, valor2->info);
    strcpy(valor2->info, aux);
}

// Algoritmos de Busca

int binary_search(int* vetor, int size , int x)
{
	int e = 0, r = size - 1, m;

	do
	{
		m = ( e - r ) / 2;
		if( x == vetor[m])
		{
			return m;
		}
		else if(x < vetor[m])
		{
			r = m - 1;
		}
		else if(x > vetor[m])
		{
			e = m + 1;
		}
        
	}while(e <= r);

	return -1;
}

// Algoritmos de Ordenacao

void merge(int * v, int left , int right , int * a)
{
    int i,j,k;

    for(i = left; i <= right; i++)
    {
        a[i]=v[i];
    }

    int mid = ((left+right)/2);

    i=left;
    j=mid+1;

    for(k = left ; k <= right ; k++)
    {
        if(j > right)
        {
            v[k]=a[i];
            i++;
        }else if(i > mid)
        {
            v[k]=a[j];
            j++;
        }else if(a[i] < a[j])
        {
            v[k]=a[i];
            i++;
        }else
        {
            v[k]=a[j];
            j++;
        }
    }
}

void msort(int * v , int left , int right,int *a)
{
    if(left!=right)
    {
        int mid = ((left+right)/2);
        msort(v,left,mid,a);
        msort(v,mid+1,right,a);
        merge(v,left,right,a);
    }
}

void mergesort(int *v, int right)
{
    int *a= new int[right + 1];
    msort(v, 0, right, a);
    delete[] a;
}

// Arvore Binaria


void preOrder_BT(struct *&root)
{
    if(root == NULL)
    {
        return;
    }

    visit(root);
    preorder_BT(root->left);
    preorder_BT(root->right);
}

void emOrder_BT(struct *&root)
{
    if(root == NULL)
    {
        return;
    }

    preorder_BT(root->left);
    visit(root);
    preorder_BT(root->right);    
}

void posOrder_BT(struct *&root)
{
    if(root == NULL)
    {
        return;
    }

    preorder_BT(root->left);
    preorder_BT(root->right);    
    visit(root);
}

// Arvore de Busca Binária

Arvore* bst_inserir(Arvore*& root, int valor)
{
    if(root == NULL)
    {
        root = new Arvore;
        root->val = valor;
        root->right = NULL;
        root->left = NULL;
        return root;
    }
    else
    {
        if(valor < root->val)
        {
            root->left = bst_inserir(root->left, valor);
            return root;
        }
        else
        {
            root->right = bst_inserir(root->right, valor);
            return root;
        }
    }
}

Arvore* bst_search(Arvore*& root, int valor)
{
    if(root == NULL)
    {
        return NULL; // Valor n encontrado na Arvore
    }

    if(v == root -> val)
    {
        return root;
    }
    else if(v > root->val)
    {
        return bst_search(root->right, valor);
    }
    else
    {
        return bst_search(root->left, valor);
    }
}

Arvore* bst_delete_min(Arvore*& root)
{
    int v;
    int r;
    if(root->left == NULL)
    {
        v = root->val;
        r = root->right;
        free(root);
        return r, v;
    }
    else
    {
        root->left, v = bst_delete_min(root->left);
        return root, v;
    }   
}

Arvore* bst_delete(Arvore*& root, int valor)
{
    if(root == NULL)
    {
        return NULL;
    }
    else if(valor < root->val)
    {
        root->left = bst_delete(root->left, valor);
        return root;
    }
    else if(valor > root->val)
    {
        root->right = bst_delete(root->right, valor);
        return root;
    }
    else
    {
        if(root->left == NULL)
        {
            Arvore* r = root->right;
            free(root);
            return r;  
        }
        else if(root->right == NULL)
        {
            Arvore* l = root->left;
            free(root);
            return l;
        }
        else
        {
            root->right, root->val = bst_delete_min(root->right);
        }
    }
}

void tree_debugger(Arvore*& root){

    if(root==NULL){
        return ;
    }else{
        tree_debugger(root->left);
        cout << root->val << endl;
        tree_debugger(root->right);
    }
}
