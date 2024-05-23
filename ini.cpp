/*
 * @Author: Ivan Chichvarin ichichvarin@humanplus.ru
 * @Date: 2024-05-22 23:43:49
 * @LastEditors: Ivan Chichvarin ichichvarin@humanplus.ru
 * @LastEditTime: 2024-05-23 23:08:24
 * @FilePath: /IniParser/ini.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "ini.h"

using namespace std;

ini::Section& ini::Document::AddSection(std::string name){
    sections_.insert({name,Section()});
    return sections_.at(name);
}

const ini::Section& ini::Document::GetSection(const std::string& name) const{
    static Section empty_sect = Section();
    if(sections_.find(name) != sections_.end()){//threre is such section
        return sections_.at(name);
    }else{
        return empty_sect;
    }
    
}

std::size_t ini::Document::GetSectionCount() const{
    return sections_.size();
}

ini::Document ini::Load(std::istream& input){
    Document ret_doc;
    std::string line;
    Section* p_current_section = nullptr;
    while(getline(input, line)){
        size_t iterator = line.find_first_not_of(" ");
        if(iterator == std::string::npos){//empty line
            continue;
        }

        if(line[iterator] == '['){//new section
            p_current_section = &ret_doc.AddSection(line.substr(iterator + 1,line.find("]") - iterator - 1));
        }else{//same section
            string name_;
            string value_;
            size_t subst_end = iterator;
            for(int it = iterator; it < line.size();it++){
                if((line[it] == ' ') || (line[it] == '=')){
                    subst_end = it;
                    break;
                }
            }
            name_ = line.substr(iterator, subst_end - iterator);
            iterator = line.find("=") + 1;

            while(line[iterator]==' '){
                ++iterator;
            }
            
            subst_end = line.find_last_not_of(" ");
            value_ = line.substr(iterator, subst_end-iterator + 1);
            p_current_section->insert({name_,value_});
        }

    }
    return ret_doc;
}