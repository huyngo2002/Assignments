/*
    * Ho Chi Minh City University of Technology
    * Faculty of Computer Science and Engineering
    * Initial code for Assignment 0
    * Programming Fundamentals Spring 2022
    * Author: Tran Huy
    * Date: 06.01.2022
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef studyInPink_h
#define studyInPink_h

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

////////////////////////////////////////////////////////////////////////
///STUDENT'S ANSWER BEGINS HERE
///Complete the following functions
///DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

int firstMeet(int& EXP1, int& EXP2, const int& E1){
    //Complete this function to gain point on task 1
    if (E1 < 0 || E1 > 999)	return -999;
    if (E1 >= 0 && E1 <= 399){
    	if (E1 >= 0 && E1 <= 49){
    		EXP2 = EXP2 + 25;
    		if(EXP2 > 900)	EXP2 = 900;
    		if(E1 % 2 ==0){
    			EXP1 = ceil((float)(EXP1 - E1 / 5.0));
				if (EXP1 < 0)	EXP1 = 0;
				if (EXP1 > 900)	EXP1 = 900;
			}
			else{
				EXP1 = ceil((float)(EXP1 + E1 / 10.0));
				if (EXP1 < 0)	EXP1 = 0;
				if (EXP1 > 900)	EXP1 = 900;
			}
    		return EXP1 + EXP2;
		}
		else if (E1 <= 99){
			EXP2 = EXP2 + 50;
    		if(EXP2 > 900)	EXP2 = 900;
    		if(E1 % 2 ==0){
				EXP1 = ceil((float)(EXP1 - E1 / 5.0));
				if (EXP1 < 0)	EXP1 = 0;
				if (EXP1 > 900)	EXP1 = 900;
			}
			else{
				EXP1 = ceil((float)(EXP1 + E1 / 10.0));
				if (EXP1 < 0)	EXP1 = 0;
				if (EXP1 > 900)	EXP1 = 900;
			}
			return EXP1 + EXP2;
		}
		else if (E1 <= 149){
			EXP2 = EXP2 + 85;
    		if(EXP2 > 900)	EXP2 = 900;
    		if(E1 % 2 ==0){
				EXP1 = ceil((float)(EXP1 - E1 / 5.0));
				if (EXP1 < 0)	EXP1 = 0;
				if (EXP1 > 900)	EXP1 = 900;
			}
			else{
				EXP1 = ceil((float)(EXP1 + E1 / 10.0));
				if (EXP1 < 0)	EXP1 = 0;
				if (EXP1 > 900)	EXP1 = 900;
			}
			return EXP1 + EXP2;
		}
		else if (E1 <= 199){
			EXP2 = EXP2 + 50 + 25;
    		if (EXP2 > 900)	EXP2 = 900;
    		if (EXP2 < 0)	EXP2 = 0;
    		if(E1 % 2 ==0){
				EXP1 = ceil((float)(EXP1 - E1 / 5.0));
				if (EXP1 < 0)	EXP1 = 0;
				if (EXP1 > 900)	EXP1 = 900;
			}
			else{
				EXP1 = ceil((float)(EXP1 + E1 / 10.0));
				if (EXP1 < 0)	EXP1 = 0;
				if (EXP1 > 900)	EXP1 = 900;
			}
			return EXP1 + EXP2;
		}
		else if (E1 <= 249){
			EXP2 = EXP2 + 85 + 25;
    		if(EXP2 > 900)	EXP2 = 900;
    		if(E1 % 2 ==0){
				EXP1 = ceil((float)(EXP1 - E1 / 5.0));
				if (EXP1 < 0)	EXP1 = 0;
				if (EXP1 > 900)	EXP1 = 900;
			}
			else{
				EXP1 = ceil((float)(EXP1 + E1 / 10.0));
				if (EXP1 < 0)	EXP1 = 0;
				if (EXP1 > 900)	EXP1 = 900;
			}
			return EXP1 + EXP2;
		}
		else if (E1 <= 299){
			EXP2 = EXP2 + 85 + 50;
    		if(EXP2 > 900)	EXP2 = 900;
    		if(E1 % 2 ==0){
				EXP1 = ceil((float)(EXP1 - E1 / 5.0));
				if (EXP1 < 0)	EXP1 = 0;
				if (EXP1 > 900)	EXP1 = 900;
			}
			else{
				EXP1 = ceil((float)(EXP1 + E1 / 10.0));
				if (EXP1 < 0)	EXP1 = 0;
				if (EXP1 > 900)	EXP1 = 900;
			}
			return EXP1 + EXP2;
		}
		else{
			EXP2 = EXP2 + 85 + 50 + 25;
    		if(EXP2 > 900)	EXP2 = 900;
    		if(E1 % 2 ==0){
				EXP1 = ceil((float)(EXP1 - E1 / 5.0));
				if (EXP1 < 0)	EXP1 = 0;
				if (EXP1 > 900)	EXP1 = 900;
			}
			else{
				EXP1 = ceil((float)(EXP1 + E1 / 10.0));
				if (EXP1 < 0)	EXP1 = 0;
				if (EXP1 > 900)	EXP1 = 900;
			}
			return EXP1 + EXP2;
		}
	}
	else if(E1 <= 999){
		if (E1 <= 499){
			EXP2 = ceil((float)(EXP2 + (E1 / 7.0 + 9)));
			if (EXP2 > 900)	EXP2 = 900;
			if (EXP2 < 0)	EXP2 = 0;
			EXP1 = ceil((float)(EXP1 - 0.1 * E1));
			if (EXP1 < 0)	EXP1 = 0;
			if (EXP1 > 900)	EXP1 = 900;
			return EXP1 + EXP2;
		}
		else if (E1 <= 599) {
			EXP2 = ceil((float)(EXP2 + (E1 / 9.0 + 11)));
			if (EXP2 > 900)	EXP2 = 900;
			if (EXP2 < 0)	EXP2 = 0;
			EXP1 = ceil((float)(EXP1 - 0.1 * E1));
			if (EXP1 < 0)	EXP1 = 0;
			if (EXP1 > 900)	EXP1 = 900;
			return EXP1 + EXP2;
		}
		else if (E1 <= 699){
			EXP2 = ceil((float)(EXP2 + (E1 / 5.0 + 6)));
			if (EXP2 > 900)	EXP2 = 900;
			if (EXP2 < 0)	EXP2 = 0;
			EXP1 = ceil((float)(EXP1 - 0.1 * E1));
			if (EXP1 < 0)	EXP1 = 0;
			if (EXP1 > 900)	EXP1 = 900;
			return EXP1 + EXP2;
		}
		else if (E1 <= 799) {
			EXP2 = ceil((float)(EXP2 + (E1 / 7.0 + 9)));
			if (EXP2 > 900)	EXP2 = 900;
			if (EXP2 < 0)	EXP2 = 0;
			EXP1 = ceil((float)(EXP1 - 0.1 * E1));
			if (EXP1 < 0)	EXP1 = 0;
			if (EXP1 > 900)	EXP1 = 900;
			if (EXP2 > 200){
				EXP2 = ceil((float)(EXP2 + (E1 / 9.0 + 11)));
				if (EXP2 > 900)	EXP2 = 900;
				if (EXP2 < 0)	EXP2 = 0;
			}
			return EXP1 + EXP2;
		}
		else{
			EXP2 = ceil((float)(EXP2 + (E1 / 7.0 + 9) + (E1 / 9.0 +11)));
			if (EXP2 > 600){
				EXP2 = ceil((float)(EXP2 + (E1 / 5.0 + 6)));
				EXP2 = ceil((float)(EXP2 * 1.15));
				if (EXP2 > 900)	EXP2 = 900;
				if (EXP2 < 0)	EXP2 = 0;
			}
			EXP1 = ceil((float)(EXP1 - 0.1 * E1));
			if (EXP1 < 0)	EXP1 = 0;
			if (EXP1 > 900)	EXP1 = 900;
			return EXP1 + EXP2;
		}
	}
    
}

int investigateScene(int& EXP1, int& EXP2, int& HP2, int& M2, const int& E2){
	if (E2 < 0 || E2 > 999)	return -999;
    if (E2 >= 0 && E2 <= 299){
    	int d;
    	d = ceil((float)(E2 / 9.0 + 10));
    	EXP2 = EXP2 + d;
    	if (EXP2 > 900)	EXP2 = 900;
    	if (EXP2 < 0)	EXP2 = 0;
    	EXP1 = ceil((float)(EXP1 + d / 3.0));
    	if(EXP1 > 900)	EXP1 = 900;
    	if(EXP1 < 0)	EXP1 = 0;
	}
	else if (E2 <= 499) {
		int d;
		d = ceil((float)(E2 / 9.0 + 10));
    	EXP2 = EXP2 + d;
    	if (EXP2 > 900)	EXP2 = 900;
    	if (EXP2 < 0)	EXP2 = 0;
    	EXP1 = ceil((float)(EXP1 + d / 3.0));
    	if(EXP1 > 900)	EXP1 = 900;
    	if(EXP1 < 0)	EXP1 = 0;
    	EXP2 = ceil((float)(EXP2 + E2 * 35 / 100.0));
    	if (EXP2 > 900)	EXP2 = 900;
    	if (EXP2 < 0)	EXP2 = 0;
    	EXP1 = ceil((float)(EXP1 + E2 * 35 / 100.0 / 3.0));
    	if(EXP1 > 900)	EXP1 = 900;
    	if(EXP1 < 0)	EXP1 = 0;
	}
	else{
		int EXP1_t = EXP1, EXP2_t = EXP2;
		int d;
    	d = ceil((float)(E2 / 9.0 + 10));
    	EXP2 = EXP2 + d;
    	if (EXP2 > 900)	EXP2 = 900;
    	if (EXP2 < 0)	EXP2 = 0;
    	EXP1 = ceil((float)(EXP1 + d / 3.0));
    	if(EXP1 > 900)	EXP1 = 900;
    	EXP2 = ceil((float)(EXP2 + E2 * 35 / 100.0));
    	if (EXP2 > 900)	EXP2 = 900;
    	if (EXP2 < 0)	EXP2 = 0;
    	EXP1 = ceil((float)(EXP1 + E2 * 35 / 100.0 / 3.0));
    	if(EXP1 > 900)	EXP1 = 900;
    	if(EXP1 < 0)	EXP1 = 0;
    	int t;
    	t = ceil((float)((EXP2 - EXP2_t) * 17 / 100.0));
    	EXP2 = EXP2_t + t;
    	if (EXP2 > 900)	EXP2 = 900;
    	if (EXP2 < 0)	EXP2 = 0;
    	t = ceil((float)(t / 3.0));
    	EXP1 = EXP1_t + t;
    	if(EXP1 > 900)	EXP1 = 900;
    	if(EXP1 < 0)	EXP1 = 0;
	}
	HP2 = ceil((float)(HP2 - (E2 * E2 * E2) / (float)(pow(2, 23))));
	if (HP2 > 999)	HP2 = 999;
	if (HP2 < 0)	HP2 = 0;
	if (E2 % 2 == 0){
		M2 = ceil((float)(M2 + E2 * E2 / 50.0));
		if (M2 > 2000)	M2 = 2000;
	}
	return EXP2 + HP2 + M2 + EXP1;
}

int traceLuggage(int& HP1, int& EXP1, int& M1, const int& E3){
    if (E3 < 0 || E3 > 999)	return -999;
    int p[9] = {1, 3, 5, 7, 9, 11, 13, 15, 17};
    int k;
    for (int i = 0; i < 8; i++){
    	p[i] = (p[i] + E3) % 26 + 65;
    	if(p[i] == 80){
    		k = i + 1;
    		break;
		}
	}
	HP1 = HP1 - 80 * k * 2;
	EXP1 = EXP1 + (1000 - 80 * k) % 101;
	M1 = ceil((float)(M1 - k * E3 / 9.0));
	int p_2[7] = {2, 3, 5, 7, 11, 13, 17};
	int s = 0;
	for (int i = 0; i < 6; i++){
		p_2[i] = (p_2[i] + E3) % 26;
		s += p_2[i];
	}
	int k_1;
	int m = ceil((float)(s / 7.0));
	for (int i = 0; i < 6; i++){
		p_2[i] = (p_2[i] + s + m) % 26 + 65;
		if(p_2[i] == 80){
    		k_1 = i + 1;
    		break;
		}
	}
	HP1 = HP1 - 80 * k_1 * 2;
	EXP1 = EXP1 + (1000 - 80 * k_1) % 101;
	M1 = ceil((float)(M1 - k_1 * E3 / 9.0));
	int P_3[20];
	for (int i = 0; i < 19; i++){
		P_3[i] = (2 * i + 2) * (2 * i + 2);
	}
	int max = 0;
	for (int i = 0; i < 19; i++){
		P_3[i] = (P_3[i] + E3 * E3) % 113;
		if (P_3[i] > max)	max = P_3[i];
	}
	int k_2;
	for (int i = 18; i >= 0; i--){
		P_3[i] = (int)ceil((float)((P_3[i] + E3) / max)) % 26 + 65;
		if(P_3[i] == 80){
    		k_2 = i + 1;
    		break;
		}
	}
	for (int i = 0; i <= k_2; i++){
		HP1 = HP1 - P_3[i] * k_2 * 3;
		EXP1 = EXP1 + (3500 - P_3[i] * k_2) % 300;
	}
	int P_4[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int min = 0, min_idx;
	for (int i = 0; i < 11; i++){
		P_4[i] = (P_4[i] + (E3 / 29) * (E3 / 29) * (E3 / 29)) % 9;
		if (P_4[i] < min)	min = P_4[i];
	}
	for (int i = 0; i < 11; i++){
		if (min == P_4[i]){
			min_idx = i + 1;
			break;
		}
	}
	for (int i = 0; i < 11; i++){
		P_4[i] = ((P_4[i] + E3) * (min / min_idx)) % 26 + 65;
	}
	int k3;
	for (int i = 0; i < 11; i++){
		if (P_4[i] == 80){
			k3 = i + 1;
			break;
		}
	}
	for (int i = 0; i < 11; i++){
		HP1 = HP1 - P_4[i] * k3 * 4;
		EXP1 = EXP1 + (4500 - P_4[i] * k3) % 400;
	}
	if (k!= 80 && k_1 != 80 && k_2 != 80 && k3 != 80){
		HP1 = HP1 - (59 * E3) % 900;
		EXP1 = EXP1 + (79 * E3) % 300;
	}
	return -1;
}

////////////////////////////////////////////////
///END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* studyInPink_h */
