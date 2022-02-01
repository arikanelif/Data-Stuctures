/*
YOU HAVE TO WRITE THE REQUIRED  FUNCTIONS. YOU CAN ADD NEW FUNCTIONS IF YOU NEED.
*/
/* @Tolga Ovatman
Student Name: Elif Arıkan
Student ID : 150180010
Date: 11.11.2020 */

#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "counter.h"

using namespace std;

	
int Counter::findindex(Token *arr,char *elem){
	//THIS FUNCTION WILL BE CODED BY me:)
	int result = -1;
	for(int i=0; i<ARRAY_SIZE ; i++){
		if((arr[i].token[0]== elem[0]) && (arr[i].token[1]== elem[1]) ){
			
			return i;

		}	
	}
	
	return result;
	
} 

bool Counter::contains(char *token, char target){
	//THIS FUNCTION WILL BE CODED BY me

	char target_arr[TOKEN_LENGTH];
	target_arr[0]= target ;
	target_arr[1]= target ;
	if(token[0] == target_arr[0])
		return true;
	else {
		if(token[1] == target_arr[1])
			return true ;
		else
			return false;
	}
}

void Counter::read_and_count(){
	//THIS FUNCTION WILL BE CODED BY YOu
	const char *filename;
	FILE *file_pi;
	char a ,b ,ch[2];
	int result;
	bool end1, end2;
	filename= "pi_approximate" ;
	file_pi=fopen( filename , "r") ;
	result = fscanf(file_pi ,"%c%c" , &a, &b) ;
	ch[0] =a;
	ch[1] =b;
	
	while (result != EOF){
		result = fscanf(file_pi ,"%c" , &a);
		if(a == '\n') 
			break ;
		ch[0]= ch[1] ; 
		ch[1]= a ;
		end1 = contains(ch, '.');
		end2 = contains (ch, '\0');
		if(end1 == false && end2 == false){
			if(findindex(token_array, ch) == -1){
				for(int n =0 ; n<2 ; n++)
					token_array[token_count].token[n]= ch[n] ;
				token_array[token_count].count++;
				token_count++;

			}
			else{
				token_array[findindex(token_array, ch)].count++;
			}		
		}
	}
	fclose(file_pi);
}


Token *Counter::get_most_common_three(){
	//THIS FUNCTION WILL BE CODED BY elif
	static Token most_token[3];
	
	int most[] ={0,0,0};
	int index_biggest[] ={0,0,0} ;
	for (int i = 0; i < ARRAY_SIZE; i++){
		if(token_array[i].count > most[0]){
			most[0] = token_array[i].count;
			index_biggest[0]=i ;
		}
	}
	for (int i = 0; i < ARRAY_SIZE; i++){
		if(token_array[i].count > most[1] && i != index_biggest[0]){
			most[1] = token_array[i].count;
			index_biggest[1]=i ;
			
		}
	}for (int i = 0; i < ARRAY_SIZE; i++){
		if( i != index_biggest[0] && i != index_biggest[1]){
			if(token_array[i].count > most[2]){
				most[2] = token_array[i].count;
				index_biggest[2]=i ;
			}
		}
	}int token_lengt=0;
	while(token_lengt<3){
		int a = index_biggest[token_lengt];
		for (int j = 0; j< 2; j++){
			most_token[token_lengt].token[j] = token_array[a].token[j] ;
		}
		most_token[token_lengt].count=most[token_lengt];
		most_token[token_lengt].token[2] = '\0' ;
		token_lengt++;
	}
	return most_token;
}
