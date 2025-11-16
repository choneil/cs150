#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include "Candidate.h"

using namespace std;

ifstream inFile;
string lineString;
string voterID;
string votes;
string filename = "Election8.txt";
Candidate* candidates;
int numVoters;
int numCandidates;
int winner = 0;

void setVotersAndCandidates(ifstream& inputFile, int& voters, int& candidates);
void createCandidates(Candidate* candArray, int candidates);
void countVotes(ifstream& inputFile, int candidates, Candidate* candArray);
bool openFile(ifstream& inputFile, const string file);
void checkMajority(int cadndidates, Candidate* candArray);
void eliminateCandidate(Candidate* candArray, int candidates);
void printNice(char f);
void printNicer(string padding);

int main() {
	
	cout << "Reading " << filename << endl;
	printNice('*');

	// Open file
	openFile(inFile, filename);

	// Retrieve number of voters and number of candidates from file
	setVotersAndCandidates(inFile, numVoters, numCandidates);

	// Create a new array of class Candidate with the appropriate size 
	Candidate* candidateArray = new Candidate[numCandidates];
	
	// Assign IDs to candidates
	createCandidates(candidateArray, numCandidates);

	// While no candidate has majority votes
	while(winner==0){

	// Count Votes and Adjust candidates' vote value
	countVotes(inFile, numCandidates, candidateArray);

	// Eliminate the candidate with the lowest number of votes
	eliminateCandidate(candidateArray, numCandidates);

	// Check if anyone has won
	checkMajority(numCandidates, candidateArray);

	}
}

void checkMajority(int candidates, Candidate* candArray) {
	Candidate* current = candArray;
	for (int i = 0; i < candidates; i++) {
		if (current->votes > numVoters / 2) {
			cout << "Candidate " << i + 1 << " wins with " << current->votes << " votes." << endl;
			printNicer(" (^_^)/ ");
			winner = 1;
			return;
		}
		else {
			
		}
		current++;
	}
}

bool openFile(ifstream& inputFile, const string file) {
	inFile.open(file);

	if (inputFile.fail()) {
		cout << "Failed to open " << file << "." << endl;
		return 0;
	}
	else {
		return 1;
	}
}

void setVotersAndCandidates(ifstream& inputFile, int& voters, int& candidates){
	
	string rdVoters;
	string rdCandidates;
	
	getline(inputFile, rdVoters, ' ');
	voters = stoi(rdVoters);
	cout <<setw(20)<< setfill(' ') << left << "Voters: " << right << numVoters << endl;
	
	getline(inputFile, rdCandidates);
	candidates = stoi(rdCandidates);
	cout << setw(20) << left << "Candidates: " << right << numCandidates << endl;

	printNice('*');
}

void createCandidates(Candidate* candArray, int candidates) {
	Candidate* current = candArray;
	for (int i = 0; i < candidates; i++) {
		current->id = i;
		current++;
	}
}

void countVotes(ifstream& inputFile, int candidates, Candidate* candArray) {
	inputFile.clear();
	inputFile.seekg(0);
	int* votes = new int[candidates];
	for (int i = 0; i < candidates; i++) {
		votes[i] = 0;
	}
	string id;
	string top_choice;
	int voted;
	string garb;
	int line = 1;
	while (!inputFile.eof() && line != numVoters + 1) {
		
		inputFile >> ws >> id;
		
		if (size(id) < 10) {
			getline(inputFile, garb);
			inputFile >> ws >> id;
		}
		inputFile >> ws >> top_choice;
		voted = stoi(top_choice) - 1;
		while(candArray[voted].isOut) {
			
			inputFile >> ws >> top_choice;
			voted = stoi(top_choice) - 1;
		}
		getline(inputFile, garb);

		votes[voted]++;
		line++;
	}
	Candidate* current = candArray;
	for (int i = 0; i < candidates; i++) {
		current->votes = votes[i];
		float percentageVotes = static_cast<float>(current->votes) / static_cast<float>(numVoters) * 100;
		cout << "Candidate " << i + 1 << " has " << votes[i] << " votes. " << percentageVotes << "%." << endl;
		current++;
	}
}

void eliminateCandidate(Candidate* candArray, int candidates) {
	Candidate* current = candArray;
	int* voteCount = new int[candidates];
	for(int i = 0; i < candidates; i++){
		voteCount[i] = current->votes;
		current++;
	}
	int min = 0;
	int currentVotes;
	current = candArray;
	for (int i = 0; i < candidates; i++) {
		
		currentVotes = current->votes;
		if (currentVotes == 0) {
			if (min == i) {
				min++;
			}
			candArray[i].isOut = 1;
		}
		if (currentVotes < candArray[min].votes && !candArray[i].isOut) {
			min = i;
		}
		current++;
	}
	candArray[min].isOut = 1;
	
	printNice('-');
	cout << "Candidate " << min + 1 << " is eliminated." << endl;
	printNice('*');

}

void printNice(char f) {
	cout << endl;
	cout << setw(38) << setfill(f) << " " << endl;
	cout << endl;
}

void printNicer(string padding) {
	cout << endl;
	int sz = size(padding);
	for (int i = 0; i < 35 / sz; i++) {
		cout << padding;
	}
	cout << '\n';
	cout << '\n';
}