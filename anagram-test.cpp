#define CATCH_CONFIG_MAIN

#include<bits/stdc++.h>
#include "catch.hpp"
#include "receiver.h"
using namespace std;

CheckValues check;
string tempreature="tempreature",humidity=humidity;
TEST_CASE("raise error and warning when tempreature is greater than alert level")
{   
    REQUIRE(check.checkforhighvalues(42,tempreature,40,37)=("ALERT!! tempreature is very high"));
    REQUIRE(check.checkforhighvalues(42,tempreature,40,37)=("ALERT!! tempreature is high"));
    
}
TEST_CASE("raise error and warning when tempreature is lower than alert level")
{
     REQUIRE(check.checkforlowvalues(-0.92,tempreature,0,4)=("ALERT!! tempreature is very low"));
     REQUIRE(check.checkforlowvalues(2,tempreature,0,4)=("WARNING!! tempreature is low"));
}
TEST_CASE("raise error and warning when humidity is greater than alert level")
{
    REQUIRE(check.checkforhighvalues(93,humidity,90,70)=("ALERT!! humidity is very high"));
    REQUIRE(check.checkforhighvalues(73,humidity,90,70)=("ALERT!! humidity is high"));
}
TEST_CASE("Do nothing when tempreature is in normal conditions")
{      
    REQUIRE(check.CheckValuesForAlert(5,tempreature,40,37,0,4)=="");
    REQUIRE(check.CheckValuesForAlert(34,tempreature,40,37,0,4)=="");
}
TEST_CASE("Do nothing when humidity is in normal conditions")
{
    REQUIRE(check.CheckValuesForAlert(7,humidity,90,70,0,0)="");
    REQUIRE(check.CheckValuesForAlert(34,humidity,90,70,0,0)="");
}
