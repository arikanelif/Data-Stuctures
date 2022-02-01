/* @Tolga Ovatman
Student Name: Elif Arıkan
Student ID : 150180010
Date: -- */
#include <stdio.h>
#include <iostream> 
#include <stdlib.h>

using namespace std;
struct valueList
{
	double value;
	int quantity;
	valueList * next ;
};

struct resistor{
char group;
double value;
int quantity;
resistor *next;
};

#ifndef _H
#define _H
struct circuit{
	valueList* headvalue;
	resistor *head;
	void create();
	void add_resistor(char, double);
	int remove_resistor(char, double);
	void delete_resistor(char);
	void circuit_info();
	void clear();
};
#endif

struct resistor_list{
    char group;
    double value;
};

circuit ResistorList;

int main(int argc, char** argv)
{
	const char *filename = argv[1] ;
	//const char *filename="input.txt";
	FILE *file_pi;
	file_pi=fopen(filename , "r") ;
	if(!file_pi){
		cout<<" dosya acilamadi"<< endl;
	}

	else{
		ResistorList.create();
		resistor_list k;
        while(fscanf(file_pi , "%c %lf ", &k.group, &k.value) != EOF){
			resistor* node = new resistor ;
			node->group=k.group;
			node->value=k.value;
			node->next=NULL;
            node->quantity=1;

            if(node->value > 0){
				ResistorList.add_resistor(node->group, node->value);
			}
            else if(node->value < 0){
            	int result =ResistorList.remove_resistor(node->group, node->value);
				if (result== 3)
				{
					ResistorList.delete_resistor(node->group);
				}
            }else if(node->group == 'A' && node->value == 0){
            	ResistorList.circuit_info();
            }
		}
		fclose(file_pi);
    	ResistorList.clear();
	}
	//getchar();
    return 0;
}

void circuit ::create(){
	head=NULL;
}
void circuit ::add_resistor(char ch, double n){
    resistor* node = new resistor;
	node->group= ch;
    node->value= n;
    node->quantity=1;
    node->next=NULL;

    // add the new node to convenient where in linked list
	resistor *traverse, *previous;
	traverse=head;
	if (!traverse){ // first node adding
		head=node;
		return;
	}
	int i=0; // to check whether it comes before head or not
	while (traverse && traverse->group <= node->group){   
        if(traverse->group == node->group)
        {	if(traverse->value== node->value){
            	traverse->quantity++;
				return;
			}else
			{
				cout << "NO_RESISTOR" << endl; 
			}
			
        }
		else if (traverse->group < node->group)
        {
            previous=traverse;
            traverse=traverse->next;
            i++;
        }
	}
	if(i==0) // new node is placed instead of head
	{
		node->next=head;
		head=node;
	}	
	else if(traverse) // add into the mid position
	{
		node->next=traverse;    // p n t
		previous->next=node;
	}
	else // add to the end of the list
	{
		previous->next=node;  	// p n
		
    }
}
int circuit :: remove_resistor(char ch, double n) {
	resistor *transverse;
	for(transverse=head; transverse ; transverse=transverse->next){
		if(transverse->group == ch){
			if(transverse->quantity > 1){
				transverse->quantity--;
				return 0 ;

			}
			else 
			{
				return 3;
			}	
		}	
	}cout << "NO_RESISTOR" << endl;
	return 0 ;
}
void circuit ::delete_resistor(char ch){
	resistor *traverse , *previous;
	traverse=head ;
	for(int i=0; traverse ; traverse=traverse->next, i++ ){
		
		if(traverse->group == ch){
			if(i==0){
				head=head->next;
			}else{
				previous->next = traverse->next;
				delete traverse;
				return;
			}
		}previous=traverse;
	}
}
void circuit ::circuit_info() {
    double total=0;
	resistor* traverse ;
	valueList *previous, *temp ;
	headvalue =NULL;
	traverse=head;
	for(int i=0; traverse ; traverse=traverse->next, i++ ){
		total += (traverse->value/traverse->quantity);

		valueList *node = new valueList;
		node->value=traverse->value;
		node->quantity= traverse->quantity;
		node->next=NULL;

		temp=headvalue;

		if (i==0){
			headvalue= node;
		}
		else
		{
			int n=0;
			while (temp && temp->value <= node->value)
			{   
        		if(temp->value == node->value)
       	 		{
            		temp->quantity++;
					
					break;
				}
				else if (temp->value < node->value)
				{
					previous=temp;
					temp=temp->next;
					n++;
				}
			}
			if(n==0) // new node is placed instead of head
			{
				node->next=headvalue;
				headvalue = node;
			}	
			else if(temp) // add into the mid position
			{	
				if(node->value != temp->value)
				{
					node->next=temp;    // pre - traverse- temp 
					previous->next=node;
				}

			}
			else // add to the end of the list
			{
				previous->next=node;  	// pre - tra 
				
			}
			
			
			
		
		}
	}	
	for (temp=headvalue; temp; temp=temp->next){
		cout << temp->value <<":"<< temp->quantity << endl;
	}
	cout << "Total resistance="<< total << " ohm" << endl;

}


void circuit ::clear() {
	resistor *traverse;
	while (head)  
	{
		traverse=head;
		head=head->next;
		delete traverse;
	}
}