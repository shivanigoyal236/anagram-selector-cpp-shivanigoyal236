#include "anagram.h"
#include<bits/stdc++.h>
using namespace std;
std::string removespace(const std::string& s1)
{
    std::string s;
        for(int i=0;i<s1.length();i++)
        {
            if(s1[i]!=' ')
            s+=s1[i];
        }
         transform(s.begin(),s.end(),s.begin(),::tolower);
     return s;
}

bool Anagram::WordPairIsAnagram(const std::string& word1, const std::string& word2) {
    //Fill the correct implementation here
      int l1,l2;
         std::string s1,s2;
         s1=removespace(word1);
         s2=removespace(word2);
         l1=s1.length();
      l2=s2.length();
      if(l1!=l2)
      return false;
      else
      {
        int sum=0;
        for(int i=0;i<s2.length();i++)
        {
            sum^=s1[i]^s2[i];

        }
        if(sum==0)
        return true;}
        
    return false;
}

std::vector<std::string> Anagram::SelectAnagrams(
        const std::string& word,
        const std::vector<std::string>& candidates) {
    //Fill the correct implementation here
         std::vector<std::string> candidates1;
    int l1=candidates.size();
    bool k;
    for(int i=0;i<l1;i++)
       { k=Anagram::WordPairIsAnagram(word,candidates[i]);
           if(k==true)
            candidates1.push_back(candidates[i]);
       }


    return candidates1;
}
