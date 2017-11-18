#include <iostream>
#include <fstream>
#include <istream>
#include <algorithm>
#include <map>
#include <string> 
#include <regex> 
#include <vector> 
#include <unordered_set>

using namespace std;

//fast_scrable
// g++ -Ofast -Wall -Werror -std=c++11 -o ./fscr *.cpp

std::istream& safeGetline(std::istream& is, std::string& t)
{
    t.clear();

    std::istream::sentry se(is, true);
    std::streambuf* sb = is.rdbuf();

    for(;;) {
        int c = sb->sbumpc();
        switch (c) {
        case '\n':
            return is;
        case '\r':
            if(sb->sgetc() == '\n')
                sb->sbumpc();
            return is;
        case EOF:
            // Also handle the case when the last line has no line ending
            if(t.empty())
                is.setstate(std::ios::eofbit);
            return is;
        default:
            t += (char)c;
        }
    }
}
    
string read_input()
{
    string input_user;
    bool flag = false;
    regex pattern { "[a-zA-Z]+" };
    while(flag == false)
    {
        cin >> input_user;
        flag = regex_match(input_user, pattern);
    }
    return input_user;
}


multimap<string,string> load_file_in_set(string path_file, string return_user_input)
{
    multimap<string,string> multimap_dico;
    ifstream dict_file(path_file.c_str());
    string line;
    while (!safeGetline(dict_file, line).eof()) {    
        string new_line = line;
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        string tmp_newline = line;
        sort(tmp_newline.begin(), tmp_newline.end());
        multimap_dico.insert(make_pair(tmp_newline, new_line));
    }
    return multimap_dico;
}


int main(int argc, char **argv)
{
    while(true)
    {
    /* Read Input User */
    string return_user_input = read_input();
    
    /* Load in Set */
    multimap<string,string> mymultimap;
    multimap<string,string>::iterator it;

    mymultimap = load_file_in_set(argv[2], return_user_input);

    string tmp = return_user_input;
    transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
    sort(tmp.begin(), tmp.end());


    pair<multimap<string,string>::iterator, multimap<string,string>::iterator> ii;
    ii = mymultimap.equal_range(tmp); 
    for(it = ii.first; it != ii.second; ++it)
    {
        cout<<it->second<<endl;
    }

    /*
    auto its = mymultimap.equal_range(tmp);
        for (auto it = its.first; it != its.second; ++it) 
        {
            cout << it->second << endl;
        }
    */

    }
    
  	return 0;
}