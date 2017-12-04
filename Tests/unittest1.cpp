#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SpaceShooter_Tp3_v2\List.h"
#include "..\SpaceShooter_Tp3_v2\Stack.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace algoPart;

namespace SpaceShooterTest
{		
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestMethod1)
        {
            int a = 0;
            List<int> list;
            list.PushBack(0);
            list.PushBack(1);
            list.PushBack(2);
            list.PushBack(3);
            list.PushBack(4);
            list.PushBack(5);
            for (List<int>::Iterator i = List<int>::Iterator(list.Start()); i != list.End(); ++i)
            {

                Assert::AreEqual(*i, a);
                a++;
            }
            // TODO: Ici, votre code de test
        }

        /*

        //Constructeur
        Stack();

        //Destructeur
        ~Stack();

        //Est-il vide?
        bool IsEmpty();

        //Retourner le premier ajouté
        T Front();

        //Retirer le premier élément ajouté
        void Pop();

        //Ajouter une valeur à la pile
        void Push(T value);

        */

#pragma region:Stack
        //<smasson>

        TEST_METHOD(TestStack_ConstructorDestructor_intfloatdoublechar)
        {
            //Déclaration des variables
            Stack<int>* stackInt = new Stack<int>();
            Stack<float>* stackFloat = new Stack<float>();
            Stack<double>* stackDouble = new Stack<double>();
            Stack<char>* stackChar = new Stack<char>();

            //Clean-up
            delete stackInt;
            delete stackFloat;
            delete stackDouble;
            delete stackChar;
        }

        TEST_METHOD(TestStack_IsEmpty_TRUE)
        {
            //Déclaration des variables
            Stack<int>* stackInt = new Stack<int>();
            Stack<float>* stackFloat = new Stack<float>();
            Stack<double>* stackDouble = new Stack<double>();
            Stack<char>* stackChar = new Stack<char>();

            //Validations
            Assert::IsTrue(stackInt->IsEmpty());
            Assert::IsTrue(stackFloat->IsEmpty());
            Assert::IsTrue(stackDouble->IsEmpty());
            Assert::IsTrue(stackChar->IsEmpty());

            //Clean-up
            delete stackInt;
            delete stackFloat;
            delete stackDouble;
            delete stackChar;
        }

        TEST_METHOD(TestStack_PushSingle)
        {
            //Déclaration des variables
            Stack<int>* stackInt = new Stack<int>();
            Stack<float>* stackFloat = new Stack<float>();
            Stack<double>* stackDouble = new Stack<double>();
            Stack<char>* stackChar = new Stack<char>();
            
            //Execution
            stackInt->Push(1);
            stackFloat->Push(2.3f);
            stackDouble->Push(2.34444);
            stackChar->Push('c');

            //Validations
            //de la Size
            Assert::AreEqual(1, (int)stackInt->Size());
            Assert::AreEqual(1, (int)stackFloat->Size());
            Assert::AreEqual(1, (int)stackDouble->Size());
            Assert::AreEqual(1, (int)stackChar->Size());
            //du Contenu
            Assert::AreEqual(1, stackInt->Front());
            Assert::AreEqual(2.3f, stackFloat->Front());
            Assert::AreEqual(2.34444, stackDouble->Front());
            Assert::AreEqual('c', stackChar->Front());

            //Clean-up
            delete stackInt;
            delete stackFloat;
            delete stackDouble;
            delete stackChar;
        }

        TEST_METHOD(TestStack_PushMultiple)
        {
            //Déclaration des variables
            Stack<int>* stackInt = new Stack<int>();
            Stack<float>* stackFloat = new Stack<float>();
            Stack<double>* stackDouble = new Stack<double>();
            Stack<char>* stackChar = new Stack<char>();

            //Execution
            stackInt->Push(1);
            stackInt->Push(2);
            stackInt->Push(3);
            stackInt->Push(4);

            stackFloat->Push(2.3f);
            stackFloat->Push(2.4f);
            stackFloat->Push(2.5f);
            stackFloat->Push(2.6f);

            stackDouble->Push(2.34444);
            stackDouble->Push(2.36666);
            stackDouble->Push(2.37777);
            stackDouble->Push(2.38888);

            stackChar->Push('c');
            stackChar->Push('d');
            stackChar->Push('e');
            stackChar->Push('f');

            //Validations
            //de la Size
            Assert::AreEqual(4, (int)stackInt->Size());
            Assert::AreEqual(4, (int)stackFloat->Size());
            Assert::AreEqual(4, (int)stackDouble->Size());
            Assert::AreEqual(4, (int)stackChar->Size());
            //du contenu
            Assert::AreEqual(4, stackInt->Front());
            Assert::AreEqual(2.6f, stackFloat->Front());
            Assert::AreEqual(2.38888, stackDouble->Front());
            Assert::AreEqual('f', stackChar->Front());

            //Clean-up
            delete stackInt;
            delete stackFloat;
            delete stackDouble;
            delete stackChar;
        }
        TEST_METHOD(TestStack_IsEmpty_FALSE)
        {
            //Déclaration des variables
            Stack<int>* stackInt = new Stack<int>();
            Stack<float>* stackFloat = new Stack<float>();
            Stack<double>* stackDouble = new Stack<double>();
            Stack<char>* stackChar = new Stack<char>();
            
            //Execution
            stackInt->Push(1);
            stackFloat->Push(2.3f);
            stackDouble->Push(2.34444);
            stackChar->Push('c');

            //Validations
            Assert::IsFalse(stackInt->IsEmpty());
            Assert::IsFalse(stackFloat->IsEmpty());
            Assert::IsFalse(stackDouble->IsEmpty());
            Assert::IsFalse(stackChar->IsEmpty());

            //Clean-up
            delete stackInt;
            delete stackFloat;
            delete stackDouble;
            delete stackChar;
        }

        TEST_METHOD(TestStack_PopOnSingleVal)
        {
            //Déclaration des variables
            Stack<int>* stackInt = new Stack<int>();
            Stack<float>* stackFloat = new Stack<float>();
            Stack<double>* stackDouble = new Stack<double>();
            Stack<char>* stackChar = new Stack<char>();

            //Execution
            stackInt->Push(1);
            stackFloat->Push(2.3f);
            stackDouble->Push(2.34444);
            stackChar->Push('c');

            stackInt->Pop();
            stackFloat->Pop();
            stackDouble->Pop();
            stackChar->Pop();

            //Validations
            //de la Size
            Assert::AreEqual(0, (int)stackInt->Size());
            Assert::AreEqual(0, (int)stackFloat->Size());
            Assert::AreEqual(0, (int)stackDouble->Size());
            Assert::AreEqual(0, (int)stackChar->Size());
            //du contenu
            Assert::IsTrue(stackInt->IsEmpty());
            Assert::IsTrue(stackFloat->IsEmpty());
            Assert::IsTrue(stackDouble->IsEmpty());
            Assert::IsTrue(stackChar->IsEmpty());

            //Clean-up
            delete stackInt;
            delete stackFloat;
            delete stackDouble;
            delete stackChar;
        }

        TEST_METHOD(TestStack_PopOnMultipleVal)
        {
            //Déclaration des variables
            Stack<int>* stackInt = new Stack<int>();
            Stack<float>* stackFloat = new Stack<float>();
            Stack<double>* stackDouble = new Stack<double>();
            Stack<char>* stackChar = new Stack<char>();

            //Execution
            stackInt->Push(1);
            stackInt->Push(2);
            stackInt->Push(3);
            stackInt->Push(4);

            stackFloat->Push(2.3f);
            stackFloat->Push(2.4f);
            stackFloat->Push(2.5f);
            stackFloat->Push(2.6f);

            stackDouble->Push(2.34444);
            stackDouble->Push(2.36666);
            stackDouble->Push(2.37777);
            stackDouble->Push(2.38888);

            stackChar->Push('c');
            stackChar->Push('d');
            stackChar->Push('e');
            stackChar->Push('f');

            stackInt->Pop();
            stackFloat->Pop();
            stackDouble->Pop();
            stackChar->Pop();

            //Validations
            //de la Size
            Assert::AreEqual(3, (int)stackInt->Size());
            Assert::AreEqual(3, (int)stackFloat->Size());
            Assert::AreEqual(3, (int)stackDouble->Size());
            Assert::AreEqual(3, (int)stackChar->Size());
            //du contenu
            Assert::AreEqual(3, stackInt->Front());
            Assert::AreEqual(2.5f, stackFloat->Front());
            Assert::AreEqual(2.37777, stackDouble->Front());
            Assert::AreEqual('e', stackChar->Front());

            //Clean-up
            delete stackInt;
            delete stackFloat;
            delete stackDouble;
            delete stackChar;
        }

        //</smasson>
#pragma endregion

    };
}