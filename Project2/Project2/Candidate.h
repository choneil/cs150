class Candidate {
public:
	int id;
	int votes=0;
	bool isOut=0;

	Candidate() {
		this->id = 0;
		this->votes = 0;
		this->isOut = 0;
	}

	void setStatus(bool status) {
		this->isOut = status;
	}

	void setVotes(int votesReceived) {
		this->votes = votesReceived;
	}

	int getVotes() {
		return this->votes;
	}

};