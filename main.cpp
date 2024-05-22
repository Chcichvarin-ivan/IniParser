/*
 * @Author: Ivan Chichvarin ichichvarin@humanplus.ru
 * @Date: 2024-05-22 23:43:06
 * @LastEditors: Ivan Chichvarin ichichvarin@humanplus.ru
 * @LastEditTime: 2024-05-23 00:05:00
 * @FilePath: /IniParser/main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <cassert>
#include <sstream>
#include "ini.h"

using namespace std;

int main() {
    std::istringstream input{
        "[vegetables]\n"
        "potatoes=10\n"
        "onions=1 \n"
        "\n"
        "cucumbers=12\n"
        "\n"
        "[guests] \n"
        "guest1_name = Ivan Durak\n"
        "guest2_name =  Vasilisa Premudraya\n"
        "[guest black list]"};
    ini::Document doc = ini::Load(input);

    assert(doc.GetSectionCount() == 3);
    assert((doc.GetSection("vegetables"s)
            == ini::Section{
                {"potatoes"s, "10"s},
                {"onions"s, "1"s},
                {"cucumbers"s, "12"s},
            }));
    assert((doc.GetSection("guests"s)
            == ini::Section{{"guest1_name"s, "Ivan Durak"s}, {"guest2_name"s, "Vasilisa Premudraya"s}}));
    assert((doc.GetSection("dragons"s) == ini::Section{}));
    assert((doc.GetSection("guest black list"s) == ini::Section{}));

    doc.AddSection("pets"s) = ini::Section{{"nasty"s, "rat"s}};
    assert(doc.GetSectionCount() == 4);
}