// TreeObhod.cpp: îïðåäåëÿåò òî÷êó âõîäà äëÿ êîíñîëüíîãî ïðèëîæåíèÿ.
//
/*
Â ôàéëå äåðåâî â âèäå
Ann
.Boris
..Cat
..Dora
...Eva
...Fred
..Goga
...Helmut
....Marta
.....Bred
.....Stiv
.....Jon
......Tom
...Nata
.Nina
Ïîñòðîèòü áèíàðíîå äåðåâî. Îáåñïå÷èòü âûäà÷ó áèíàðíîãî äåðåâà â
3 ïîðÿäêàõ îáõîäà. Âûäàòü èñõîäíîå äåðåâî èç áèíàðíîãî. 
Èìÿ âõîäíîãî ôàéëà - ÷åðåç êîìàíäíóþ ñòðîêó.
*/
stepan_crazy_boy@mail.ru
#include "stdafx.h"   
#include <fstream>

const int DL = 20;          // ìàêñèìàëüíàÿ äëèíà

using namespace std;

struct Tree 
{
    char name[DL];
    int urov;
    Tree *fath;         // îòåö â èñõîäíîì äåðåâå
    Tree *left;
    Tree *right;
};

int read_from_file(FILE *F, Tree **r);  // ÷òåíèå èç ôàéëà, ôîðìèðîâàíèå äåðåâà
void back_from_bin(Tree *p);            // âûäà÷à èñõîäíîå äåðåâà èç áèíàðíîãî 
void print_down_bin(Tree *p, int lev);  // âûäà÷à áèíàðíîãî ñâåðõó âíèç
void print_up_bin(Tree *p, int lev);    // âûäà÷à áèíàðíîãî ñíèçó ââåðõ
void print_right_bin(Tree *p, int lev); // âûäà÷à áèíàðíîãî ñëåâà íàïðàâî

int main(int argc, char* argv[])
{
    Tree *root = 0;
    FILE *Fin;
    setlocale(LC_ALL, "rus");
    if (argc != 2)
    {
       printf("\nNumber parameters is wrong");
       getchar();
       return -1;
    }
/*	Fin = fopen("input.txt", "r");    // îòëàäêà
    if (Fin == NULL )
    {
         printf("\nCan not open file %s", Fin);
         getchar();
	 return -1;
    } */
    Fin = fopen(argv[1], "r");
    if (Fin == NULL )
    {
         printf("\nCan not open file %s", argv[1]);
         getchar();
	 return -1;
    } 
    read_from_file(Fin, &root);
    printf("Áèíàðîå äåðåâî ïîñòðîåíî\n");
    getchar();
    printf("Âûâîä èç áèíàðíîãî äåðåâà ñèëüíî âåòâÿùåãîñÿ\n");
    back_from_bin(root);
    getchar();
    printf("Âûâîä áèíàðíîãî äåðåâà ñâåðõó âíèç\n");
    print_down_bin(root, 0);
    getchar();
    printf("Âûâîä áèíàðíîãî äåðåâà ñíèçó ââåðõ\n");
    print_up_bin(root, 0);
    getchar();
    printf("Âûâîä áèíàðíîãî äåðåâà ñëåâà íàïðàâî\n");
    print_right_bin(root, 0);
    getchar();
}

int read_from_file(FILE *F, Tree **r)
{
    char buf[DL];
    int i, k, m, len;
    Tree *p, *q, *t;       // *root = 0 
    m = 0;                 // óðîâåíü âåðøèíû
    t = 0;
    while (!feof(F))
    {
		 k = fscanf(F, "%s", buf);
	     len = strlen(buf);              
		 if (len == 0) break;            // åñëè êîíåö ôàéëà â ñëåäóþùåé ñòðîêå
	     k = 0;
	     while (buf[k] == '.') k++ ;     // k-óðîâåíü âåðøèíû
         p = new Tree;
         strncpy(p -> name, &buf[k], len-k+1);  // 0-(k-1) - òî÷êè, (k-1)-(len-1) - èìÿ, \0 - êîíåö ñòðîêè
		 buf[0] = '\0';                  // åñëè êîíåö ôàéëà â ñëåäóþùåé ñòðîêå
         p -> urov = k;
         p -> left = 0;
         p -> right = 0;
	     if (k == 0)                    // êîðåíü
	     {
	         *r = p;
	         t = *r;
	         continue;
         }
         if (k > m)                  // ïåðåõîä íà ñëåäóþùèé óðîâåíü
	     {
	         t -> left = p;
	         p -> fath = t;
	     }
         else if (k == m)            // òîò æå óðîâåíü
	     {
              t -> right = p;
              p -> fath = t-> fath;  // îòåö òîò æå
         }
         else        // ïîäúåì ïî äåðåâó íà m-k óðîâíåé
         {
              q = t;
              for (i = 0; i < m - k; i++) q = q -> fath;
              // q - ïðåäûäóùàÿ âåðøèíà òîãî æå óðîâíÿ
              p -> fath = q -> fath;   // îòåö òîò æå, ÷òî ó áðàòà
              q -> right = p;
         }
         m = k;      // òåêóùèé óðîâåíü
         t = p;      // òåêóùàÿ âåðøèíà
    }
    fclose( F);
    return 0;
}

void back_from_bin(Tree *p)
{
    int i, j;
    char st[DL];
    if (p)
    {
        for (i = 0; i < p -> urov; i++) st[i] = '.';
        j = 0;
        while ((p -> name)[j] != 0) st[i++] = (p -> name)[j++];
        st[i] = '\0';
        printf("%s\n", st);
        back_from_bin(p -> left);
        back_from_bin(p -> right);
    }
}

void print_right_bin(Tree *p, int level)
{
    if (p)
    {
        print_right_bin(p -> left, level + 1);
        for (int i = 0; i < level; i++)
          printf("%c",'.');
        printf("%s\n", p -> name);
        print_right_bin(p -> right, level + 1);
    }
}

void print_up_bin(Tree *p, int level)
{
    if (p)
    {
        print_up_bin(p -> left, level + 1);
        print_up_bin(p -> right, level + 1);
        for (int i = 0; i < level; i++)
          printf("%c",'.');
        printf("%s\n", p -> name);
    }
}

void print_down_bin(Tree *p, int level)
{
    if (p)
    {
        for (int i = 0; i < level; i++)
          printf("%c",'.');
        printf("%s\n", p -> name);
        print_down_bin(p -> left, level + 1);
        print_down_bin(p -> right, level + 1);
    }
}
