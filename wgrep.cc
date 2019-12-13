// wgrep - locate words in text files, wildcard + denotes any character
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

#define MAXLINE 9999
#define MAXWORD 999
#define SPACE 32

using namespace std;

int compareword(char tword[]);
int separatewords(char tline[], int tlowercaseflag, int wordidtoreturn=0);
// turnred text manipulator
ostream &turnred(ostream &stream)
{
   cout << "\e[10m\e[31m";
   
 return stream;
}
// turnoffred text manipulator
ostream &turnoffred(ostream &stream)
{
   cout << "\e[0m" ;
  
 return stream;
}

int lowercaseflag=1;
char word[MAXWORD];
struct Word {
char lWord[MAXWORD]; };
vector<Word> words; 

int main(int argc, char *argv[])
{
 int i, i1, lines=0;
 char tline[MAXLINE];
 ifstream infile(argv[2]);

  // see if parameters are correct
  if (argc<3 || argc>4 || !infile) {
   cout << "wgrep <word (+ for unknown letters)> <filename> [-c match case]" << endl;
  return -1; }
  // parse -c option
  if (argc==4) {
   if (!strcmp(argv[3], "-c"))
    lowercaseflag=0;
   else {
    cout << "non accepted parameter " << argv[3] << endl;
  return -1; } }
  // copy tolower requested word
  for (i=0;i<strlen(argv[1]);i++)
   word[i]=(lowercaseflag) ? tolower(argv[1][i]) : argv[1][i];
  
   // loop search in requested file
   while (infile) {
    infile.getline(tline, MAXLINE);
    ++lines;
    separatewords(tline, lowercaseflag);
    for (i=0;i<words.size();i++) {
     if (!compareword(words[i].lWord)) {
      cout << "line " << lines << ":";
      for (i1=0;i1<words.size();i1++) {
       if (i1==i)
        cout << turnred << words[separatewords(tline, 0, i1)].lWord << " ";
       else
        cout << turnoffred << words[separatewords(tline, 0, i1)].lWord << " "; 
     if (i1==words.size()-1)
   cout << endl; } } } }
   
  infile.close();
}

// compare word found with global word[]
int compareword(char tword[])
{
 int i;
 
   if (strlen(tword)!=strlen(word))
    return -1; 
   for (i=0;i<strlen(tword);i++) {
    if (word[i]=='+')
   tword[i]='+'; }

  return strcmp(word, tword);
}

// separate words in string and store in vector inside structures
int separatewords(char tline[], int tlowercaseflag, int wordidtoreturn)
{
  int i, n;
  Word tword;
  vector<Word>::iterator p=words.begin();
  while (p<words.end()) // because words.clear() only moves pointer, words are kept
   words.erase(p++);
  words.clear();
    
   for (i=0;i<strlen(tline);i++) {
    n=0;
    while (!isspace(tline[i]) && i<strlen(tline))
     tword.lWord[n++]=(!tlowercaseflag) ? tline[i++] : tolower(tline[i++]);
    tword.lWord[n]='\0';
   words.push_back(tword); }

 return wordidtoreturn;
}
