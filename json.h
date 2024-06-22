#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

enum class JSONType : short
{
    NUMBER,
    STRING,
    NULLT,
    OBJECT,
    ARRAY,
    BOOL
};

class JSONNode
{
    // member variables
    JSONType d_type;                                  // holds the type of this json object
    std::unordered_map<std::string, JSONNode> d_data; // potentially stores key value records of this json if it this an object node
    std::vector<JSONNode> d_array;                    // potentially sores a list of JSON objects if it this is an array node

    // union to hold the value if there is a value.
    union value
    {
        std::string d_string;
        double d_number;
        bool d_bool;
        value() {}
        ~value() {}

        // conversion operators for the union
        operator std::string()
        {
            return d_string;
        }

        operator double()
        {
            return d_number;
        }

        operator int()
        {
            return d_number;
        }

        operator bool()
        {
            return d_bool;
        }

    } d_value;

    void limitToArray()
    {
        if (!isArray())
        {
            throw std::runtime_error("this operation is only available to array node");
        }
    }

    void limitToObject()
    {
        if (!isObject())
        {
            throw std::runtime_error("this operation is only available to object node");
        }
    }

public:
    JSONNode(JSONType type) : d_type(type) {}

    // default constructor creates null value node
    JSONNode() : d_type(JSONType::NULLT) {}

    // constructors for implicit conversion from nullptr
    JSONNode(nullptr_t value) : JSONNode() {}

    JSONNode(double value) : d_type(JSONType::NUMBER)
    {
        d_value.d_number = value;
    }

    JSONNode(const std::vector<JSONNode> &nodes) : d_type(JSONType::ARRAY), d_array(nodes) {}

    JSONNode(int value) : d_type(JSONType::NUMBER)
    {
        d_value.d_number = value;
    }

    JSONNode(const std::string &value) : d_type(JSONType::STRING)
    {
        d_value.d_string = value;
    }

    JSONNode(const char *value) : d_type(JSONType::STRING)
    {
        d_value.d_string = value;
    }

    JSONNode(bool value) : d_type(JSONType::BOOL)
    {
        d_value.d_bool = value;
    }

    // copy constructor
    JSONNode(const JSONNode &node)
    {
        d_type = node.d_type;
        d_data = node.d_data;
        d_array = node.d_array;

        d_value.d_bool = node.d_value.d_bool;
        d_value.d_string = node.d_value.d_string;
        d_value.d_number = node.d_value.d_number;
    }

    // copy assignment operator 
    JSONNode &operator=(const JSONNode &node)
    {
        d_type = node.d_type;
        d_data = node.d_data;
        d_array = node.d_array;

        d_value.d_bool = node.d_value.d_bool;
        d_value.d_string = node.d_value.d_string;
        d_value.d_number = node.d_value.d_number;

        return *this;
    }


    bool isValue()
    {
        return d_type == JSONType::BOOL ||
               d_type == JSONType::NUMBER ||
               d_type == JSONType::STRING ||
               d_type == JSONType::NULLT;
    }

    // helper methods
    bool isObject()
    {
        return d_type == JSONType::OBJECT;
    }

    bool isArray()
    {
        return d_type == JSONType::ARRAY;
    }

    bool isNUll()
    {
        return d_type == JSONType::NULLT;
    }

    void appendArray(const JSONNode &node)
    {
        d_array.push_back(node);
    }

    template <typename T>
    T get()
    {
        if (!isValue())
        {
            throw std::runtime_error("unable to get value for this type");
        }
        return static_cast<T>(d_value);
    }


    // index operator overloads
    JSONNode &operator[](int index)
    {
        limitToArray();
        return d_array[index];
    }

    JSONNode &operator[](const std::string &key)
    {
        limitToObject();
        return d_data[key];
    }

    JSONNode &operator[](const char *key)
    {
        limitToObject();
        return d_data[key];
    }

    // conversion operator oveloads
    operator std::string()
    {
        return d_value.d_string;
    }

    operator int()
    {
        return d_value.d_number;
    }

    operator double()
    {
        return d_value.d_number;
    }

    operator bool()
    {
        return d_value.d_bool;
    }    
};

using JSON = JSONNode;
