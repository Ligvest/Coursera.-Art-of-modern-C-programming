#pragma once

#include "http_request.h"

#include <map>
#include <string_view>
using namespace std;

class Stats {
    template <typename enumItem>
    int enumToInt(enumItem item) {
        return static_cast<int>(item);
    }
    enum class Method { GET, POST, PUT, DELETE, UNKNOWN, Last_ };
    enum class Uri {
        MAIN = static_cast<int>(Method::Last_),
        ORDER,
        PRODUCT,
        BASKET,
        HELP,
        UNKNOWN,
        Last_
    };

    void fillDataBase() {
        {  // Methods
            dataBase_[enumToInt(Method::GET)] = "GET";
            dataBase_[enumToInt(Method::POST)] = "POST";
            dataBase_[enumToInt(Method::PUT)] = "PUT";
            dataBase_[enumToInt(Method::DELETE)] = "DELETE";
            dataBase_[enumToInt(Method::UNKNOWN)] = "UNKNOWN";
        }
        {  // URIs
            dataBase_[enumToInt(Uri::MAIN)] = "/";
            dataBase_[enumToInt(Uri::ORDER)] = "/order";
            dataBase_[enumToInt(Uri::PRODUCT)] = "/product";
            dataBase_[enumToInt(Uri::BASKET)] = "/basket";
            dataBase_[enumToInt(Uri::HELP)] = "/help";
            dataBase_[enumToInt(Uri::UNKNOWN)] = "unknown";
        }
    }

    void initAmounts() {
        int methodEnd = enumToInt(Method::Last_);
        int uriEnd = enumToInt(Uri::Last_);

        for (int i = 0; i < methodEnd; ++i) {
            methodAmounts_[dataBase_[i]] = 0;
        }

        for (int i = methodEnd; i < uriEnd; ++i) {
            uriAmounts_[dataBase_[i]] = 0;
        }
    }

   public:
    Stats() {
        fillDataBase();
        initAmounts();
    }
    void AddMethod(string_view method) {
        auto pos = methodAmounts_.find(method);
        if (pos != methodAmounts_.end()) {
            ++pos->second;
        } else {
            ++methodAmounts_["UNKNOWN"];
        }
    }
    void AddUri(string_view uri) {
        auto pos = uriAmounts_.find(uri);
        if (pos != uriAmounts_.end()) {
            ++pos->second;
        } else {
            ++uriAmounts_["unknown"];
        }
    }

    const map<string_view, int>& GetMethodStats() const { return methodAmounts_; }
    const map<string_view, int>& GetUriStats() const { return uriAmounts_; }

   private:
    std::array<std::string, static_cast<int>(Uri::Last_)> dataBase_;
    std::map<std::string_view, int> methodAmounts_;
    std::map<std::string_view, int> uriAmounts_;
};

HttpRequest ParseRequest(string_view line) {
    HttpRequest request;

    // remove spaces before
    line.remove_prefix(line.find_first_not_of(' '));

    size_t pos = line.find(' ');
    request.method = std::string_view(line.data(), pos);

    line.remove_prefix(++pos);
    pos = line.find(' ');
    request.uri = std::string_view(line.data(), pos);

    line.remove_prefix(++pos);
    request.protocol = line;

    return request;
}
