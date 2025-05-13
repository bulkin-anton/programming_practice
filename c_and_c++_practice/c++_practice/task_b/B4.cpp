#include <cstring>

class String{
    public:
        String();
        String(char);
        String(const char *);
        String(const String &);
        const char* get() const;
        void append(const String &);
        int compare(const String &);
        void assign(const String &);
        ~String();
    private:
        char *str ;
};

String::String(){
    str = new char[1];
    str[0] = 0;
}

String::~String(){
    delete []str;
}

String::String(const String &str1){
    str = new char[strlen(str1.str) + 1];
    strcpy(str, str1.str);
}

String::String(const char *str1){
    str = new char[strlen(str1) + 1];
    strcpy(str, str1);
}

String::String(char c){
    str = new char[2];
    str[0] = c;
    str[1] = 0;
}

const char*
String::get() const{
    return str;
}

void
String::append(const String& str3){
    int new_len = strlen(str3.str);
    int len = strlen(str);
    char *buf = new char[len + 1];
    strcpy(buf, str);
    delete []str;
    str = new char[len + new_len + 1];
    strcpy(str, buf);
    delete []buf;
    strcat(str, str3.get());
}

int
String::compare(const String& str3){
    return strcmp(str, str3.get());
}

void
String::assign(const String& str3){
    delete []str;
    str = new char[strlen(str3.str) + 1];
    strcpy(str, str3.str);
}
