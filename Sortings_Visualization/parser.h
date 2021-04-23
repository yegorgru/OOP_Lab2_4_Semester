#ifndef PARSER_H
#define PARSER_H
#include <algorithm>
#include <iostream>
#include <list>
#include <string>
using namespace std;
class Component
{
protected:
    Component *parent_;
public:
    virtual ~Component() {}
    void SetParent(Component* parent){
        this->parent_ = parent;
    }
    Component * GetParent() const {
        return this->parent_;
    }

    virtual void Add(Component *component){}
    virtual void Remove(Component *component){}
    virtual bool IsComposite() const {
        return false;
      }
    virtual string Operation() const  {}



};
class Leaf :public Component{
public:
 std::string Operation() const override {
   return "Leaf";
 }
};
class Composite :public Component {
protected:
       list<Component*> children_;
public:
       void Add(Component *component) override {
           this->children_.push_back(component);
           component->SetParent(this);
         }
       void Remove(Component *component) override {
           children_.remove(component);
           component->SetParent(nullptr);
         }
       bool IsComposite() const override {
           return true;
         }
       string Operation() const override {
           string result;
           for (const Component *c : children_) {
             if (c == children_.back()) {
               result += c->Operation();
             } else {
               result += c->Operation() + "+";
             }
           }
           return "Branch(" + result + ")";
         }

};
void Simple_tree(Component *component) {

  cout << "RESULT: " << component->Operation();

}
void Complex_tree(Component *component1, Component *component2) {

  if (component1->IsComposite()) {
    component1->Add(component2);
  }
  cout << "RESULT: " << component1->Operation();

}
#endif // PARSER_H
