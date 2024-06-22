// #include <gtest/gtest.h>
// #include "json.h"

// // JSONNullValue
// TEST(JSONNullValue, getType){
//     ose4g::jsonpp::JSONNullValue json1;
//     ose4g::jsonpp::JSONNode json2 = ose4g::jsonpp::JSONNullValue();
//     EXPECT_EQ(json1.getType(), ose4g::jsonpp::JSONType::NULLT);
//     EXPECT_EQ(json2.getType(), ose4g::jsonpp::JSONType::NULLT);
// }

// TEST(JSONNullValue, value){
//     ose4g::jsonpp::JSONNullValue json1;
//     ose4g::jsonpp::JSONNode json2 = ose4g::jsonpp::JSONNullValue();
//     EXPECT_EQ(json1.value(), nullptr);
//     EXPECT_EQ(json2.value(), nullptr);
// }

// // JSONBoolValue
// TEST(JSONBoolValue, getType){
//     ose4g::jsonpp::JSONBoolValue json1(true);
//     ose4g::jsonpp::JSONNode json2 = ose4g::jsonpp::JSONBoolValue(false);
//     EXPECT_EQ(json1.getType(), ose4g::jsonpp::JSONType::BOOL);
//     EXPECT_EQ(json2.getType(), ose4g::jsonpp::JSONType::BOOL);
// }

// TEST(JSONBoolValue, value){
//     ose4g::jsonpp::JSONBoolValue json1(true);
//     ose4g::jsonpp::JSONNode json2 = ose4g::jsonpp::JSONBoolValue(false);
//     EXPECT_EQ(json1.value(), true);
//     EXPECT_EQ(json2.value(), false);
// }



