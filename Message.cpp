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

        while (input != -2) //would accept input
        {

                std::cin >> input;


                if (input >= 0) //would insert the word fragments as recieved and order them
                {
                        std::cin  >> frag;
                        one.insert(input,frag);

                }

                if (input == -1)
                {
                        one.print_message(); //would print the message so far recieved
                }
        }

        std::cout <<"end";
        return 0;

}
#endif

Message::Message()    //node constructor
{
        head=nullptr;
}

Message::~Message()   //node deconstructor
{
        Node *p_head{head};


        while (p_head != nullptr)
        {
                Node *temp_node{p_head};
                p_head = p_head->p_next;
                delete temp_node;
        }

        delete p_head;
        p_head = nullptr;


}

void Message::insert( unsigned int id, std::string fragment)    //inserts a node into the list and orders it
{

        if (head == nullptr)
        {
                head = new Node(id,fragment);
                head->p_next = nullptr;
        }
        else if (id < head->identifier)
        {
                Node *temp_node{new Node(id,fragment)};
                temp_node->p_next= head;
                head = temp_node;
        }
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

void Message::print_message()   //prints the messaged so far recieved
{

        unsigned int counter{0};
        Node *temp_node = head;

        for(Node *p_head{head}; p_head != nullptr; p_head = p_head->get_next())
        {

                temp_node = p_head;

                for(unsigned int count{0}; count < (p_head->identifier - counter); ++count )
                {
                        std::cout <<"... ";
                }

                if (p_head->get_fragment() != "EOT")
                {
                        std::cout << p_head->get_fragment() << " ";
                }

                counter = (p_head->identifier ) + 1;

        }
        if (temp_node == nullptr || temp_node->fragment != "EOT")
        {
                std::cout <<"???";
        }

        std::cout<< std::endl;
}

Node::Node(unsigned int id, std::string frag )    //constructs the node
{
        identifier = id;
        fragment = frag;
        p_next = nullptr;

}

Node *Node::get_next()    //gets the next node
{
        return p_next;
}

std::string Node::get_fragment()    //returns the word fragment
{

        return fragment;
}

