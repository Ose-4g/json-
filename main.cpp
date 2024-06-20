#include <iostream>
#include "json.h"

int main(){
   ose4g::jsonpp::JSONNode json = ose4g::jsonpp::JSONObjectNode();
   json["name"] = ose4g::jsonpp::JSONStringValue("name");
}