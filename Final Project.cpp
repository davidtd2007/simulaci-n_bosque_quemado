#include <iostream>
#include <cstdlib>
#include <cstring>
#include< stdio.h >
#include<stdlib.h>
#include<time.h>
using namespace std;


int getRandomNumber(int max, int min) { //this method gives a random number each time it is called

	int num = min + rand() % (max+1 - min);

	return num;
}

class Cells
{
	char state;			// detaills of the cels
	int change_state;//if the cells need to change to the next stage =1 if not =0

public:
	Cells(char n, int c_state); // constructor


	char getState();   // returns the current state of the cell


	int getStateBool();  // returns the bool

	void setState(char newState); // changes the state if the cell

	void setStateBool(int newStateBool); // changes wheter

};

class CellsList
{
	Cells* List[21][21];  // List of cells 

	//This ints will record some information to be displayed in the simulation
	int numberOfGround = 0;
	int numberOfFire = 0;
	int numberOfTrees = 0;
	int numberOfSteps= 0;


public:
	void InitializeCells(); //first state of all cells
	
	void showCells();// display all the cells 

	void changestate();// checks all the states and change them if necesary

	bool checkfireleft(); // check if there are any fire left to finsih the simulation
	
	void informationDisplay();// display the information of the current state of  the simulation


};


int main(void)
{
	srand((unsigned)time(0));
	bool bolean=1;
	CellsList* Forest = new CellsList;

	Forest->InitializeCells();


	while (bolean == 1) {
		Forest->showCells();
		Forest->informationDisplay();
		system("PAUSE");
		system("cls");
		Forest->changestate();
		bolean = Forest->checkfireleft();
	}
	Forest->showCells();
	Forest->informationDisplay();
	cout << "No fire left, simulation finished" << endl;

	system("PAUSE");
	return 0;
}



Cells::Cells(char n, int c_state)
{
	state = n;
	change_state = c_state;
}


char Cells::getState() 
{
	return state;
}
void Cells::setState(char newState) {
	state = newState;
}

void Cells::setStateBool(int newStateBool) {
	change_state = newStateBool;
}

int  Cells::getStateBool() {
	{
		return  change_state;
	}
}

void CellsList::InitializeCells() {
	{
		int i = 0;
		int j = 0; //Cell position

		while (i <= 20) {

			if ((i ==0) || (j == 0) || (i == 20) || (j == 20)) { // the cells in the border are set to ground since are the boundaries
				List[i][j] = new Cells('G', 0);
				j++;
			}
			else {
				List[i][j] = new Cells('*', 0); // the rest are set to have a tree
				j++;
			}

			if (j == 21) {
				i++;
				j = 0;
			}


		}
		int numberoffires = getRandomNumber(5,1);
		int t = 0;
		while (t<=numberoffires) {
			i= getRandomNumber(19, 1);
			j=getRandomNumber(19, 1);
			List[i][j]->setState('F');
			t++;
		}
	}
}

void CellsList::showCells() {

	int i =0;

	while (i<=20) {
		cout << List[i][0]->getState() << "   " << List[i][1]->getState() << "   " << List[i][2]->getState()
			<< "   " << List[i][3]->getState() << "   " << List[i][4]->getState() << "   " << List[i][5]->getState()
			<< "   " << List[i][6]->getState() << "   " << List[i][7]->getState() << "   " << List[i][8]->getState()
			<< "   " << List[i][9]->getState() << "   " << List[i][10]->getState() << "   " << List[i][11]->getState()
			<< "   " << List[i][12]->getState() << "   " << List[i][13]->getState() << "   " << List[i][14]->getState()
			<< "   " << List[i][15]->getState() << "   " << List[i][16]->getState() << "   " << List[i][17]->getState()
			<< "   " << List[i][18]->getState() << "   " << List[i][19]->getState() << "   " << List[i][20]->getState() << endl;

		cout << endl;
		i++;
	}
	
	

}


void CellsList::informationDisplay() {
	int i = 0;
	int j = 0; //Cell position
	numberOfSteps++;//each time this method runs one step

	//reset the number of each element
	numberOfFire = 0;
	numberOfTrees = 0;
	numberOfGround = 0;

	while (i <= 20) { 

		switch (List[i][j]->getState()) //count how many cells of each type are there
		{
		case 'F':
			numberOfFire++;
			j++;
			break;
		case 'G': 
			numberOfGround++;
			j++;
			break;
		case '*': 
			numberOfTrees++;
			j++;
			break;
		}

		if (j == 21) { //check the next line of cells 
			i++;
			j = 0;
		}
		

	}
	
	cout << "Step number: " <<numberOfSteps<<endl ;
	cout << "Numeber of Trees: " << numberOfTrees << endl;
	cout << "Numeber of Ground Cells: " << numberOfGround << endl;
	cout << "Numeber of Burning Trees: " << numberOfFire << endl;


}


bool CellsList::checkfireleft() {
	int i = 1;
	int j = 1; //Cell position
	bool result=0;

	while (i <= 19) { // this code doesn't check the boundary cells since they can't burn

		if (List[i][j]->getState()=='F') { //check if the surronding cells are burining
			result = 1;
			j++;
		}
		else {
			j++;
		}

		if (j == 20) { //check the next line of cells 
			i++;
			j = 0;
		}

		
	}
	return result;
}


/*This method follows the following steps:
* 1 Check for each cell if the surrounding are burning and if they have a tree
* 2 10% Chance of a tree appearing on a ground cell, if it happens change it
* 3 Change the burning cells to ground since they stop burning when finishing the step
* 4 The cells witch have a tree and burning surrinding cells have a probability to get burn
*/
void CellsList::changestate() {
	
		int i = 1;
		int j = 1; //Cell position

		while (i <= 19) { // this code doesn't check the boundary cells since they can't burn

			if (((List[i+1][j]->getState()=='F') || (List[i - 1][j]->getState() == 'F') || (List[i][j+1]->getState() == 'F') || (List[i][j-1]->getState() == 'F'))&&(List[i][j]->getState() == '*')) { //check if the surronding cells are burining
				List[i][j]->setStateBool(1);// that cells has to be changed later
				j++;
			}
			else {
				j++;
			}

			if (j == 20) { //check the next line of cells 
				i++;
				j = 0;
			}


		}

		int p = 1;
		int o = 1;
		
		while (p <= 19) { // this code doesn't check the boundary cells since they can't burn

			if ((List[p][o]->getState() == 'G') && (getRandomNumber(100,1)<=10)) {// if there is ground on each step there is a 10% chance of growing a tree

				List[p][o]->setState('*');

				o++;



			}
			else {
				o++;
			}
			if (o == 20) {
				p++;
				o = 1;
			}


		}


		int a = 1;
		int b = 1;
		while (a <= 19) { // this code doesn't check the boundary cells since they can't burn

			if ((List[a][b]->getState() == 'F')) {

				List[a][b]->setState('G');

				b++;



			}
			else {
				b++;
			}
			if (b == 20) {
				a++;
				b = 0;
			}


		}


		


		int x = 1;
		int y = 1;

		while (x <= 19) { // this code doesn't check the boundary cells since they can't burn
			
			if ((List[x][y]->getStateBool() == 1)&&(getRandomNumber(100,1) <= 50)) {
				

				
					List[x][y]->setState('F');
					List[x][y]->setStateBool(0);// The cell no longer has to be changed
					y++;
					
					


			}
			else {
				List[x][y]->setStateBool(0);// The cell no longer has to be changed
				y++;
				
				


			}
			if (y == 20) {
				x++;
				y = 0;
			}


		}
}