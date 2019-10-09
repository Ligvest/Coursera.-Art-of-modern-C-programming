#include <deque>
#include <map>
#include <string>
#include <string_view>
#include "test_runner.h"

using namespace std;

class Translator {
   public:
    void Add(string_view source, string_view target) {
        int& srcId = trgtToSrcId_[target];
        int& trgtId = srcToTrgtId_[source];
        if (trgtId > 0) {
            dataBase_[srcId] = source;
            dataBase_[trgtId] = target;
        } else {
            dataBase_.emplace_back(source);
            srcId = dataBase_.size() - 1;
            dataBase_.emplace_back(target);
            trgtId = dataBase_.size() - 1;
        }
    }

    string_view TranslateForward(string_view source) const {
        std::string_view sv("");
        if (srcToTrgtId_.count(source) > 0) {
            int trgtId = srcToTrgtId_.at(source);
            sv = dataBase_.at(trgtId);
        }
        return sv;
    }
    string_view TranslateBackward(string_view target) const {
        std::string_view sv("");
        if (trgtToSrcId_.count(target) > 0) {
            int srcId = trgtToSrcId_.at(target);
            sv = dataBase_.at(srcId);
        }
        return sv;
    }

   private:
    std::map<std::string_view, int> srcToTrgtId_;
    std::map<std::string_view, int> trgtToSrcId_;
    std::deque<std::string> dataBase_{2, ""};
};

void TestSimple() {
    Translator translator;
    translator.Add(string("okno"), string("window"));
    translator.Add(string("stol"), string("table"));

    ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
    ASSERT_EQUAL(translator.TranslateBackward("stol"), "");

    ASSERT_EQUAL(translator.TranslateForward("stol"), "table");
    translator.Add(string("stol"), string("aatable"));
    ASSERT_EQUAL(translator.TranslateForward("stol"), "aatable");
    ASSERT_EQUAL(translator.TranslateBackward("aatable"), "stol");
    translator.Add(string("stolasd"), string("22222aatable"));
    ASSERT_EQUAL(translator.TranslateBackward("22222aatable"), "stolasd");
    ASSERT_EQUAL(translator.TranslateForward("stolasd"), "22222aatable");
    translator.Add(string("stolasd"), string("e"));
    ASSERT_EQUAL(translator.TranslateBackward("e"), "stolasd");
    ASSERT_EQUAL(translator.TranslateForward("stolasd"), "e");
    translator.Add(string("e"), string("e"));
    ASSERT_EQUAL(translator.TranslateBackward("e"), "e");
    ASSERT_EQUAL(translator.TranslateForward("e"), "e");
    translator.Add(string("e"), string("stolasd"));
    ASSERT_EQUAL(translator.TranslateBackward("stolasd"), "e");
    ASSERT_EQUAL(translator.TranslateForward("e"), "stolasd");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSimple);
    return 0;
}
