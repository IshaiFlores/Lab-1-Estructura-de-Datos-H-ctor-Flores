#pragma once
class Score
{

	int Max;
	int Min;
	int Total;


	public:
	
		Score();

		Score(int max, int min, int total);

		int GetMin() { return Min; }

		int GetMax() { return Max; }

		int GetTotal() { return Total; }

		void SetMin(int min) { Min = min; }

		void SetMax(int max) { Max = max; }
		
		void SetTotal(int total) { Total = total; }

		

};

