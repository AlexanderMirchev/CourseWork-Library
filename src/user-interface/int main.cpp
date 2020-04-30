#include <iostream>
#include <optional>
#include <string>

void kur(const std::string& str) {
    std::cout << str;
}

int main() {

    // std::optional<std::string> opt;
    // std::cout << opt.value_or("kur");

    // opt = line;
    // std::cout << opt.value_or("kur");
    // std::cout << std::boolalpha << opt.has_value();
    // std::string line("kurvi");
    // std::cout << std::boolalpha << (line == "kurvi") << std::endl;
    kur("kur");
  
}