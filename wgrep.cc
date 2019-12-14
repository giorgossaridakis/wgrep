// wgrep - locate words in text files, wildcard + denotes any character
#include <iostream>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <vector>

#define MAXLINE 9999
#define MAXWORD 999
#define SPACE 32

using namespace std;

int compareword(char tword[]);
int separatewords(char tline[], int tlowercaseflag, int wordidtoreturn=0);
char *myname;
void showusage();
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

// global variables
int lowercaseflag=1, showlinenumber=1, standardinput=0;
char word[MAXWORD];
struct Word {
char lWord[MAXWORD]; };
vector<Word> words; 

int main(int argc, char *argv[])
{
 int i, i1, c, lines=0;
 char tline[MAXLINE];
 ifstream infile;

  myname=argv[0];
  // parse command line
  while ((c = getopt(argc, argv, ":cq")) != -1) {
   switch (c) {
	case 'c':
     lowercaseflag=0;
    break;
    case 'q':
     showlinenumber=0;
    break;
    case '?':
     showusage();
  break; } }
  // command line contains at least a pattern to look for ?
  if (optind == argc)
   showusage();
  
  // copy tolower requested word
  for (i=0;i<strlen(argv[optind]);i++)
   word[i]=(lowercaseflag) ? tolower(argv[optind][i]) : argv[optind][i];
  ++optind;
  if (optind==argc) // no files, default to stdin
   standardinput=1;
  
   // loop search in requested files or until end of standardinput
   while (optind<argc || standardinput) {
    if (!standardinput) { // open next file, exit if failure
     infile.open(argv[optind]);
     if (!infile)
      showusage();
    cout << argv[optind] << "--->" << endl; }
    while (infile || standardinput) {
     if (!standardinput)
      infile.getline(tline, MAXLINE);
     else
      cin.getline(tline, MAXLINE);
     if (!strlen(tline))
      standardinput=0;
     ++lines;
     separatewords(tline, lowercaseflag);
     for (i=0;i<words.size();i++) {
      if (!compareword(words[i].lWord)) {
       if (showlinenumber)
        cout << "line " << lines << ":";
       for (i1=0;i1<words.size();i1++) {
        if (i1==i)
         cout << turnred << words[separatewords(tline, 0, i1)].lWord << turnoffred << " ";
        else
         cout << words[separatewords(tline, 0, i1)].lWord << " "; 
      if (i1==words.size()-1)
    cout << endl; } } } }
    infile.close();
   ++optind;  }
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
  words.clear();
    
   for (i=0;i<strlen(tline);i++) {
    n=0;
    while (!isspace(tline[i]) && i<strlen(tline))
     tword.lWord[n++]=(!tlowercaseflag) ? tline[i++] : tolower(tline[i++]);
    tword.lWord[n]='\0';
   words.push_back(tword); }

 return wordidtoreturn;
}

// show usage
void showusage()
{
   cout << "usage:" << myname << " [-c match case] [-q no line #] pattern(+ is wildcard) [files ...]" << endl;
 
 exit(-1);
}
