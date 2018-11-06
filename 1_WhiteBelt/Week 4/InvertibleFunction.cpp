class Function {
public:
	void AddPart(char op, double param) {
		vecOps.push_back(op);
		vecParams.push_back(param);
	}

	double Apply(double quality) const {
		double res = quality;
		for (int i = 0; i < vecOps.size(); ++i) {
			if (vecOps[i] == '-') {
				res -= vecParams[i];
			}
			else if (vecOps[i] == '+') {
				res += vecParams[i];
			}
		}
		
		return res;
	}

	void Invert() {
		for (auto& op : vecOps) {
			if (op == '-') {
				op = '+';
			}
			else if (op == '+') {
				op = '-';
			}
		}
	}

private:
	std::vector<char> vecOps;
	std::vector<double> vecParams;
};