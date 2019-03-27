//============================================================================
// Name        : Message.cpp
// Author      : Juliette Rocco
// Description : Message Ordering
//============================================================================

#include <iostream>
#include "Message.h"

#ifndef MARMOSET_TESTING
int main();
#endif


#ifndef MARMOSET_TESTING

int main() {

        Message one;

        int input{0};
        std::string frag;

        while (input != -2) 
        {
                //takes input
                std::cin >> input;

                //inserts the word fragments as recieved and orders them
                if (input >= 0) 
                {
                        std::cin  >> frag;
                        one.insert(input,frag);

                }
                
                //would print the message so far recieved
                if (input == -1)
                {
                        one.print_message(); 
                }
        }

        std::cout <<"end";
        return 0;

}
#endif

//node constructor
Message::Message()    
{
        head=nullptr;
}

//node deconstructor
Message::~Message()   
{
        Node *p_head{head};

        //deconstructs the nodes 
        while (p_head != nullptr)
        {
                Node *temp_node{p_head};
                p_head = p_head->p_next;
                delete temp_node;
        }

        delete p_head;
        p_head = nullptr;


}

 //inserts a node into the list and orders it
void Message::insert( unsigned int id, std::string fragment) 
{
        //if its going to be the head of the node
        if (head == nullptr)
        {
                head = new Node(id,fragment);
                head->p_next = nullptr;
        }
        //inserts the node in the proper location
        else if (id < head->identifier)
        {
                Node *temp_node{new Node(id,fragment)};
                temp_node->p_next= head;
                head = temp_node;
        }
        //assings temp nodes to move things around
        else
        {
                Node *p_head{head};
                Node *next{p_head->p_next};

                while(next != nullptr && next->identifier<id )
                {
                        p_head = next;
                        next = next->p_next;

                }
                Node *temp_node_2{new Node(id, fragment)};

                temp_node_2->p_next = next;
                p_head->p_next = temp_node_2;
        }

}

//prints the message so far recieved
void Message::print_message() 
{

        unsigned int counter{0};
        Node *temp_node = head;

        for(Node *p_head{head}; p_head != nullptr; p_head = p_head->get_next())
        {

                temp_node = p_head;
                
                //prints dots
                for(unsigned int count{0}; count < (p_head->identifier - counter); ++count )
                {
                        std::cout <<"... ";
                }

                //prints EOT if the entire fragment hasn't been recieved yet 
                if (p_head->get_fragment() != "EOT")
                {
                        std::cout << p_head->get_fragment() << " ";
                }

                counter = (p_head->identifier ) + 1;

        }
        //missing fragment
        if (temp_node == nullptr || temp_node->fragment != "EOT")
        {
                std::cout <<"???";
        }

        std::cout<< std::endl;
}

//constructs the node 
Node::Node(unsigned int id, std::string frag )
{
        identifier = id;
        fragment = frag;
        p_next = nullptr;

}

//gets the next node 
Node *Node::get_next()
{
        return p_next;
}

//returns the word fragment 
std::string Node::get_fragment() 
{

        return fragment;
}

