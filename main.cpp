#include <iostream>
#include "json.h"

int main()
{
    //test JSON parsing from string
    const std::string jsonstring = "{\"array\":[1,2,3],\"boolean\":true,\"color\":\"gold\",\"null\":null,\"number\":123,\"object\":{\"a\":\"b\",\"c\":\"d\"},\"string\":\"HelloWorld\"}";
    JSON json1(JSON::parse(jsonstring));

    std::cout<<"array third element is "<<int(json1["array"][2])<<std::endl;
    std::cout<<"value of color is "<<std::string(json1["color"])<<std::endl;
    std::cout<<"value of a in object is "<<std::string(json1["object"]["a"])<<std::endl;
    std::cout<<"value of number is "<<int(json1["number"])<<std::endl;
    std::cout<<"\n\n\n";

    // Test JSON stringify
    JSON json = JSON(JSONType::OBJECT);
    json["name"] = "ose4g";
    json["age"] = 24;
    json["height"] = 5.11;
    json["hobbies"] = std::vector<JSON>{"Gym", "Anime"};
    json["enemies"] = nullptr;
    json["valid"] = true;
    json["school"] = JSON(JSONType::OBJECT);
    json["school"]["name"] = "UNILAG";

    std::string s = JSON::stringify(json);
    std::cout<<"JSON::stringify result:\n"<<s<<"\n\n\n";
    
    //Test parsing from stringified JSON.
    auto ans  = JSON::parse(s);
    
    // parsing the strigified json.
    std::cout<<"Result of parsing the stringified json:\n"<<JSON::stringify(ans)<<"\n\n\n";

}