#include <iostream>
#include <string>
using namespace std;
// Huffman Code
class cNode
{
public:
    int data;
    char Character;
    string code;
    cNode* pNext;
    cNode* pleft;
    cNode* pright;
    cNode()
    {
        data = 0;
        Character = '\0';
        pNext = NULL;
        pleft = NULL;
        pright = NULL;
        code = "";
    }
};
class SortedList
{
public:
    cNode* pHead;
    cNode* pTail;
    SortedList()
    {
        pHead = NULL;
        pTail = NULL;
    }
    ~SortedList()
    {
        cNode* ptrav = pHead;
        while (pHead != NULL)
        {
            pHead = ptrav->pNext;
            ptrav->pNext = NULL;
            delete ptrav;
            ptrav = pHead;
        }
    }
    void Display()
    {
        cNode* pTrav = pHead;
        while (pTrav != NULL)
        {
            cout << "Character: ";
            if (pTrav->Character == '\0')
            {
                cout << "Internal";
            }
            else {
                cout << pTrav->Character;
            }
            cout << ", Frequency: " << pTrav->data << endl;

            pTrav = pTrav->pNext;
        }
        cout << endl;
    }
    void attach(cNode* pnn)
    {
        if (pHead == NULL)
        {
            pHead = pnn;
            //pTail = pnn;
        }
        else
        {
            cNode* pTrav = pHead;
            cNode* pBack = NULL;
            while (pTrav != NULL && pnn->data > pTrav->data)
            {
                pBack = pTrav;
                pTrav = pTrav->pNext;
            }
            pnn->pNext = pTrav;
            if (pBack != NULL)
            {
                pBack->pNext = pnn;
            }
            else
            {
                pHead = pnn;
            }
            /*if (pBack == pTail)
            {
                pTail = pnn;
            }*/
        }
    }
};
void GenerateCode(cNode* root, string code)
{
    if (root == NULL)
        return;

    if (root->Character != '\0') // Leaf node
    {
        root->code = code;
        cout << "Character: " << root->Character << " -> Code: " << root->code << endl;
    }




    // Recur for left and right children
    GenerateCode(root->pleft, code + "0");
    GenerateCode(root->pright, code + "1");
}

cNode* Huffman_Tree(SortedList& l)
{
    while (l.pHead->pNext != NULL) // Combine nodes until one remains
    {
        cNode* first = l.pHead;
        l.pHead = l.pHead->pNext;
        first->pNext = NULL;

        cNode* second = l.pHead;
        l.pHead = l.pHead->pNext;
        second->pNext = NULL;

        // Create a new node
        cNode* internal = new cNode;
        internal->data = first->data + second->data;
        internal->pleft = first;
        internal->pright = second;
        internal->Character = '\0';


        l.attach(internal);
    }
    return l.pHead; // Return the root of the tree
}
int isfound(SortedList& sl, char c) //! the &
{
    cNode* ptrav = sl.pHead;
    while (ptrav != NULL)
    {


        if (ptrav->Character == c)
        {
            return 1;
        }
        ptrav = ptrav->pNext;

    }
    return 0;
}
void Frequency(string str)
{
    int Frequency, Flag;
    SortedList SortedList;
    cNode* pnn;
    for (int i = 0; i < str.length(); i++)
    {
        Frequency = Flag = 0;
        if ((Flag = isfound(SortedList, str[i])) == 0)
        {
            for (int j = i; j < str.length(); j++)
            {
                if (str[i] == str[j])
                {
                    Frequency++;
                }
            }
            pnn = new cNode;
            pnn->data = Frequency;
            pnn->Character = str[i];
            SortedList.attach(pnn);
        }
    }
    cout << "Character Frequencies:\n";
    SortedList.Display();
    cNode* root = Huffman_Tree(SortedList);
    cout << "Huffman Tree built successfully.\n";
    cout << "Generated Huffman GenerateCode:\n";
    GenerateCode(root, "");
}
int main()
{

    string str;
    cout << "Enter a string: ";
    getline(cin, str);
    Frequency(str);
    return 0;

}
