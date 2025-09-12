#include "System_Files.hpp"

using namespace std;
// enter "EXIT" to exit the loop
int main()
{
    system_files system;

    string inp;
    while (cin >> inp)
    {
        if (inp == "CREATE")
        {
            string filename;
            cin >> filename;
            system.CREATE(filename);
        }
        else if (inp == "READ")
        {
            string filename;
            cin >> filename;
            system.READ(filename);
        }
        else if (inp == "INSERT")
        {
            string filename, content;
            cin >> filename;
            getline(cin, content);
            if (!content.empty() && content[0] == ' ')
            {
                content.erase(0, 1);
            }
            system.INSERT(filename, content);
        }
        else if (inp == "UPDATE")
        {
            string filename, content;
            cin >> filename;
            getline(cin, content);
            if (!content.empty() && content[0] == ' ')
            {
                content.erase(0, 1);
            }
            system.UPDATE(filename, content);
        }
        else if (inp == "SNAPSHOT")
        {
            string filename, message;
            cin >> filename;
            getline(cin, message);
            if (!message.empty() && message[0] == ' ')
            {
                message.erase(0, 1);
            }
            system.SNAPSHOT(filename, message);
        }
        else if (inp == "ROLLBACK")
        {
            string rem_inp;
            getline(cin, rem_inp);

            // Removed leading space if present
            if (!rem_inp.empty() && rem_inp[0] == ' ')
            {
                rem_inp.erase(0, 1);
            }

            vector<string> input;
            string current_word = "";

            for (char s : rem_inp)
            {
                if (s == ' ')
                {
                    if (!current_word.empty())
                    {
                        input.push_back(current_word);
                        current_word = "";
                    }
                }
                else
                {
                    current_word += s;
                }
            }

            if (!current_word.empty())
            {
                input.push_back(current_word);
            }

            if (input.empty())
            {
                throw runtime_error("invalid command : filename required!!");
            }

            string filename = input[0];

            if (input.size() == 1)
            {
                system.ROLLBACK(filename);
            }
            else if (input.size() == 2)
            {
                string version_str = input[1];
                int versionId = 0;

                for (char c : version_str)
                {
                    if (c < '0' || c > '9')
                    {
                        throw runtime_error("Invalid version ID : must be a number!!");
                    }
                    versionId = versionId * 10 + (c - '0');
                }

                system.ROLLBACK(filename, versionId);
            }
            else
            {
                throw runtime_error("Invalid command format!!");
            }
        }
        else if (inp == "HISTORY")
        {
            string filename;
            cin >> filename;
            system.HISTORY(filename);
        }
        else if (inp == "RECENT_FILES")
        {
            int num = 0;
            string input_num;
            cin >> input_num;
            for (char c : input_num)
            {
                if (c < '0' || c > '9')
                {
                    throw runtime_error("Invalid input : must be a number!!");
                }
                num = num * 10 + (c - '0');
            }
            system.RECENT_FILES(num);
        }
        else if (inp == "BIGGEST_TREES")
        {
            int num = 0;
            string input_num;
            cin >> input_num;
            for (char c : input_num)
            {
                if (c < '0' || c > '9')
                {
                    throw runtime_error("Invalid input : must be a number!!");
                }
                num = num * 10 + (c - '0');
            }
            system.BIGGEST_TREES(num);
        }
        else if (inp == "EXIT")
        {
            cout << "Exiting the Loop. Programme Termninated" << endl;
            break;
        }
        else
        {
            throw runtime_error("Invalid inp");
        }
    }

    return 0;
}
