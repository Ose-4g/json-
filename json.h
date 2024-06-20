#include <iostream>
#include <string>
#include <type_traits>
#include <concepts>

namespace ose4g::jsonpp {
    enum class JSONType: short{
        NUMBER,
        STRING,
        NULLT,
        OBJECT,
        ARRAY,
        BOOL,
        DEFAULT
    };

    template<typename Derived, JSONType TYPE=JSONType::DEFAULT>
    class JSONNode{
        public:
            Derived& getDerived()
            {
                return static_cast<Derived&>(*this);
            }
            JSONType getType(){
                return TYPE;
            }

            constexpr auto& value(){
                static_assert(TYPE==JSONType::NUMBER || TYPE==JSONType::STRING || TYPE==JSONType::NULLT || TYPE==JSONType::BOOL);
                return getDerived().value();
            }
            
            constexpr auto& operator[](int index){
                static_assert(TYPE == JSONType::ARRAY);
                return getDerived().operator[](index);
            }

            constexpr auto& operator[](std::string key){
                static_assert(TYPE == JSONType::OBJECT);
                return getDerived().operator[](key);
            }

    };

    auto parse(const std::string& s);

    
    class JSONStringValue: public JSONNode<JSONStringValue ,JSONType::STRING>{
        private: 
            std::string d_value;
        public:
            JSONStringValue()=default;
            JSONStringValue(const std::string& value):d_value(value){}
            
            std::string& value(){
                return d_value;
            }
    };

    class JSONNullValue: public JSONNode<JSONNullValue ,JSONType::NULLT>{
        nullptr_t d_value;
        public: 
            nullptr_t& value(){
                return d_value;
            };
            int k;
    };

    class JSONIntValue: public JSONNode<JSONIntValue ,JSONType::NUMBER>{
        int64_t d_value;
        public: 
            JSONIntValue()=default;
            JSONIntValue(int64_t value):d_value(value){}
            int64_t& value(){
                return d_value;
            };
    };

    class JSONFloatValue: public JSONNode<JSONFloatValue ,JSONType::NUMBER>{
        double d_value;
        public: 
            JSONFloatValue()=default;
            JSONFloatValue(double value):d_value(value){}

            double& value(){
                return d_value;
            };
    };

    class JSONBoolValue: public JSONNode<JSONBoolValue ,JSONType::BOOL>{
        bool d_value;
        public: 
            JSONBoolValue()=default;
            JSONBoolValue(bool value):d_value(value){}

            bool& value(){
                return d_value;
            };
    };
    
    class JSONArrayNode: public JSONNode<JSONArrayNode ,JSONType::ARRAY>{
        std::vector<JSONNode> d_children;
        public: 
            JSONArrayNode()=default;

            void append(const JSONNode& node)
            {
                d_children.push_back(node);
            }

            JSONNode& operator[](int index){
                return d_children[index];
            }
    }; 

    class JSONObjectNode: public JSONNode<JSONObjectNode ,JSONType::OBJECT>{
        std::unordered_map<std::string ,JSONNode> d_children;
        public: 
            JSONObjectNode()=default;

            void add(std::string key,const JSONNode& node)
            {
                d_children[key]=node;
            }

            JSONNode& operator[](std::string key){
                return d_children[key];
            }
    };

namespace
{
    JSONArrayNode parseArray(const std::string& s);

    int getEndBrace(const std::string& s, int start)
    {
        char c = s[start];
        char conj = c == '[' ? ']' : '}';

        int bal = 1;
        start++;
        while(bal !=0 && start < s.length() )
        {
            if(s[start]==c)
            {
                bal++;
            }
            else if(s[start]==conj)
            {
                bal--;
            }
            start++;
        }

        return start;
    }
    JSONObjectNode parseObject(const std::string& s, int start, int end){
        int i = start+1;
        JSONObjectNode node;

        while(i < end)
        {
            std::string key = "";
            std::string value = "";
            // for each statement

            //find the start of the key
            while(i < end && s[i] != '"')
            {
                i++;
            }
            i++;

            // parse the key
            while(i < end && s[i]!= '"')
            {
                key += s[i];
                i++;
            }

            
            // find the semi colon
            while(i < end && s[i]!=':')
            {
                i++;
            }
            i++;

            //skip white spaces
            while(i < end && s[i] == ' ')
            {
                i++;
            }
            
            //parse value
            while(i < end && s[i]!=',')
            {
                value+=s[i];
                i++;
            }

            std::cout<<key<<":"<<value<<std::endl;
            // node[key] = JSONStringValue(value);
        }

        return JSONObjectNode();
    }
}

auto parse(const std::string& s)
{
    return parseObject(s,0,s.length()-1);
}

}