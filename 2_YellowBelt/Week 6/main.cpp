#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"
//#include "MyTimer.h"
#include <cctype>

#include <iostream>
#include <stdexcept>

using namespace std;

string ParseEvent(istream& is) { 
	while (std::isspace(is.peek())) {
		is.ignore(1);
	}
	std::string sEvent;
	std::getline(is, sEvent);
	return sEvent;
}

void TestAll();

int main() {
  TestAll();

  Database db;

  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
	{
	//	MyTimer mt;
		if (command == "Add") {
			const auto date = ParseDate(is);
			const auto event = ParseEvent(is);
			db.Add(date, event);
		}
		else if (command == "Print") {
			db.Print(std::cout);
		}
		else if (command == "Del") {
			//DateComparisonNode(Data date, LogicalOp cmp)  || EventComparisonNode
			auto condition = ParseCondition(is);
			auto predicate = [condition](const Date& date, const string& event) {
				return condition->Evaluate(date, event); // bool 
			};
			int count = db.RemoveIf(predicate);
			cout << "Removed " << count << " entries" << endl;
		}
		else if (command == "Find") {
			auto condition = ParseCondition(is);
			auto predicate = [condition](const Date& date, const string& event) {
				return condition->Evaluate(date, event);
			};

			const auto entries = db.FindIf(predicate);
			for (const auto& entry : entries) {
				cout << entry << endl;
			}
			cout << "Found " << entries.size() << " entries" << endl;
		}
		else if (command == "Last") {
			try {
				cout << db.Last(ParseDate(is)) << endl;
			}
			catch (invalid_argument&) {
				cout << "No entries" << endl;
			}
		}
		else if (command.empty()) {
			continue;
		}
		else {
			throw logic_error("Unknown command: " + command);
		}
	}

  }

  return 0;
}


void TestDateComparison() {
	{
		Assert(Date{ 2017, 11, 18 } == Date{ 2017, 11, 18 }, "Compare date 1");
		Assert(Date{ 2017, 11, 18 } != Date{ 2017, 11, 19 }, "Compare date 2");

		Assert(Date{ 2017, 11, 18 } < Date{ 2017, 11, 19 }, "Compare date 3");
		Assert(Date{ 2017, 10, 18 } < Date{ 2017, 11, 19 }, "Compare date 4");
		Assert(Date{ 2016, 11, 18 } < Date{ 2017, 11, 19 }, "Compare date 5");
		Assert(Date{ 2017, 11, 20 } > Date{ 2017, 11, 19 }, "Compare date 6");
		Assert(Date{ 2017, 12, 18 } > Date{ 2017, 11, 19 }, "Compare date 7");
		Assert(Date{ 2018, 11, 18 } > Date{ 2017, 11, 19 }, "Compare date 8");

		Assert(Date{ 2017, 11, 18 } >= Date{ 2017, 11, 18 }, "Compare date 9");
		Assert(Date{ 2017, 11, 18 } <= Date{ 2017, 11, 18 }, "Compare date 10");

		Assert(Date{ 2017, 11, 18 } <= Date{ 2017, 11, 19 }, "Compare date 11");
		Assert(Date{ 2017, 10, 18 } <= Date{ 2017, 11, 19 }, "Compare date 12");
		Assert(Date{ 2016, 11, 18 } <= Date{ 2017, 11, 19 }, "Compare date 13");
		Assert(Date{ 2017, 11, 20 } >= Date{ 2017, 11, 19 }, "Compare date 14");
		Assert(Date{ 2017, 12, 18 } >= Date{ 2017, 11, 19 }, "Compare date 15");
		Assert(Date{ 2018, 11, 18 } >= Date{ 2017, 11, 19 }, "Compare date 16");
	}
}



void TestParseEvent() {
  {
    istringstream is("event");
    AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
  }
  {
    istringstream is("   sport event ");
    AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
  }
  {
    istringstream is("  first event  \n  second event");
    vector<string> events;
    events.push_back(ParseEvent(is));
    events.push_back(ParseEvent(is));
    AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
  }
}

void TestAll() {
  TestRunner tr;  
  tr.RunTest(TestDateComparison, "TestDateComparison");
  tr.RunTest(TestParseEvent, "TestParseEvent");
  tr.RunTest(TestParseCondition, "TestParseCondition");
}
