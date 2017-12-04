#pragma once
#include <vector>

using namespace std;

namespace algoPart
{
    template<class T>
    class Stack
    {
    public:
        //Constructeur
        Stack();
        //Destructeur
        ~Stack();
        //Est-il vide?
        bool IsEmpty();
        //Retourner le premier ajouté
        T Front();
        //Retourner la size de la pile
        size_t Size();
        //Retirer le premier élément ajouté
        void Pop();
        //Ajouter une valeur à la pile
        void Push(T value);
    private:
        vector<T> stack;
    };

    template<class T>
    inline Stack<T>::Stack()
    {
    }

    template<class T>
    inline Stack<T>::~Stack()
    {
    }

    template<class T>
    inline bool Stack<T>::IsEmpty()
    {
        return stack.size() == 0;
    }

    template<class T>
    inline T Stack<T>::Front()
    {
        return stack.front();
    }

    template<class T>
    inline size_t Stack<T>::Size()
    {
        return stack.size();
    }

    template<class T>
    inline void Stack<T>::Pop()
    {
        stack.erase(stack.begin());
    }

    template<class T>
    inline void Stack<T>::Push(T value)
    {
        stack.insert(stack.begin(), value);
    }

}