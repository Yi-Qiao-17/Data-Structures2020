#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<algorithm>
using namespace std;

bool repeat_search_data(vector<string>search, string s) {
    for (int i = 0; i < search.size() - 1; i++) {
        if (s == search[i])return true;
        else if (i == search.size() - 2 && s != search[i])return false;
    }
    return false;
}

int find_search(vector<string>search, string data) {
    int index = 0, temp = 0;
    int   f = 0, l = 0;
    string s;

    for (int i = 0; i < search.size() - 1; i++) {
        if (data.find(search[i], 0) == -1)return-1;
        for (int j = temp; j < data.size(); j++) {
            if (data[j] == '\"') {
                f = j + 1;
                l = data.find('\"', j + 1);
                s = data.substr(f, l - f);
                if (s != search[i] && data.find(search[i], l + 1) != string::npos) {
                    j = l + 1;
                    temp = l + 1;
                    continue;
                }
                else if (s != search[i] && data.find(search[i], l + 1) == string::npos) return -1;
                else if (s == search[i]) {

                    j = l + 1;
                    temp = l + 1;
                    break;


                }

            }
        }
    }
    int left_curly = 0/*{*/, right_curly = 0/*}*/, left_square = 0/*[*/, right_square = 0/*]*/;

    if (data.find(search[search.size() - 1], temp) == -1) {
        return-1;
    }

    for (int k = temp; k < data.size(); k++) {
        if (data[k] == '{')left_curly++;
        else if (data[k] == '}')right_curly++;
        else if (data[k] == '[')left_square++;
        else if (data[k] == ']')right_square++;
        else if (data[k] == ',' && (left_curly == right_curly) && (left_square == right_square)) {
            data = data.substr(0, k);
            break;
        }
    }

    for (int j = temp; j < data.size(); j++) {
        if (data[j] == '\"') {
            f = j + 1;
            l = data.find('\"', j + 1);
            s = data.substr(f, l - f);
            if (repeat_search_data(search, s)) {
                j += s.size() + 1;
                continue;
            }
            if (s != search[search.size() - 1] && data.find(search[search.size() - 1], l + 1) != string::npos) {
                if (search.size() == 1) {
                    left_curly = 0/*{*/, right_curly = 0/*}*/, left_square = 0/*[*/, right_square = 0/*]*/;                   
                    int the_find_last = 0;
                    if (!(j-1<=0)&&(data[j - 1] == '{'|| data[j - 1] == ','))the_find_last = data.find('}', j)+1;
                    else the_find_last = data.size();                    
                    int num= data.find(':', l)+1;
                    
                    for (int k = num; k < /*data.size()*/the_find_last; k++) {
                        if (data[k] == '{')left_curly++;
                        else if (data[k] == '}')right_curly++;
                        else if (data[k] == '[')left_square++;
                        else if (data[k] == ']')right_square++;
                        else if (data[k] == ',' && (left_curly == right_curly) && (left_square == right_square)) {
                            string temp = data.substr(num, k - num/*+1*/);
                            if (temp.find(':', 0) == -1) {
                                for (int h = j; h < k; h++)data[h] = ' ';
                                l = k - 1;
                                break;
                            }                           
                            vector<string>mid;                           
                            mid.push_back(search[search.size() - 1]);
                            int check = find_search(mid, temp);
                            if (check == -1) {
                                for (int h = j; h < k ; h++)data[h] = ' ';
                                l = k - 1;
                                break;
                            }
                            else {
                                //int arrary_find = find_search(search_last, temp) + j - 1;
                                return check + num;
                            }
                           
                        }
                        if (data.find(',', k) == -1 && (left_curly == right_curly) && (left_square == right_square)) {
                            string temp = data.substr(num, k - num + 1);                           
                            vector<string>mid;
                            mid.push_back(search[search.size() - 1]);
                            int check = find_search(mid, temp);
                            if (temp.find(':', 0) == -1) {
                                for (int h = j; h < k; h++)data[h] = ' ';
                                l = k - 1;
                                break;
                            }
                            if (check == -1) {
                                for (int h = j; h < k ; h++)data[h] = ' ';
                                l = k - 1;
                                break;
                            }
                            else {
                                //int arrary_find = find_search(search_last, temp) + j - 1;
                                return check + num;
                            }
                        }
                        if (k == the_find_last-1) {
                            string temp = data.substr(num, k - num + 1);                           
                            vector<string>mid;
                            mid.push_back(search[search.size() - 1]);
                            int check = find_search(mid, temp);
                            if (check == -1) {
                                for (int h = j; h < k; h++)data[h] = ' ';
                                l = k - 1;
                                break;
                            }
                            else {
                                //int arrary_find = find_search(search_last, temp) + j - 1;
                                return check + num;
                            }
                        }
                    }

                }
                else {
                    size_t start = data.find(':', l + 1);
                    size_t end;
                    if (data[start + 1] == '\"') {
                        end = data.find('\"', start + 2);
                        for (int k = start + 2; k < end; k++)data[k] = ' ';
                        l = end;//jojo
                        //continue;
                    }

                    else {
                        left_curly = 0/*{*/, right_curly = 0/*}*/, left_square = 0/*[*/, right_square = 0/*]*/;
                        //int num = 0;
                        //if (!(j - 1 <= 0) && data[j - 2] == ',') num = j - 1;
                        //else num = l + 1;
                        int the_find_last = 0;
                        if (!(j - 1 <= 0) && (data[j - 1] == '{' || data[j - 1] == ','))the_find_last = data.find('}', j) + 1;
                        else the_find_last = data.size();
                        int num= data.find(':', l)+1;
                       
                        for (int k = num; k < /*data.size()*/the_find_last; k++) {
                            if (data[k] == '{')left_curly++;
                            else if (data[k] == '}')right_curly++;
                            else if (data[k] == '[')left_square++;
                            else if (data[k] == ']')right_square++;
                            else if (data[k] == ',' && (left_curly == right_curly) && (left_square == right_square)) {
                                for (int h = j; h < k + 1; h++)data[h] = ' ';
                                l = k - 1;
                                break;
                            }
                            if (data.find(',', k) == -1 && (left_curly == right_curly) && (left_square == right_square)) {
                                for (int h = j; h < k + 1; h++)data[h] = ' ';
                                l = k - 1;
                                break;
                            }
                            if (k == the_find_last - 1) {
                                for (int h = j; h < k ; h++)data[h] = ' ';
                                l = k - 1;
                                break;
                            }
                        }
                    }
                }

                j = l + 1;
                temp = l + 1;
                if (data.find(search[search.size() - 1], j) == -1)return -1;
                continue;
            }
            else if (s != search[search.size() - 1] && data.find(search[search.size() - 1], l + 1) == string::npos) return -1;
            else if (s == search[search.size() - 1]) {
                
                index = data.find(search[search.size() - 1], j);
                return index;

            }




        }

    }
}


int main(int argc, char* argv[])
{

    ifstream fin1, fin2;
    //4 5 自己
    fin1.open(argv[1]/*"01.txt"*/);//json
    fin2.open(argv[2]/*"s01.txt"*/);//search
    if (!fin1) {
        cout << "Json File could not be opened" << endl;
        exit(1);
    }
    if (!fin2) {
        cout << "Search File could not be opened" << endl;
        exit(1);
    }

    vector<string> input_searchdata;
    string data, input_string;
    int i, j, k;
    int left_curly = 0/*{*/, right_curly = 0/*}*/, left_square = 0/*[*/, right_square = 0/*]*/;
    while (getline(fin1, data)) {
        for (i = 0; i < data.size(); i++) {
            if (data[i] == '\"') {
                i = data.find('\"', i + 1) + 1;
                /*  for (j = i + 1; j < data.size() - 1; j++) {
                      if (data[j] == '\"') {

                          break;
                      }
                  }
                  i = j + 1;*/
            }
            if (data[i] == ' '|| data[i] == '\t') {
                data.erase(i, 1);
                i--;
            }
            else if (data[i] == '{')left_curly++;
            else if (data[i] == '}')right_curly++;
            else if (data[i] == '[')left_square++;
            else if (data[i] == ']')right_square++;
        }
        input_string += data;
        if (left_curly == right_curly)break;
    }
    left_curly = 0/*{*/, right_curly = 0/*}*/, left_square = 0/*[*/, right_square = 0/*]*/;

    while (getline(fin2, data)) input_searchdata.push_back(data);

    //cout << input_string << endl << endl;

    vector<string>Data, stack;
    data.clear();
    int cut_number = 1;
    if (input_string == "");
    else {
        for (i = 1; i < input_string.size() - 1; i++) {

            if (input_string[i] == '\"') {
                i = input_string.find('\"', i + 1) + 1;
                /* for (j = i + 1; j < input_string.size() - 1; j++) {
                     if (input_string[j] == '\"') {

                         break;
                     }
                 }
                 i = j + 1;*/
            }
            if (input_string[i] == '{')left_curly++;
            else if (input_string[i] == '}')right_curly++;
            else if (input_string[i] == '[')left_square++;
            else if (input_string[i] == ']')right_square++;
            else if (input_string[i] == ',') {
                if ((left_curly == right_curly) && (left_square == right_square)) {
                    Data.push_back(input_string.substr(cut_number, i - cut_number));
                    cut_number = i + 1;
                    left_curly = 0/*{*/, right_curly = 0/*}*/, left_square = 0/*[*/, right_square = 0/*]*/;
                }
            }
            if (i == input_string.size() - 2) {

                if ((left_curly == right_curly) && (left_square == right_square)) {
                    Data.push_back(input_string.substr(cut_number, i - cut_number + 1));

                    left_curly = 0/*{*/, right_curly = 0/*}*/, left_square = 0/*[*/, right_square = 0/*]*/;
                }

            }
        }
    }
    /* for (i = 0; i < input_searchdata.size(); i++)cout << input_searchdata[i]<<endl;*/

    stack = Data;
    for (i = 0; i < input_searchdata.size(); i++) {
        vector<string>search;
        vector<string>value;
        cut_number = 0;
        for (j = 0; j <= input_searchdata[i].size(); j++) {
            if (input_searchdata[i][j] == '>' || j == input_searchdata[i].size()) {
                search.push_back(input_searchdata[i].substr(cut_number, j - cut_number));
                cut_number = j + 1;
            }
        }//處理search

        for (k = 0; k < Data.size(); k++) {
            int number = find_search(search, Data[k]);
            if (number == -1)continue;
            while (number != -1) {
                int first = 0, last = 0;
                int x = 0;
                if (first != 0 && last != 0)  break;
                if (Data[k].find(':', number) != string::npos) {
                    // x = Data[k].find(':', number);
                    x = Data[k].find(':', Data[k].find('\"', number));
                    size_t s1 = Data[k].find('[', x + 1), s2 = Data[k].find('\"', x + 1), s3 = Data[k].find(',', x + 1), s4 = Data[k].find('}', x + 1), s5 = 0;
                    if (Data[k].find('[', x + 1) == -1 && Data[k].find('\"', x + 1) == -1 && Data[k].find(',', x + 1) == -1 && Data[k].find('}', x + 1) == -1)s5 = -1;
                    else {
                        s5 = (s1 < s2) ? s1 : s2;
                        s5 = (s5 < s3) ? s5 : s3;
                        s5 = (s5 < s4) ? s5 : s4;
                    }
                    if (s5 == s1 && s5 != -1) {
                        first = s1 + 1;
                        last = Data[k].find(']', s1 + 1);
                        //break;
                    }
                    else if (s5 == s2 && s5 != -1) {
                        first = s2 + 1;
                        //have_comma<have_paratheses   取have_comma-1//逗號先//{"A":"C","B":"D"}
                        //have_comma>have_paratheses   取have_paratheses-1//先{"a":"b"}
                        //other//"a":"c"
                        size_t have_comma = Data[k].find(',', s2 + 1);
                        size_t have_paratheses = Data[k].find('}', s2 + 1);
                        if (Data[k].find(',', s2 + 1) == -1 && Data[k].find('}', s2 + 1) == -1)last = Data[k].size() - 1;
                        else if (have_comma < have_paratheses)last = Data[k].find(',', s2 + 1) - 1;
                        else if (have_comma > have_paratheses) last = Data[k].find('}', s2 + 1) - 1;

                        //break;
                    }
                    else if (s5 == s3 && s5 != -1) {
                        first = x + 1;
                        /*last = Data[k].find(',', x) - 1;*/
                        last = s3;
                        //break;
                    }
                    else if (s5 == s4 && s5 != -1) {
                        first = x + 1;
                        /*last = Data[k].find('}', x) - 1;*/
                        last = s4;
                        //break;
                    }
                    else if (s5 == -1) {
                        first = x + 1;
                        last = Data[k].size();
                        // break;
                    }

                }
                value.push_back(Data[k].substr(first, last - first));
                // Data[k] = Data[k].replace(number, search[search.size() - 1].size(), "");
                Data[k].erase(number, search[search.size() - 1].size());
                number = find_search(search, Data[k]);
                first = 0, last = 0;

            }

        }
        if (value.empty()) {
            if (i != input_searchdata.size() - 1)
                cout << endl << endl;
            //cout << endl << endl;
            else if (i == input_searchdata.size() - 1)
                cout << endl;
        }

        else {
            for (j = 0; j < value.size(); j++) {
                if (value[j].find(',', 0) != -1) {
                    stringstream ss;
                    ss.str("");
                    ss.clear();
                    ss << value[j];
                    string m;
                    while (getline(ss, m, ',')) {
                        if (value[j].find('\"', 0) != -1) {
                            int f = value[j].find('\"', 0);
                            int index = m.find('\"', f + 1);
                            cout << m.substr(f + 1, index - f - 1) << endl;
                        }
                        else cout << m << endl;
                    }
                }
                //else if (value[j] == "")continue;
                else cout << value[j] << endl;
            }
            if (i != input_searchdata.size() - 1)
                cout << endl;
        }
        Data = stack;
    }

    //if (input_searchdata.size() == 0 && Data.size() == 0)cout << endl;

    Data.clear();
    //search.clear();
    //stack2.clear();
    input_searchdata.clear();
    stack.clear();
    fin1.close();
    fin2.close();
    return 0;
}

