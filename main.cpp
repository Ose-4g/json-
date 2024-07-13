#include <iostream>
#include "json.h"

int main()
{
    JSON json = JSON(JSONType::OBJECT);
    json["name"] = "ose4g";
    json["age"] = 24;
    json["height"] = 5.11;
    json["hobbies"] = std::vector<JSON>{"Gym", "Anime"};
    json["enemies"] = nullptr;
    json["valid"] = true;
    json["school"] = JSON(JSONType::OBJECT);
    json["school"]["name"] = "UNILAG";

    std::string s = "{  \n\"name\":\"ose\n4g\",\"age\":24,\"height\":5.11,\"school\":{\"name\":\"uni\"},\"hobbies\":[\"gym\",1,  1.5,  \nfalse]}";
    auto ans  = JSON::parse(s);

    std::cout<<(bool(ans["hobbies"][3]) == true ? "true" : "false")<<std::endl;
}