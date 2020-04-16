#include "FamilyTree.hpp"

#include <iostream>
#include <string>
#include <stdexcept>

void family::Tree::deleteNodeTree(Person* person) {
    if (person == nullptr)
        return;

    deleteNodeTree(person->mother);
    deleteNodeTree(person->father);

    delete person;
}

void family::Tree::getLevel(Person* root, std::string& name, int level){
    if(root == nullptr)
        return;

    if(!root->name.compare(name) && root->mother == nullptr && root->father == nullptr) {
        root->level = level;
        return;
    }
    getLevel(root->mother,name,level+1);
    getLevel(root->father,name,level+1);
}

std::string family::Tree::setRelation(Person* person,std::string name,const std::string& gForgM){
    std::string relation;
    getLevel(root,name,1);
    int level = person->level;
    int i = 3;

    while(i<level){
        relation += "great-";
        i++;
    }

    relation += gForgM;
    return relation;
    }

family::Person* family::Tree::ifNameExists(const std::string& name,Person* person){
    if (person == nullptr)
        return nullptr;

    if (!person->name.compare(name))
        return person;

    family::Person* searchLeft = ifNameExists(name, person->mother);
        if(searchLeft)
        return searchLeft;

    family::Person* searchRight = ifNameExists(name, person->father);
        return searchRight;
}

family::Person* family::Tree::ifNameExistsForRemove(const std::string& name,Person* person){
    if (person == nullptr)
        return nullptr;
    if(person->mother != nullptr){
        if(!person->mother->name.compare(name))
            return person;
    }
    if(person->father != nullptr){
        if(!person->father->name.compare(name))
            return person;
    }

    family::Person* searchLeft = ifNameExistsForRemove(name, person->mother);
    if(searchLeft)
        return searchLeft;

    family::Person* searchRight = ifNameExistsForRemove(name, person->father);
    return searchRight;
}

family::Person* family::Tree::ifRelationExists(const std::string& relation,Person* person){
    if (person == nullptr)
        return nullptr;

    if (!person->familyRelation.compare(relation))
        return person;

    family::Person* searchLeft = ifRelationExists(relation, person->mother);
        if(searchLeft)
            return searchLeft;

    family::Person* searchRight = ifRelationExists(relation, person->father);
        return searchRight;
}

void family::Tree::printBT(const std::string& prefix, const Person* node, bool isLeft){//https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
    if( node != nullptr ){
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        std::cout << node->name << "[" << node->familyRelation << "]" << std::endl;

        printBT( prefix + (isLeft ? "│   " : "    "), node->father, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->mother, false);
    }
}

/**
 ** EX Functions
 **/

family::Tree& family::Tree::addFather(const std::string& name,const std::string& father){
    if (!this->root->name.compare(name) && this->root->father == nullptr) {
        this->root->father = new Person(father);
        this->root->father->familyRelation = "father";
        this->root->father->level = 2;
        return *this;
    }else {
        Person* search = ifNameExists(name, root);
        if(search != nullptr && search->father == nullptr) {
            if(!search->name.compare(name)) {
                search->father = new Person(father);
                search->father->familyRelation = setRelation(search->father,father,"grandfather");
                return *this;
            }
        }else
            throw std::out_of_range{"The name is not found or he/she already has a father"};
    }
    return *this;
}

family::Tree& family::Tree::addMother(const std::string& name,const std::string& mother){
    if (!this->root->name.compare(name) && this->root->mother == nullptr) {
        this->root->mother = new Person(mother);
        this->root->mother->familyRelation = "mother";
        this->root->mother->level = 2;
        return *this;
    }else {
        Person* search = ifNameExists(name, root);
        if(search != nullptr && search->mother == nullptr) {
            if(!search->name.compare(name)) {
                search->mother = new Person(mother);
                search->mother->familyRelation = setRelation(search->mother,mother,"grandmother");
                return *this;
            }
        }else
            throw std::out_of_range{"The name is not found or he/she already has a mother"};
    }
    return *this;
}

std::string family::Tree::relation(const std::string& person){
    std::string relation;
    Person* search = ifNameExists(person,root);

    if(search)
        relation += search->familyRelation;
    else
    relation += "unrelated";

    return relation;
}

std::string family::Tree::find(const std::string& relation){
    std::string name;
    Person* search = ifRelationExists(relation,root);

    if(search)
        name += search->name;
    else
        throw std::out_of_range{"No relation exists in the tree"};

    return name;
}

void family::Tree::display(){
    if(root == nullptr)
        return;
    printBT("", root, false);
}

void family::Tree::remove(const std::string& name){
    if(!root->name.compare(name))
        throw std::out_of_range{"It is impossible to erase the person"};

    Person* searchNull = ifNameExistsForRemove(name,root);
    Person* search = ifNameExists(name,root);

    if(searchNull){
        if(searchNull->father != nullptr){
            if(!searchNull->father->name.compare(name))
            searchNull->father = nullptr;    
        }if(searchNull->mother != nullptr){
            if(!searchNull->mother->name.compare(name))
                searchNull->mother = nullptr;
            }
    }

    if(search)
    deleteNodeTree(search);
    else
        throw std::out_of_range{"The name is not found in the tree"};
}
