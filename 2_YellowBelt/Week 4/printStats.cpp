void PrintStats(vector<Person> persons) {
	std::cout << "Median age = " << ComputeMedianAge(std::begin(persons), std::end(persons)) << std::endl;
	auto it = std::partition(std::begin(persons), std::end(persons), [](const Person& obj) {return (obj.gender == Gender::FEMALE); });
	std::cout << "Median age for females = " << ComputeMedianAge(std::begin(persons), it) << std::endl;
	it = std::partition(std::begin(persons), std::end(persons), [](const Person& obj) {return (obj.gender == Gender::MALE); });
	std::cout << "Median age for males = " << ComputeMedianAge(std::begin(persons), it) << std::endl;
	it = std::partition(std::begin(persons), std::end(persons), [](const Person& obj) {return (obj.gender == Gender::FEMALE) && (obj.is_employed == true); });
	std::cout << "Median age for employed females = " << ComputeMedianAge(std::begin(persons), it) << std::endl;
	it = std::partition(std::begin(persons), std::end(persons), [](const Person& obj) {return (obj.gender == Gender::FEMALE) && (obj.is_employed == false); });
	std::cout << "Median age for unemployed females = " << ComputeMedianAge(std::begin(persons), it) << std::endl;
	it = std::partition(std::begin(persons), std::end(persons), [](const Person& obj) {return (obj.gender == Gender::MALE) && (obj.is_employed == true); });
	std::cout << "Median age for employed males = " << ComputeMedianAge(std::begin(persons), it) << std::endl;
	it = std::partition(std::begin(persons), std::end(persons), [](const Person& obj) {return (obj.gender == Gender::MALE) && (obj.is_employed == false); });
	std::cout << "Median age for unemployed males = " << ComputeMedianAge(std::begin(persons), it) << std::endl;
}