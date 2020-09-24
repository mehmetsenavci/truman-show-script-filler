   #include <iostream>
   #include <fstream>
   #include <string.h>
   #include <ctime>

   using namespace std;

   int myFind(string s, char c){
       for(int i = 0; i < s.length(); i++){
           if(s[i] == c){
               return i;
           }
       }
       return -1;
   }

   int myRfind(string s, char c){
       for(int i = (int)s.length()-1; i > 0; i--){
           if(s[i] == c){
               return i;
           }
       }
       return -1;
   }

   unsigned int horsPoolMatching(string text, string pattern, int startingIndex) {
                  
       int n = 256;
       int patternLength = (int)pattern.length();
       int i = 0;
       int shiftTable[n];
       
       for (i = 0; i <= n - 1; i++){
           shiftTable[i] = patternLength;
       }
       
       int j = 0;
       
       for (j = 0; j <= patternLength - 2; j++){
           int d = (int)pattern[j];
           shiftTable[d] = patternLength - 1 - j;
       }
                  
       int textLength = (int)text.length();
       
       i = startingIndex + patternLength - 1;
       while (i < textLength){
           int k = 0;
           while (k < patternLength && pattern[patternLength - 1 - k] == text[i - k]){
               k++;
           }
           if (k == patternLength){
               return i - patternLength + 1;
           }
           else{
               i = i + shiftTable[text[i]];
           }
       }
    
       return -1;
   }

   int main() {
       long clkStart = clock();
       
       fstream statements;
       char stateChar;
       string stateWord;
       string stateStr;
       string stateLine;
       
       fstream script;
       char scriptChar;
       string scriptWord;
       string scriptStr;
       
       string beforeBlank;
       string afterBlank;
       int beforeBlankShift;
       int afterBlankShift;
       
       
       
       statements.open("statements.txt");
       script.open("the_truman_show_script.txt");
       
       if(script.fail()){
           cout << "Failed to open the_truman_show_script.txt." << endl;
       }
       else{
           while(!script.eof()){
               script.get(scriptChar);
               scriptWord += tolower(scriptChar);
               
               if(scriptChar == ' ' && scriptWord != ""){
                   scriptStr += scriptWord;
                   scriptWord = "";
               }
           }
       }
       
       if(statements.fail()){
           cout << "Failed to open statements.txt." << endl;
       }
       else{
           while (!statements.eof()) {
               statements.get(stateChar);
               stateWord += tolower(stateChar);
               
               if((stateChar == '?' || stateChar == ' ') && stateWord != "" ){
                   stateStr += stateWord;
  //                 cout << stateWord << endl;
                   stateWord = "";
               }
           }
       }
       stateStr.erase(stateStr.length()-1); // Can be removed
  //     cout << stateStr << endl;
       script.close();
       statements.close();
       
       // After from here we have the text into the string
       
       while(stateStr != ""){
           if (myRfind(stateStr,'\n') != string::npos) {
               stateLine = stateStr.substr(0, myFind(stateStr, '\n')+1);
               beforeBlank  = stateLine.substr(0, myFind(stateLine, '_')-1);
               afterBlank = stateLine.substr(myRfind(stateLine, '_')+1, stateLine.length()-myRfind(stateLine, '_')-1);
               afterBlank = afterBlank.erase(myRfind(afterBlank,'\n')-1); // when i remove -1 it doesn't work for the given statements file but it works for my example ?!?
               
               cout << stateLine;
//               cout << afterBlank;
               beforeBlankShift = horsPoolMatching(scriptStr, beforeBlank, 0);
               afterBlankShift = horsPoolMatching(scriptStr, afterBlank, beforeBlankShift);
               
               if(beforeBlankShift == -1){
                   cout << "Statement NOT found." << endl;
               }
               else{
                   if(afterBlankShift == -1){
                       cout << "Statement NOT found." << endl;
                   }
                   else{
                       string ans = scriptStr.substr(beforeBlankShift+beforeBlank.length(), afterBlankShift-beforeBlankShift-beforeBlank.length());
                       cout << beforeBlank << ans << afterBlank <<endl;                }
               }
               
               stateStr.erase(0, stateStr.find("\n")+1);
           }
           else{
               stateLine = stateStr.substr(0, stateStr.length());
               beforeBlank  = stateLine.substr(0, myFind(stateLine, '_')-1);
               afterBlank = stateLine.substr(myRfind(stateLine, '_')+1, stateLine.length()-myRfind(stateLine, '_')-1);
               
               cout << stateLine << endl;
               
               beforeBlankShift = horsPoolMatching(scriptStr, beforeBlank, 0);
               afterBlankShift = horsPoolMatching(scriptStr, afterBlank, beforeBlankShift);
                 
               
               if(beforeBlankShift == -1){
                   cout << "Statement NOT found." << endl;
               }
               else{
                   if(afterBlankShift == -1){
                       cout << "Statement NOT found." << endl;
                   }
                   else{
                       string ans = scriptStr.substr(beforeBlankShift+beforeBlank.length(), afterBlankShift-beforeBlankShift-beforeBlank.length());
                       cout << beforeBlank << ans << afterBlank <<endl;
                   }
               }
               
               stateStr.erase(0, stateStr.length());
           }
       }

       long clkEnd = clock();
       cout << "Runing time is " << (clkEnd-clkStart)/double(CLOCKS_PER_SEC) << endl;
       
       return 0;
   }
