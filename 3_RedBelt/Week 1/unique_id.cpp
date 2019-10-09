#include <string>
#include <vector>
using namespace std;


#define CONCAT_ID_N_NUM(lineNum) uniqueId_ ## lineNum
#define EXPAND_N_FWD(arg) CONCAT_ID_N_NUM(arg)
#define UNIQ_ID EXPAND_N_FWD(__LINE__)


int main() {
    int UNIQ_ID = 0;
    string UNIQ_ID = "hello";
    vector<string> UNIQ_ID = {"hello", "world"};
    vector<int> UNIQ_ID = {1, 2, 3, 4};
}
