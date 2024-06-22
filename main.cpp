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

    std::string name = json["name"];
    std::cout << std::string(name) << " | " << json["hobbies"][1].get<std::string>() << " | " << std::endl;
}