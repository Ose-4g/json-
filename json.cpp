#include "json.h"
#include "utils.h"

JSONNode parseObject(const std::string &s, int start, int end, std::unordered_map<int,int> &bracePair);
JSONNode parseArray(const std::string &s, int start, int end, std::unordered_map<int,int> &bracePair);



JSONNode parseObject(const std::string &s, int start, int end, std::unordered_map<int,int> &bracePair){
    /**
     * s: the json string
     * start: the index of the opening curly brace for this object
     * end: the index of the closing curly brace for this object
     * bracePair: an map that maps index of opening brackets to their corresponding closing brackets.
     */

    int i = start;
    JSONNode ans(JSONType::OBJECT);

    while(i < end)
    {
        // ignore all characters before the first quote for the key string
        while(s[i] != '"')
        {
            i++;
        }
        i++;

        // add all characters between the quotes to the key
        std::string key = "";

        while(s[i]!='"')
        {
            key+=s[i];
            i++;
        }

        // find the semicolon between the key and value
        while(s[i]!=':')
        {
            i++;
        }
        i++;

        // ignore all whitespaces till you get to the start of the value
        while(isWhitespace(s[i]))
        {
            i++;
        }
        std::string value = "";
        
        // if value starts with a curly brace, it means its an object. 
        // parse that object.
        if(s[i]=='{')
        {
            ans[key] = parseObject(s, i, bracePair[i], bracePair);
            i = bracePair[i]+1;
            continue;
        }
        // if value starts with a square bracket, it is an array
        // parse the array
        else if(s[i]=='[')
        {
             ans[key] = parseArray(s, i, bracePair[i], bracePair);
            i = bracePair[i]+1;
            continue;
        }
        // it is a JSON Value. Parse it and store it. 
        // stop when you get to a comma or reach end of this JSON.
        while(i < end && s[i] !=',')
        {
            value += s[i];
            i++;
        }
        

        ans[key] = getValue(value);
    }

    return ans;
}

JSONNode parseArray(const std::string &s, int start, int end, std::unordered_map<int,int> &bracePair){
    /**
     * s: the json string
     * start: the index of the opening square bracket for this object
     * end: the index of the closing square bracket for this object
     * bracePair: an map that maps index of opening brackets to their corresponding closing brackets.
     */
    int i = start;
    JSONNode ans(JSONType::ARRAY);
    i++;
    while(i < end)
    {
        //ignore all whitespace
        while(isWhitespace(s[i]))
        {
            i++;
        }
        // find a value
        std::string value = "";

        //stop when you see a comma or reach end of the array.
        while(i < end && s[i]!=',')
        {
            value += s[i];
            i++;
        }
        i++;
        ans.appendArray(getValue(value));

    }
    return ans;
}

JSONNode JSONNode::parse(const std::string &s)
{
    std::unordered_map<int,int> bracePairs;
    findBracePairs(s, bracePairs);

    int i = 0;

    while(isWhitespace(s[i]))
    {
        i++;
    }

    if(s[i]=='[')
    {
        return parseArray(s, i, bracePairs[i], bracePairs);
    }

    return parseObject(s, i, bracePairs[i], bracePairs);

}