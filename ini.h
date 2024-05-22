/*
 * @Author: Ivan Chichvarin ichichvarin@humanplus.ru
 * @Date: 2024-05-22 23:44:30
 * @LastEditors: Ivan Chichvarin ichichvarin@humanplus.ru
 * @LastEditTime: 2024-05-22 23:46:21
 * @FilePath: /IniParser/ini.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <string>
#include <unordered_map>


namespace ini{
    using Section = std::unordered_map<std::string, std::string>;

    class Document {
    public:
        Section& AddSection(std::string name);
        
        const Section& GetSection(const std::string& name) const;
        
        std::size_t GetSectionCount() const;

    private:
        std::unordered_map<std::string, Section> sections_;
    };

    Document Load(std::istream& input);
}