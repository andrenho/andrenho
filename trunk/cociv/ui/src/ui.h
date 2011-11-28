#ifndef UI_H
#define UI_H

class UI
{
  public:
    UI();
    void Init();
    bool Running();
    char* AskConnectAddress();
    void Message(char* m);
    void Close();
};

#endif
