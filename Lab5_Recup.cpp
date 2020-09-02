#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#define SIZE 20
#define FILENAME "pon.txt"

typedef struct tree_table
{
        char* key;
        char* info;
	struct tree_table* left;
	struct tree_table* right;
} tree_t;

tree_t* mtree = 0;

int add(char* key, char* info, int size) 
{
	char* s;
	if (!mtree)
	{
		mtree = (tree_t*) calloc(20,sizeof(char));
        if (!mtree) 
			return 2;
        mtree->key = (char*)calloc(20,sizeof(char));
		strncpy(mtree->key, key, strlen(key));
        mtree->info = (char*)calloc(20,sizeof(char));
		mtree->right = 0;
		mtree->left = 0;
	    strncpy(mtree->info, info, strlen(info));
		return 0;
	}
	tree_t* now = mtree;
	tree_t* last = NULL;
	int right = 0;
	while (now && now->info)
	{
		if (strcmp(now->key, key) == 0) 
			return 1;
		last = now;
		if (strcmp(key,now->key) > 0)
		{
			now = now->right;
			right = 1;
		}
		else
		{
			now = now->left;
			right = 0;
		}
	}
	if (!now)
	{
		now = (tree_t*) malloc(sizeof(tree_t));
		if (!now) 
			return 2;
		now->right = 0;
		now->left = 0;
	}
	if (last)
	{
		if (right)
			last->right = now;
		else 
			last->left = now;
	}
	now->key = (char*)calloc(20,sizeof(char));
	now->info = (char*)calloc(20,sizeof(char));
	strcpy(now->info, info);
	strncpy(now->key,key,strlen(key));
	return 0;
}

int rebuild(tree_t* tree) //перестраивание дерева после удаление элемента из дерева
{
	if (!tree) return 1;
	if (tree->left) 
		rebuild(tree->left);
	if (tree->right) 
		rebuild(tree->right);
	if (tree->info)
	{
		add(tree->key, tree->info, strlen(tree->info));
		free(tree->info);
	}
	free(tree);
	return 0;
}

int rm(char* key) //удаление элемента из дерева
{
    tree_t* now = mtree;
	tree_t* last = NULL;
	tree_t* buf = NULL;
	tree_t* last1 = NULL;
	if (strcmp(now->key,key) == 0)
	{
		buf = now->left;
		last = buf->left;
		last1 = buf->right;
		buf->right = now->right;
		buf->left = NULL;
		mtree = buf;
		rebuild(last);
		rebuild(last1);
		return 0;
	}
    if (!now) 
		return 1;
    do{
    	last = now;
    	if (strcmp(key, now->key) == 0)
    		break;
    		else if (strcmp(key,now->key) > 0)
    			now = now->right;
    		else
    			now = now->left;
    		if (!now)
    			return 1;
	}
	while (strcmp(key, now->key)!=0);
	
	if (last == now)
		last = NULL;
	else
	{
		if (strcmp(last->key,now->key) < 0)
			last->right = NULL;
		else
			last->left = NULL;
	}
	rebuild(now->left);
	rebuild(now->right);
	if (now->info)
		free(now->info);
	free(now);
	return 0;
}

int look_into_depth(tree_t* now, int count)
{
	tree_t* previous;
	while (now)
	{
		previous = now;
		if (now->left!=NULL)
		{
			now = now->left;
			count++;
			look_into_depth(now, count);
		}
		now = previous;
		if (now->right!=NULL)
		{
			now = now->right;
			count++;
			look_into_depth(now, count);
		}
		else
			return count;
	}
	return 0;
}

int find_r(tree_t* tree, char* key)
{
	if (!mtree)
		return 1;
	if (tree->left) 
		find_r(tree->left, key);
	if ((tree->info) && (strncmp(tree->key, key, strlen(key)) == 0))
			printf("%s:%s\n", tree->key, tree->info);
	if (tree->right) 
		find_r(tree->right, key);
	return 0;
}

int find(char* key)
{
	tree_t* now = mtree;
	if (!now)
		return 1;
    while (strcmp(key,now->key) != 0)
        {
                if (strcmp(key,now->key) > 0) 
					now = now->right;
                else 
					now = now->left;
                if (!now)
					return 1;
        }
	if (!now->info) 
		return 2;
   // printf("%s\n", now->info);
	return 0;
}

int print_all(tree_t* tree)
{
	if (!tree) 
		return 1;
	if (tree->left) 
		print_all(tree->left);
	if (tree->info)
		printf("%s:%s\n", tree->key, tree->info);
	if (tree->right) 
		print_all(tree->right);
}

int print_all_tab(tree_t* tree, int depth)
{
	int space, depth1, i;
	depth1 = depth;
	space = 0;
	if (!tree) 
		return 1;
	if (tree->info)
	{
		for (i = 0; i<depth; i++)
			printf(" ");
		printf("%s:%s",tree->key, tree->info);
		for (i = 0; i<space; i++ )
			printf(" ");
		space = 2*(depth1-depth);
	}
	if (tree->left) 
		print_all(tree->left);
	if (tree->right) 
		print_all(tree->right);
	return 0;
}

int print_table (tree_t* tree, char* key)
{
        if (!mtree)
			return 1;
	if (tree->left) 
		print_table(tree->left, key);
	if ((!strlen(key))&&(tree->info))
		printf("%s:%s\n", tree->key, tree->info);
	else
	{
		if ((tree->info) && (strcmp(tree->key,key) > 0))
			printf("%s:%s\n", tree->key, tree->info);
	}
	if (tree->right) 
		print_table(tree->right, key);
	return 0;
}

int print_tree_r(tree_t* now)
{
	if (!now) 
		return 0;
	printf("KEY: %s\n", now->key);
	if (!now->info) 
		printf("REMOVED\n");
	else printf
		("INFO: %s\n", now->info);
	if (!now->left) 
		printf("::LEFT ::NULL\n");
    else 
		printf("::LEFT ::KEY=%s\n", now->left->key);
	if (!now->right) 
		printf("::RIGHT::NULL\n");
	else 
		printf("::RIGHT::KEY=%s\n", now->right->key);
	if (now->left) 
		print_tree_r(now->left);
	if (now->right) 
		print_tree_r(now->right);
}

int beautiful_output (tree_t* tree, int depth)
{
	if (!tree)
		return 1;
	print_all_tab(tree,depth);
	return 0;
}

void print_Tree(tree_t * p,int level)
{
    if(p)
    {
    	print_Tree(p->right,level + 1);
        for(int i = 0;i< level;i++)
			printf("   ");
        printf("%s\n",p->key);
        print_Tree(p->left,level + 1);
        
    }
}

int print_tree()
{
        if (!mtree)
			return 1;
        print_tree_r(mtree);
}

int send_to_file_r(FILE* fp, tree_t* now)
{
	char* key1;
	char* info1;
	char* s1;
	key1 = (char*)calloc(20,sizeof(char));
	info1 = (char*)calloc(20,sizeof(char));
	s1 = (char*)calloc(1,sizeof(char));
	if (!now) 
		return 1;
	if (!fp) 
		return 2;
	if (now->info) 
	{
		s1 = strchr(s1,'\n');
		if(s1!=NULL)
		{
			strncpy(key1,now->key,strlen(now->key)-1);
			printf(now->info);
		}
		else
		{
			strncpy(key1,now->key,strlen(now->key));
		//	printf(now->info);	
		}
		strncpy(info1,now->info,strlen(now->info)-1);
		fprintf(fp, "%s\n", key1);
		fprintf(fp, "%s\n", info1);
		free(key1);
		free(info1);
	}
	if (now->left) 
		send_to_file_r(fp, now->left);
	if (now->right) 
		send_to_file_r(fp, now->right); 
}

int send_to_file()
{
        if (!mtree)
			return 0;
        FILE *fp;
        fp = fopen(FILENAME, "w+");
        send_to_file_r(fp, mtree);	
	fclose(fp);
}

int load_from_file()
{
	if (access(FILENAME, F_OK) != -1)
        {
		FILE* fp;
		char* line = (char*)malloc(20);
		size_t len = 20;
		fp = fopen(FILENAME, "r");
                if (fp == NULL)
                        return 1;
		//fclose(fp);
		while (1)
		{
			if (!fgets(line, len, fp))
			{
				if (line) 
					free(line);
				fclose(fp);
				return 0;
			}
			char* key = (char*)malloc(20);
			key = strcpy(key,line);
			if (strchr(key,'\n') == NULL);
			else
				key[strlen(key)-1] = '\0';
			if (!fgets(line, len, fp))
			{
				if (line) 
					free(line);
				fclose(fp);
				return 0;
			}
			if (strchr(line,'\n') == NULL);
			else
				line[strlen(line)-1] = '\0';
			add(key, line, strlen(line));
		}
	}
}

int free_tree_r(tree_t* tree)
{
	if (!tree) 
		return 0;
	if (tree->left) 
		free_tree_r(tree->left);
	if (tree->right) 
		free_tree_r(tree->right);
	if (tree->info) 
		free(tree->info);
	free(tree);
}

int free_tree()
{
	if (!mtree) return 0;
	free_tree_r(mtree);
}

int print_menu()
{
	printf("%s\n", "1> Add an element");
    printf("%s\n", "2> Delete an element");
    printf("%s\n", "3> Find an element");
	printf("%s\n", "4> Find the closest element");
    printf("%s\n", "5> The table is");
	printf("%s\n", "6> Some kinda tree");
	printf("%s\n", "7> Cool tree");
    printf("%s\n", "8> Escape!");
    printf("%s\n\n", "9> Timing of tree");
    printf("%s", "Put your command> ");
    return 0;
}

int clear_fgets(char* str)
{
	char *pos;
	if ((pos=strchr(str, '\n')) != NULL)
    		*pos = '\0';
}

int D_Timing(tree_t* mtree)
{
	tree_t* root = mtree;
	char* s1 = (char*)calloc(1,sizeof(char));
	char* s = (char*)calloc(1,sizeof(char));
	char** key = (char**)malloc(10000*sizeof(char*));
	int n = 10, k, key1, k1, cnt = 1000000, i, m;
	clock_t first, last;
	srand(time(NULL));
	while (n-- > 0)
	{
		for (i = 0; i<10000; ++i)
		{
			key[i] = (char*)malloc(sizeof(char));
			key1 = rand() * rand();
			itoa(key1,key[i],10);
		}
		for ( i = 0; i< cnt;) 
		{
			k = rand() * rand();
			k1 = rand() * rand();
			itoa(k,s,10);
			itoa(k1,s1,10);
			add(s1,s,20);
			i++;
		}
		m  = 0;
		first = clock();
		for (i = 0; i<5000; ++i)
		{
			if (rm(key[i])) 
				++m;
		}
		last = clock();
		printf(	"%d items were found\n",m);
		printf("test #%d, number of nodes = %d, time %d\n", 10-n, (10-n)*cnt, last-first);
	}
	free_tree();
}

int action()
{
	char* input = (char*)calloc(20,sizeof(char));
	char* s;
	fgets(input, 20, stdin);
	int action_number = atoi(input);
	if (action_number < 1 || action_number > 9)
	{
		free(input);
		return 1;
	}
	if (action_number == 1)
	{
		printf("Input key: ");
		fgets(input, 20, stdin);
		char* key = (char*)calloc(20,sizeof(char));
		s = strchr(input, '\n');
		if (s!=NULL)
			strncpy(key,input,strlen(input)-1);
		else
			strncpy(key,input,strlen(input));
		printf("Input info: ");
		fgets(input, 20, stdin);
		int ret = add(key, input, strlen(input));
		if (ret == 1) printf("already exists!\n");
		if (ret == 2) printf("lack of memory\n");
		clear_fgets(input);
		
	}
	if (action_number == 2)
	{
		printf("Input key: ");
		fgets(input, 20, stdin);
        char* key = (char*)calloc(20,sizeof(char));
        s = strchr(input, '\n');
		if (s!=NULL)
			strncpy(key,input,strlen(input)-1);
		else
			strncpy(key,input,strlen(input));
		int ret = rm(key);
		if (ret == 1) printf("not created!\n");
		if (ret == 2) printf("already removed!\n");
		clear_fgets(input);
	}
	if (action_number == 3)
	{
		printf("Input key: ");
        fgets(input, 20, stdin);
        char* key = (char*)calloc(20,sizeof(char));
        s = strchr(input, '\n');
		if (s!=NULL)
			strncpy(key,input,strlen(input)-1);
		else
			strncpy(key,input,strlen(input));
        int ret = find(key);
		if (ret == 1) printf("not created\n");
		if (ret == 2) printf("removed\n");
		clear_fgets(input);
	}
	if (action_number == 4)
	{
		printf("Enter the key\n");
		fgets(input,20,stdin);
		char* key = (char*)calloc(20,sizeof(char));
        s = strchr(input, '\n');
		if (s!=NULL)
			strncpy(key,input,strlen(input)-1);
		else
			strncpy(key,input,strlen(input));
		find_r(mtree, key);
		clear_fgets(input);
	}
	if (action_number == 5)
	{
		printf("Enter the key\n");
		fgets(input,20,stdin);
		char* key = (char*)calloc(20,sizeof(char));
		s = strchr(input, '\n');
		if (s!=NULL)
			strncpy(key,input,strlen(input)-1);
		else
			strncpy(key,input,strlen(input));
		int ret = print_table(mtree, key);
		if (ret == 1)
			printf("Table is clear!\n");
		clear_fgets(input);
	}
	if (action_number == 6)
	{
		int ret = print_tree();
		if (ret == 1) printf("table is clear!\n");
	}
	if (action_number == 7)
	{
		int i = 0;
		i = look_into_depth(mtree,1);
		printf("The depth is : %d\n",i);
		print_Tree(mtree,1);
		
	}
	if (action_number == 8)
	{
		free(input);
		send_to_file();
		free_tree();
		exit(0);
	}
	if (action_number == 9)
		D_Timing(mtree);
	free(input);
	printf("\n");
}

int main()
{
	
	int j;
	tree_t* root;
	load_from_file();
	while(1)
	{
		print_menu();
		action();
	}
}
