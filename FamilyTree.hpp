#pragma once

#include <string>

namespace family {
    class Person{
    public:
        std::string name;
        std::string familyRelation;
        int level;
        Person *father,*mother;

        Person(std::string name): name(name),familyRelation("me"),level(1),father(nullptr),mother(nullptr){}

    };

    class Tree{
        public:
            Person* root;

            Tree(std::string name) {this->root = new Person(name);}
            ~Tree(){deleteNodeTree(root);}

            Tree& addFather(const std::string& name,const std::string& father);
            Tree& addMother(const std::string& name,const std::string& mother);
            std::string relation(const std::string& person);
            std::string find(const std::string& relation);
            void remove(const std::string& name);
            void display();

        private:
            void deleteNodeTree(Person* person);
            void getLevel(Person* root, std::string& name, int level);
            std::string setRelation(Person* person,std::string name,const std::string& gForgM);
            Person* ifNameExists(const std::string& name,Person* person);
            Person* ifNameExistsForRemove(const std::string& name,Person* person);
            Person* ifRelationExists(const std::string& relation,Person* person);
            void printBT(const std::string& prefix, const Person* node, bool isLeft);


    };
}