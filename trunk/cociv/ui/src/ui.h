#ifndef UI_H
#define UI_H

class UI
{
  public:
    void Init();
    bool Running();
    char* AskConnectAddress();
    void Message(char* m);
    void Close();
};

#endif
