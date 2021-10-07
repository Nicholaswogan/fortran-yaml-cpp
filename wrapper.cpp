#include <iostream>
#include <vector>
#include <cstring>
#include "yaml-cpp/yaml.h"

const int STRING_LENGTH = 1024;

struct TypeNode
{
  // Node
  int type = 0;
  
  // Scalar
  char *string = NULL;
  
  // Dictionary
  TypeNode *first_keyvaluepair = NULL;
  char *key = NULL;
  TypeNode *value = NULL;
  TypeNode *next_keyvaluepair = NULL;
  
  // List
  TypeNode *first_listitem = NULL;
  TypeNode *node = NULL;
  TypeNode *next_listitem = NULL;
  
  // Utlities
  bool IsMap(){return type == 1;}
  bool IsSequence(){return type == 2;}
  bool IsScalar(){return type == 3;}
  bool IsNull(){return type == 4;}
};

void read_value(YAML::Node node, TypeNode *&mynode)
{  
  if (node.IsMap()){
    mynode = new TypeNode;
    mynode->type = 1;
    mynode->first_keyvaluepair = new TypeNode;
    
    TypeNode *keyvaluepair = mynode->first_keyvaluepair;
    int i = 0;
    for (YAML::const_iterator it=node.begin(); it != node.end(); ++it)
    {
      std::string key = it->first.as<std::string>();
      YAML::Node value = it->second;
      
      // and set the key
      keyvaluepair->key = new char[STRING_LENGTH]();
      // keyvaluepair->key = "";
      strcpy(keyvaluepair->key, key.c_str());
      
      // read the corresponing value of the key value pair
      read_value(value, keyvaluepair->value);
      
      // move on to the next key value pair
      if (i < node.size() - 1){
        keyvaluepair->next_keyvaluepair = new TypeNode;
        keyvaluepair = keyvaluepair->next_keyvaluepair;
      }
      i += 1;
    }
  }
  else if (node.IsSequence()){
    // std::cout << "it is a sequence" << std::endl;
    mynode = new TypeNode;
    mynode->type = 2;
    mynode->first_listitem = new TypeNode;
    
    TypeNode *listitem = mynode->first_listitem;
    for (int i = 0; i < node.size(); i++){
      YAML::Node item = node[i];
      
      read_value(item, listitem->node);
      
      if (i < node.size() - 1){
        listitem->next_listitem = new TypeNode;
        listitem = listitem->next_listitem;
      }
    }
  }
  else if (node.IsScalar()){
    // std::cout << "it is a scalar = " << node.as<std::string>() << std::endl;
    
    // allocate sclar and set string
    mynode = new TypeNode;
    mynode->type = 3;
    mynode->string = new char[STRING_LENGTH]();
    // mynode->string = "";
    strcpy(mynode->string, node.as<std::string>().c_str());
    
  }
  else if (node.IsNull()){
    // std::cout << "it is a null" << std::endl;
    mynode = new TypeNode;
    mynode->type = 4;
  }
    
}

void destroy(TypeNode *&node)
{
  if (node->IsMap()){
    TypeNode *pair;
    TypeNode *next;
    pair = node->first_keyvaluepair;    
    while (pair){
      next = pair->next_keyvaluepair;
      destroy(pair->value);
      delete[] pair->key;
      delete pair->value;
      delete pair;
      pair = next;
    }
    node->first_keyvaluepair = NULL;
  }
  else if (node->IsSequence()){
    TypeNode *item;
    TypeNode *next;
    item = node->first_listitem;
    while (item){
      next = item->next_listitem;
      destroy(item->node);
      delete item->node;
      delete item;
      item = next;
    }
    node->first_listitem = NULL;
  }
  else if (node->IsScalar()){
    delete[] node->string;
    delete node;
    node = NULL;
  }
  else if (node->IsNull()){
    delete node;
    node = NULL;
  }
}


void dump(TypeNode *&node)
{
  if (node->IsMap()){
    std::cout << "\n";
    TypeNode *keyvaluepair = node->first_keyvaluepair;    
    while (keyvaluepair){
      std::cout << keyvaluepair->key << ": ";
      dump(keyvaluepair->value);
      keyvaluepair = keyvaluepair->next_keyvaluepair;
    }
  }
  else if (node->IsSequence()){
    std::cout << "\n";
    TypeNode *item = node->first_listitem;
    while (item){
      std::cout << "- ";
      dump(item->node);
      item = item->next_listitem;
    }
  }
  else if (node->IsScalar()){
    std::cout << node->string << std::endl;
  }
  else if (node->IsNull()){
    std::cout << "" << std::endl;
  }
}

extern "C"
{

TypeNode* LoadFile_c(char* filename)
{
  YAML::Node file = YAML::LoadFile(filename);
  TypeNode *root;
  read_value(file, root);
  return root;
}

void DestroyNode(TypeNode *&root)
{
  destroy(root);
  delete root;
  root = NULL;
}

}




