#ifndef ED2_PARTE3_FINAL_QUESTION_H
#define ED2_PARTE3_FINAL_QUESTION_H

#include <string>
using namespace std;

class question
{
public:
    question();
    question(int id, int userId, string date, int score, string title, string body);
    virtual ~question();
    int getId();
    void setId(int id);
    void setUser(int userId);
    int getUser();
    string getDate();
    void setDate(string date);
    int getScore();
    void setScore(int score);
    string getTitle();
    void setTitle(string title);
    string getBody();
    void setBody(string body);

protected:

private:
    int _id;
    int _userId;
    string _date;
    int _score;
    string _title;
    string _body;
};

#endif //ED2_PARTE3_FINAL_QUESTION_H
