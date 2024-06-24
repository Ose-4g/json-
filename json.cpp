#include "json.h"

JSONNode parseObject(const std::string &s, int start, int end, std::unordered_map<int,int> &bracePair);
JSONNode parseArray(const std::string &s, int start, int end, std::unordered_map<int,int> &bracePair);

void findBracePairs(const std::string &s, std::unordered_map<int,int> &bracePairs)
{
    // assuming no occurence of [ ] or { } in keys or values. 
    //also assuming valid json
    std::vector<int> stack;

    int n = s.length();

    for(int i = 0; i < n; i++)
    {
        if(s[i]=='[' || s[i] == '{')
        {
            stack.push_back(i);
        }
        else if(s[i] == ']' || s[i] == '}')
        {
            bracePairs[stack.back()] = i;
            stack.pop_back();
        }
    }

}


bool isDouble(const std::string &s)
{
    int i = 0;
    if(s[0]=='+' || s[0]=='-')
    {
        i++;
    }

    bool dotSeen = 0;

    while(i < s.length())
    {
        if(!std::isdigit(s[i]) && s[i]!='.')
        {
            return false;
        }

        if(s[i]=='.')
        {
            if(dotSeen)
            {
                return false;
            }
            dotSeen = true;
        }
        i++;
    }

    return true;
}

bool isInteger(const std::string &s)
{
    int i = 0;
    if(s[0]=='+' || s[0]=='-')
    {
        i++;
    }

    bool dotSeen = 0;

    while(i < s.length())
    {
        if(!std::isdigit(s[i]))
        {
            return false;
        }
        i++;
    }

    return true;
}

JSONNode getValue(const std::string &s){
    int i = 0; int j = s.length()-1;
    while(s[i]==' ')
    {
        i++;
    }

    while(s[j]==' ')
    {
        j--;
    }
    std::string temp = s.substr(i, j-i + 1);

    if(temp[0]=='"')
    {
        return JSONNode(temp.substr(1, temp.length()-2));
    }

    if(temp == "true" || temp == "false")
    {
        return JSONNode(s=="true");
    }

    if(temp == "null")
    {
        return JSONNode();
    }

    if(isDouble(temp)){
        return JSONNode(std::stod(temp));
    }

    if(isInteger(temp))
    {
        return JSONNode(std::stoi(temp));
    }

    return JSONNode(temp);
}

JSONNode parseObject(const std::string &s, int start, int end, std::unordered_map<int,int> &bracePair){
    int i = start;
    JSONNode ans(JSONType::OBJECT);

    while(i < end)
    {
        while(s[i] != '"')
        {
            i++;
        }
        i++;
        std::string key = "";

        while(s[i]!='"')
        {
            key+=s[i];
            i++;
        }

        while(s[i]!=':')
        {
            i++;
        }
        i++;

        while(s[i]==' ')
        {
            i++;
        }
        std::string value = "";
        
        if(s[i]=='{')
        {
            ans[key] = parseObject(s, i, bracePair[i], bracePair);
            i = bracePair[i]+1;
            continue;
        }
        else if(s[i]=='[')
        {
             ans[key] = parseArray(s, i, bracePair[i], bracePair);
            i = bracePair[i]+1;
            continue;
        }
        while(i < end && s[i] !=',')
        {
            value += s[i];
            i++;
        }

        if(value[0]=='"')
        {
            value = value.substr(1,value.length()-2);
        }

        std::cout<<key<<" : "<<value<<std::endl;
        ans[key] = getValue(value);
    }

    return ans;
}

JSONNode parseArray(const std::string &s, int start, int end, std::unordered_map<int,int> &bracePair){
    int i = start;
    JSONNode ans(JSONType::ARRAY);
    i++;
    while(i < end)
    {
        while(s[i]==' ')
        {
            i++;
        }

        std::string value = "";

        while(i < end && s[i]!=',')
        {
            value += s[i];
            i++;
        }
        i++;
        std::cout<<"from array "<<value<<std::endl;
        ans.appendArray(getValue(value));

    }
    return ans;
}

JSONNode JSONNode::parse(const std::string &s)
{
    std::unordered_map<int,int> bracePairs;
    findBracePairs(s, bracePairs);

    int i = 0;

    while(s[i] == ' ')
    {
        i++;
    }

    if(s[i]=='[')
    {
        return parseArray(s, i, bracePairs[i], bracePairs);
    }

    return parseObject(s, i, bracePairs[i], bracePairs);

}