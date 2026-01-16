#include <iostream>

// the type enum
enum Order
{
     Prefix,  // will be set to 0
     Infix,   // will be set to the previous + 1
     Postfix, // idem
};

void enum_values()
{
     std::cout << "Prefix is " << Order::Prefix << std::endl;
     std::cout << "Infix is " << Order::Infix << std::endl;
     std::cout << "Postfix is " << Order::Postfix << std::endl;
}

// Les structures de base de l'arbre binaire BinaryTree et Node:
// avec les méthodes pour que le code compile.
struct Node
{
     int val;
     Node *fg;
     Node *fd;
     Node(int i) : val(i), fg(nullptr), fd(nullptr) {};
     
     void insert(int i)
     {
          if (i < val)
          {
               if (fg == nullptr) {fg = new Node(i);}
               else {fg->insert(i);}
          }
          else
          {
               if (fd == nullptr) {fd = new Node(i);}
               else {fd->insert(i);}
          }
     }
     void dfs()
     {
          if (fg == nullptr and fd == nullptr) {std::cout << val;}
          else if (fg == nullptr and fd != nullptr) {std::cout << val << " "; fd->dfs();}
          else if (fg != nullptr and fd == nullptr) {fg->dfs(); std::cout << " " << val;}
          else {fg->dfs(); std::cout << " " << val << " "; fd->dfs();}
     }
     bool search(int i)
     {
          if (val == i) {return true;}
          else
          {
               if (i < val) {return fg->search(i);}
               else {return fd->search(i);}
          }
     }

};

struct BinaryTree
{
     Node* racine;
     BinaryTree() : racine(nullptr) {}
     void insert(int i)
     {
          if (racine == nullptr) {racine = new Node(i);}
          else {racine->insert(i);}
     }
     void dfs()
     {
          if (racine == nullptr) {std::cout << std::endl;}
          else {racine->dfs(); std::cout << std::endl;}
     }
     bool search(int i)
     {
          if (racine == nullptr) {return false;}
          else {return racine->search(i);}
     }

     // celle là est plus difficile
     void print() {}
};

int main()
{
     // enum_values(); // exemple pour voir un enum

     // on construit l'arbre

     // cet ordre d'insertion donne un bel arbre binaire équilibré
     // ce qui n'est bien sûr pas toujours le cas...
     // il existe des algorithmes pour garder l'arbre équilibré
     // mais c'est en dehors de notre cadre d'une simple programmation
     BinaryTree b;
     b.insert(8);
     b.insert(4);
     b.insert(6);
     b.insert(12);
     b.insert(10);
     b.insert(11);
     b.insert(9);
     b.insert(2);
     b.insert(1);
     b.insert(3);
     b.insert(5);
     b.insert(14);
     b.insert(15);
     b.insert(13);
     b.insert(7);
     // b.print();

     std::cout << "Infix ";
     b.dfs();
     // std::cout << "Postfix ";
     // b.dfs(Order::Postfix);
     // std::cout << "Prefix ";
     // b.dfs(Order::Prefix);
     std::cout << std::boolalpha << b.search(25) << std::endl;
     std::cout << std::boolalpha << b.search(2) << std::endl;

     std::cout << "Cet arbre est dégénéré:\n";
     BinaryTree bad1;
     for (int i = 1; i < 16; i++)
          bad1.insert(i);
     bad1.print();

     std::cout << "\ncelui là aussi:\n";
     BinaryTree bad2;
     for (int i = 30; i > 15; i--)
          bad2.insert(i);
     bad2.print();
}

/* l'exécution de ce programme donne:
    ----------------------------------

Prefix is 0
Infix is 4
Postfix is 5
               15
          14
               13
     12
               11
          10
               9
8
               7
          6
               5
     4
               3
          2
               1
Infix { 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15  }
Postfix { 1 3 2 5 7 6 4 9 11 10 13 15 14 12 8  }
Prefix { 8 4 2 1 3 6 5 7 12 10 9 11 14 13 15  }
false
true
Cet arbre est dégénéré:
                                                                      15
                                                                 14
                                                            13
                                                       12
                                                  11
                                             10
                                        9
                                   8
                              7
                         6
                    5
               4
          3
     2
1

celui là aussi:
30
     29
          28
               27
                    26
                         25
                              24
                                   23
                                        22
                                             21
                                                  20
                                                       19
                                                            18
                                                                 17
                                                                      16
*/
