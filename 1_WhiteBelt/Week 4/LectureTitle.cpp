struct Specialization {
	explicit Specialization(std::string new_value) {
		value = new_value;
	}
	std::string value;
};

struct Course {
	explicit Course(std::string new_value) {
		value = new_value;
	}
	std::string value;
};

struct Week {
	explicit Week(std::string new_value) {
		value = new_value;
	}
	std::string value;
};




struct LectureTitle {
	LectureTitle(Specialization new_spec, Course new_course, Week new_week) {
		specialization = new_spec.value;
		course = new_course.value;
		week = new_week.value;
	}

	std::string specialization;
	std::string course;
	std::string week;
};