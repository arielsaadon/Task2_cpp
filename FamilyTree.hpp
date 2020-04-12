#pragma once

#include <string>

using namespace std;

namespace family{
    class Person{
        public:
        string name;
        Person *father,*mother;

        Person(string name):name(name),father(nullptr),mother(nullptr){}
        ~Person();
    };

    class Tree{
        public:
        Person* root;

        public:
        Tree(string name){this->root = new Person(name);}
        ~Tree();

        Tree& addFather(string name,string father);
        Tree& addMother(string name,string mother);
        string relation(string person);
        string find(string relation);
        void display();
        void remove(string name);
    };
}