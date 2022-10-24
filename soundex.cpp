/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "testing/SimpleTest.h"
#include "strlib.h"
#include "filelib.h"
#include "simpio.h"
#include <fstream>
#include <cctype>
#include <string>
#include "vector.h"
using namespace std;

/* This function is intended to return a string which
 * contains only the letter characters from the original
 * (all non-letter characters are removed)
 * define a new string 'firstCh'="A", then add the string 's'
 * to string 'firstCh',then assign the string 'firstCh' to string 's'.
 * string 's' will become in the form of 'A*****'.
 * By using the code provided and return result.substr(1),
 * we could remove all non-letter characters.
 */
string removeNonLetters(string s) {
    string firstCh = "A";        //define a new string 'firstCh' = "A";
    firstCh += s;                //add the string 's' to string 'firstCh';
    s = firstCh;                 //assign the string 'firstCh' to string 's'.

    string result = charToString(s[0]);
    for (int i = 1; i < s.length(); i++) {
        if (isalpha(s[i])) {
            result += s[i];
        }
    }
    return result.substr(1);     //return the result from the second character
}

/* This function is intended to return a string which
 * transfor all the letters in the string to UpperCharacters.
 */
string ChaToUpper(string s){
    s = removeNonLetters(s);                       //get string 's' that all non-letter characters are removed
                                                   // transfor all the letters to UpperCharacters;
    string sUpper = charToString(s[0]);
       for (int i = 0; i < s.length(); i++) {
           sUpper += toupper(s[i]);                //converts character s[i] to uppercase
       }
       s = sUpper.substr(1);
       return s;
}


/* This function is intended to return a string which
 * transfor all the letters in the string into digits
 * follows the rule as: 0(A E I O U H W Y); 1(B F P V);
 * 2(C G J K Q S X Z);3(D T);4(L);5(M N);6(R).
 */
string LetterToDigit(string s){
    s = ChaToUpper(s);
    //transfor all the Upperletters into digits
       for (int i = 0; i < s.length(); i++) {
           if (s[i]=='A'||s[i]=='E'||s[i]=='I'||s[i]=='O'||s[i]=='U'||s[i]=='H'||s[i]=='W'||s[i]=='Y') {
               s[i] = '0';}
           if(s[i]=='B'||s[i]=='F'||s[i]=='P'||s[i]=='V'){
                   s[i] = '1';}
           if (s[i]=='C'||s[i]=='G'||s[i]=='J'||s[i]=='K'||s[i]=='Q'||s[i]=='S'||s[i]=='X'||s[i]=='Z') {
               s[i] = '2';}
           if (s[i]=='D'||s[i]=='T') {
               s[i] = '3';}
           if (s[i] == 'L') {
               s[i] = '4';}
           if (s[i] == 'M'||s[i]=='N') {
               s[i] = '5';}
           if(s[i] == 'R') {
               s[i] = '6';}
           }
       return s;
}

 /* This function is intended to achieve the Soundex algorithm.
 * The Soundex algorithm processes the input name and converts it to Soundex encoding.
 * A Soundex code is a string of 4 characters, starting with a letter, followed by 3 numbers.
 */
string soundex(string s) {
    /* TODO: Fill in this function. */
    string sfirst = ChaToUpper(s);   //get string 's' of Upper charaters
    s = LetterToDigit(s);            //get string 's' that all characters are transfored to Digits
    /* Merge adjacent repeating numbers */
    if (s.length() > 1){
        for (int i = 1; i <= s.length(); i++){
             if (s[i]==s[i-1]){
                 s.erase(i,1);
                 i=i-1;
             }
        }
    }
    /*Replace the first digit with the first letter
     *  of the name and convert to uppercase.     */
        s[0] = sfirst[0];
    /* Remove all '0' from the string. */
        if (s.length() > 1){
            for (int i = 1; i <= s.length(); i++){
                 if (s[i] == '0'){
                     s.erase(i,1);
                 }
            }
        }
    /* Make the encoded length exactly 4 by
     * padding with 0 or truncating the excess. */
        if(s.length() == 1){
            s.append("000");
        }
        if(s.length() == 2){
            s.append("00");
        }
        if(s.length() == 3){
            s.append("0");
        }
        if(s.length() > 4){
            s = s.substr(0,4);
        }
        return s;
}


/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
void soundexSearch(string filepath) {
    // The proivded code opens the file with the given name
    // and then reads the lines of that file into a vector.
    ifstream in;
    Vector<string> databaseNames;
    Vector<string> NameMatches;

    if (openFile(in, filepath)) {
        readEntireFile(in, databaseNames);
    }
    cout << "Read file " << filepath << ", "
         << databaseNames.size() << " names found." << endl;
    cout << endl;

    // The names in the database are now stored in the provided
    // vector named databaseNames

    /* The program repeatedly asks the user to enter a surname
     * and searches the database. For each input, the program
     * calculates the Soundex code for that input, and then
     * finds all surnames in the database that have the same code. */

    while (true){
           string surname = getLine("Enter a surname (RETURN to quit):");

        if (removeNonLetters(surname) != ""){
            string NumOfSurname = soundex(surname);
            cout << "Soundex code is " << NumOfSurname << endl;

    //A loop that searches the code of the surname from the database
    // and store the matched surnames into the vector "NameMatches"
            for (int i = 0; i<databaseNames.size(); i++){
                string NumOfDatabase = soundex(databaseNames[i]);
                if (NumOfDatabase == NumOfSurname){
                    NameMatches += databaseNames[i];
                }
            }

            NameMatches.sort();           //Sort the matched surnames

    //output the matched surnames in a ordered form
            cout << "Matches from database:{";
            for (int n = 0; n < NameMatches.size(); n++){
                 cout<< "\"" <<NameMatches[n] << "\"";
                 if (n < NameMatches.size()-1){
                     cout<< ", ";
                 }
            }
            cout<<"}" <<endl;
            cout << endl;
            NameMatches.clear();
        }
        else{
            break;
        }
    }
        cout << "All done!" <<endl;

}


/* * * * * * Test Cases * * * * * */


PROVIDED_TEST("Test removing puntuation, digits, and spaces") {
    string s = "O'Hara";
    string result = removeNonLetters(s);
    EXPECT_EQUAL(result, "OHara");
    s = "Planet9";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "Planet");
    s = "tl dr";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "tldr");
}


PROVIDED_TEST("Sample inputs from handout") {
    EXPECT_EQUAL(soundex("Curie"), "C600");
    EXPECT_EQUAL(soundex("O'Conner"), "O256");
}

PROVIDED_TEST("hanrahan is in lowercase") {
    EXPECT_EQUAL(soundex("hanrahan"), "H565");
}

PROVIDED_TEST("DRELL is in uppercase") {
    EXPECT_EQUAL(soundex("DRELL"), "D640");
}

PROVIDED_TEST("Liu has to be padded with zeros") {
    EXPECT_EQUAL(soundex("Liu"), "L000");
}

PROVIDED_TEST("Tessier-Lavigne has a hyphen") {
    EXPECT_EQUAL(soundex("Tessier-Lavigne"), "T264");
}

PROVIDED_TEST("Au consists of only vowels") {
    EXPECT_EQUAL(soundex("Au"), "A000");
}

PROVIDED_TEST("Egilsdottir is long and starts with a vowel") {
    EXPECT_EQUAL(soundex("Egilsdottir"), "E242");
}

PROVIDED_TEST("Jackson has three adjcaent duplicate codes") {
    EXPECT_EQUAL(soundex("Jackson"), "J250");
}

PROVIDED_TEST("Schwarz begins with a pair of duplicate codes") {
    EXPECT_EQUAL(soundex("Schwarz"), "S620");
}

PROVIDED_TEST("Van Niekerk has a space between repeated n's") {
    EXPECT_EQUAL(soundex("Van Niekerk"), "V526");
}

PROVIDED_TEST("Wharton begins with Wh") {
    EXPECT_EQUAL(soundex("Wharton"), "W635");
}

PROVIDED_TEST("Ashcraft is not a special case") {
    // Some versions of Soundex make special case for consecutive codes split by hw
    // We do not make this special case, just treat same as codes split by vowel
    EXPECT_EQUAL(soundex("Ashcraft"), "A226");
}

//// TODO: add your test cases here
STUDENT_TEST("Test removing puntuation, digits, and spaces") {
    string s = "   A0b1";
    string result = removeNonLetters(s);
    EXPECT_EQUAL(result, "Ab");
    s = "123Ab";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "Ab");
    s = "   Ab123";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "Ab");
    s = "   ";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "");
    s = "';'Ab";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "Ab");
}

STUDENT_TEST("Test convertting all characters in string s to digits") {
    string s = "curie";
    string result = LetterToDigit(s);
    EXPECT_EQUAL(result, "20600");
    s = "O'Conner";
    result = LetterToDigit(s);
    EXPECT_EQUAL(result, "0205506");
    s = "Angelou";
    result = LetterToDigit(s);
    EXPECT_EQUAL(result, "0520400");
    s = " '1curie";
    result = LetterToDigit(s);
    EXPECT_EQUAL(result, "20600");
    s = "";
    result = LetterToDigit(s);
    EXPECT_EQUAL(result, "");
}

STUDENT_TEST("Test sondex") {
    string s = "curie";
    string result = soundex(s);
    EXPECT_EQUAL(result, "C600");
    s = "O'Conner";
    result = soundex(s);
    EXPECT_EQUAL(result, "O256");
    s = "Angelou";
    result = soundex(s);
    EXPECT_EQUAL(result, "A524");
    s = " '2curie";
    result = soundex(s);
    EXPECT_EQUAL(result, "C600");
    s = " ";
    result = soundex(s);
    EXPECT_EQUAL(result, "");
    s = " ,.123";
    result = soundex(s);
    EXPECT_EQUAL(result, "");
}
