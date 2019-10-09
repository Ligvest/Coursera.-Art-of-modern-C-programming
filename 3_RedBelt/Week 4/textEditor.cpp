#define TEST
#include <deque>
#include <string>
//#include <string_view>
#include <list>
#include "profile.h"
#include "test_runner.h"
using namespace std;

class Editor {
    static const size_t MAX_SYMBOLS = 1'000'000;

    auto getCurPosIt() { return curPosIt_; }
    auto nextPosIt(size_t offset) {
        return std::next(curPosIt_, std::min(offset, data_.size() - curPos_));
    }
    bool savePos() {
        savedPos_ = std::prev(curPosIt_);
        return curPosIt_ == data_.begin();
    }

    void loadPos(bool wasBegin) {
        if (wasBegin) {
            curPosIt_ = data_.begin();
            return;
        }

        if (savedPos_ == data_.end()) {
            curPosIt_ = savedPos_;
        } else {
            curPosIt_ = std::next(savedPos_);
        }
    }

   public:
    // Реализуйте конструктор по умолчанию и объявленные методы
    Editor() { curPosIt_ = data_.begin(); }
    void Left() {
        if (curPos_ > 0) {
            --curPosIt_;
            --curPos_;
        }
    }
    void Right() {
        if (curPos_ < data_.size()) {
            ++curPosIt_;
            ++curPos_;
        }
    }
    void Insert(char token) {
        auto temp = *curPosIt_;
        data_.insert(getCurPosIt(), token);
        ++curPos_;
        temp = *curPosIt_;
        temp = *curPosIt_;
    }
    void Cut(size_t tokens = 1) {
        if (!data_.empty()) {
            buffer_.clear();
            bool wasBegin = savePos();
            buffer_.splice(buffer_.begin(), data_, getCurPosIt(), nextPosIt(tokens));
            loadPos(wasBegin);
        }
    }
    void Copy(size_t tokens = 1) {
        if (!data_.empty()) {
            buffer_.clear();
            buffer_.assign(getCurPosIt(), nextPosIt(tokens));
        }
    }

    void Paste() {
        if (!buffer_.empty()) {
            data_.insert(getCurPosIt(), buffer_.begin(), buffer_.end());
            curPos_ += buffer_.size();
        }
    }
    string GetText() const { return {data_.begin(), data_.end()}; }

   private:
    std::list<char> data_;
    std::list<char> buffer_;
    size_t curPos_ = 0;
    std::list<char>::iterator curPosIt_;
    std::list<char>::iterator savedPos_;
};

void TypeText(Editor& editor, const string& text) {
    for (char c : text) {
        editor.Insert(c);
    }
}

void easyTest() {
    Editor editor;
    const string text = "hello, world";
    for (char c : text) {
        editor.Insert(c);
    }

    // Текущее состояние редактора: `hello, world|`
    ASSERT_EQUAL(editor.GetText(), "hello, world");
    for (size_t i = 0; i < text.size(); ++i) {
        editor.Left();
    }
    // Текущее состояние редактора: `|hello, world`
    editor.Cut(7);
    // Текущее состояние редактора: `|world`
    ASSERT_EQUAL(editor.GetText(), "world");
    // в буфере обмена находится текст `hello, `
    for (size_t i = 0; i < 5; ++i) {
        editor.Right();
    }
    // Текущее состояние редактора: `world|`
    editor.Insert(',');
    editor.Insert(' ');
    // Текущее состояние редактора: `world, |`
    ASSERT_EQUAL(editor.GetText(), "world, ");
    editor.Paste();
    // Текущее состояние редактора: `world, hello, |`
    editor.Left();
    editor.Left();
    //Текущее состояние редактора: `world, hello|, `
    editor.Cut(3);  // Будут вырезаны 2 символа
    // Текущее состояние редактора: `world, hello|`
}
#ifdef TEST
void TestEditing() {
    {
        Editor editor;

        const size_t text_len = 12;
        const size_t first_part_len = 7;
        TypeText(editor, "hello, world");
        for (size_t i = 0; i < text_len; ++i) {
            editor.Left();
        }
        editor.Cut(first_part_len);
        //        std::cout << editor.buffer_ << std::endl;
        for (size_t i = 0; i < text_len - first_part_len; ++i) {
            editor.Right();
        }

        TypeText(editor, ", ");
        editor.Paste();
        editor.Left();
        editor.Left();
        editor.Cut(3);

        ASSERT_EQUAL(editor.GetText(), "world, hello");
    }
    {
        Editor editor;

        TypeText(editor, "misprnit");
        editor.Left();
        editor.Left();
        editor.Left();
        editor.Cut(1);
        editor.Right();
        editor.Paste();

        ASSERT_EQUAL(editor.GetText(), "misprint");
    }
}

void TestReverse() {
    Editor editor;

    const string text = "esreveR";
    for (char c : text) {
        editor.Insert(c);
        editor.Left();
    }

    ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
    Editor editor;
    ASSERT_EQUAL(editor.GetText(), "");

    editor.Left();
    editor.Left();
    editor.Right();
    editor.Right();
    editor.Copy(0);
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
    Editor editor;

    editor.Paste();
    TypeText(editor, "example");
    editor.Left();
    editor.Left();
    editor.Paste();
    editor.Right();
    editor.Paste();
    editor.Copy(0);
    editor.Paste();
    editor.Left();
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "example");
}

void TestManyCopy() {
    Editor editor;

    std::string million(100000, 'c');
    TypeText(editor, million);
    //    for (int i = 0; i < 1000000; ++i) {
    //        editor.Copy(1000000);
    //        editor.Right();
    //    }
}

void TestManyCuts() {
    Editor editor;

    std::string million(1000000, 'c');
    TypeText(editor, million);
    for (int i = 0; i < 1000000; ++i) {
        editor.Cut(1);
        editor.Copy(1);
        editor.Right();
    }
}

void TestManyPaste() {
    Editor editor;

    std::string million(10000000, 'c');
    TypeText(editor, million);

    for (int i = 0; i < 1000000; ++i) {
        editor.Cut(10000000);
        editor.Right();
        editor.Paste();
    }
}

void TestManyQueries() {
    Editor editor;
    for (int i = 0; i < 1000000; ++i) {
        editor.Cut(i);
        //        editor.Left();
        //        editor.Right();
        //        editor.Copy(4);
        //        editor.Cut(4);
        //        editor.Paste();
        //        editor.Right();
        //        editor.Copy(4);
        //        editor.Cut(4);
        //        editor.Paste();
    }
}
#endif
int main() {
#ifndef TEST
    Editor editor;
    TypeText(editor, "four");
    editor.Cut(2);
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "four");
    std::cout << editor.GetText() << std::endl;
#else
    TestRunner tr;
    RUN_TEST(tr, easyTest);
    RUN_TEST(tr, TestEditing);
    RUN_TEST(tr, TestReverse);
    RUN_TEST(tr, TestNoText);
    RUN_TEST(tr, TestEmptyBuffer);
    {
        LOG_DURATION("Many copies")
        TestManyCopy();
    }
//    {
//        LOG_DURATION("Many cuts")
//        TestManyCuts();
//    }
//    {
//        LOG_DURATION("Many paste")
//        TestManyPaste();
//    }

//    {
//        LOG_DURATION("Many queries")
//        TestManyQueries();
//    }
#endif
    return 0;
}
